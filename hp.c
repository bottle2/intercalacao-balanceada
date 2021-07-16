#include <stdio.h>

void ord_heapsort(int * vet, int tam);
void maxHeap(int * vet, int tam);
void heapsort(int * vet, int tam);
void heapify(int * vet, int father, int tam);
void swap(int * vet, int father, int lado);
void mostrar_vetor(int * vet, int tam);

void ord_heapsort(int * vet, int tam){    
    if(tam <= 1) return;
    maxHeap(vet, tam);
    heapsort(vet, tam);
}

void maxHeap(int * vet, int tam){
    int count;
    for(count = (tam/2)-1; count >= 0; count --){
        heapify(vet, count, tam);
    }
}

void heapsort(int * vet, int tam){
    if(tam <= 1) return;
    heapify(vet, 0, tam);
        int aux = vet[0];
        vet[0] = vet[tam-1];
        vet[tam-1] = aux;
    heapsort(vet, tam-1);
}

void heapify(int * vet, int father, int tam){
    if((father * 2) + 1 < tam && (father * 2) + 2 < tam) 
    {
        if(vet[(father * 2) + 2] < vet[(father * 2) + 1])
        {
            if(vet[father] < vet[(father * 2) + 1]) 
            {
                swap(vet, father, (father * 2) + 1);
                heapify(vet, (father * 2) + 1, tam);
            }
        }    
        else
        {
            if(vet[father] < vet[(father * 2) + 2]) 
            {
                swap(vet, father, (father * 2) + 2);
                heapify(vet, (father * 2) + 2, tam);
            }
        }           
    }   
    else if((father * 2) + 1 < tam)   
    {
        if(vet[father] < vet[(father * 2) + 1])
        {
            swap(vet, father, (father * 2) + 1);
            heapify(vet, (father * 2) + 1, tam);
        }
    }
    else
    {
        //folha
    }
}

void swap(int * vet, int father, int son){
    int aux = vet[son];
    vet[son] = vet[father];
    vet[father] = aux;   
}

void mostrar_vetor(int * vet, int tam)
{
    for(int count = 0; count < tam; count++)
    {
        printf("%i ", vet[count]);
    }
    printf("\n");
}   

int main(){
    int vet1[] = {4,8,6,3,5,7,9,1};
    int vet2[] = {26, 15, 47, 1, 64, 13, 12, 4, 8, 11, 44, 80, 60, 34, 15, 75, 19, 15, 66, 82};
    int vet3[] = {13, 9, 220, 190, 71, 12, 236, 105, 59, 12, 92, 197, 157, 192, 41, 28, 70, 165, 103, 9, 83, 9, 223, 12, 49, 23, 122, 20, 98, 67, 22, 243, 192, 94, 191, 152, 199, 235, 117, 233, 190, 134, 140, 224, 12, 32, 48, 9, 83, 210};
 
    ord_heapsort(vet1, 8);
    ord_heapsort(vet2, 20);
    ord_heapsort(vet3, 50);

    mostrar_vetor(vet1, 8);
    mostrar_vetor(vet2, 20);
    mostrar_vetor(vet3, 50);
}
