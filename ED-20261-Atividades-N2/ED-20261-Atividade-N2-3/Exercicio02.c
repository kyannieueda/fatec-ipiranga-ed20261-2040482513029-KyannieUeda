/* RA: 2040482513029 - Kyannie Risame Ueda da Mata                 */

/*---------------------------------------------------------------------------------*/
/* FATEC-Ipiranga                                                                  */
/* ADS - Estrutura de Dados                                                        */
/* Id da Atividade: N2-3                                                           */
/* Objetivo: Ponteiro com Array e Passagem de Ponteiro em Funções                  */               
/* Autor: Kyannie Risame Ueda da Mata                                              */
/* Data: 21/05/2026                                                                */
/*---------------------------------------------------------------------------------*/

#include <stdio.h>

/* ------------------------------------------------------------
 * calcularMedia
 * Percorre o vetor via incremento de ponteiro, acumula a soma
 * e retorna a media aritmetica.
 * ------------------------------------------------------------ */
float calcularMedia(float *vet, int n) {
    float soma = 0.0f;
    float *ptr;                          /* ponteiro auxiliar de iteracao */

    for (ptr = vet; ptr < vet + n; ptr++) { /* ptr = vet: inicia no primeiro elemento */
        soma += *ptr;                       /* * desreferencia ptr: le o valor apontado */
    }

    return soma / (float)n;
}

/* ------------------------------------------------------------
 * encontrarExtremos
 * Escreve diretamente nos enderecos apontados por 'maior' e
 * 'menor' — nao retorna valores, altera via ponteiro.
 * ------------------------------------------------------------ */
void encontrarExtremos(float *vet, int n, float *maior, float *menor) {
    *maior = *vet; /* * desreferencia vet: inicializa *maior com o primeiro elemento */
    *menor = *vet; /* * desreferencia vet: inicializa *menor com o primeiro elemento */

    float *ptr;
    for (ptr = vet + 1; ptr < vet + n; ptr++) { /* começa no segundo elemento */
        if (*ptr > *maior) {  /* * desreferencia ptr: compara valor atual com o maior */
            *maior = *ptr;    /* * desreferencia maior: atualiza o maior no endereco recebido */
        }
        if (*ptr < *menor) {  /* * desreferencia ptr: compara valor atual com o menor */
            *menor = *ptr;    /* * desreferencia menor: atualiza o menor no endereco recebido */
        }
    }
}

/* ------------------------------------------------------------
 * normalizar
 * Divide cada elemento pelo valor maximo, alterando o vetor
 * ORIGINAL — porque o ponteiro aponta para o mesmo espaco de
 * memoria do vetor declarado em main (passagem por referencia).
 *
 * Por que o vetor original e alterado?
 * Em C, ao passar um array para uma funcao, o que e passado e
 * o ENDERECO do primeiro elemento. Assim, 'vet' dentro desta
 * funcao aponta para a mesma regiao de memoria que 'notas' em
 * main. Qualquer escrita via *ptr modifica diretamente os dados
 * originais — nao ha copia do conteudo do vetor.
 * ------------------------------------------------------------ */
void normalizar(float *vet, int n) {
    float maior, menor_ignorado;
    encontrarExtremos(vet, n, &maior, &menor_ignorado); /* & passa endereco das variaveis locais */
    (void)menor_ignorado;

    float *ptr;
    for (ptr = vet; ptr < vet + n; ptr++) { /* ptr = vet: inicia no primeiro elemento */
        *ptr = *ptr / maior; /* * desreferencia ptr: le e ESCREVE o valor normalizado no endereco */
    }
}

/* ------------------------------------------------------------
 * imprimirVetor
 * Percorre e exibe cada elemento com dois decimais.
 * ------------------------------------------------------------ */
void imprimirVetor(float *vet, int n, const char *titulo) {
    printf("\n[ %s ]\n", titulo);

    float *ptr;
    int i = 1;
    for (ptr = vet; ptr < vet + n; ptr++, i++) { /* ptr = vet: percorre do inicio ao fim */
        printf("  [%d] %.4f\n", i, *ptr); /* * desreferencia ptr: le o valor para impressao */
    }
}

/* ============================================================ */
int main(void) {
    float notas[] = {7.5f, 3.2f, 9.8f, 6.0f, 5.5f, 8.1f};
    int n = 6;

    /* 1. Exibe o vetor ANTES de normalizar */
    imprimirVetor(notas, n, "Notas ANTES de normalizar");

    /* 2. Calcula e exibe media, maior e menor ANTES de normalizar */
    float media = calcularMedia(notas, n);   /* passa ponteiro para o inicio do vetor */

    float maior, menor;
    encontrarExtremos(notas, n, &maior, &menor); /* & passa enderecos de 'maior' e 'menor' */

    printf("\n  Media  : %.4f\n", media);
    printf("  Maior  : %.4f\n", maior);
    printf("  Menor  : %.4f\n", menor);

    /* 3. Normaliza o vetor original */
    normalizar(notas, n); /* passa o endereco do primeiro elemento — altera o vetor original */

    /* 4. Exibe o vetor DEPOIS de normalizar — prova que o original foi modificado */
    imprimirVetor(notas, n, "Notas DEPOIS de normalizar (vetor original alterado)");

    /*
     * Demonstracao: o vetor 'notas' em main foi modificado porque
     * normalizar() recebeu o ENDERECO do primeiro elemento (&notas[0]).
     * Todo acesso via *ptr dentro da funcao leu e escreveu diretamente
     * na memoria de 'notas' — sem criar nenhuma copia dos dados.
     */

    return 0;
}
