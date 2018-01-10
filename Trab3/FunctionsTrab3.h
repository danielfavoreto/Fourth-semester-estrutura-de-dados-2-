#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#define STRLEN 30

extern int** jobs;


typedef char* string;

typedef struct sequencia{
	int *caminho, *visitados, tempo, multa,nVisitados,lb,ub;
	struct sequencia *prox;
}Sequencia;

extern int *menorSequencia;
extern Sequencia **melhores;


//funções bs
void bs(int n, int imprimir); //bs
void addMelhores(Sequencia s[], Sequencia nova,int w); //bs 
Sequencia createSeq(Sequencia s, int pos, int n,int multa, int tempo); //bs
void liberarPonteiros(int n); //main
//funções bb
void addMelhoresBb(int posM,Sequencia s, int pos, int n, int multa, int tempo, int lb,int ub);//bb
void bb(int n);//bb
