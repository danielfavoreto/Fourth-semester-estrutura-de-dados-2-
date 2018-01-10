#include "FunctionsTrab3.h"

int main(int argc, string argv[])
{
	if (argc != 3)
	{
		printf("Erro no numero de argumentos! Esperado: 3\n");
		exit(1);
	}

	if(!strcmp(argv[2],"bb"))
	{
		bs(atoi(argv[1]),0);
		bb(atoi(argv[1]));
	}

	if(!strcmp(argv[2],"bs"))
		bs(atoi(argv[1]),1);


	if(menorSequencia != NULL)
		free(menorSequencia);

	liberarPonteiros(atoi(argv[1]));

	return EXIT_SUCCESS;
}
