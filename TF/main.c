#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila_fifo.h"
#include "logtree.h"
#include "escalonador.h"

typedef struct cliente {
	long numero;
	int tipo;
	int ops;
} CLIENTE;

typedef struct caixa {
	CLIENTE* atual;

}

void arquivoSaida(char* arg){
	
	int tamanho = strlen(arg);
	char num[4] = "";
	char arquivo[16] = "saida_";
	char tipo_arq[4] = ".txt";
	
	if (tamanho > 4) { printf("Erro no Parametro"); return 0;}
	
	if ( tamanho == 1 ) { strcpy(num,"000"); strcat(num,arg);}
	else if ( tamanho == 2 ) { strcpy(num,"00"); strcat(num,arg);}
	else if ( tamanho == 3 ) { strcpy(num,"0"); strcat(num,arg);}
	else if ( tamanho == 4 ) { strcat(num,arg); }	

	strcat(arquivo,num);
	strcat(arquivo,tipo_arq);
	printf("%s",arquivo);
	return arquivo;
}

void arquivoEntrada(char* arg){
	
	int tamanho = strlen(arg);
	char num[4] = "";
	char arquivo[16] = "entrada_";
	char tipo_arq[4] = ".txt";
	
	if (tamanho > 4) { printf("Erro no Parametro"); return 0;}
	
	if ( tamanho == 1 ) { strcpy(num,"000"); strcat(num,arg);}
	else if ( tamanho == 2 ) { strcpy(num,"00"); strcat(num,arg);}
	else if ( tamanho == 3 ) { strcpy(num,"0"); strcat(num,arg);}
	else if ( tamanho == 4 ) { strcat(num,arg); }	

	strcat(arquivo,num);
	strcat(arquivo,tipo_arq);
	printf("%s",arquivo);
	return arquivo;
}

int main(int narg, char* argv[]) {
	Fila_FIFO *premium, *ouro, *prata, *bronze, *leezo = malloc(sizeof(Fila_FIFO));

	
	
}
