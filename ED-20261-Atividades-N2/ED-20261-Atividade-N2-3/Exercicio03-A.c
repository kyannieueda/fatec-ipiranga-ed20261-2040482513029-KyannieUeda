/* RA: 2040482513029 - Kyannie Risame Ueda da Mata                 */

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
 * hanoi: transfere n discos de 'origem' para 'destino' usando 'auxiliar'.
 *
 * Logica recursiva:
 *   Caso base:    n == 0 -> nada a fazer, retorna.
 *   Caso recursivo:
 *     1. Move os (n-1) discos de cima da origem para o auxiliar.
 *     2. Move o disco maior (disco n) da origem para o destino.
 *     3. Move os (n-1) discos do auxiliar para o destino.
 */
void hanoi(int n, char origem, char destino, char auxiliar) {
    /* Caso base: sem discos, nada a mover */
    if (n == 0) return;

    /* Passo 1: move os (n-1) menores para a haste auxiliar */
    hanoi(n - 1, origem, auxiliar, destino);

    /* Passo 2: move o disco maior para o destino */
    printf("Mover disco %d: %c -> %c\n", n, origem, destino);

    /* Passo 3: move os (n-1) menores do auxiliar para o destino */
    hanoi(n - 1, auxiliar, destino, origem);
}

int main(void) {
    printf("=== n = 1 ===\n");
    hanoi(1, 'A', 'C', 'B');

    printf("\n=== n = 3 ===\n");
    hanoi(3, 'A', 'C', 'B');

    printf("\n=== n = 4 ===\n");
    hanoi(4, 'A', 'C', 'B');

    return 0;
}
