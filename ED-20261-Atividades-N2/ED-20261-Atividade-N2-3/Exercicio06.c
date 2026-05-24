/* RA: 2040482513029 - Kyannie Risame Ueda da Mata                                 */

/*---------------------------------------------------------------------------------*/
/* FATEC-Ipiranga                                                                  */
/* ADS - Estrutura de Dados                                                        */
/* Id da Atividade: N2-3                                                           */
/* Objetivo: Ancestrais, Descendentes e Relatorio Completo de um No                */
/* Autor: Kyannie Risame Ueda da Mata                                              */
/* Data: 23/05/2026                                                                */
/*---------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================================
 * Estrutura do No
 * ============================================================ */
typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

/* ============================================================
 * inserir
 * Insere 'valor' na ABB respeitando a propriedade:
 *   - valores menores vao para a esquerda
 *   - valores maiores vao para a direita
 * Retorna o ponteiro para a raiz (nova ou existente).
 * ============================================================ */
No *inserir(No *raiz, int valor) {
    if (raiz == NULL) {
        No *novo = (No *)malloc(sizeof(No));
        if (novo == NULL) { printf("Erro: malloc falhou.\n"); exit(1); }
        novo->dado = valor;
        novo->esq  = NULL;
        novo->dir  = NULL;
        return novo;
    }
    if (valor < raiz->dado)      raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->dado) raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

/* ============================================================
 * alturaNo
 * Retorna -1 para ponteiro nulo; 0 para folha.
 * ============================================================ */
int alturaNo(No *no) {
    if (no == NULL) return -1;
    int ae = alturaNo(no->esq);
    int ad = alturaNo(no->dir);
    return 1 + (ae > ad ? ae : ad);
}

/* ============================================================
 * profundidadeNo
 * Retorna -1 se o valor nao existir na arvore.
 * ============================================================ */
int profundidadeNo(No *raiz, int valor, int prof) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return prof;
    if (valor < raiz->dado) return profundidadeNo(raiz->esq, valor, prof + 1);
    else                    return profundidadeNo(raiz->dir, valor, prof + 1);
}

/* ============================================================
 * grauNo
 * Retorna o numero de filhos diretos (0, 1 ou 2).
 * ============================================================ */
int grauNo(No *no) {
    if (no == NULL) return 0;
    int g = 0;
    if (no->esq != NULL) g++;
    if (no->dir != NULL) g++;
    return g;
}

/* ============================================================
 * buscarNo
 * Busca e retorna o ponteiro para o no com 'valor', ou NULL.
 * ============================================================ */
No *buscarNo(No *raiz, int valor) {
    if (raiz == NULL) return NULL;
    if (raiz->dado == valor) return raiz;
    if (valor < raiz->dado) return buscarNo(raiz->esq, valor);
    else                    return buscarNo(raiz->dir, valor);
}

/* ============================================================
 * _ancestralRec (funcao auxiliar interna)
 * Logica recursiva para imprimir ancestrais.
 *
 * Estrategia recursiva:
 *   - Caso base 1: raiz == NULL -> valor nao existe, retorna 0.
 *   - Caso base 2: raiz->dado == valor -> chegou no proprio no,
 *                  retorna 1 sem imprimir.
 *   - Caso recursivo: desce na direcao correta; se encontrou,
 *                     o no atual EH ancestral — imprime e propaga.
 * Retorna 1 se o valor foi encontrado na subarvore, 0 caso contrario.
 * ============================================================ */
static int _ancestralRec(No *raiz, int valor) {
    if (raiz == NULL) return 0;                  /* caso base 1: nao encontrou */
    if (raiz->dado == valor) return 1;           /* caso base 2: chegou no no  */

    int encontrou = 0;
    if (valor < raiz->dado)
        encontrou = _ancestralRec(raiz->esq, valor);
    else
        encontrou = _ancestralRec(raiz->dir, valor);

    if (encontrou)
        printf("%d ", raiz->dado);               /* este no e ancestral        */

    return encontrou;
}

/* ============================================================
 * imprimirAncestral
 * Assinatura exata exigida pelo professor.
 * Imprime todos os ancestrais do no com 'valor',
 * do pai ate a raiz (ordem crescente de profundidade).
 * ============================================================ */
void imprimirAncestral(No *raiz, int valor) {
    _ancestralRec(raiz, valor);
}

/* ============================================================
 * montarAncestralStr
 * Monta a lista de ancestrais em uma string para uso no relatorio.
 * Retorna 1 se encontrou, 0 caso contrario.
 * ============================================================ */
int montarAncestralStr(No *raiz, int valor, char *buf, int buflen) {
    if (raiz == NULL) return 0;
    if (raiz->dado == valor) return 1;

    int encontrou = 0;
    if (valor < raiz->dado)
        encontrou = montarAncestralStr(raiz->esq, valor, buf, buflen);
    else
        encontrou = montarAncestralStr(raiz->dir, valor, buf, buflen);

    if (encontrou) {
        char tmp[16];
        snprintf(tmp, sizeof(tmp), "%d ", raiz->dado);
        strncat(buf, tmp, buflen - strlen(buf) - 1);
    }
    return encontrou;
}

/* ============================================================
 * montarDescendentesStr (percurso em-ordem)
 * Monta os descendentes da subarvore de 'no' em uma string.
 * ============================================================ */
void montarDescendentesStr(No *no, char *buf, int buflen) {
    if (no == NULL) return;
    montarDescendentesStr(no->esq, buf, buflen);
    char tmp[16];
    snprintf(tmp, sizeof(tmp), "%d ", no->dado);
    strncat(buf, tmp, buflen - strlen(buf) - 1);
    montarDescendentesStr(no->dir, buf, buflen);
}

/* ============================================================
 * imprimirDescendentes (percurso em-ordem)
 * Imprime todos os descendentes do no com 'valor'.
 * ============================================================ */
void imprimirDescendentesEmOrdem(No *no) {
    if (no == NULL) return;
    imprimirDescendentesEmOrdem(no->esq);
    printf("%d ", no->dado);
    imprimirDescendentesEmOrdem(no->dir);
}

void imprimirDescendentes(No *raiz, int valor) {
    No *alvo = buscarNo(raiz, valor);
    if (alvo == NULL) return;
    imprimirDescendentesEmOrdem(alvo->esq);
    imprimirDescendentesEmOrdem(alvo->dir);
}

/* ============================================================
 * contarDescendentes
 * Conta todos os nos da subarvore de 'no'.
 *
 * Caso base:    no == NULL -> retorna 0.
 * Caso recursivo: 1 (no atual) + descendentes esq + descendentes dir.
 * ============================================================ */
int contarDescendentes(No *no) {
    if (no == NULL) return 0;
    return 1 + contarDescendentes(no->esq) + contarDescendentes(no->dir);
}

/* ============================================================
 * relatorioNo
 * Imprime o relatorio estrutural completo de um no.
 * ============================================================ */
void relatorioNo(No *raiz, int valor) {
    No *alvo = buscarNo(raiz, valor);

    if (alvo == NULL) {
        printf("+----------------------------------+\n");
        printf("| ERRO: No %d nao encontrado       |\n", valor);
        printf("+----------------------------------+\n\n");
        return;
    }

    int prof   = profundidadeNo(raiz, valor, 0);
    int altura = alturaNo(alvo);
    int grau   = grauNo(alvo);
    int qtd    = contarDescendentes(alvo->esq) + contarDescendentes(alvo->dir);

    /* Monta strings para ancestrais e descendentes */
    char buf_anc[256] = "";
    char buf_desc[256] = "";

    if (prof == 0) {
        strncpy(buf_anc, "(nenhum - raiz)", sizeof(buf_anc) - 1);
    } else {
        montarAncestralStr(raiz, valor, buf_anc, sizeof(buf_anc));
        /* remove espaco final */
        int len = strlen(buf_anc);
        if (len > 0 && buf_anc[len - 1] == ' ') buf_anc[len - 1] = '\0';
    }

    if (qtd == 0) {
        strncpy(buf_desc, "(nenhum - folha)", sizeof(buf_desc) - 1);
    } else {
        montarDescendentesStr(alvo->esq, buf_desc, sizeof(buf_desc));
        montarDescendentesStr(alvo->dir, buf_desc, sizeof(buf_desc));
        int len = strlen(buf_desc);
        if (len > 0 && buf_desc[len - 1] == ' ') buf_desc[len - 1] = '\0';
    }

    printf("+----------------------------------+\n");
    printf("| RELATORIO DO NO: %-15d |\n", valor);
    printf("+----------------------------------+\n");
    printf("| Profundidade : %-17d |\n", prof);
    printf("| Altura       : %-17d |\n", altura);
    printf("| Grau         : %-17d |\n", grau);
    printf("| Ancestrais   : %-17s |\n", buf_anc);
    printf("| Descendentes : %-17s |\n", buf_desc);
    printf("| Qtd Descend. : %-17d |\n", qtd);
    printf("+----------------------------------+\n\n");
}

/* ============================================================
 * liberarArvore
 * ============================================================ */
void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

/* ============================================================
 * MAIN
 * ============================================================ */
int main(void) {

    /*
     * ABB resultante apos insercoes: 50,30,70,20,40,60,80,10,25,45,65
     *
     *                     50
     *                   /    \
     *                 30      70
     *                /  \    /  \
     *              20   40  60  80
     *             /  \    \    \
     *            10  25   45   65
     *
     * Verificacao manual:
     *   No 50 (raiz): ancestrais=(nenhum), descendentes=todos, qtd=10
     *   No 30: ancestrais={50}, descendentes={10,20,25,40,45}, qtd=5
     *   No 10 (folha): ancestrais={20,30,50}, descendentes=(nenhum), qtd=0
     *   No 70: ancestrais={50}, descendentes={60,65,80}, qtd=3
     */

    No *raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};
    int total = 11;
    int i;
    for (i = 0; i < total; i++)
        raiz = inserir(raiz, valores[i]);

    /* Parte C: teste sistematico */
    relatorioNo(raiz, 50);  /* raiz             */
    relatorioNo(raiz, 30);  /* no intermediario */
    relatorioNo(raiz, 10);  /* folha            */
    relatorioNo(raiz, 70);  /* no intermediario */

    /* Teste com valor inexistente */
    relatorioNo(raiz, 99);

    liberarArvore(raiz);
    raiz = NULL;

    return 0;
}
