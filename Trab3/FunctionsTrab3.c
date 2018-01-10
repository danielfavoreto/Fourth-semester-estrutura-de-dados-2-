#include "FunctionsTrab3.h"

int** jobs = NULL;
int *menorSequencia = NULL;
int valorMenorSeq = -1;
Sequencia **melhores = NULL;

void bs(int n, int imprimir)
{
	int i,j,k;
	jobs = (int**) malloc(n*sizeof(int*));

	for(i=0;i<n;i++)
		jobs[i] = (int*) malloc(3*sizeof(int));

	for(i=0;i<n;i++)
		scanf("%d %d %d\n", &jobs[i][0],&jobs[i][1],&jobs[i][2]);

	int w;


	if(n>10)
		w = 7;
	else
		w = 3;


	Sequencia caminhos[n];
	Sequencia melhores[n][w];


	for(i=0;i<n;i++)
	{
		for(j=0;j<w;j++)
		{
			melhores[i][j].caminho = NULL;
			melhores[i][j].visitados = NULL;
			melhores[i][j].multa = -1;
		}
	}

	for(i=0;i<n;i++)
	{
		caminhos[i].caminho = (int*) malloc(sizeof(int)*n);
		caminhos[i].caminho[0] = i;
		caminhos[i].visitados = (int*) malloc(sizeof(int)*n);
		for(j=0;j<n;j++)
			caminhos[i].visitados[j] = 0;

		caminhos[i].visitados[i] = 1;

		caminhos[i].nVisitados = 1;
		caminhos[i].multa = 0;
		caminhos[i].tempo = 0;
	}



	int multa, tempo;
	Sequencia s;

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if( i != j)
			{
				if(jobs[i][0] > jobs[i][1])
					multa = jobs[i][2];
				else
					multa = 0;

				tempo = jobs[i][0] +  jobs[j][0];

				if(tempo > jobs[j][1])
					multa += jobs[j][2];
				else
					multa = 0;

				s = createSeq(caminhos[i],j,n,multa, tempo);

				addMelhores(melhores[0],s,w);
			}
		}

	}

	for(i=0;i<n-1;i++)
	{
		for(j=0;j<w;j++)
		{
			for(k=0;k<n;k++)
			{
				if(melhores[i][j].visitados[k] != 1)
				{

					tempo = melhores[i][j].tempo +  jobs[k][0];

					if(tempo > jobs[k][1])
						multa = jobs[k][2];
					else
						multa = 0;

					s = createSeq(melhores[i][j],k,n,multa, tempo);

					addMelhores(melhores[i+1],s,w);
				}
			}
		}
	}


	if(imprimir == 1)
	{
		printf("%d: ", melhores[n-2][0].multa);

		for(i=0;i<n;i++)
			printf("%d ",melhores[n-2][0].caminho[i]);

		printf("\n");
	}
	else
	{
		menorSequencia = (int*) malloc(sizeof(int)*n);
		valorMenorSeq = melhores[n-2][0].multa;
		for(i=0;i<n;i++)
			menorSequencia[i] = melhores[n-2][0].caminho[i];
	}

	for(i=0;i<n;i++)
	{
		free(caminhos[i].caminho);
		free(caminhos[i].visitados);
		for(j=0;j<w;j++)
		{
			free(melhores[i][j].caminho);
			free(melhores[i][j].visitados);
		}
	}


}


void bb(int n)
{
	int i,j,k, tempo = 0, multa, cont,lowerBound = 0,upBound = 0, tempoAcum;

	melhores = (Sequencia**) malloc (sizeof(Sequencia*)*n);
	Sequencia caminhos[n];

	for(i=0;i<n;i++)
	{
		caminhos[i].caminho = (int*) malloc(sizeof(int)*n);
		caminhos[i].caminho[0] = i;
		caminhos[i].visitados = (int*) malloc(sizeof(int)*n);
		for(j=0;j<n;j++)
			caminhos[i].visitados[j] = 0;

		caminhos[i].visitados[i] = 1;

		caminhos[i].nVisitados = 1;
		caminhos[i].multa = 0;
		caminhos[i].tempo = 0;

		caminhos[i].prox = NULL;
	}

	for(i=0;i<n;i++)
		melhores[i] = NULL;


	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i != j)
			{
				tempo = jobs[i][0];
				if(tempo>jobs[i][1])
					multa = jobs[i][2];
				else
					multa = 0;

				tempo = tempo + jobs[j][0];
				if(tempo>jobs[j][1])
					multa += jobs[j][2];

				lowerBound += multa;
				for(k=0;k<n;k++)
				{
					if(k != j && k!=i)
					{
						tempoAcum = tempo + jobs[k][0];
						if(jobs[k][1] < tempoAcum)
							lowerBound +=  jobs[k][2];
						upBound += jobs[k][2];
					}

				}
				if(lowerBound<=valorMenorSeq)
					addMelhoresBb(0,caminhos[i],j,n,multa,tempo,lowerBound,upBound);
				lowerBound = 0;
				upBound = 0;
			}
		}

	}
	Sequencia *p;

	cont = 2;
	for(i=0;i<n-1;i++)
	{
		Sequencia *p = melhores[i];

		while( p != NULL  )
		{
			for(j=0;j<n;j++)
			{
				if(p->visitados[j] != 1)
				{
					tempo = p->tempo + jobs[j][0];

					lowerBound = p->lb;

					if(tempo>jobs[j][1])
					{
						multa = p->multa + jobs[j][2];

						if(p->tempo <= jobs[j][1])
							lowerBound += jobs[j][2];
					}
					else
						multa = p->multa;

					upBound = p->ub - multa;

					if(melhores[i+1]==NULL)
						addMelhoresBb(i+1,*p,j,n,multa,tempo,lowerBound, upBound);
					else
					{
						if(melhores[i+1]->lb >= lowerBound && melhores[i+1]->ub <= upBound)
							addMelhoresBb(i+1,*p,j,n,multa,tempo,lowerBound, upBound);
					}



				}
			}

			p = p->prox;
		}


		cont++;
	}
	p = melhores[n-2];


	printf("%d: ", p->multa);
	for(i=0;i<p->nVisitados;i++)
		printf("%d ", p->caminho[i]);
	
	for(i=0;i<n;i++)
	{
		free(caminhos[i].caminho);
		free(caminhos[i].visitados);
	}


	printf("\n");
}

void addMelhoresBb(int posM, Sequencia s, int pos, int n, int multa, int tempo, int lb,int ub)
{
	int i;
	Sequencia *new = (Sequencia*) malloc (sizeof(Sequencia));


	new->caminho = (int*) malloc(sizeof(int)*n);
	for(i=0;i<s.nVisitados;i++)
			new->caminho[i] = s.caminho[i];

	new->caminho[ s.nVisitados ] = pos;
	new->nVisitados = s.nVisitados + 1;

	new->visitados = (int*) malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
		new->visitados[i] = s.visitados[i];

	new->visitados[pos] = 1;

	new->prox = NULL;

	new->multa = multa;
	new->tempo = tempo;

	new->lb = lb;
	new->ub = ub;

	Sequencia *p;
	if(melhores[posM] == NULL)
	{
		melhores[posM] = new;
	}
	else
	{
		Sequencia *tmp;
		if(new->lb <= melhores[posM]->lb)
		{
			tmp = melhores[posM];
			melhores[posM] = new;
			new->prox = tmp;
			return;
		}
		p = melhores[posM];
		while(p->prox != NULL)
			p = p->prox;


		p->prox = new;
	}

}

void liberarPonteiros(int n)
{
	int i;

	if(melhores != NULL)
	{
		for(i=0;i<n;i++)
		{
			Sequencia *p = melhores[i], *aux;
			while(p != NULL)
			{
				aux = p->prox;				
				free(p->caminho);
				free(p->visitados);
				free(p);
				p = aux;
			}
		}
		free(melhores);
	}

	if(jobs != NULL)
	{
		for(i=0;i<n;i++)
			free(jobs[i]);

		free(jobs);
	}

}

Sequencia createSeq(Sequencia s, int pos, int n , int multa, int tempo)
{
	Sequencia new;
	int i;

	new.caminho = (int*) malloc(sizeof(int)*n);
	for(i=0;i<s.nVisitados;i++)
			new.caminho[i] = s.caminho[i];
	new.caminho[ s.nVisitados ] = pos;
	new.nVisitados = s.nVisitados + 1;

	new.visitados = (int*) malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
		new.visitados[i] = s.visitados[i];

	new.visitados[pos] = 1;

	new.multa = multa + s.multa;
	new.tempo = tempo ;

	return new;

}

void addMelhores(Sequencia s[], Sequencia nova, int w)
{
	int i,j;

	for(i=0;i<w;i++)
	{
		if(s[i].multa == -1)
		{
			s[i] = nova;
			return;
		}

		if(s[i].multa > nova.multa )
		{

			if(s[i].caminho != NULL)
				free(s[w-1].caminho);

			if(s[i].visitados != NULL)
				free(s[w-1].visitados);

			for(j=w-1;j>i;j--)
				s[j] = s[j-1];

			s[i] = nova;
			return;
		}

	}

	free(nova.visitados);
	free(nova.caminho);
}




string gerarSequencia(int n)
{
	int i;
	string str = (string) malloc(n*sizeof(char));

	for(i=0;i<n;i++)
		str[i] = (char) i+ 'A';

	return str;
}

int* gerarCaminho(int n)
{
	int* caminho = (int*) malloc(n*sizeof(int));
	int i;
	for(i=0;i<n;i++)
		caminho[i] = i;

	return caminho;
}
