#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_fifo.h"
#include "logtree.h"

void e_inicializar(Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5) {
	Fila_FIFO *fila1, *fila2, *fila3, *fila4, *fila5 = malloc(sizeof(Fila_FIFO));
	f_inicializar(&fila1);
	f_inicializar(&fila2);
	f_inicializar(&fila3);
	f_inicializar(&fila4);
	f_inicializar(&fila5);

	e->caixas = caixas;
	e->delta_t = delta_t;
	e->fila1 = fila1; //Premium
	e->fila2 = fila2; //Ouro
	e->fila3 = fila3; //Prata
	e->fila4 = fila4; //Bronze
	e->fila5 = fila5; //Leezo

	e->controle_ciclo = [0, 0, 0, 0, 0];
	e->disciplina = [n_1, n_2, n_3, n_4, n_5];
}

int e_inserir_por_fila(Escalonador *e, int classe, int num_conta, int qtde_operacoes) {
	if(classe == 1)
		f_inserir(&(e->fila1), num_conta, qtde_operacoes);
	else if(classe == 2)
		f_inserir(&(e->fila2), num_conta, qtde_operacoes);
	else if(classe == 3)
		f_inserir(&(e->fila3), num_conta, qtde_operacoes);
	else if(classe == 4)
		f_inserir(&(e->fila4), num_conta, qtde_operacoes);
	else if(classe == 5) 
		f_inserir(&(e->fila5), num_conta, qtde_operacoes);
}

int e_obter_prox_num_conta(Escalonador *e) {
	if(e->controle_ciclo[0] < e->disciplina[0] && e->fila1)
		return f_obter_proxima_chave(&(e->fila1));
	else if(e->controle_ciclo[1] < e->disciplina[1] && e->fila2)
		return f_obter_proxima_chave(&(e->fila2));
	else if(e->controle_ciclo[2] < e->disciplina[2] && e->fila3)
		return f_obter_proxima_chave(&(e->fila3));
	else if(e->controle_ciclo[3] < e->disciplina[3] && e->fila4)
		return f_obter_proxima_chave(&(e->fila4));
	else if(e->controle_ciclo[4] < e->disciplina[4] && e->fila5)
		return f_obter_proxima_chave(&(e->fila5));
	else {
		e->controle_ciclo = [0, 0, 0, 0, 0]; //Reinicia Escalonador no caso de ter feito ciclo completo.
		return e_obter_prox_num_conta(e); //Repetir processo com escalonador reiniciado.
	}
}

int e_consular_prox_num_conta(Escalonador *e) {

	//Se o ciclo para X classe não está completo && Fila de X classe não está vazia.
	if(e->controle_ciclo[0] < e->disciplina[0] && e->fila1)
		return f_consultar_proxima_chave(&(e->fila1));
	else if(e->controle_ciclo[1] < e->disciplina[1] && e->fila2)
		return f_consultar_proxima_chave(&(e->fila2));
	else if(e->controle_ciclo[2] < e->disciplina[2] && e->fila3)
		return f_consultar_proxima_chave(&(e->fila3));
	else if(e->controle_ciclo[3] < e->disciplina[3] && e->fila4)
		return f_consultar_proxima_chave(&(e->fila4));
	else if(e->controle_ciclo[4] < e->disciplina[4] && e->fila5)
		return f_consultar_proxima_chave(&(e->fila5));
	else {
		e->controle_ciclo = [0, 0, 0, 0, 0]; //Reinicia Escalonador no caso de ter feito ciclo completo.
		return e_consultar_prox_num_conta(e); //Repetir processo com escalonador reiniciado.
	}
}

int e_consultar_prox_qtde_oper(Escalonador *e) {
	if(e->controle_ciclo[0] < e->disciplina[0])
		return f_consultar_proximo_valor(&(e->fila1));
	else if(e->controle_ciclo[1] < e->disciplina[1])
		return f_consultar_proximo_valor(&(e->fila2));
	else if(e->controle_ciclo[2] < e->disciplina[2])
		return f_consultar_proximo_valor(&(e->fila3));
	else if(e->controle_ciclo[3] < e->disciplina[3])
		return f_consultar_proximo_valor(&(e->fila4));
	else if(e->controle_ciclo[4] < e->disciplina[4])
		return f_consultar_proximo_valor(&(e->fila5));
	else {
		e->controle_ciclo = [0, 0, 0, 0, 0]; //Reinicia Escalonador no caso de ter feito ciclo completo.
		return e_consultar_prox_qtde_oper(e); //Repetir processo com escalonador reiniciado.
	}
}

int e_consultar_prox_fila(Escalonador *e) {
	if(e->controle_ciclo[0] < e->disciplina[0])
		return 1;
	else if(e->controle_ciclo[1] < e->disciplina[1])
		return 2;
	else if(e->controle_ciclo[2] < e->disciplina[2])
		return 3;
	else if(e->controle_ciclo[3] < e->disciplina[3])
		return 4;
	else if(e->controle_ciclo[4] < e->disciplina[4])
		return 5;
	else {
		e->controle_ciclo = [0, 0, 0, 0, 0]; //Reinicia Escalonador no caso de ter feito ciclo completo.
		return e_consultar_prox_fila(e); //Repetir processo com escalonador reiniciado.
	}
}

int e_consultar_qtde_clientes (Escalonador *e) {
	int quantidade = 0;
	quantidade += f_num_elementos(&(e->fila1));
	quantidade += f_num_elementos(&(e->fila2));
	quantidade += f_num_elementos(&(e->fila3));
	quantidade += f_num_elementos(&(e->fila4));
	quantidade += f_num_elementos(&(e->fila5));
	return quantidade;
}

int e_consultar_tempo_prox_cliente (Escalonador *e) {
	return (e_consultar_prox_qtde_oper(e) * e->delta_t);
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
	
}

