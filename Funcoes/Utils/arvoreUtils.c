// Funções auxiliares para manipulação de árvores (AVL e Rubro)
// - Impressão da árvore (em ordem, pré-ordem)
// - Liberar memória da árvore
// - Calcular altura da árvore
// - Verificar propriedades comuns

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arvoreUtils.h"

void imprimirComPontos(int numero) {
    char buffer[50];
    sprintf(buffer, "%d", numero);

    int len = strlen(buffer);
    int pontos = (len - 1) / 3; // Quantidade de pontos a inserir
    int tamanhoFinal = len + pontos;

    char formatado[60];
    formatado[tamanhoFinal] = '\0';

    int i = len - 1;
    int j = tamanhoFinal - 1;
    int contador = 0;

    while (i >= 0) {
        formatado[j--] = buffer[i--];
        contador++;
        if (contador == 3 && i >= 0) {
            formatado[j--] = '.';
            contador = 0;
        }
    }

    printf("%s", formatado);
}

void quicksort(int arr[], int inicio, int fim) {
    if (inicio >= fim) return;

    int pivo = arr[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (arr[j] < pivo) {
            i++;
            // troca arr[i] e arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // coloca o pivo na posição correta
    int temp = arr[i + 1];
    arr[i + 1] = arr[fim];
    arr[fim] = temp;

    quicksort(arr, inicio, i);
    quicksort(arr, i + 2, fim);
}