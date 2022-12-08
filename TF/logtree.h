#ifndef _logtree_
#define _logtree_

typedef struct log {
	int conta;
	int classe;
	int timer; 
	int caixa;
	struct log *pai;
	struct log *esq;
	struct log *dir;
} Log;

void log_inicializar(Log **l);
void log_registrar(Log **l, int conta, int classe, int timer, int caixa);
float log_media_por_classe(Log **l, int classe);
int log_obter_soma_por_classe(Log **l, int classe);
int log_obter_contagem_por_classe(Log **l, int classe);

#endif