#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#define STRLEN 30

typedef char* string;

typedef struct listaDocumentos{
	string nome;
	int *pos,nPos;
	struct listaDocumentos *prox;
}ListaDocumentos;

typedef struct listaString{ // Hash Encadeada
	string palavra;
	ListaDocumentos *docs;
	struct listaString *prox;
}ListaString;

//Fun��es
void indexarHash(char tipo,string entradaDocs, string indiceGerado);
void addString(int indice,string palavra,int pos,string nomeDoc);
void liberarPonteiros(char tipo);
void hashEncadeada(string palavra, int indice, int posicao,string nomeDoc);
void addDoc(string doc,ListaDocumentos *d,int pos);
int aceitavel(string palavra);
void gerarIndice(int tamanho,char tipo, string indiceGerado);
int tamanhoHash(string entradaDocs);
void lerIndice(char tipo, string arqIndice );
void hashLinear(string palavra, int indice, int posicao, string nomeDoc);
void reHash(string palavra, int indice, int posicao, string nomeDoc);

void buscarPalavra(char tipo,string arqPalavras);
void buscarHashEncad (string palavra,ListaDocumentos **docs);
void buscarHashLin(string palavra, ListaDocumentos **docs);
void buscarReHash(string palavra,ListaDocumentos **docs);



