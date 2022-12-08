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
			*f = novo;
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
		int retorno = aux->chave;
		*f = aux->prox;
		free(aux);
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

void imprimir(Fila_FIFO *f) {
	printf("Fila com %d elementos: \n\n", f_num_elementos(&f));

	while(f) {
		printf("\n\tChave: %d\n\tValor: %d\n\n", f->chave, f->valor);
		f = f->prox;
	}
}

int main() {

	Fila_FIFO *fila = malloc(sizeof(Fila_FIFO));
	f_inicializar(&fila);

	int opcao, chave, valor, posicao;

	do {
		printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Obter Prox. Chave");
		printf("\n\t4 - Consultar Prox. Chave\n\t5 - Consultar Prox. Valor");
		printf("\n\t6 - Consultar Chave por Posicao\n\t7 - Consultar Valor por Posicao\n\n");
		scanf("%d", &opcao);

		switch(opcao) {
			case 1:
				printf("Digite a chave e o valor(A chave nao pode ser repetida): ");
				scanf("%d %d", &chave, &valor);
				f_inserir(&fila, chave, valor);
				break;
			case 2:
				imprimir(fila);
				break;
			case 3:
				printf("%d\n\n", f_obter_proxima_chave(&fila));
				break;
			case 4:
				printf("%d\n\n", f_consultar_proxima_chave(&fila));
				break;
			case 5:
				printf("%d\n\n", f_consultar_proximo_valor(&fila));
				break;
			case 6:
				printf("Digite a posicao de busca: ");
				scanf("%d", &posicao);
				printf("\nChave da posicao %d: %d\n\n", posicao, f_consultar_chave_por_posicao(&fila, posicao));
				break;
			case 7:
				printf("Digite a posicao de busca: ");
				scanf("%d", &posicao);
				printf("\nValor da posicao %d: %d\n\n", posicao, f_consultar_valor_por_posicao(&fila, posicao));
				break;
			default:
				if(opcao != 0)
					printf("Opcao invalida");
				break;
		}

	} while(opcao != 0);


}