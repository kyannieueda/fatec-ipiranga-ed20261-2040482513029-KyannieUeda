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

/* Contador global — incrementado a cada movimento real */
int contador = 0;

void hanoi(int n, char origem, char destino, char auxiliar) {
    if (n == 0) return;

    hanoi(n - 1, origem, auxiliar, destino);

    printf("Mover disco %d: %c -> %c\n", n, origem, destino);
    contador++; /* contabiliza cada movimento realizado */

    hanoi(n - 1, auxiliar, destino, origem);
}

int main(void) {
    int n;

    /*
     * Tabela de complexidade:
     * n | Movimentos (contado) | 2^n - 1 (esperado)
     * --+---------------------+-------------------
     * 1 |          1          |         1
     * 2 |          3          |         3
     * 3 |          7          |         7
     * 4 |         15          |        15
     * 5 |         31          |        31
     * 6 |         63          |        63
     *
     * Conclusao: o numero de movimentos cresce exponencialmente — O(2^n).
     * A cada disco adicionado, o trabalho dobra mais um movimento.
     */

    printf("%-4s %-22s %-20s\n", "n", "Movimentos (contado)", "2^n - 1 (esperado)");
    printf("-------------------------------------------------------\n");

    for (n = 1; n <= 6; n++) {
        contador = 0;          /* zera o contador antes de cada teste */
        hanoi(n, 'A', 'C', 'B');

        int esperado = (1 << n) - 1; /* 2^n - 1 usando deslocamento de bits */
        printf("%-4d %-22d %-20d\n", n, contador, esperado);
    }

    return 0;
}
