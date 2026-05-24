/* RA: 2040482513029 - Kyannie Risame Ueda da Mata                                 */

/*---------------------------------------------------------------------------------*/
/* FATEC-Ipiranga                                                                  */
/* ADS - Estrutura de Dados                                                        */
/* Id da Atividade: N2-3                                                           */
/* Objetivo: Busca Binária Recursiva e Potenciação Rápida                          */               
/* Autor: Kyannie Risame Ueda da Mata                                              */
/* Data: 22/05/2026                                                                */
/*---------------------------------------------------------------------------------*/

#include <stdio.h>

/* Contadores globais para comparar as duas abordagens */
static int chamadas_rapida = 0;
static int chamadas_ingenua = 0;

/*
 * potenciaRapida: calcula base^exp recursivamente em O(log exp).
 *
 * Caso base:    exp == 0 -> qualquer numero elevado a 0 eh 1.
 * Caso recursivo par:  base^exp = (base^(exp/2))^2
 *   -> divide o expoente pela metade, reduzindo chamadas pela metade.
 * Caso recursivo impar: base^exp = base * base^(exp-1)
 *   -> subtrai 1 para tornar par e aplica a regra acima na proxima chamada.
 *
 * Complexidade: O(log exp) — a cada dois passos o expoente cai pela metade.
 */
long long potenciaRapida(long long base, int exp) {
    chamadas_rapida++;

    /* Caso base: exp == 0 */
    if (exp == 0) return 1;

    /* Caso recursivo par: b^exp = (b^(exp/2))^2 */
    if (exp % 2 == 0) {
        long long metade = potenciaRapida(base, exp / 2);
        return metade * metade;
    }

    /* Caso recursivo impar: b^exp = b * b^(exp-1) */
    return base * potenciaRapida(base, exp - 1);
}

/*
 * potenciaIngenua: calcula base^exp recursivamente em O(exp).
 *
 * Caso base:    exp == 0 -> retorna 1.
 * Caso recursivo: base^exp = base * base^(exp-1)
 *   -> decrementa 1 por chamada — muito mais lento para expoentes grandes.
 *
 * Complexidade: O(exp) — numero de chamadas igual ao proprio expoente.
 */
long long potenciaIngenua(long long base, int exp) {
    chamadas_ingenua++;

    /* Caso base */
    if (exp == 0) return 1;

    /* Caso recursivo: reduz expoente em 1 a cada chamada */
    return base * potenciaIngenua(base, exp - 1);
}

/* Funcao auxiliar: roda os dois e exibe a comparacao */
void testar(long long base, int exp) {
    chamadas_rapida = 0;
    chamadas_ingenua = 0;

    long long res_rapida  = potenciaRapida(base, exp);
    long long res_ingenua = potenciaIngenua(base, exp);

    printf("%lld^%-2d = %-12lld | rapida: %2d chamadas | ingenua: %2d chamadas\n",
           base, exp, res_rapida, chamadas_rapida, chamadas_ingenua);

    /* Sanidade: os dois devem retornar o mesmo resultado */
    if (res_rapida != res_ingenua)
        printf("  [ERRO] resultados divergem!\n");
}

int main(void) {
    printf("%-20s %-20s %-20s\n",
           "Calculo", "Rapida (O(log n))", "Ingenua (O(n))");
    printf("--------------------------------------------------------------\n");

    testar(2,  10);  /* 2^10  = 1024          */
    testar(3,  7);   /* 3^7   = 2187          */
    testar(5,  0);   /* 5^0   = 1 (caso base) */
    testar(7,  12);  /* 7^12  = 13841287201   */

    /*
     * Comparacao de chamadas recursivas:
     *
     * 2^10: rapida usa  4 chamadas  (log2(10) ~ 4)
     *       ingenua usa 11 chamadas (expoente + 1)
     *
     * 7^12: rapida usa  5 chamadas  (log2(12) ~ 4, mais ajustes impares)
     *       ingenua usa 13 chamadas
     *
     * Conclusao: para expoentes grandes a diferenca e enorme.
     * Ex: base^1000 -> rapida ~10 chamadas vs ingenua 1001 chamadas.
     */

    return 0;
}
