#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_fifo.h"


void f_inicializar(Fila_FIFO **f) {
	*f = NULL;
}

int f_inserir(Fila_FIFO **f, int chave, int valor) {
	Fila_FIFO *aux, *novo = malloc(sizeof(Fila_FIFO));

	if(novo) {
		novo->chave = chave;
		novo->valor = valor;
		novo->prox = NULL;

		if(*f == NULL)
			*fila = novo;
		else {
			aux = *f;
			while(aux->prox && aux->chave != novo->chave)
				aux = aux->prox;
			if(aux->prox == NULL && aux->chave != novo->chave)
				aux->prox = novo;
		}
	}
}

int f_obter_proxima_chave(Fila_FIFO **f) {

	Fila_FIFO *aux = malloc(sizeof(Fila_FIFO));
	aux = *f;

	if(aux) {
		int retorno = aux->chave
		aux = aux->prox;
		return retorno;
	}
	else
		return -1;
}

int f_consultar_proxima_chave(Fila_FIFO **f) {
	Fila_FIFO *aux = malloc(sizeof(Fila_FIFO));
	aux = *f;

	return aux->chave;
}

int f_consultar_proximo_valor(Fila_FIFO **f) {
	Fila_FIFO *aux = malloc(sizeof(Fila_FIFO));
	aux = *f;

	return aux->valor;
}

int f_num_elementos(Fila_FIFO **f) {
	Fila_FIFO *aux = malloc(sizeof(Fila_FIFO));
	aux = *f;
	int num; //Quantidade de elementos

	if(aux) {
		num = 1;
		while(aux->prox){
			aux = aux->prox;
			num++;
		}
	}
	else
		return 0;
}

int f_consultar_chave_por_posicao(Fila_FIFO **f, int posicao) {
	Fila_FIFO *aux = malloc(sizeof(Fila_FIFO));
	aux = *f;
	int num;

	if(aux) {
		num = 1;
		while(aux->prox && num != posicao) {
			aux = aux->prox;
			num++;
		}
		if(num == posicao)
			return aux->chave;
		else
			return -1;
	}
	else
		return -1;
}

int f_consultar_valor_por_posicao(Fila_FIFO **f, int posicao) {
	Fila_FIFO *aux = malloc(sizeof(Fila_FIFO));
	aux = *f;
	int num;

	if(aux) {
		num = 1;
		while(aux->prox && num != posicao) {
			aux = aux->prox;
			num++;
		}
		if(num == posicao)
			return aux->valor;
		else
			return -1;
	}
	else
		return -1;
}