#include "gera.h"
#include "utility.h"

int main (int argc, char* argv[])
{
	if (argc != 3) {
		printf("Argumentos insuficientes, digite 3 argumentos\n");
		exit(1);
	}
	
	int i,n = atoi(argv[2]),vetor[n],quantidade = sizeof(vetor)/sizeof(vetor[0]);
	
		for (i = 0; i < n; i++)
		{
			scanf("%d",&vetor[i]);
		}
	
	if (!strcmp(argv[1],"bubble")) { 

		bubble(quantidade,vetor);

		for (i = 0; i < n; i++)
			printf ("%d\n",vetor[i]);
	}
	else if (!strcmp(argv[1],"shake")) {

		shake(quantidade,vetor);

		for (i = 0; i < n; i++)
			printf ("%d\n",vetor[i]);
	}
	else if (!strcmp(argv[1],"insertion")) {

		insertion(quantidade,vetor);

		for (i = 0; i < n; i++)
			printf ("%d\n",vetor[i]);
	}
	else if (!strcmp(argv[1],"shell")) {

		shell(quantidade,vetor);

		for (i = 0; i < n; i++)
			printf ("%d\n",vetor[i]);
	}
	else if (!strcmp(argv[1],"selection")) {

		selection(quantidade,vetor);

		for (i = 0; i < n; i++)
			printf ("%d\n",vetor[i]);
	}
	else if (!strcmp(argv[1],"merge")) {
		
		mergeSort(quantidade,vetor);
		
		for (i = 0; i < n; i++)
			printf ("%d\n",vetor[i]);
	}
	else if (!strcmp(argv[1],"heap")) {
	
		heap(quantidade,vetor);
		
		for (i  = 0; i < n;i++) 
			printf ("%d\n",vetor[i]);
	}
	else if (!strcmp(argv[1],"quickcentral")) {
		
		quickcentral(vetor,0,quantidade-1);

		for (i = 0; i < quantidade; i++) 
			printf ("%d\n",vetor[i]);
	}
	else if (!strcmp(argv[1],"quickprimeiro")) {
		
		quickprimeiro(vetor,0,quantidade-1);

		for (i = 0; i < quantidade; i++) 
			printf ("%d\n",vetor[i]);
	}
	else if (!strcmp(argv[1],"quickmediana3")) {
		
		quickmediana3(vetor,0,quantidade-1);

		for (i = 0; i < quantidade; i++) 
			printf ("%d\n",vetor[i]);
	}
	else if (!strcmp(argv[1],"quickrandom")) {
		
		quickrandom(vetor,0,quantidade-1);

		for (i = 0; i < quantidade; i++) 
			printf ("%d\n",vetor[i]);
	}
	else if (!strcmp(argv[1],"radix")) {

		radix_sort(vetor,quantidade);
		
		for (i = 0; i < quantidade;i++)
			printf ("%d\n",vetor[i]);
	}
	else if (!strcmp(argv[1],"rank")) {
	
		rank_sort(vetor,quantidade);
		
		for (i = 0; i < quantidade;i++)
			printf ("%d\n",vetor[i]);
	}
	return 0;
}
