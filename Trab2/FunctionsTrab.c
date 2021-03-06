#include "FunctionsTrab.h"

ListaString **hashEncad = NULL, **hashLin = NULL, **rHash = NULL;
FILE *arqDocs = NULL, *doc =NULL, *ind = NULL, *arq = NULL;
int HASHLEN = 0, nDocs = 0;


void buscarPalavra(char tipo,string arqPalavras)
{
	arq = fopen(arqPalavras, "r");
	if(arq == NULL)
	{
		printf("ERRO: Arquivo ''%s'' não encontrado", arqPalavras);
		exit(-1);

	}
	int i;
	string linha = (string) malloc(sizeof(char) * STRLEN);
	string palavra;
	ListaDocumentos **docs = (ListaDocumentos**) malloc(sizeof(ListaDocumentos*)* nDocs);
	for(i=0;i<nDocs;i++)
		docs[i] = NULL;

	while(fgets(linha,999999, arq) != NULL)
	{
		//fgets(linha,999999, arq);
		strtok(linha, "\r\n");

		printf("%s\n",linha);


		palavra = strtok(linha," \r\n");

		while( palavra != NULL)
		{
			switch(tipo)
			{
				case 'E':
					buscarHashEncad(palavra,docs);
					break;
				case 'L':
					buscarHashLin(palavra,docs);
					break;
				case 'R':
					buscarReHash(palavra,docs);
					break;

			}
			palavra = strtok(NULL," \r\n");
		}

	for(i=0;i<nDocs;i++)
	{
		if(docs[i] != NULL)
			printf("%s\n",docs[i]->nome);
		docs[i] = NULL;
	}

	}
	free(docs);
	free(linha);
}

void buscarReHash(string palavra,ListaDocumentos **docs)
{
	int i,indice = 0,j;
	for(i=0;i<strlen(palavra);i++)
	{
		int letra = (int) palavra[i];

		if(i % 2)
			indice =+ letra * i + 7;
		else
			indice = indice * letra + i + 11;
	}

	if(indice < 0)
		indice = indice * (-1);

	indice = indice%HASHLEN;

	if(rHash[indice] != NULL)
	{
		if(!strcmp( rHash[indice]->palavra, palavra))
		{
			ListaDocumentos *d = NULL;
			d = rHash[indice]->docs;
			while(d != NULL)
			{
				for(i=0;i<nDocs;i++)
				{
					if( docs[i] != NULL && !strcmp(docs[i]->nome,d->nome))
						break;

					if(docs[i] == NULL)
					{
						docs[i] = d;
						break;
					}

				}
				d = d->prox;
			}

		}
		else
		{
			int quant = 0;
			while(rHash[indice] != NULL && quant != HASHLEN )
			{
				if(!strcmp(rHash[indice]->palavra,palavra))
				{
					ListaDocumentos *d = NULL;
					d = rHash[indice]->docs;
					while(d != NULL)
					{
						for(j=0;j<nDocs;j++)
						{
							if( docs[j] != NULL && !strcmp(docs[j]->nome,d->nome))
								break;
							if(docs[j] == NULL)
							{
								docs[j] = d;
								break;
							}

						}
						d = d->prox;
					}


				}
				indice =  1 + (indice % (HASHLEN -1));
				indice = indice%HASHLEN;
				quant++;
			}

		}
	}
}

void buscarHashLin(string palavra, ListaDocumentos **docs)
{
	int i, indice = 0,j;
	for(i=0;i<strlen(palavra);i++)
	{
		int letra = (int) palavra[i];

		if(i % 2)
			indice =+ letra * i + 7;
		else
			indice = indice * letra + i + 11;
	}

	if(indice < 0)
		indice = indice * (-1);

	indice = indice%HASHLEN;

	if(hashLin[indice] != NULL)
	{
		if(!strcmp( hashLin[indice]->palavra, palavra))
		{
			ListaDocumentos *d = NULL;
			d = hashLin[indice]->docs;
			while(d != NULL)
			{
				for(i=0;i<nDocs;i++)
				{
					if( docs[i] != NULL && !strcmp(docs[i]->nome,d->nome))
						break;

					if(docs[i] == NULL)
					{
						docs[i] = d;
						break;
					}

				}
				d = d->prox;
			}

		}
		else
		{
			for(i=indice+1;i<HASHLEN;i++)
			{
				if(hashLin[i] == NULL)
					break;

				if(!strcmp(hashLin[i]->palavra,palavra))
				{

					ListaDocumentos *d = NULL;
					d = hashLin[i]->docs;
					while(d != NULL)
					{
						for(j=0;j<nDocs;j++)
						{
							if( docs[j] != NULL && !strcmp(docs[j]->nome,d->nome))
								break;
							if(docs[j] == NULL)
							{
								docs[j] = d;
								break;
							}

						}
						d = d->prox;
					}
				}
			}
		}
	}
	
}

void buscarHashEncad (string palavra, ListaDocumentos **docs)
{
	int i,indice = 0;
	for(i=0;i<strlen(palavra);i++)
	{
		int letra = (int) palavra[i];

		if(i % 2)
			indice =+ letra * i + 7;
		else
			indice = indice * letra + i + 11;
	}

	if(indice < 0)
		indice = indice * (-1);

	indice = indice%HASHLEN;

	ListaString *p = hashEncad[indice];
	ListaDocumentos *d = NULL;

	while(p != NULL)
	{
		if(!strcmp(p->palavra,palavra))
		{
			d = p->docs;
			while(d != NULL)
			{
				for(i=0;i<nDocs;i++)
				{
					if( docs[i] != NULL && !strcmp(docs[i]->nome,d->nome))
						break;

					if(docs[i] == NULL)
					{
						docs[i] = d;
						break;
					}

				}
				d = d->prox;
			}

		}

		p = p->prox;
	}
	
}

void lerIndice(char tipo, string arqIndice )
{

	ind = fopen(arqIndice,"r");
	if(ind == NULL)
	{
		printf("ERRO: Arquivo %s nao encontrado.\n", arqIndice);
		exit(-1);
	}
	string linha = (string) malloc(999999999* sizeof(char)) ;

	fgets(linha,10,ind);

	if(linha[0] != tipo)
	{
		printf("ERRO: Tipo de modelo indexado %s \nTipo de modelo buscado %c\n",linha,tipo);
		fclose(ind);
		free(linha);
		exit(-1);
	}
	string palavra = (string) malloc (STRLEN * sizeof(char));
	string doc = (string) malloc (STRLEN * sizeof(char));
	string tok;
	fgets(linha,999999999,ind);

	switch(tipo)
	{
		case 'E':
			HASHLEN = atoi(linha);
			break;
		case 'L':
		case 'R':
			HASHLEN = atoi(linha);
			HASHLEN--;
			HASHLEN = HASHLEN/2;
			break;
	}
	fgets(linha,999999999,ind);

	nDocs = atoi(linha);


	while(fgets(linha,999999999,ind) != NULL)
	{
		strtok(linha, "\n\r");
		int posHash, qPos,i,j,pos;

		tok = strtok(linha,":");
		posHash = atoi(tok);

		tok = strtok(NULL,":");
		strcpy(palavra,tok);

		for(i=0;i<nDocs;i++)
		{
			tok = strtok(NULL,":");
			if(tok == NULL)
				break;

			strcpy(doc,tok);

			tok = strtok(NULL,":");
			qPos = atoi(tok);


			for(j=0;j<qPos;j++)
			{
				tok = strtok(NULL,":");
				pos = atoi(tok);

				switch(tipo)
				{
					case 'E':
						hashEncadeada(palavra,posHash,pos,doc);
						break;
					case 'L':
						hashLinear(palavra,posHash,pos,doc);
						break;
					case 'R':
						reHash(palavra,posHash,pos,doc);
						break;
				}
			}
		}

	}	
	
	free(palavra);
	free(doc);
	free(linha);
	fclose(ind);
	
}

void gerarIndice(int tamanho,char tipo, string indiceGerado)
{
	int i,j;
	ind = fopen(indiceGerado,"w");
	ListaString *p;
	ListaDocumentos *d;

	fprintf(ind,"%c\n",tipo);
	fprintf(ind,"%d\n",tamanho);
	fprintf(ind,"%d\n",nDocs);
	for(i=0;i<tamanho;i++)
	{
		switch(tipo)
		{
			case 'E':
				p = hashEncad[i];
				break;
			case 'L':
				p = hashLin[i];
				break;
			case 'R':
				p = rHash[i];
				break;
		}

		while(p != NULL)
		{
			fprintf(ind,"%d:",i);
			if(strlen(p->palavra) != 1)
				fprintf(ind,"%s:",p->palavra);
			else
				fprintf(ind,"%c:",p->palavra[0]);

			d = p->docs;

			while(d != NULL)
			{
				fprintf(ind,"%s:",d->nome);
				fprintf(ind,"%d:",d->nPos);
				for(j=0;j<d->nPos;j++)
					fprintf(ind,"%d:",d->pos[j]);

				d = d->prox;
			}

			p = p->prox;
			fprintf(ind,"\n");

		}
	}

		fclose(ind);



}

void liberarPonteiros(char tipo)
{
	int i;
	
	if(arqDocs != NULL)
		fclose(arqDocs);
	
	if(arq != NULL)
		fclose(arq);

	for(i=0;i<HASHLEN;i++)
	{
		ListaString *p;
		switch(tipo)
		{
			case 'E':
				p = hashEncad[i];
				break;
			case 'L':
				p = hashLin[i];
				break;
			case 'R':
				p = rHash[i];
				break;
		}

		ListaString *aux;
		ListaDocumentos *aux2;

		while(p != NULL)
		{
			free(p->palavra);
			aux = p->prox;
			ListaDocumentos *d = p->docs;
			while(d != NULL)
			{
				free(d->nome);
				free(d->pos);
				aux2 = d->prox;
				free(d);
				d = aux2;
			}
			free(p);
			p= aux;
		}
	}
	
	switch(tipo)
	{
		case 'E':
			free(hashEncad);
			break;
		case 'L':
			free(hashLin);
			break;
		case 'R':
			free(rHash);
			break;
	}
}

void addDoc(string doc,ListaDocumentos *d,int pos)
{
	ListaDocumentos *p = d;
	int i;

	while(p != NULL)
	{
		if(!strcmp(p->nome,doc))
		{
			int *novaPos = (int*)malloc(sizeof(int)* p->nPos +1);

			for(i=0;i<p->nPos;i++)
				novaPos[i] = p->pos[i];
			p->nPos++;
			novaPos[ p->nPos -1 ] = pos;

			free(p->pos);
			p->pos = novaPos;

			return;
		}

		if(p->prox != NULL)
			p = p->prox;
		else
		{
			ListaDocumentos *nd =  (ListaDocumentos*) malloc(sizeof(ListaDocumentos));
			nd->nome = (string) malloc(strlen(doc) * sizeof(char) + 1);
			strcpy(nd->nome,doc);

			nd->pos = (int*) malloc(sizeof(int));
			nd->pos[0] = pos;
			nd->nPos = 1;

			nd->prox = NULL;
			p->prox = nd;
			return;
		}
	}
}

void addString(int indice, string palavra,int pos,string nomeDoc)
{
	ListaString *p = hashEncad[indice];

	if(hashEncad[indice] == NULL)
	{
		ListaString *l = (ListaString*) malloc(sizeof(ListaString));
		l->palavra = (string) malloc(STRLEN * sizeof(char));
		strcpy(l->palavra,palavra);

		//Salva o documento e suas posiï¿½ï¿½es
			l->docs = (ListaDocumentos*) malloc(sizeof(ListaDocumentos));
			l->docs->nome = (string) malloc(strlen(nomeDoc) * sizeof(char) + 1);
			strcpy(l->docs->nome,nomeDoc);

			l->docs->pos = (int*) malloc(sizeof(int));
			l->docs->pos[0] = pos;
			l->docs->nPos = 1;
			l->docs->prox = NULL;

		l->prox = NULL;
		hashEncad[indice] = l;
	}
	else
	{
		while(p != NULL)
		{
			if(!strcmp(palavra,p->palavra))
			{
				addDoc(nomeDoc,p->docs,pos);
				return;
			}

			if(p->prox != NULL)
				p = p->prox;
			else
			{
				ListaString *l = (ListaString*) malloc(sizeof(ListaString));
				l->palavra = (string) malloc(STRLEN * sizeof(char));
				strcpy(l->palavra,palavra);
				//Salva o documento e suas posicoes
					l->docs = (ListaDocumentos*) malloc(sizeof(ListaDocumentos));
					l->docs->nome = (string) malloc(strlen(nomeDoc) * sizeof(char) + 1);
					strcpy(l->docs->nome,nomeDoc);

					l->docs->pos = (int*) malloc(sizeof(int));
					l->docs->pos[0] = pos;
					l->docs->nPos = 1;
					l->docs->prox = NULL;

				l->prox = NULL;
				p->prox = l;
				return;
			}
		}
	}
}

void reHash(string palavra, int indice, int posicao, string nomeDoc)
{
	int i;
	if(rHash == NULL)
	{
		HASHLEN = HASHLEN * 2 +1 ;
		rHash = (ListaString**) malloc (HASHLEN * sizeof(ListaString*));

		for(i=0;i<HASHLEN;i++)
		{
			rHash[i] = NULL;
		}
	}

	if(rHash[indice] == NULL)
	{
		ListaString *l = (ListaString*) malloc(sizeof(ListaString));

		l->palavra = (string) malloc(STRLEN * sizeof(char));
		strcpy(l->palavra,palavra);

		//Salva o documento e suas posicoes
			l->docs = (ListaDocumentos*) malloc(sizeof(ListaDocumentos));
			l->docs->nome = (string) malloc(strlen(nomeDoc) * sizeof(char) + 1);
			strcpy(l->docs->nome,nomeDoc);

			l->docs->pos = (int*) malloc(sizeof(int));
			l->docs->pos[0] = posicao;
			l->docs->nPos = 1;
			l->docs->prox = NULL;

		l->prox = NULL;
		rHash[indice] = l;
		return;
	}
	else
	{
		if(!strcmp(rHash[indice]->palavra,palavra))
		{
			addDoc(nomeDoc,rHash[indice]->docs,posicao);
			return;
		}
		else
		{
			int quant = 0;
			while(rHash[indice] != NULL && quant != HASHLEN )
			{
				if(!strcmp(rHash[indice]->palavra,palavra))
				{
					addDoc(nomeDoc,rHash[indice]->docs,posicao);
					return;
				}
				indice =  1 + (indice % (HASHLEN -1));
				indice = indice%HASHLEN;
				quant++;

			}
			ListaString *l = (ListaString*) malloc(sizeof(ListaString));

			l->palavra = (string) malloc(STRLEN * sizeof(char));
			strcpy(l->palavra,palavra);

			//Salva o documento e suas posicoes
				l->docs = (ListaDocumentos*) malloc(sizeof(ListaDocumentos));
				l->docs->nome = (string) malloc(strlen(nomeDoc) * sizeof(char) + 1);
				strcpy(l->docs->nome,nomeDoc);

				l->docs->pos = (int*) malloc(sizeof(int));
				l->docs->pos[0] = posicao;
				l->docs->nPos = 1;
				l->docs->prox = NULL;

			l->prox = NULL;
			rHash[indice] = l;
			return;
		}
	}

}

void hashLinear(string palavra, int indice, int posicao, string nomeDoc)
{
	int i;
	if(hashLin == NULL)
	{
		HASHLEN = HASHLEN * 2 +1 ;
		hashLin = (ListaString**) malloc (HASHLEN * sizeof(ListaString*));

		for(i=0;i<HASHLEN;i++)
		{
			hashLin[i] = NULL;
		}
	}

	if(hashLin[indice] == NULL)
	{
		ListaString *l = (ListaString*) malloc(sizeof(ListaString));

		l->palavra = (string) malloc(STRLEN * sizeof(char));
		strcpy(l->palavra,palavra);

		//Salva o documento e suas posicoes
			l->docs = (ListaDocumentos*) malloc(sizeof(ListaDocumentos));
			l->docs->nome = (string) malloc(strlen(nomeDoc) * sizeof(char) + 1);
			strcpy(l->docs->nome,nomeDoc);

			l->docs->pos = (int*) malloc(sizeof(int));
			l->docs->pos[0] = posicao;
			l->docs->nPos = 1;
			l->docs->prox = NULL;

		l->prox = NULL;
		hashLin[indice] = l;
		return;
	}
	else
	{
		if(!strcmp(hashLin[indice]->palavra,palavra))
		{
			addDoc(nomeDoc,hashLin[indice]->docs,posicao);
			return;
		}
		else
		{
			if(indice+1 != HASHLEN)
			{
				for(i=indice+1;i<HASHLEN;i++)
				{
					if(hashLin[i] == NULL)
					{
						ListaString *l = (ListaString*) malloc(sizeof(ListaString));

						l->palavra = (string) malloc(STRLEN * sizeof(char));
						strcpy(l->palavra,palavra);

						//Salva o documento e suas posicoes
							l->docs = (ListaDocumentos*) malloc(sizeof(ListaDocumentos));
							l->docs->nome = (string) malloc(strlen(nomeDoc) * sizeof(char) + 1);
							strcpy(l->docs->nome,nomeDoc);

							l->docs->pos = (int*) malloc(sizeof(int));
							l->docs->pos[0] = posicao;
							l->docs->nPos = 1;
							l->docs->prox = NULL;

						l->prox = NULL;
						hashLin[i] = l;
						return;
					}
					else
					{
						if(!strcmp(hashLin[i]->palavra,palavra))
						{
							addDoc(nomeDoc,hashLin[i]->docs,posicao);
							return;
						}

					}

				}

			}

		}

	}

}

void hashEncadeada(string palavra, int indice,int posicao,string nomeDoc)
{
	int i;

	if(hashEncad == NULL)
	{
		hashEncad = (ListaString**) malloc (HASHLEN * sizeof(ListaString*));

		for(i=0;i<HASHLEN;i++)
		{
			hashEncad[i] = NULL;
		}
	}

	addString(indice, palavra,posicao,nomeDoc);
}

int aceitavel(string palavra)
{
	string a[] = {"a", "as", "o", "os", "de", "da", "das", "do", "dos", "com", "e", "em", "pela", "aos",
				  "ao", "que", "se","na","no","i","ii","iv", "v","iii","vii", "x", "ix", "xi", "ou","l","p",
				  "s", ""};
	int i;
	
	int len =sizeof(a)/sizeof(string);
	for(i=0;i<len;i++)
		if( !strcmp(palavra,a[i]) )
			return 0;

	if(atoi(palavra))
		return 0;

	len = strlen(palavra);
	for(i=0;i<len;i++)
	{
		if(!isalpha( (int) palavra[i]) && palavra[i] > 0  )
			return 0;
	}

	return 1;

}

int tamanhoHash(string entradaDocs)
{
	int tamanho = 0, maiorTamanho = 0;
	FILE *docTam = NULL, *documento = NULL;
	string tam = (string) malloc(sizeof(char) * STRLEN);
	docTam = fopen(entradaDocs,"r");
	if(docTam == NULL)
	{
		printf("ERRO: Arquivo ''%s'' nao encontrado\n",tam);
		exit(-1);
	}

	string doc = (string) malloc(sizeof(char) * STRLEN);

	while(!feof(docTam))
	{
		tamanho = 0;
		fscanf(docTam,"%s\r\n",doc);
		documento = fopen(doc,"r");
		if(documento == NULL)
		{
			printf("ERRO: Arquivo ''%s'' nao encontrado\n",doc);
			exit(-1);

		}
		while(!feof(documento))
		{
			fscanf(documento,"%s\n",tam);
			tamanho++;
		}
		fclose(documento);
		if(tamanho > maiorTamanho)
			maiorTamanho = tamanho;

	}
	free(tam);
	free(doc);
	fclose(docTam);

	tamanho = tamanho*0.15;

	if(tamanho % 2 == 0)
		return tamanho;
	else
		return tamanho++;


}

void indexarHash(char tipo,string entradaDocs, string indiceGerado)
{
	arqDocs = fopen(entradaDocs,"r");
	if(arqDocs == NULL)
	{
		perror("ERRO: Arquivo ''entradaDocs'' nao encontrado");
		exit(-1);

	}
	int i,indice = 0, posicao; // Posicao da palavra no arquivo texto;

	if(HASHLEN == 0)
		HASHLEN = tamanhoHash(entradaDocs);


	while(!feof(arqDocs))
	{
		string nomeDoc = (string) malloc(STRLEN * sizeof(char)), palavra;
		fscanf(arqDocs,"%s\n",nomeDoc);

		nDocs++; // Contar o numero de documentos

		doc = fopen(nomeDoc, "r");
		if(doc == NULL)
		{
			printf("Documento ''%s'' não encontrado!\n",nomeDoc);
			exit(1);
		}

		posicao = 1;

		while(!feof(doc))
		{
			palavra = (string) malloc(STRLEN * sizeof(char));
			fscanf(doc,"%s\n\r",palavra);

			int len = strlen(palavra);

			unsigned char c;
			for(i=0;i<len;i++)
			{
				c = palavra[i];
				palavra[i] = tolower(c);
			}
			if(palavra[len - 1 ] == '.' || palavra[len -1] == ',' || palavra[len -1] == '!' ||
			   palavra[len -1] == ':' || palavra[len -1] == '?' || palavra[len-1] == ';')
			{
				if(palavra[len-2] == '.' && palavra[len -3] == '.')
					palavra[len-3] = '\0';
				else
					palavra[len - 1] = '\0';

			}

			if(aceitavel(palavra))
			{
				for(i=0;i<strlen(palavra);i++)
				{
					int letra = (int) palavra[i];

					if(i % 2)
						indice =+ letra * i + 7;
					else
						indice = indice * letra + i + 11;
				}

				if(indice < 0)
					indice = indice * (-1);

				indice = indice%HASHLEN;
				switch(tipo)
				{
					case 'E':
						hashEncadeada(palavra, indice,posicao,nomeDoc);
						break;
					case 'L':
						hashLinear(palavra,indice,posicao,nomeDoc);
						break;
					case 'R':
						reHash(palavra,indice,posicao,nomeDoc);
						break;
				}
			}

			posicao++;
			indice = 0;
			free(palavra);
		}
		fclose(doc);
		free(nomeDoc);
	}

	gerarIndice(HASHLEN,tipo,indiceGerado);
}




