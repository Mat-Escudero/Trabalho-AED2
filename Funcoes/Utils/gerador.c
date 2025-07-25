// Funções para gerar dados aleatórios ou sequências
// - Gerar números aleatórios
// - Criar listas de teste
// - Gerar entradas simuladas para testes
#include <stdlib.h>

#include "gerador.h"

// Parâmetros tamanho do vetor, fração desejada de colisões (0, 1), valor inicial do contador
int* gerarNumerosAleatorios(int n, double p, int base) {
    int* v = malloc(sizeof(int)*n);
    int* uniques = malloc(sizeof(int)*n);
    int u = 0, next = base;

    for (int i = 0; i < n; i++) {
        double r = (double)rand() / RAND_MAX;
        if (u > 0 && r < p) {
            v[i] = uniques[rand() % u];      // colisão
        } else {
            v[i] = next;                     // novo valor
            uniques[u++] = next;
            next++;
        }
    }
    /* Fisher–Yates shuffle */
    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = v[i]; v[i] = v[j]; v[j] = tmp;
    }
    free(uniques);
    return v;
}
