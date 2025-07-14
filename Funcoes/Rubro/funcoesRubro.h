#ifndef FUNCOESRUBRO_H
#define FUNCOESRUBRO_H

#define VERMELHO 1
#define PRETO 0

struct NodeRN {
    int valor;
    int cor;
    struct NodeRN* esq;
    struct NodeRN* dir;
    struct NodeRN* pai;
};

struct NodeRN* inserirRN(struct NodeRN* raiz, int valor);
struct NodeRN* buscarRN(struct NodeRN* raiz, int valor);
struct NodeRN* removerRN(struct NodeRN* raiz, struct NodeRN* remover, int valor);

// Funcoes de balanceamento
struct NodeRN* rotacaoEsquerdaRN(struct NodeRN* raiz, struct NodeRN* no);
struct NodeRN* rotacaoDireitaRN(struct NodeRN* raiz, struct NodeRN* no);
struct NodeRN* balancearInsercaoRN(struct NodeRN* raiz, struct NodeRN* no);
struct NodeRN* balancearRemocaoRN(struct NodeRN* raiz, struct NodeRN* x, struct NodeRN* pai);

// Utilitarios
struct NodeRN* sucessorRN(struct NodeRN* no);
struct NodeRN* novoNoRN(int valor);
void destruirArvoreRN(struct NodeRN* raiz);
void preOrdemRN(struct NodeRN* raiz);
void posOrdemRN(struct NodeRN* raiz);
void inOrdemRN(struct NodeRN* raiz);
int maxAlturaRN(struct NodeRN* raiz);

#endif