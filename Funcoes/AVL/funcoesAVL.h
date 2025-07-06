#ifndef FUNCOESAVL_H
#define FUNCOESAVL_H

struct NodeAVL {
    int valor;
    int altura;
    struct NodeAVL* filhoEsq;
    struct NodeAVL* filhoDir;
};

struct NodeAVL* inserirAVL(struct NodeAVL* raiz, int valor);
struct NodeAVL* removerAVL(struct NodeAVL* raiz, int valor);
struct NodeAVL* buscarAVL(struct NodeAVL* raiz, int valor);

// Funcoes de balanceamento
int fatorBalanceamentoAVL(struct NodeAVL* no);
struct NodeAVL* rotacaoDireitaAVL(struct NodeAVL* y);
struct NodeAVL* rotacaoEsquerdaAVL(struct NodeAVL* x);
struct NodeAVL* rotacaoDireitaEsquerdaAVL(struct NodeAVL* no);
struct NodeAVL* rotacaoEsquerdaDireitaAVL(struct NodeAVL* no);

// Utilitarios
int alturaAVL(struct NodeAVL* no);
struct NodeAVL* sucessorAVL(struct NodeAVL* no);
void destruirArvoreAVL(struct NodeAVL* raiz);
void preOrdemAVL(struct NodeAVL* raiz);
void posOrdemAVL(struct NodeAVL* raiz);
void inOrdemAVL(struct NodeAVL* raiz);

#endif