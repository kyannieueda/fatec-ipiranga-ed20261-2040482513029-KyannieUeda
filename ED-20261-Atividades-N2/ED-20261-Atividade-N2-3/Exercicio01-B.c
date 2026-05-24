/* RA: 2040482513029 - Kyannie Risame Ueda da Mata                                 */

/*---------------------------------------------------------------------------------*/
/* FATEC-Ipiranga                                                                  */
/* ADS - Estrutura de Dados                                                        */
/* Id da Atividade: N2-3                                                           */
/* Objetivo: Operadores de Referência, Desreferenciação e Aritmética de PonteirosL */               
/* Autor: Kyannie Risame Ueda da Mata                                              */
/* Data: 21/05/2026                                                                */
/*---------------------------------------------------------------------------------*/

#include <stdio.h>

int main(void) {
    int v[] = {10, 20, 30, 40, 50};
    int tamanho = 5;

    /* --- a) Imprimir cada elemento e seu endereco --- */
    printf("=== a) Elementos e enderecos ===\n");

    int *ptr; /* ponteiro que percorrera o vetor */

    for (ptr = v; ptr < v + tamanho; ptr++) { /* ptr = v: aponta para o primeiro elemento */
        printf("  Endereco: %p  |  Valor: %d\n",
               (void *)ptr,   /* ptr contem o endereco do elemento atual */
               *ptr);         /* * desreferencia ptr: acessa o valor no endereco */
    }

    /* --- b) Soma de todos os elementos --- */
    printf("\n=== b) Soma dos elementos ===\n");

    int soma = 0;
    for (ptr = v; ptr < v + tamanho; ptr++) { /* ptr = v: reinicia no primeiro elemento */
        soma += *ptr; /* * desreferencia ptr: le o valor apontado e acumula na soma */
    }
    printf("  Soma = %d\n", soma);

    /* --- c) Inversao in-place com dois ponteiros --- */
    printf("\n=== c) Inversao in-place ===\n");

    int *inicio = v;              /* inicio aponta para o primeiro elemento do vetor */
    int *fim    = v + tamanho - 1; /* fim aponta para o ultimo elemento do vetor */

    while (inicio < fim) {
        /* Troca usando aritmetica, sem variavel temporaria */
        *inicio = *inicio + *fim; /* * desreferencia ambos: soma e guarda em *inicio */
        *fim    = *inicio - *fim; /* * desreferencia: recupera valor original de *inicio em *fim */
        *inicio = *inicio - *fim; /* * desreferencia: recupera valor original de *fim em *inicio */

        inicio++; /* avanca ponteiro do inicio para o proximo elemento */
        fim--;    /* recua ponteiro do fim para o elemento anterior */
    }

    printf("  Vetor invertido:\n");
    for (ptr = v; ptr < v + tamanho; ptr++) { /* percorre novamente com aritmetica de ponteiros */
        printf("  Endereco: %p  |  Valor: %d\n",
               (void *)ptr, /* endereco do elemento atual */
               *ptr);       /* * desreferencia: valor no endereco apontado */
    }

    return 0;
}
