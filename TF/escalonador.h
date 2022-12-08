#ifndef _escalonador_
#define _escalonador_

#include "fila_fifo.c"

typedef struct escalonador {
	Fila_FIFO *fila1;
	Fila_FIFO *fila2;
	Fila_FIFO *fila3;
	Fila_FIFO *fila4;
	Fila_FIFO *fila5;
	int controle_ciclo[5]; //Controle de disciplina
	int disciplina[5];
	int delta_t;
	int caixas;
} Escalonador;


void e_inicializar(Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5);
int e_inserir_por_fila(Escalonador *e, int classe, int num_conta, int qtde_operacoes);
int e_obter_prox_num_conta(Escalonador *e);
int e_consultar_prox_num_conta(Escalonador *e);
int e_consultar_prox_qtde_oper(Escalonador *e);
int e_consultar_prox_fila(Escalonador *e);
int e_consultar_qtde_clientes (Escalonador *e);
int e_consultar_tempo_prox_cliente (Escalonador *e);
int e_conf_por_arquivo (Escalonador *e, char *nome_arq_conf);
void e_rodar (Escalonador *e, char *nome_arq_in, char *nome_arq_out);

#endif