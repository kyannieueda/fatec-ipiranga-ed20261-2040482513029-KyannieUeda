/* RA: 2040482513029 - Kyannie Risame Ueda da Mata                                 */

/*---------------------------------------------------------------------------------*/
/* FATEC-Ipiranga                                                                  */
/* ADS - Estrutura de Dados                                                        */
/* Id da Atividade: N2-3                                                           */
/* Objetivo: Torres de Hanói Recursivo com Rastreamento                            */               
/*                                                                                 */
/* Autor: Kyannie Risame Ueda da Mata                                              */
/* Data: 22/05/2026                                                                */
/*---------------------------------------------------------------------------------*/

#include <stdio.h>

/*
 * hanoi com parametro 'nivel' para rastrear a profundidade da recursao.
 * Antes de cada movimento imprime o nivel atual, indentado com nivel*2 espacos.
 *
 * Caso base:    n == 0 -> retorna sem imprimir nada.
 * Caso recursivo:
 *   1. Desce um nivel para mover os (n-1) menores para o auxiliar.
 *   2. Imprime o movimento do disco maior com indentacao proporcional ao nivel.
 *   3. Desce um nivel para mover os (n-1) menores do auxiliar para o destino.
 */
void hanoi(int n, char origem, char destino, char auxiliar, int nivel) {
    if (n == 0) return; /* caso base: sem discos, encerra a recursao */

    /* Passo 1: desce na recursao — nivel aumenta */
    hanoi(n - 1, origem, auxiliar, destino, nivel + 1);

    /* Imprime indentacao proporcional: nivel * 2 espacos */
    int i;
    for (i = 0; i < nivel * 2; i++) {
        printf(" ");
    }
    printf("[nivel %d] Mover disco %d: %c -> %c\n", nivel, n, origem, destino);

    /* Passo 3: desce na recursao novamente */
    hanoi(n - 1, auxiliar, destino, origem, nivel + 1);
}

int main(void) {
    printf("=== n = 1 ===\n");
    hanoi(1, 'A', 'C', 'B', 0); /* nivel inicial = 0 (raiz da recursao) */

    printf("\n=== n = 3 ===\n");
    hanoi(3, 'A', 'C', 'B', 0);

    printf("\n=== n = 4 ===\n");
    hanoi(4, 'A', 'C', 'B', 0);

    return 0;
}
