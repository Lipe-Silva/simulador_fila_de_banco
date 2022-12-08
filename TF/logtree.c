#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logtree.h"
#include "fila_fifo.h"
#include "escalonador.h"

void log_inicializar(Log **l) {
	*l = NULL;
}

void log_registrar(Log **l, int conta, int classe, int timer, int caixa) {
	Log *aux, *aux2, *novo = malloc(sizeof(Log));
	aux = *l; //Raiz
	aux2 = NULL;

	if(novo) {
		novo->caixa = caixa;
		novo->timer = timer;
		novo->conta = conta;
		novo->classe = classe;
		novo->esq = NULL;
		novo->dir = NULL;

		while(aux != NULL) {
			aux2 = aux;
			if(novo->classe <= aux->classe)
				aux = aux->esq;
			else
				aux = aux->dir;
		}

		if(novo->classe <= aux2->classe)
			aux2->esq = novo;
		else
			aux2->dir = novo;

		novo->pai = aux2;
	}
}

int log_obter_soma_por_classe(Log **l, int classe) {
	Log *aux = malloc(sizeof(Log));
	aux = *l;

	if(aux == NULL)
		return 0;
	else
		return (aux->timer + log_obter_soma_por_classe(&(aux->esq), classe) + log_obter_soma_por_classe(&(aux->dir), classe));
}

int somaClasse(Log *l, int classe) {
	if(l == NULL)
		return 0;
	else {
		if(l->classe == classe)
			return (1 + somaClasse(l->esq, classe) + somaClasse(l->dir, classe));
		else
			return (somaClasse(l->esq, classe) + somaClasse(l->dir, classe));
	}
}

int log_obter_contagem_por_classe(Log **l, int classe) {
	return somaClasse(*l, classe);
}

float log_media_por_classe(Log **l, int classe) {
	return log_obter_soma_por_classe(l, classe) / (float)log_obter_contagem_por_classe(l, classe);
}