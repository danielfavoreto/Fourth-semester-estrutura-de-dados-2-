#include "gera.h"
char* nomearquivo = "entrada.txt"; // modifique aqui o nome do arquivo de entrada

int cmpfunc_crescente (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int cmpfunc_decrescente (const void * a, const void * b)
{
   return ( *(int*)b - *(int*)a );
}
int main (int argc,char* argv[])
{
	if (argc != 3) {
		printf("Argumentos insuficientes, digite 3 argumentos\n");
		exit(1);
	}
	
	if (!strcmp(argv[1],"-a")) { 
		gera_ale(atoi(argv[2])); // aleatorio
	}
	else if (!strcmp(argv[1],"-c")){
		gera_cre(atoi(argv[2])); // crescente
	}
	else if (!strcmp(argv[1],"-d")){
		gera_dec(atoi(argv[2])); //decrescente
	}
	return 0;
}
void gera_ale (int n){

	FILE *in = fopen(nomearquivo,"w");
	
	int i,num;
	
	srand ( (unsigned) time(NULL));
	
	for (i = 1;i <= n;i++){
	
		num = rand()%(n+1);
		printf("%d\n",num);
		fprintf(in,"%d\n",num);
	}
	fclose(in);
}
void gera_cre (int n) {

	FILE *in = fopen (nomearquivo,"w");
	
	int i,num,v[n];
	
	srand ( (unsigned) time(NULL));
	
	for (i = 0;i < n;i++) {
	
		num = rand()%(n+1);
		v[i] = num;
	}
	qsort(v, n, sizeof(int), cmpfunc_crescente);
	for (i = 0; i < n;i++)
	{
		printf ("%d\n",v[i]);
		fprintf(in,"%d\n",v[i]);
	}
	fclose(in);
}
void gera_dec (int n) {

	FILE *in = fopen (nomearquivo,"w");
	
	int i,num,v[n];
	
	srand ( (unsigned) time(NULL));
	
	for (i = 0;i < n;i++) {
	
		num = rand()%(n+1);
		v[i] = num;
	}
	qsort(v, n, sizeof(int), cmpfunc_decrescente);
	for (i = 0; i < n;i++)
	{
		printf ("%d\n",v[i]);
		fprintf(in,"%d\n",v[i]);
	}
	fclose(in);
}
