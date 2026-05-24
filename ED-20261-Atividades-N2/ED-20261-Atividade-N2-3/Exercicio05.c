/* RA: 2040482513029 - Kyannie Risame Ueda da Mata                 */

/*---------------------------------------------------------------------------------*/
/* FATEC-Ipiranga                                                                  */
/* ADS - Estrutura de Dados                                                        */
/* Id da Atividade: N2-3                                                           */
/* Objetivo: Construção e Propriedades Estruturais da Árvore                       */               
/* Autor: Kyannie Risame Ueda da Mata                                              */
/* Data: 23/05/2026                                                                */
/*---------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>

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
    /* Caso base: posicao vazia encontrada — cria o novo no */
    if (raiz == NULL) {
        No *novo = (No *)malloc(sizeof(No));
        if (novo == NULL) {
            printf("Erro: malloc falhou.\n");
            exit(1);
        }
        novo->dado = valor;
        novo->esq  = NULL;
        novo->dir  = NULL;
        return novo;
    }

    /* Caso recursivo: decide para qual lado descer */
    if (valor < raiz->dado)
        raiz->esq = inserir(raiz->esq, valor); /* desce para a esquerda */
    else if (valor > raiz->dado)
        raiz->dir = inserir(raiz->dir, valor); /* desce para a direita */
    /* valor == raiz->dado: duplicata ignorada */

    return raiz;
}

/* ============================================================
 * alturaNo
 * Retorna a altura do no: maior caminho ate uma folha descendente.
 * Retorna -1 para ponteiro nulo (convenção: no inexistente).
 * Folha tem altura 0.
 *
 * Caso base:    no == NULL -> retorna -1.
 * Caso recursivo: 1 + max(altura_esq, altura_dir).
 * ============================================================ */
int alturaNo(No *no) {
    if (no == NULL) return -1; /* caso base: no inexistente */

    int alt_esq = alturaNo(no->esq); /* altura da subarvore esquerda */
    int alt_dir = alturaNo(no->dir); /* altura da subarvore direita  */

    int maior = alt_esq > alt_dir ? alt_esq : alt_dir;
    return 1 + maior;
}

/* ============================================================
 * profundidadeNo
 * Retorna a profundidade do no com 'valor': distancia em arestas
 * da raiz ate ele.
 * Retorna -1 se o valor nao existir na arvore.
 *
 * Caso base 1: raiz == NULL -> valor nao encontrado, retorna -1.
 * Caso base 2: raiz->dado == valor -> encontrou, retorna prof.
 * Caso recursivo: desce na direcao correta incrementando prof.
 * ============================================================ */
int profundidadeNo(No *raiz, int valor, int prof) {
    if (raiz == NULL) return -1; /* valor nao existe na arvore */

    if (raiz->dado == valor) return prof; /* encontrou: profundidade atual */

    if (valor < raiz->dado)
        return profundidadeNo(raiz->esq, valor, prof + 1); /* desce esquerda */
    else
        return profundidadeNo(raiz->dir, valor, prof + 1); /* desce direita  */
}

/* ============================================================
 * grauNo
 * Retorna o grau do no: numero de filhos diretos (0, 1 ou 2).
 * ============================================================ */
int grauNo(No *no) {
    if (no == NULL) return 0;
    int grau = 0;
    if (no->esq != NULL) grau++;
    if (no->dir != NULL) grau++;
    return grau;
}

/* ============================================================
 * percursoEmOrdem
 * Percorre a arvore em ordem (esq -> raiz -> dir) e imprime
 * dado, grau de cada no.
 * ============================================================ */
void percursoEmOrdem(No *raiz) {
    if (raiz == NULL) return;
    percursoEmOrdem(raiz->esq);
    printf("  No %2d | grau: %d\n", raiz->dado, grauNo(raiz));
    percursoEmOrdem(raiz->dir);
}

/* ============================================================
 * liberarArvore
 * Libera toda a memoria alocada (pos-ordem: filhos antes do pai).
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
     * Parte C — Verificacao manual (ASCII art da ABB resultante)
     *
     * Insercoes em sequencia: 50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65
     *
     *                     50
     *                   /    \
     *                 30      70
     *                /  \    /  \
     *              20   40  60  80
     *             /  \    \   \
     *            10  25   45  65
     *
     * Verificacao manual para 3 nos:
     *
     * No 50 (raiz):
     *   - Profundidade: 0 (eh a raiz, sem arestas acima)
     *   - Altura: 3 (caminho mais longo: 50->30->20->10 ou 50->30->40->45)
     *   - Grau: 2 (tem filho esq=30 e filho dir=70)
     *
     * No 30:
     *   - Profundidade: 1 (50 -> 30)
     *   - Altura: 2 (caminho: 30->20->10 ou 30->40->45)
     *   - Grau: 2 (filhos: 20 e 40)
     *
     * No 10 (folha):
     *   - Profundidade: 3 (50->30->20->10)
     *   - Altura: 0 (folha, sem descendentes)
     *   - Grau: 0 (sem filhos)
     */

    No *raiz = NULL;

    /* Construcao da ABB com os valores em sequencia */
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};
    int total = 11;
    int i;
    for (i = 0; i < total; i++)
        raiz = inserir(raiz, valores[i]);

    /* ----------------------------------------------------------
     * Parte B-a: Altura dos nos 50, 30, 70, 20, 10
     * ---------------------------------------------------------- */
    printf("=== Parte B-a: Altura dos nos ===\n");
    int nos_altura[] = {50, 30, 70, 20, 10};
    int qtd_a = 5;
    for (i = 0; i < qtd_a; i++) {
        /* Para calcular alturaNo de um valor especifico,
           precisamos encontrar o ponteiro do no primeiro */
        /* Usamos profundidade para confirmar existencia e
           uma funcao auxiliar inline de busca */
        No *cur = raiz;
        while (cur != NULL && cur->dado != nos_altura[i]) {
            if (nos_altura[i] < cur->dado) cur = cur->esq;
            else                           cur = cur->dir;
        }
        printf("  alturaNo(%2d) = %d\n", nos_altura[i], alturaNo(cur));
    }

    /* ----------------------------------------------------------
     * Parte B-b: Profundidade dos nos 50, 30, 70, 45, 10
     * ---------------------------------------------------------- */
    printf("\n=== Parte B-b: Profundidade dos nos ===\n");
    int nos_prof[] = {50, 30, 70, 45, 10};
    int qtd_b = 5;
    for (i = 0; i < qtd_b; i++)
        printf("  profundidadeNo(%2d) = %d\n",
               nos_prof[i], profundidadeNo(raiz, nos_prof[i], 0));

    /* ----------------------------------------------------------
     * Parte B-c: Grau de cada no (percurso em-ordem)
     * ---------------------------------------------------------- */
    printf("\n=== Parte B-c: Grau de cada no (em-ordem) ===\n");
    percursoEmOrdem(raiz);

    /* ----------------------------------------------------------
     * Parte B-d: Altura total da arvore
     * ---------------------------------------------------------- */
    printf("\n=== Parte B-d: Altura total da arvore ===\n");
    printf("  Altura da arvore = %d\n", alturaNo(raiz));

    /* ----------------------------------------------------------
     * Libera toda a memoria alocada
     * ---------------------------------------------------------- */
    liberarArvore(raiz);
    raiz = NULL;

    return 0;
}
