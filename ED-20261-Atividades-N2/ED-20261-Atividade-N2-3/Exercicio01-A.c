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

/*
 * Troca os valores apontados por 'a' e 'b'
 * usando apenas aritmetica de inteiros (soma e subtracao).
 * Sem variavel temporaria, sem XOR.
 */
void trocar(int *a, int *b) {
    *a = *a + *b; /* desreferencia a e b: soma os valores e armazena em *a */
    *b = *a - *b; /* desreferencia: subtrai o antigo *b, recuperando o valor original de *a em *b */
    *a = *a - *b; /* desreferencia: subtrai o novo *b (antigo *a), recuperando o valor original de *b em *a */
}

int main(void) {
    int x = 15;
    int y = 42;

    /* & retorna o endereco de memoria de x e y */
    printf("Enderecos:\n");
    printf("  &x = %p\n", (void *)&x); /* & obtem o endereco de x */
    printf("  &y = %p\n", (void *)&y); /* & obtem o endereco de y */

    printf("\nValores ANTES da troca:\n");
    printf("  x = %d\n", x);
    printf("  y = %d\n", y);

    trocar(&x, &y); /* & passa os enderecos de x e y para a funcao */

    printf("\nValores DEPOIS da troca:\n");
    printf("  x = %d\n", x);
    printf("  y = %d\n", y);

    return 0;
}
