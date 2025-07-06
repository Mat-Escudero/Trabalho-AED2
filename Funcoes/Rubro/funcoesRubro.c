// funcoesRubro.c
// Implementação das funções para manipulação da Árvore Rubro-Negra,
// incluindo inserção, remoção, rotações e balanceamento.

#include <stdio.h>
#include <stdlib.h>

#include "funcoesRubro.h"

struct NodeRN* inserirRN(struct NodeRN* raiz, int valor) {
    if (raiz == NULL) {
        raiz = novoNoRN(valor);
        raiz->cor = PRETO;
        return raiz;
    }
    struct NodeRN* x = raiz;
    struct NodeRN* y = NULL;

    while (x != NULL) {
        if (x->valor == valor) {
            return raiz;
        }
        if (x->valor > valor) {
            y = x;
            x = x->esq;
        }
        else if (x->valor < valor) {
            y = x;
            x = x->dir;
        }
    }
    x = novoNoRN(valor);
    x->pai = y;

    if (y->valor > valor) {
        y->esq = x;
    }
    if (y->valor < valor) {
        y->dir = x;
    }

    if (y->cor == PRETO) {
        return raiz;
    }
    if (y->cor == VERMELHO) {
       raiz = balancearInsercaoRN(raiz, x);
    }
    return raiz;
}

struct NodeRN* buscarRN(struct NodeRN* raiz, int valor) {
    struct NodeRN* x = raiz;
    while (x != NULL && x->valor != valor) {
        if (x->valor > valor) {
            x = x->esq;
        }
        else if (x->valor < valor) {
            x = x->dir;
        }
    }
    if (x == NULL) {
        return NULL;
    }
    return x;
}

struct NodeRN* removerRN(struct NodeRN* raiz, struct NodeRN* remover, int valor) {
    if (remover == NULL) {
        remover = buscarRN(raiz, valor);
    }
    if (remover == NULL) {
        return raiz;
    }

    if (remover->esq == NULL && remover->dir == NULL) {
        // Verifica se é a raiz
        if (remover->pai == NULL) {
            free(remover);
            return NULL;
        }
    
        // Guarda o pai antes de liberar
        struct NodeRN* pai = remover->pai;
        
        if (pai->esq == remover) pai->esq = NULL;
        else pai->dir = NULL;
        // Se for vermelho, só remover
        if (remover->cor == VERMELHO) {
            free(remover);
            return raiz;
        }
        free(remover);
        // Se for preto, balancear
        // Desconecta do pai
        // Aqui, x é NULL, mas o pai ainda existe
        raiz = balancearRemocaoRN(raiz, NULL, pai);  // Nova assinatura com pai
        return raiz;
    } 
    else if (remover->esq == NULL && remover->dir != NULL) {
        struct NodeRN* filho = remover->dir;
        // Verifica se é a raiz
        if (remover->pai == NULL) {
            raiz = filho;
            filho->pai = NULL;
            filho->cor = PRETO;
            free(remover);
            return raiz;
        }
        struct NodeRN* pai = remover->pai;

        // Ajusta o pai do filho
        filho->pai = pai;

        if (pai->esq == remover) {
            pai->esq = filho;
        } else {
            pai->dir = filho;
        }

        // Se remover for preto, filho deve ficar preto para manter propriedades
        if (remover->cor == PRETO) {
            // não precisa balancear se o filho for vermelho
            if (filho->cor == VERMELHO) {
                filho->cor = PRETO;
            } else {
                // precisa balancear se o filho for preto
                raiz = balancearRemocaoRN(raiz, filho, filho->pai);
            }
        }

        // Finalmente libera remover
        free(remover);
        return raiz;
        
    }
    else if (remover->esq != NULL && remover->dir == NULL) {
        struct NodeRN* filho = remover->esq;
        // Verifica se é a raiz
        if (remover->pai == NULL) {
            raiz = filho;
            filho->pai = NULL;
            filho->cor = PRETO;
            free(remover);
            return raiz;
        }
        struct NodeRN* pai = remover->pai;

        // Ajusta o pai do filho
        filho->pai = pai;

        if (pai->esq == remover) {
            pai->esq = filho;
        } else {
            pai->dir = filho;
        }

        // Se remover for preto, filho deve ficar preto para manter propriedades
        if (remover->cor == PRETO) {
            // não precisa balancear se o filho for vermelho
            if (filho->cor == VERMELHO) {
                filho->cor = PRETO;
            } else {
                // precisa balancear se o filho for preto
                raiz = balancearRemocaoRN(raiz, filho, filho->pai);
            }
        }

        // Finalmente libera remover
        free(remover);
        return raiz;
    }
    else {
        struct NodeRN* sucessor = sucessorRN(remover);
        int temp = remover->valor;
        remover->valor = sucessor->valor;
        sucessor->valor = temp;
        raiz = removerRN(raiz, sucessor, sucessor->valor);
        return raiz;

    }
}

// Funcoes de balanceamento
struct NodeRN* rotacaoEsquerdaRN(struct NodeRN* raiz, struct NodeRN* x) {
    struct NodeRN* y = x->dir;
    x->dir = y->esq;

    if (y->esq != NULL)
        y->esq->pai = x;

    y->pai = x->pai;

    if (x->pai == NULL)
        raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    y->esq = x;
    x->pai = y;

    return raiz;
}

struct NodeRN* rotacaoDireitaRN(struct NodeRN* raiz, struct NodeRN* y) {
    struct NodeRN* x = y->esq;
    y->esq = x->dir;

    if (x->dir != NULL)
        x->dir->pai = y;

    x->pai = y->pai;

    if (y->pai == NULL)
        raiz = x;
    else if (y == y->pai->esq)
        y->pai->esq = x;
    else
        y->pai->dir = x;

    x->dir = y;
    y->pai = x;

    return raiz;
}

struct NodeRN* balancearInsercaoRN(struct NodeRN* raiz, struct NodeRN* no) {
    while (no != raiz && no->pai && no->pai->cor == VERMELHO) {
        struct NodeRN* avo = no->pai->pai;
        if (!avo) break;

        if (no->pai == avo->esq) {
            struct NodeRN* tio = avo->dir;

            if (tio && tio->cor == VERMELHO) {
                // Caso 1: Tio vermelho
                no->pai->cor = PRETO;
                tio->cor = PRETO;
                avo->cor = VERMELHO;
                no = avo;
            } else {
                if (no == no->pai->dir) {
                    // Caso 2: Filho direito
                    no = no->pai;
                    raiz = rotacaoEsquerdaRN(raiz, no);
                }
                // Caso 3: Filho esquerdo
                no->pai->cor = PRETO;
                avo->cor = VERMELHO;
                raiz = rotacaoDireitaRN(raiz, avo);
            }
        } else {
            struct NodeRN* tio = avo->esq;

            if (tio && tio->cor == VERMELHO) {
                no->pai->cor = PRETO;
                tio->cor = PRETO;
                avo->cor = VERMELHO;
                no = avo;
            } else {
                if (no == no->pai->esq) {
                    no = no->pai;
                    raiz = rotacaoDireitaRN(raiz, no);
                }
                no->pai->cor = PRETO;
                avo->cor = VERMELHO;
                raiz = rotacaoEsquerdaRN(raiz, avo);
            }
        }
    }

    raiz->cor = PRETO;
    return raiz;
}

struct NodeRN* balancearRemocaoRN(struct NodeRN* raiz, struct NodeRN* x, struct NodeRN* pai) {
    // Enquanto x for duplo‑preto (NULL ou preto) e não for raiz
    while ((x == NULL || x->cor == PRETO) && x != raiz) {
        // Se x é filho esquerdo de pai
        if (pai->esq == x) {
            struct NodeRN* w = pai->dir;  // irmão de x

            // Caso 1: w é vermelho
            if (w && w->cor == VERMELHO) {
                w->cor = PRETO;
                pai->cor = VERMELHO;
                raiz = rotacaoEsquerdaRN(raiz, pai);
                w = pai->dir;
            }

            // Caso 2: w é preto e ambos os filhos de w são pretos (ou NULL)
            if ((w->esq == NULL || w->esq->cor == PRETO) &&
                (w->dir == NULL || w->dir->cor == PRETO)) {
                if (w) w->cor = VERMELHO;
                x = pai;
                pai = x->pai;
            }
            else {
                // Caso 3: w é preto, w->dir é preto, w->esq é vermelho
                if (w->dir == NULL || w->dir->cor == PRETO) {
                    if (w->esq) w->esq->cor = PRETO;
                    w->cor = VERMELHO;
                    raiz = rotacaoDireitaRN(raiz, w);
                    w = pai->dir;
                }
                // Caso 4: w é preto e w->dir é vermelho
                if (w) {
                    w->cor = pai->cor;
                    pai->cor = PRETO;
                    if (w->dir) w->dir->cor = PRETO;
                    raiz = rotacaoEsquerdaRN(raiz, pai);
                }
                x = raiz;  // força saída do loop
            }
        }
        // Simétrico: x é filho direito
        else {
            struct NodeRN* w = pai->esq;

            // Caso 1
            if (w && w->cor == VERMELHO) {
                w->cor = PRETO;
                pai->cor = VERMELHO;
                raiz = rotacaoDireitaRN(raiz, pai);
                w = pai->esq;
            }

            // Caso 2
            if ((w->esq == NULL || w->esq->cor == PRETO) &&
                (w->dir == NULL || w->dir->cor == PRETO)) {
                if (w) w->cor = VERMELHO;
                x = pai;
                pai = x->pai;
            }
            else {
                // Caso 3
                if (w->esq == NULL || w->esq->cor == PRETO) {
                    if (w->dir) w->dir->cor = PRETO;
                    w->cor = VERMELHO;
                    raiz = rotacaoEsquerdaRN(raiz, w);
                    w = pai->esq;
                }
                // Caso 4
                if (w) {
                    w->cor = pai->cor;
                    pai->cor = PRETO;
                    if (w->esq) w->esq->cor = PRETO;
                    raiz = rotacaoDireitaRN(raiz, pai);
                }
                x = raiz;
            }
        }
    }

    // No fim, x (se não for NULL) vira preto
    if (x) x->cor = PRETO;
    return raiz;
}


// Utilitarios
struct NodeRN* sucessorRN(struct NodeRN* no) {
    struct NodeRN* temp = no;
    temp = temp->dir;
    while(temp->esq != NULL) {
        temp = temp->esq;
    }

    return temp;
}

struct NodeRN* novoNoRN(int valor) {
    struct NodeRN* no = (struct NodeRN*)malloc(sizeof(struct NodeRN));
    no->valor = valor;
    no->cor = VERMELHO;
    no->esq = no->dir = no->pai = NULL;
    return no;
}

void destruirArvoreRN(struct NodeRN* raiz) {
    if (raiz == NULL)
        return;
    destruirArvoreRN(raiz->esq);
    destruirArvoreRN(raiz->dir);
    free(raiz);
}

void preOrdemRN(struct NodeRN* raiz) {
    if (raiz == NULL)
        return;

    printf("%d(%s) ", raiz->valor, raiz->cor == VERMELHO ? "R" : "P");
    preOrdemRN(raiz->esq);
    preOrdemRN(raiz->dir);
}

void posOrdemRN(struct NodeRN* raiz) {
    if (raiz == NULL)
        return;

    posOrdemRN(raiz->esq);
    posOrdemRN(raiz->dir);
    printf("%d(%s) ", raiz->valor, raiz->cor == VERMELHO ? "R" : "P");
}

void inOrdemRN(struct NodeRN* raiz) {
    if (raiz == NULL)
        return;
    inOrdemRN(raiz->esq);
    printf("%d(%s) ", raiz->valor, raiz->cor == VERMELHO ? "R" : "P");
    inOrdemRN(raiz->dir);
}