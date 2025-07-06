// funcoesAVL.c
// Implementação das funções para manipulação da Árvore AVL,
// incluindo inserção, remoção, rotações e balanceamento.

#include <stdio.h>
#include <stdlib.h>

#include "funcoesAVL.h"
#include "../Utils/matematicas.h"

struct NodeAVL* inserirAVL(struct NodeAVL* raiz, int valor) {
    if (raiz == NULL) {
        struct NodeAVL* novo = (struct NodeAVL*)malloc(sizeof(struct NodeAVL));
        novo->valor = valor;
        novo->altura = 0;
        novo->filhoEsq = NULL;
        novo->filhoDir = NULL;
        return novo;
    }

    if (valor < raiz->valor)
        raiz->filhoEsq = inserirAVL(raiz->filhoEsq, valor);
    else if (valor > raiz->valor)
        raiz->filhoDir = inserirAVL(raiz->filhoDir, valor);
    else
        return raiz; // Não permite valores duplicados

    // Atualiza altura do nó atual
    raiz->altura = 1 + max(alturaAVL(raiz->filhoEsq), alturaAVL(raiz->filhoDir));

    // Verifica fator de balanceamento
    int fb = fatorBalanceamentoAVL(raiz);

    // Casos de desbalanceamento
    if (fb > 1 && valor < raiz->filhoEsq->valor) // Esquerda-Esquerda
        return rotacaoDireitaAVL(raiz);

    if (fb < -1 && valor > raiz->filhoDir->valor) // Direita-Direita
        return rotacaoEsquerdaAVL(raiz);

    if (fb > 1 && valor > raiz->filhoEsq->valor) { // Esquerda-Direita
        raiz->filhoEsq = rotacaoEsquerdaAVL(raiz->filhoEsq);
        return rotacaoDireitaAVL(raiz);
    }

    if (fb < -1 && valor < raiz->filhoDir->valor) { // Direita-Esquerda
        raiz->filhoDir = rotacaoDireitaAVL(raiz->filhoDir);
        return rotacaoEsquerdaAVL(raiz);
    }

    return raiz; // Retorna a raiz (sem alterações de estrutura)
}

struct NodeAVL* removerAVL(struct NodeAVL* raiz, int valor) {
    if (raiz == NULL)
        return NULL;

    // Busca normal em ABB
    if (valor < raiz->valor)
        raiz->filhoEsq = removerAVL(raiz->filhoEsq, valor);
    else if (valor > raiz->valor)
        raiz->filhoDir = removerAVL(raiz->filhoDir, valor);
    else {
        // Nó com um ou nenhum filho
        if (raiz->filhoEsq == NULL || raiz->filhoDir == NULL) {
            struct NodeAVL* temp = raiz->filhoEsq ? raiz->filhoEsq : raiz->filhoDir;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp; // Copia conteúdo do filho
            }

            free(temp);
        }
        // Nó com dois filhos
        else {
            struct NodeAVL* temp = sucessorAVL(raiz->filhoDir);
            raiz->valor = temp->valor;
            raiz->filhoDir = removerAVL(raiz->filhoDir, temp->valor);
        }
    }

    // Se a árvore ficou vazia após a remoção
    if (raiz == NULL)
        return NULL;

    // Atualiza altura
    raiz->altura = 1 + max(alturaAVL(raiz->filhoEsq), alturaAVL(raiz->filhoDir));

    // Verifica fator de balanceamento
    int fb = fatorBalanceamentoAVL(raiz);

    // Casos de rebalanceamento

    // Esquerda-Esquerda
    if (fb > 1 && fatorBalanceamentoAVL(raiz->filhoEsq) >= 0)
        return rotacaoDireitaAVL(raiz);

    // Esquerda-Direita
    if (fb > 1 && fatorBalanceamentoAVL(raiz->filhoEsq) < 0) {
        raiz->filhoEsq = rotacaoEsquerdaAVL(raiz->filhoEsq);
        return rotacaoDireitaAVL(raiz);
    }

    // Direita-Direita
    if (fb < -1 && fatorBalanceamentoAVL(raiz->filhoDir) <= 0)
        return rotacaoEsquerdaAVL(raiz);

    // Direita-Esquerda
    if (fb < -1 && fatorBalanceamentoAVL(raiz->filhoDir) > 0) {
        raiz->filhoDir = rotacaoDireitaAVL(raiz->filhoDir);
        return rotacaoEsquerdaAVL(raiz);
    }

    return raiz;
}

struct NodeAVL* buscarAVL(struct NodeAVL* raiz, int valor) {
    if (raiz == NULL)
        return NULL; 

    if (valor == raiz->valor)
        return raiz;   // Valor encontrado

    if (valor < raiz->valor)
        return buscarAVL(raiz->filhoEsq, valor);
    else
        return buscarAVL(raiz->filhoDir, valor);
}

int alturaAVL(struct NodeAVL* no) {
    if (no == NULL)
    return -1;
    return no->altura;
}

// Funcoes de balanceamento
int fatorBalanceamentoAVL(struct NodeAVL* no) {
    if (no == NULL)
    return 0;
    return alturaAVL(no->filhoEsq) - alturaAVL(no->filhoDir);
}

struct NodeAVL* rotacaoDireitaAVL(struct NodeAVL* y) {
    struct NodeAVL* x = y->filhoEsq;
    struct NodeAVL* T2 = x->filhoDir;

    x->filhoDir = y;
    y->filhoEsq = T2;

    y->altura = 1 + max(alturaAVL(y->filhoEsq), alturaAVL(y->filhoDir));
    x->altura = 1 + max(alturaAVL(x->filhoEsq), alturaAVL(x->filhoDir));

    return x;
}

struct NodeAVL* rotacaoEsquerdaAVL(struct NodeAVL* x) {
    struct NodeAVL* y = x->filhoDir;
    struct NodeAVL* T2 = y->filhoEsq;

    y->filhoEsq = x;
    x->filhoDir = T2;

    x->altura = 1 + max(alturaAVL(x->filhoEsq), alturaAVL(x->filhoDir));
    y->altura = 1 + max(alturaAVL(y->filhoEsq), alturaAVL(y->filhoDir));

    return y;
}

// Utilitarios
void destruirArvoreAVL(struct NodeAVL* raiz) {
    if (raiz == NULL)
        return;

    destruirArvoreAVL(raiz->filhoEsq);
    destruirArvoreAVL(raiz->filhoDir);
    free(raiz);
}

struct NodeAVL* sucessorAVL(struct NodeAVL* no) {
    struct NodeAVL* atual = no;
    while (atual && atual->filhoEsq != NULL)
        atual = atual->filhoEsq;
    return atual;
}

void preOrdemAVL(struct NodeAVL* raiz) {
    if (raiz == NULL)
        return;
    printf("%d ", raiz->valor);
    preOrdemAVL(raiz->filhoEsq);
    preOrdemAVL(raiz->filhoDir);
}

void posOrdemAVL(struct NodeAVL* raiz) {
    if (raiz == NULL)
        return;
    posOrdemAVL(raiz->filhoEsq);
    posOrdemAVL(raiz->filhoDir);
    printf("%d ", raiz->valor);
}

void inOrdemAVL(struct NodeAVL* raiz) {
    if (raiz == NULL)
        return;
    inOrdemAVL(raiz->filhoEsq);
    printf("%d ", raiz->valor);
    inOrdemAVL(raiz->filhoDir);
}