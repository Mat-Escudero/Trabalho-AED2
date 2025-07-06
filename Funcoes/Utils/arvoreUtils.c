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