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


int main(int narg, char* argv[]) {
	Fila_FIFO *premium, *ouro, *prata, *bronze, *leezo = malloc(sizeof(Fila_FIFO));

	
}