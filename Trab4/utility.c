#include "utility.h"

//https://pt.wikipedia.org/wiki/Radix_sort
void radix_sort(int vetor[], int tamanho) {
    int i;
    int *b;
    int maior = 1000000;
    int exp = 1;

    b = (int *)calloc(tamanho, sizeof(int));
 
    while (maior/exp > 0) {
        int bucket[10] = { 0 };
    	for (i = 0; i < tamanho; i++)
    	    bucket[(vetor[i] / exp) % 10]++; 
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
    	for (i = tamanho - 1; i >= 0; i--)
    	    b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
    	for (i = 0; i < tamanho; i++)
    	    vetor[i] = b[i];
    	exp *= 10;
    }

    free(b);
}
// feito por Daniel Favoreto
void rank_sort(int v[], int tam)
{
	int *vaux,i,aux = 0,j;
	vaux = calloc(1000000,sizeof(int));
	for (i = 0; i < tam; i++)
		vaux[v[i]]++;
	for (i = 0; i < 1000001; i++) {
		for (j = 0; j < vaux[i];j++) {
			v[aux] = i;
			aux++;
		}
	}
	free(vaux);
}


//https://pt.wikipedia.org/wiki/Quicksort
void quickcentral(int valor[], int esquerda, int direita) // quicksort escolhendo o elemento central
{
    int i, j, pivot, y;
    i = esquerda;
    j = direita;
    pivot = valor[(esquerda + direita) / 2]; //pivot é o do meio

    while(i <= j)
    {
        while(valor[i] < pivot && i < direita)
        {
            i++;
        }
        while(valor[j] > pivot && j > esquerda)
        {
            j--;
        }
        if(i <= j)
        {
            y = valor[i];
            valor[i] = valor[j];
            valor[j] = y;
            i++;
            j--;
        }
    }
    if(j > esquerda)
    {
        quickcentral(valor, esquerda, j);
    }
    if(i < direita)
    {
        quickcentral(valor,  i, direita);
    }
}
// com adaptações por Daniel Favoreto
void quickprimeiro(int valor[], int esquerda, int direita) // quicksort escolhendo primeiro elemento
{
    int i, j, pivot, y;
    i = esquerda;
    j = direita;    
    pivot = valor[esquerda]; // pivot é o primeiro

    while(i <= j)
    {
        while(valor[i] < pivot && i < direita)
        {
            i++;
        }
        while(valor[j] > pivot && j > esquerda)
        {
            j--;
        }
        if(i <= j)
        {
            y = valor[i];
            valor[i] = valor[j];
            valor[j] = y;
            i++;
            j--;
        }
    }
    if(j > esquerda)
    {
        quickprimeiro(valor, esquerda, j);
    }
    if(i < direita)
    {
        quickprimeiro(valor,  i, direita);
    }
}

// com adaptações por Daniel Favoreto
void quickrandom(int valor[], int esquerda, int direita) // quicksort escolhendo elemento aleatório
{
    int i, j, pivot, y,pivot_indice;
    i = esquerda;
    j = direita;

    srand((unsigned) time(NULL));
	
    pivot_indice = esquerda + rand() % (direita - esquerda + 1);

    pivot = valor[pivot_indice]; // pivot aleatorio 
	
    while(i <= j)
    {
        while(valor[i] < pivot && i < direita)
        {
            i++;
        }
        while(valor[j] > pivot && j > esquerda)
        {
            j--;
        }
        if(i <= j)
        {
            y = valor[i];
            valor[i] = valor[j];
            valor[j] = y;
            i++;
            j--;
        }
    }
    if(j > esquerda)
    {
        quickrandom(valor, esquerda, j);
    }
    if(i < direita)
    {
        quickrandom(valor,  i, direita);
    }
}
// com adaptações por Daniel Favoreto
void quickmediana3(int valor[], int esquerda, int direita) // quicksort escolhendo pivot com mediana de 3
{
    int i, j, pivot, y,meio;
    i = esquerda;
    j = direita;
    meio = (esquerda + direita)/2;
    
    if (valor[meio] < valor[direita]){
	if (valor[meio] > valor[esquerda])
		pivot = valor[meio];
	else if (valor[esquerda] > valor[direita])
		pivot = valor[direita];
	else 
		pivot = valor[esquerda];
    }
    else if (valor[meio] < valor[esquerda]){
    	pivot = valor[meio];
    }
    else if (valor[direita] > valor[esquerda]) {
    	pivot = valor[direita];
    }
    else
    	pivot = valor[esquerda];
    
    	

    while(i <= j)
    {
        while(valor[i] < pivot && i < direita)
        {
            i++;
        }
        while(valor[j] > pivot && j > esquerda)
        {
            j--;
        }
        if(i <= j)
        {
            y = valor[i];
            valor[i] = valor[j];
            valor[j] = y;
            i++;
            j--;
        }
    }
    if(j > esquerda)
    {
        quickmediana3(valor, esquerda, j);
    }
    if(i < direita)
    {
        quickmediana3(valor,  i, direita);
    }
}

//http://geeksquiz.com/heap-sort/

void swap(int* a, int* b) { int t = *a; *a = *b;  *b = t; }

void maxHeapify(struct MaxHeap* maxHeap, int idx)
{
    int largest = idx; 
    int left = (idx << 1) + 1; 
    int right = (idx + 1) << 1;
 

    if (left < maxHeap->size && 
        maxHeap->array[left] > maxHeap->array[largest])
        largest = left;
 
    if (right < maxHeap->size && 
        maxHeap->array[right] > maxHeap->array[largest])
        largest = right;

    if (largest != idx)
    {
        swap(&maxHeap->array[largest], &maxHeap->array[idx]);
        maxHeapify(maxHeap, largest);
    }
}
 
// A utility function to create a max heap of given capacity
struct MaxHeap* createAndBuildHeap(int *array, int size)
{
    int i;
    struct MaxHeap* maxHeap = 
              (struct MaxHeap*) malloc(sizeof(struct MaxHeap));
    maxHeap->size = size;   
    maxHeap->array = array; 

    for (i = (maxHeap->size - 2) / 2; i >= 0; --i)
        maxHeapify(maxHeap, i);
    return maxHeap;
}
 
// The main function to sort an array of given size
void heap(int size, int* array)
{

    struct MaxHeap* maxHeap = createAndBuildHeap(array, size);

    while (maxHeap->size > 1)
    {
        swap(&maxHeap->array[0], &maxHeap->array[maxHeap->size - 1]);
        --maxHeap->size;  

        maxHeapify(maxHeap, 0);
    }
}
//https://gist.github.com/mycodeschool/9678029
void merge(int *A,int *L,int leftCount,int *R,int rightCount) {
	int i,j,k;

	i = 0; j = 0; k =0;

	while(i<leftCount && j< rightCount) {
		if(L[i]  < R[j]) A[k++] = L[i++];
		else A[k++] = R[j++];
	}
	while(i < leftCount) A[k++] = L[i++];
	while(j < rightCount) A[k++] = R[j++];
}

// Recursive function to sort an array of integers. 
void mergeSort(int n,int *A) {
	int mid,i, *L, *R;
	if (n < 2) return;

	mid = n/2; 

	L = (int*)malloc(mid*sizeof(int)); 
	R = (int*)malloc((n- mid)*sizeof(int)); 
	
	for(i = 0;i<mid;i++) L[i] = A[i];
	for(i = mid;i<n;i++) R[i-mid] = A[i];

	mergeSort(mid,L);
	mergeSort(n-mid,R);
	merge(A,L,mid,R,n-mid);
        free(L);
        free(R);
}

//https://pt.wikipedia.org/wiki/Selection_sort

void selection (int n,int array[n])
{
	int i,j;
	int iMin;

	for (j = 0; j < n-1; j++) {
	    iMin = j;
	    for ( i = j+1; i < n; i++) {
	        if (array[i] < array[iMin]) {
	            iMin = i;
	        }
    	}
	
	    if (iMin != j) {
        		swap(&array[j], &array[iMin]);
    		}
	}
}

//https://pt.wikipedia.org/wiki/Shell_sort
void shell (int n, int array[n]) {
    int i , j , value;
    int gap = 1;
    
    while(gap < n) {
        gap = 3*gap+1;
    }
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < n; i++) {
            value = array[i];
            j = i - gap;
            while (j >= 0 && value < array[j]) {
                array [j + gap] = array[j];
                j -= gap;
            }
            array [j + gap] = value;
        }
    }
}

//https://pt.wikipedia.org/wiki/Insertion_sort
void insertion (int n,int array[n]) {

   int i, j, eleito;
   
   for (i = 1; i < n; i++){
      eleito = array[i];
      j = i - 1;
      
      while ((j >= 0) && (eleito < array[j])) {
         array[j+1] = array[j];
         j--;
      }
      array[j+1] = eleito;
   }
}

//http://www.programming-algorithms.net/article/40270/Shaker-sort
void shake (int n, int array[n])
{
	int i;
	for ( i = 0; i < n/2; i++) {

	int trocou = 0;

		for (int j = i; j < n - i - 1; j++) {

			if (array[j] > array[j+1]) {

				int tmp = array[j];
				array[j] = array[j+1];
				array[j+1] = tmp;
				trocou = 1;
			}
		}

		for (int j = n - 2 - i; j > i; j--) { //and back

			if (array[j] < array[j-1]) {

				int tmp = array[j];
				array[j] = array[j-1];
				array[j-1] = tmp;
				trocou = 1;
			}
		}

	if (trocou == 0)
		break; 
		
	}
}
//http://www.programmingsimplified.com/c/source-code/c-program-bubble-sort
void bubble (int n,int array[n])
{
	int c, d, swap,trocou = 0;
 
  	for (c = 0 ; c < ( n - 1 ); c++)
  	{
    		for (d = 0 ; d < n - c - 1; d++)
    		{
      			if (array[d] > array[d+1])
      			{
        			swap       = array[d];
        			array[d]   = array[d+1];
        			array[d+1] = swap;
        			trocou = 1;
      			}
    		}
    		if (trocou == 0)
    			break;

    		trocou = 0;
  	}
}
