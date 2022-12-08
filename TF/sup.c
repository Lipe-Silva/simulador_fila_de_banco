#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_fifo.h"
#include "logtree.h"
#include "escalonador.h"

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

int e_conf_por_arquivo (Escalonador *e, char *nome_arq_conf) {
	FILE *f = fopen(nome_arq_conf, "r+");
	int caixas, delta_t, n_1, n_2, n_3, n_4, n_5;

	//Checar se é ou não NULO.
	if(f) {
		fscanf(f, "qtde de caixas = %d", &caixas);
		fscanf(f, "delta t = %d", &delta_t);
		fscanf(f, "disciplina de escalonamento = {%d,%d,%d,%d,%d}", &n_1, &n_2, &n_3, &n_4, &n_5);

		e_inicializar(e, caixas, delta_t, n_1, n_2, n_3, n_4, n_5);
		
		return 1;
	}
	else
		return 0;
}

void e_rodar (Escalonador *e, char *nome_arq_in, char *nome_arq_out) {
	FILE *in, *out;
	in = fopen(nome_arq_in, "r");
	out = fopen(nome_arq_out, "w");
}


int main(int narg, char *argv[]) {
	char input[4];
	strcpy(input, argv[1]);

	char entrada[16] = "entrada-";
	char saida[14] = "saida-";
	strcat(entrada, argv[1]);
	strcat(saida, argv[1]);
	strcat(entrada, ".txt");
	strcat(saida, ".txt");

	Escalonador escalonador;
	e_conf_por_arquivo(&escalonador, entrada);
	e_rodar(&escalonador, entrada, saida);



}