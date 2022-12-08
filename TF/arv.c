#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logtree.h"

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

		if(aux == NULL) {
			novo->pai = NULL;
			*l = novo;
		}
		else {
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
}

void imprimir(Log *raiz) {
	if(raiz != NULL) {
		printf("\nConta: %d\nClasse: %d\nCaixa: %d\nTimer: %d\n\n", raiz->conta, raiz->classe, raiz->caixa, raiz->timer);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
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

int main() {

	Log *arvore = malloc(sizeof(Log));
	log_inicializar(&arvore);

	int op, conta, classe, timer, caixa;

	do {
		printf("\n\t0 - Sair\n\t1 - Registrar\n\t2 - Imprimir\n\t3 - Soma de tempo por classe");
		printf("\n\t4 - Quantidade por classe\n\n");
		scanf("%d", &op);

		switch(op) {
			case 1:
				printf("Conta: ");
				scanf("%d", &conta);
				printf("Classe: ");
				scanf("%d", &classe);
				printf("Timer: ");
				scanf("%d", &timer);
				printf("Caixa: ");
				scanf("%d", &caixa);
				log_registrar(&arvore, conta, classe, timer, caixa);
				break;
			case 2:
				imprimir(arvore);
				break;
			case 3:
				printf("Classe: ");
				scanf("%d", &classe);
				printf("Soma dos tempos da classe %d: %d\n\n", classe, log_obter_soma_por_classe(&arvore, classe));
				break;
			case 4:
				printf("Classe: ");
				scanf("%d", &classe);
				printf("Quantidade de contas da classe %d: %d", classe, log_obter_contagem_por_classe(&arvore, classe));
				break;
			default:
				if(op != 0)
					printf("Opcao invalida.\n\n");
				break;
		}
	}while(op != 0);

}