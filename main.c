#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Funcoes/AVL/funcoesAVL.h"
#include "Funcoes/Rubro/funcoesRubro.h"
#include "Funcoes/Utils/arvoreUtils.h"
#include "Funcoes/Utils/gerador.h"
#include "Funcoes/Utils/matematicas.h"

void caso1_1();
void caso1_2();
void caso1_3();
void caso1_4();

int main() {
    int opc = -1;

    while (opc != 0) {
        printf("\n====== MENU DE TESTES ======\n");
        printf("1) Modo de testes automaticos(neste modo, cada teste sera criado uma nova arvore)\n");
        printf(" - Insercao\n");
        printf(" - Busca\n");
        printf(" - Remocao\n");
        printf("2) Modo de testes interativos(neste modo, sera usado uma arvore so para todos testes)\n");
        printf(" - Insercao um por um\n");
        printf(" - Insercao de 'n' elementos\n");
        printf(" - Busca um por um\n");
        printf(" - Busca de 'n' elementos\n");
        printf(" - Remocao um por um\n");
        printf(" - Remocao de 'n' elementos\n");
        printf("0) Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1: {
                int opcCase1 = -1;
                while(opcCase1 != 0) {
                    printf("\n====== MENU DE TESTES ======\n");
                    printf("Voce escolheu modo de testes automaticos\n");
                    printf("1) Insercao\n");
                    printf("2) Busca de elementos da arvore\n");
                    printf("3) Busca de elementos aleatorios\n");
                    printf("4) Remocao\n");
                    printf("0) Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcCase1);
                    
                    switch(opcCase1) {
                        case 1:
                            // a Inserção é O(log n), logo a Inserção de "n" elementos é O(n*log n), mas como "n" é muito grande e cresce bem mais rapido que "log n", fica difícil ver no teste impírico.
                            caso1_1();
                            break;
    
                        case 2:
                            // a Busca é O(log n), logo a busca de "n" elementos é O(n * log n).
                            caso1_2();
                            break;
    
                        case 3:
                            // a Busca é O(log n), logo a busca de "n" elementos é O(n * log n).
                            caso1_3();
                            break;
                        
                        case 4:
                            caso1_4();
                            break;

                        case 0:
                            break;
    
                        default:
                            printf("Opção inválida. Tente novamente.\n");
                            break;
                    }
                }

                break;
            }
            case 2:
                int opcCase2 = -1;
                struct NodeRN* raizRN = NULL;
                int valor;
                while(opcCase2 != 0) {
                    printf("\n====== MENU DE TESTES ======\n");
                    printf("Voce escolheu modo de testes interativo\n");
                    printf("1) Insercao\n");
                    printf("2) Busca de elementos da arvore\n");
                    printf("3) Busca de elementos aleatorios\n");
                    printf("4) Remocao\n");
                    printf("0) Voltar\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcCase2);

                    switch(opcCase2) {
                        case 1:
                            printf("Digite o numero a ser inserido:");
                            scanf("%i", &valor);
                            raizRN = inserirRN(raizRN, valor);
                            break;
                        
                        case 2:
                            printf("Digite o numero a ser removido:");
                            scanf("%i", &valor);
                            raizRN = removerRN(raizRN, buscarRN(raizRN, valor), valor);
                            break;
                        
                        case 3:
                            printf("Pre:");
                            preOrdemRN(raizRN);
                            printf("\n");
                            printf("Pos:");
                            posOrdemRN(raizRN);
                            printf("\n");
                            printf("In:");
                            inOrdemRN(raizRN);
                            printf("\n");
                            break;

                        case 0:
                            break;

                        default:
                            printf("Opção inválida. Tente novamente.\n");
                            break;
                    }
                }
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}

void caso1_1() {
    clock_t inicio, fim;
    double tempoExecucao;
    int tamanhoArray;
    int expoente;
    int testes;
    double tempoMedioAVL = 0;
    double tempoMedioRubro = 0;
    struct NodeAVL* raizAVL = NULL;
    struct NodeRN* raizRN = NULL;

    printf("Digite o expoente de 10 (ex: 6 para inserir 1.000.000 elementos). Recomenda-se no máximo 7: ");
    scanf("%i", &expoente);
    if (expoente > 8) {
        printf("Voce eh maluco? Um expoente maior que 8 vai demorar muito para computar.\n");
        printf("Digite novamente o expoente:");
        scanf("%i", &expoente);
    }
    if (expoente > 8) {
        printf("Ok... Eu avisei.\n");
    }
    tamanhoArray = expoencialDez(expoente);
    printf("Digite a quantidade de vezes para testar: ");
    scanf("%i", &testes);
    int min_val = 0;
    int max_val = 10*tamanhoArray;
    for (int j = 0; j < testes; j++) {
        int* numeros = gerarNumerosAleatorios(tamanhoArray, min_val, max_val);

        // início inserção AVL
        inicio = clock();

        for (int i = 0; i < tamanhoArray; i++) {
            raizAVL = inserirAVL(raizAVL, numeros[i]);
        }

        fim = clock();

        tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempoMedioAVL += tempoExecucao;
        printf("Tempo de execucao para insercao de ");
        imprimirComPontos(tamanhoArray);
        printf(" elementos na arvore AVL = %.6f segundos\n", tempoExecucao);

        // início inserção Rubro
        inicio = clock();

        for (int i = 0; i < tamanhoArray; i++) {
            raizRN = inserirRN(raizRN, numeros[i]);
        }

        fim = clock();

        tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempoMedioRubro += tempoExecucao;
        printf("Tempo de execucao para insercao de ");
        imprimirComPontos(tamanhoArray);
        printf(" elementos na arvore Rubro = %.6f segundos\n", tempoExecucao);

        free(numeros);
        destruirArvoreRN(raizRN);
        raizRN = NULL;

        destruirArvoreAVL(raizAVL);
        raizAVL = NULL;
    }

    printf("Tempo de execucao media\n");
    printf("AVL:%.6f\n", mediaTempo(testes, tempoMedioAVL));
    printf("Rubro:%.6f\n", mediaTempo(testes, tempoMedioRubro));
}

void caso1_2() {
    clock_t inicio, fim;
    double tempoExecucao;
    int tamanhoArray;
    int expoente;
    int buscas;
    int testes;
    double tempoMedioAVL = 0;
    double tempoMedioRubro = 0;
    struct NodeAVL* raizAVL = NULL;
    struct NodeAVL* tempAVL = NULL;
    struct NodeRN* raizRN = NULL;
    struct NodeRN* tempRN = NULL;



    printf("Digite o expoente de 10 (ex: 6 para inserir 1.000.000 elementos). Recomenda-se no máximo 7: ");
    scanf("%i", &expoente);
    if (expoente > 8) {
        printf("Voce eh maluco? Um expoente maior que 8 vai demorar muito para computar.\n");
        printf("Digite novamente o expoente:");
        scanf("%i", &expoente);
    }
    if (expoente > 8) {
        printf("Ok... Eu avisei.\n");
    }

    printf("Digite a quantidade de buscas em expoente de 10(Todas buscas estarao na arvore): ");
    scanf("%i", &buscas);
    while(buscas > expoente) {
        printf("Nao da para fazer mais buscas que o tamanho da arvore\n");
        printf("Digite novamente a quantidade de buscas: ");
        scanf("%i", &buscas);
    }

    printf("Digite a quantidade de vezes para testar: ");
    scanf("%i", &testes);
    printf("Lembrando que o tempo de espera depende mais da criacao da arvore do que da busca\n");
    printf("Mas a arvore sera criada apenas 1 vez\n");

    tamanhoArray = expoencialDez(expoente);
    buscas = expoencialDez(buscas);
    int min_val = 0;
    int max_val = 10*tamanhoArray;
    int* numeros = gerarNumerosAleatorios(tamanhoArray, min_val, max_val);


    for (int i = 0; i < tamanhoArray; i++) {
        raizAVL = inserirAVL(raizAVL, numeros[i]);
    }

    for (int i = 0; i < tamanhoArray; i++) {
        raizRN = inserirRN(raizRN, numeros[i]);
    }

    for (int j = 0; j < testes; j++) {
        int comeco = rand() % (tamanhoArray - buscas + 1); 
        int termino = comeco + buscas;
        // início Buscas AVL
        inicio = clock();
    
        for (int i = comeco; i < termino; i++) {
            tempAVL = buscarAVL(raizAVL, numeros[i]);
            (void)tempAVL;
        }
    
        fim = clock();
    
        tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempoMedioAVL += tempoExecucao;
        printf("Tempo de execucao para buscar ");
        imprimirComPontos(buscas);
        printf(" elementos na arvore AVL = %.6f segundos\n", tempoExecucao);
    
        // início Buscas Rubro
        inicio = clock();
    
        for (int i = comeco; i < termino; i++) {
            tempRN = buscarRN(raizRN, numeros[i]);
            (void)tempRN;
        }
    
        fim = clock();
    
        tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempoMedioRubro += tempoExecucao;
        printf("Tempo de execucao para buscar ");
        imprimirComPontos(buscas);
        printf(" elementos na arvore Rubro = %.6f segundos\n", tempoExecucao);
    }

    printf("Tempo de execucao media\n");
    printf("AVL:%.6f\n", mediaTempo(testes, tempoMedioAVL));
    printf("Rubro:%.6f\n", mediaTempo(testes, tempoMedioRubro));
    destruirArvoreAVL(raizAVL);
    destruirArvoreRN(raizRN);
}

void caso1_3() {
    clock_t inicio, fim;
    double tempoExecucao;
    int tamanhoArray;
    int expoente;
    int buscas;
    int testes;
    double tempoMedioAVL = 0;
    double tempoMedioRubro = 0;
    struct NodeAVL* raizAVL = NULL;
    struct NodeAVL* tempAVL = NULL;
    struct NodeRN* raizRN = NULL;
    struct NodeRN* tempRN = NULL;



    printf("Digite o expoente de 10 (ex: 6 para inserir 1.000.000 elementos). Recomenda-se no máximo 7: ");
    scanf("%i", &expoente);
    if (expoente > 8) {
        printf("Voce eh maluco? Um expoente maior que 8 vai demorar muito para computar.\n");
        printf("Digite novamente o expoente:");
        scanf("%i", &expoente);
    }
    if (expoente > 8) {
        printf("Ok... Eu avisei.\n");
    }

    printf("Digite a quantidade de buscas em expoente de 10(tem 10%% de chance de estar na arvore): ");
    scanf("%i", &buscas);
    while(buscas > expoente) {
        printf("Nao da para fazer mais buscas que o tamanho da arvore\n");
        printf("Digite novamente a quantidade de buscas: ");
        scanf("%i", &buscas);
    }

    printf("Digite a quantidade de vezes para testar: ");
    scanf("%i", &testes);
    printf("Lembrando que o tempo de espera depende mais da criacao da arvore do que da busca\n");
    printf("Mas a arvore sera criada apenas 1 vez\n");

    tamanhoArray = expoencialDez(expoente);
    buscas = expoencialDez(buscas);
    int min_val = 0;
    int max_val = 10*tamanhoArray;
    int* numeros = gerarNumerosAleatorios(tamanhoArray, min_val, max_val);


    for (int i = 0; i < tamanhoArray; i++) {
        raizAVL = inserirAVL(raizAVL, numeros[i]);
    }

    for (int i = 0; i < tamanhoArray; i++) {
        raizRN = inserirRN(raizRN, numeros[i]);
    }

    for (int j = 0; j < testes; j++) {
        int* buscasArray = gerarNumerosAleatorios(buscas, min_val, max_val);
        // início Buscas AVL
        inicio = clock();
    
        for (int i = 0; i < buscas; i++) {
            tempAVL = buscarAVL(raizAVL, buscasArray[i]);
            (void)tempAVL;
        }
    
        fim = clock();
    
        tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempoMedioAVL += tempoExecucao;
        printf("Tempo de execucao para buscar ");
        imprimirComPontos(buscas);
        printf(" elementos na arvore AVL = %.6f segundos\n", tempoExecucao);
    
        // início Buscas Rubro
        inicio = clock();
    
        for (int i = 0; i < buscas; i++) {
            tempRN = buscarRN(raizRN, buscasArray[i]);
            (void)tempRN;
        }
    
        fim = clock();
    
        tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempoMedioRubro += tempoExecucao;
        printf("Tempo de execucao para buscar ");
        imprimirComPontos(buscas);
        printf(" elementos na arvore Rubro = %.6f segundos\n", tempoExecucao);
    }

    printf("Tempo de execucao media\n");
    printf("AVL:%.6f\n", mediaTempo(testes, tempoMedioAVL));
    printf("Rubro:%.6f\n", mediaTempo(testes, tempoMedioRubro));
    destruirArvoreAVL(raizAVL);
    destruirArvoreRN(raizRN);
}

void caso1_4() {
    clock_t inicio, fim;
    double tempoExecucao;
    int tamanhoArray;
    int expoente;
    int remocoes;
    struct NodeAVL* raizAVL = NULL;
    struct NodeRN* raizRN = NULL;


    printf("Digite o expoente de 10 (ex: 6 para inserir 1.000.000 elementos). Recomenda-se no máximo 7: ");
    scanf("%i", &expoente);
    if (expoente > 8) {
        printf("Voce eh maluco? Um expoente maior que 8 vai demorar muito para computar.\n");
        printf("Digite novamente o expoente:");
        scanf("%i", &expoente);
    }
    if (expoente > 8) {
        printf("Ok... Eu avisei.\n");
    }

    printf("Digite a quantidade de remocoes em expoente de 10(Todas remocoes estarao na arvore): ");
    scanf("%i", &remocoes);
    while(remocoes > expoente) {
        printf("Nao da para fazer mais remocoes que o tamanho da arvore\n");
        printf("Digite novamente a quantidade de remocoes: ");
        scanf("%i", &remocoes);
    }

    tamanhoArray = expoencialDez(expoente);
    remocoes = expoencialDez(remocoes);
    int min_val = 0;
    int max_val = 10*tamanhoArray;
    int* numeros = gerarNumerosAleatorios(tamanhoArray, min_val, max_val);


    for (int i = 0; i < tamanhoArray; i++) {
        raizAVL = inserirAVL(raizAVL, numeros[i]);
    }

    for (int i = 0; i < tamanhoArray; i++) {
        raizRN = inserirRN(raizRN, numeros[i]);
    }

    // início Remocao AVL
    inicio = clock();
    
    for (int i = 0; i < remocoes; i++) {
        raizAVL = removerAVL(raizAVL, numeros[i]);
    }
    
    
    fim = clock();
    
    tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao para remover ");
    imprimirComPontos(remocoes);
    printf(" elementos na arvore AVL = %.6f segundos\n", tempoExecucao);
    
    // início Remocao Rubro
    inicio = clock();
    for (int i = 0; i < remocoes; i++) {
        raizRN = removerRN(raizRN, buscarRN(raizRN, numeros[i]), numeros[i]);
    }
    
    fim = clock();
    
    tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao para remover ");
    imprimirComPontos(remocoes);
    printf(" elementos na arvore Rubro = %.6f segundos\n", tempoExecucao);
    destruirArvoreAVL(raizAVL);
    destruirArvoreRN(raizRN);
}

void caso1_5() {
    clock_t inicio, fim;
    double tempoExecucao;
    int tamanhoArray;
    int expoente;
    int remocoes;
    struct NodeAVL* raizAVL = NULL;
    struct NodeRN* raizRN = NULL;


    printf("Digite o expoente de 10 (ex: 6 para inserir 1.000.000 elementos). Recomenda-se no máximo 7: ");
    scanf("%i", &expoente);
    if (expoente > 8) {
        printf("Voce eh maluco? Um expoente maior que 8 vai demorar muito para computar.\n");
        printf("Digite novamente o expoente:");
        scanf("%i", &expoente);
    }
    if (expoente > 8) {
        printf("Ok... Eu avisei.\n");
    }

    printf("Digite a quantidade de remocoes em expoente de 10(Todas remocoes estarao na arvore): ");
    scanf("%i", &remocoes);
    while(remocoes > expoente) {
        printf("Nao da para fazer mais remocoes que o tamanho da arvore\n");
        printf("Digite novamente a quantidade de remocoes: ");
        scanf("%i", &remocoes);
    }

    tamanhoArray = expoencialDez(expoente);
    remocoes = expoencialDez(remocoes);
    int min_val = 0;
    int max_val = 10*tamanhoArray;
    int* numeros = gerarNumerosAleatorios(tamanhoArray, min_val, max_val);
    int* remocoesArray = gerarNumerosAleatorios(remocoes, min_val, max_val);


    for (int i = 0; i < tamanhoArray; i++) {
        raizAVL = inserirAVL(raizAVL, numeros[i]);
    }

    for (int i = 0; i < tamanhoArray; i++) {
        raizRN = inserirRN(raizRN, numeros[i]);
    }

    // início Remocao AVL
    inicio = clock();
    
    for (int i = 0; i < remocoes; i++) {
        raizAVL = removerAVL(raizAVL, remocoesArray[i]);
    }
    
    fim = clock();
    
    tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao para remover ");
    imprimirComPontos(remocoes);
    printf(" elementos na arvore AVL = %.6f segundos\n", tempoExecucao);
    
    // início Remocao Rubro
    inicio = clock();
    
    for (int i = 0; i < remocoes; i++) {
        raizRN = removerRN(raizRN, buscarRN(raizRN, remocoesArray[i]), remocoesArray[i]);
    }
    
    fim = clock();
    
    tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao para remover ");
    imprimirComPontos(remocoes);
    printf(" elementos na arvore Rubro = %.6f segundos\n", tempoExecucao);
    destruirArvoreAVL(raizAVL);
    destruirArvoreRN(raizRN);
}