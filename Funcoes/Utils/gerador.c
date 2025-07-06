// Funções para gerar dados aleatórios ou sequências
// - Gerar números aleatórios
// - Criar listas de teste
// - Gerar entradas simuladas para testes
#include <stdlib.h>

#include "gerador.h"

int* gerarNumerosAleatorios(int n, int min_val, int max_val) {
    if (n <= 0 || min_val > max_val) return NULL;

    int* vetor = (int*) malloc(sizeof(int) * n);
    if (!vetor) return NULL;

    for (int i = 0; i < n; i++) {
        vetor[i] = min_val + rand() % (max_val - min_val + 1);
    }

    return vetor;
}