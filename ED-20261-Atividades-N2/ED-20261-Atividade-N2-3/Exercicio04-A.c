/* RA: 2040482513029 - Kyannie Risame Ueda da Mata                                  */

/*---------------------------------------------------------------------------------*/
/* FATEC-Ipiranga                                                                  */
/* ADS - Estrutura de Dados                                                        */
/* Id da Atividade: N2-3                                                           */
/* Objetivo: Busca Binária Recursiva e Potenciação Rápida                          */               
/* Autor: Kyannie Risame Ueda da Mata                                              */
/* Data: 22/05/2026                                                                */
/*---------------------------------------------------------------------------------*/
#include <stdio.h>

/* Variavel estatica para contar chamadas recursivas por busca */
static int chamadas = 0;

/*
 * buscaBinaria: retorna o indice do elemento se encontrado, ou -1.
 * O vetor deve estar ordenado em ordem crescente.
 *
 * Caso base 1: inicio > fim  -> elemento nao existe, retorna -1.
 * Caso base 2: vet[meio] == alvo -> elemento encontrado, retorna meio.
 * Caso recursivo:
 *   - Se alvo < vet[meio]: busca na metade esquerda (inicio ate meio-1).
 *   - Se alvo > vet[meio]: busca na metade direita (meio+1 ate fim).
 */
int buscaBinaria(int *vet, int inicio, int fim, int alvo) {
    chamadas++; /* conta cada chamada recursiva */

    /* Caso base 1: espaco de busca esgotado */
    if (inicio > fim) return -1;

    int meio = (inicio + fim) / 2;

    /* Caso base 2: elemento encontrado no meio */
    if (*(vet + meio) == alvo) return meio; /* * desreferencia: acessa vet[meio] via ponteiro */

    /* Caso recursivo: descarta metade do vetor */
    if (alvo < *(vet + meio))                        /* alvo esta na metade esquerda */
        return buscaBinaria(vet, inicio, meio - 1, alvo);
    else                                             /* alvo esta na metade direita */
        return buscaBinaria(vet, meio + 1, fim, alvo);
}

int main(void) {
    int dados[] = {2, 5, 8, 12, 16, 23, 38, 45, 72, 91};
    int n = 10;

    printf("Vetor: ");
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", *(dados + i)); /* * aritmetica de ponteiros: acessa dados[i] */
    printf("\n\n");

    int alvo, resultado;

    /* Busca 1: elemento PRESENTE no meio do vetor (23) */
    alvo = 23;
    chamadas = 0;
    resultado = buscaBinaria(dados, 0, n - 1, alvo);
    if (resultado != -1)
        printf("Busca por %2d -> encontrado no indice %d | chamadas: %d\n", alvo, resultado, chamadas);
    else
        printf("Busca por %2d -> nao encontrado           | chamadas: %d\n", alvo, chamadas);

    /* Busca 2: elemento AUSENTE (99) */
    alvo = 99;
    chamadas = 0;
    resultado = buscaBinaria(dados, 0, n - 1, alvo);
    if (resultado != -1)
        printf("Busca por %2d -> encontrado no indice %d | chamadas: %d\n", alvo, resultado, chamadas);
    else
        printf("Busca por %2d -> nao encontrado           | chamadas: %d\n", alvo, chamadas);

    /* Busca 3: PRIMEIRO elemento do vetor (2) */
    alvo = 2;
    chamadas = 0;
    resultado = buscaBinaria(dados, 0, n - 1, alvo);
    if (resultado != -1)
        printf("Busca por %2d -> encontrado no indice %d | chamadas: %d\n", alvo, resultado, chamadas);
    else
        printf("Busca por %2d -> nao encontrado           | chamadas: %d\n", alvo, chamadas);

    return 0;
}
