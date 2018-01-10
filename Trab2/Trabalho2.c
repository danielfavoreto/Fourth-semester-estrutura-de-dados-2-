#include "FunctionsTrab.h"

int main (int argc, char *argv[]){

	if(argc < 5 )
	{
		printf("Argumentos insuficientes!\n");
		exit(1);
	}

	if(!strcmp(argv[1],"-i"))
	{
		if(!strcmp(argv[2],"E"))
		{
			indexarHash('E',argv[3],argv[4]);

			liberarPonteiros('E');
		}
		else
		{
			if(!strcmp(argv[2],"L"))
			{
				indexarHash('L',argv[3],argv[4]);
				liberarPonteiros('L');
			}
			if(!strcmp(argv[2],"R"))
			{
				indexarHash('R',argv[3],argv[4]);
				liberarPonteiros('R');
			}

		}
	}
	if(!strcmp(argv[1],"-b"))
	{
		lerIndice(argv[2][0],argv[3]);

		switch(argv[2][0])
		{
			case 'E':
				buscarPalavra('E', argv[4]);
				liberarPonteiros('E');
				break;
			case 'L':
				buscarPalavra('L',argv[4]);
				liberarPonteiros('L');
				break;
			case 'R':
				buscarPalavra('R',argv[4]);
				liberarPonteiros('R');
				break;
		}

	}


	return 0;
}

