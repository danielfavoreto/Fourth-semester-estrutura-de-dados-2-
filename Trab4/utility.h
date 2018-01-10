#include "gera.h"

struct MaxHeap {
	int size;
	int *array;
};
void radix_sort(int vetor[], int tamanho);
void rank_sort(int v[], int tam);
void quickcentral(int valor[], int esquerda, int direita);
void quickprimeiro(int valor[], int esquerda, int direita);
void quickrandom(int valor[], int esquerda, int direita);
void quickmediana3(int valor[], int esquerda, int direita);
void swap(int* a, int* b);
void maxHeapify(struct MaxHeap* maxHeap, int idx);
struct MaxHeap* createAndBuildHeap(int *array, int size);
void heap(int size, int* array);
void merge(int *A,int *L,int leftCount,int *R,int rightCount);
void mergeSort(int n,int *A);
void selection (int n,int array[n]);
void shell (int n, int array[n]);
void insertion (int n,int array[n]);
void shake (int n, int array[n]);
void bubble (int n,int array[n]);

