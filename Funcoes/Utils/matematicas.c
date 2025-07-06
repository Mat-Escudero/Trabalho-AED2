// Funções auxiliares gerais de matemática que ajudam o projeto
// - Cálculos de fatoriais, potências, logaritmos
// - Funções para cálculos estatísticos simples
// - Outras funções numéricas que não estejam diretamente ligadas às árvores

#include "matematicas.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

double mediaTempo(int n, double valor) {
    if (n == 0) {
        return valor;
    }
    return (double) valor / n;
}

int expoencialDez(int n) {
    int v = 1;
    for (int i = 0; i < n; i++) {
        v = v*10;
    }
    return v;
}