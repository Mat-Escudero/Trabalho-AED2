#ifndef FUNCOESAVL_H
#define FUNCOESAVL_H

extern int contadorRotacaoDireitaAVL;
extern int contadorRotacaoEsquerdaAVL;

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

// Utilitarios
int alturaAVL(struct NodeAVL* no);
struct NodeAVL* sucessorAVL(struct NodeAVL* no);
void destruirArvoreAVL(struct NodeAVL* raiz);
void preOrdemAVL(struct NodeAVL* raiz);
void posOrdemAVL(struct NodeAVL* raiz);
void inOrdemAVL(struct NodeAVL* raiz);
int maxAlturaAVL(struct NodeAVL* raiz);
void preencherArrayAVL(struct NodeAVL* raiz, int* array, int* index);
int maiorValorAVL(struct NodeAVL* raiz);
int contarNosAVL(struct NodeAVL* raiz);
int is_AVL(struct NodeAVL* raiz);

#endif