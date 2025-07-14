#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Funcoes/AVL/funcoesAVL.h"
#include "Funcoes/Rubro/funcoesRubro.h"
#include "Funcoes/Utils/arvoreUtils.h"
#include "Funcoes/Utils/gerador.h"
#include "Funcoes/Utils/matematicas.h"

void caso1_1();
void caso1_1_2();
void caso1_2();
void caso1_3();
void caso1_4();
void caso1_5();
void caso1_6();
void caso1_7();

int main() {
    int opc = -1;
    int is_active;

    while (opc != 0) {
        printf("\n====== MENU DE TESTES ======\n");
        printf("1) Insercao de elementos aleatorios\n");
        printf("2) Insercao de elementos em ordem(crescente/decrescente)\n");
        printf("3) Busca de elementos da arvore\n");
        printf("4) Busca de elementos aleatorios\n");
        printf("5) Remocao de elementos da arvore\n");
        printf("6) Remocao de elementos aleatorios\n");
        printf("7) Altura maxima\n");
        printf("0) Encerrar programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opc);
        
        switch(opc) {
            case 1:
                // INSERÇÃO ALEATORIA
                // a Inserção é O(log n), logo a Inserção de "n" elementos é O(n*log n), mas como "n" é muito grande e cresce bem mais rapido que "log n", fica difícil ver no teste impírico.
                printf("Gostaria de comparar diferentes quantidades de insercoes? (digite ""1"" para sim e ""0"" para nao)\n");
                scanf("%i", &is_active);
                if (is_active == 1) {
                    caso1_1_2();
                } else {
                    caso1_1();
                }
                break;

            case 2:
                // INSERÇÃO CRESCENTE/DECRESCENTE
                caso1_2();
                break;

            case 3:
                // BUSCA ELEMENTOS DA ARVORE
                // a Busca é O(log n), logo a busca de "n" elementos é O(n * log n).
                caso1_3();
                break;

            case 4:
                // BUSCA ELEMENTOS ALEATORIOS
                caso1_4();
                break;
            
            case 5:
                // REMOÇÃO ELEMENTOS DA ARVORE
                // a Remoção também é (log n) e com "n" elementos fica O(n * log n), mas ela tem uma diferença
                // Quando a Remoção é muito grande, a AVL fica mais rapida, pois a busca da AVL é mais rapida e o balanceamento é menos relevante
                // Mas quando a Remoção é pequena, a Rubro-Negra é mais rápida, pois exige menos balanceamentos
                caso1_5();
                break;

            case 6:
                // REMOÇÃO ELEMENTOS ALEATORIOS
                caso1_6();
                break;

            case 7:
                // ALTURA MÁXIMA
                caso1_7();
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
    for (int j = 0; j < testes; j++) {
        int* numeros = gerarNumerosAleatorios(tamanhoArray, 0.3, 0);

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

// Não está nem um pouco eficiente e bonito esta função, mas funciona, então deixa
void caso1_1_2() {
    clock_t inicio, fim;
    double tempoExecucao;
    int tamanhoArray;
    int expoente;
    double tempoPrimeiraAVL, tempoPrimeiraRubro;
    double tempoSegundaAVL, tempoSegundaRubro;
    int* numeros;
    double tempoMedioAVL = 0;
    double tempoMedioRubro = 0;
    struct NodeAVL* raizAVL = NULL;
    struct NodeRN* raizRN = NULL;
    printf("---- Primeira arvore (MAIOR) ----\n");
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
    numeros = gerarNumerosAleatorios(tamanhoArray, 0.3, 0);

    // início inserção AVL
    inicio = clock();

    for (int i = 0; i < tamanhoArray; i++) {
        raizAVL = inserirAVL(raizAVL, numeros[i]);
    }

    fim = clock();

    tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    tempoMedioAVL = tempoExecucao;
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
    tempoMedioRubro = tempoExecucao;
    printf("Tempo de execucao para insercao de ");
    imprimirComPontos(tamanhoArray);
    printf(" elementos na arvore Rubro = %.6f segundos\n", tempoExecucao);

    free(numeros);
    destruirArvoreRN(raizRN);
    raizRN = NULL;

    destruirArvoreAVL(raizAVL);
    raizAVL = NULL;

    printf("Tempo de execucao media\n");
    printf("AVL:%.6f\n", tempoMedioAVL);
    printf("Rubro:%.6f\n", tempoMedioRubro);
    tempoPrimeiraAVL = tempoMedioAVL;
    tempoPrimeiraRubro = tempoMedioRubro;
    tempoMedioAVL = 0;
    tempoMedioRubro = 0;

    // Segunda Arvore

    printf("---- Segunda arvore (MENOR) ----\n");
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
    numeros = gerarNumerosAleatorios(tamanhoArray, 0.3, 0);

    // início inserção AVL
    inicio = clock();

    for (int i = 0; i < tamanhoArray; i++) {
        raizAVL = inserirAVL(raizAVL, numeros[i]);
    }

    fim = clock();

    tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    tempoMedioAVL = tempoExecucao;
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
    tempoMedioRubro = tempoExecucao;
    printf("Tempo de execucao para insercao de ");
    imprimirComPontos(tamanhoArray);
    printf(" elementos na arvore Rubro = %.6f segundos\n", tempoExecucao);

    free(numeros);
    destruirArvoreRN(raizRN);
    raizRN = NULL;

    destruirArvoreAVL(raizAVL);
    raizAVL = NULL;

    printf("Tempo de execucao media\n");
    printf("AVL:%.6f\n", tempoMedioAVL);
    printf("Rubro:%.6f\n", tempoMedioRubro);
    tempoSegundaAVL = tempoMedioAVL;
    tempoSegundaRubro = tempoMedioRubro;
    tempoMedioAVL = 0;
    tempoMedioRubro = 0;

    printf("Esta eh a quantidade de tempo que aumentou entre a primeira arvore a segunda\n");
    printf("AVL:%.6f\n", (float) tempoPrimeiraAVL / tempoSegundaAVL);
    printf("Rubro:%.6f\n", (float) tempoPrimeiraRubro / tempoSegundaRubro);

}

void caso1_2() {
    clock_t inicio, fim;
    double tempoExecucao;
    int tamanhoArray = 0;
    int expoente;
    int testes;
    int is_crescente;
    double tempoMedioAVL = 0;
    double tempoMedioRubro = 0;
    struct NodeAVL* raizAVL = NULL;
    struct NodeRN* raizRN = NULL;
    printf("A insercao eh crescente ou decrescente (""1"" = crescente)?\n");
    scanf("%i", &is_crescente);
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
    for (int j = 0; j < testes; j++) {

        // início inserção AVL
        inicio = clock();
        if (is_crescente == 1) {
            for (int i = 0; i < tamanhoArray; i++) {
                raizAVL = inserirAVL(raizAVL, i);
            }
        } else {
            for (int i = tamanhoArray - 1; i >= 0; i--) {
                raizAVL = inserirAVL(raizAVL, i);
            }
        }

        fim = clock();

        tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempoMedioAVL += tempoExecucao;
        printf("Tempo de execucao para insercao de ");
        imprimirComPontos(tamanhoArray);
        printf(" elementos na arvore AVL = %.6f segundos\n", tempoExecucao);

        // início inserção Rubro
        inicio = clock();
        if (is_crescente == 1) {
            for (int i = 0; i < tamanhoArray; i++) {
                raizRN = inserirRN(raizRN, i);
            }
        } else {
            for (int i = tamanhoArray - 1; i >= 0; i--) {
                raizRN = inserirRN(raizRN, i);
            }
        }

        fim = clock();

        tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempoMedioRubro += tempoExecucao;
        printf("Tempo de execucao para insercao de ");
        imprimirComPontos(tamanhoArray);
        printf(" elementos na arvore Rubro = %.6f segundos\n", tempoExecucao);

        destruirArvoreRN(raizRN);
        raizRN = NULL;

        destruirArvoreAVL(raizAVL);
        raizAVL = NULL;
    }

    printf("Tempo de execucao media\n");
    printf("AVL:%.6f\n", mediaTempo(testes, tempoMedioAVL));
    printf("Rubro:%.6f\n", mediaTempo(testes, tempoMedioRubro));
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
    int* numeros = gerarNumerosAleatorios(tamanhoArray, 0.3, 0);


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

void caso1_4() {
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
    int* numeros = gerarNumerosAleatorios(tamanhoArray, 0.3, 0);


    for (int i = 0; i < tamanhoArray; i++) {
        raizAVL = inserirAVL(raizAVL, numeros[i]);
    }

    for (int i = 0; i < tamanhoArray; i++) {
        raizRN = inserirRN(raizRN, numeros[i]);
    }

    for (int j = 0; j < testes; j++) {
        int* buscasArray = gerarNumerosAleatorios(buscas, 0.3, 0);
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
    int* numeros = gerarNumerosAleatorios(tamanhoArray, 0.3, 0);


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

void caso1_6() {
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
    int* numeros = gerarNumerosAleatorios(tamanhoArray, 0.3, 0);
    int* remocoesArray = gerarNumerosAleatorios(remocoes, 0.3, 0);


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

void caso1_7() {
    int tamanhoArray;
    int expoente;
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
    int* numeros = gerarNumerosAleatorios(tamanhoArray, 0.3, 0);

    // início inserção AVL

    for (int i = 0; i < tamanhoArray; i++) {
        raizAVL = inserirAVL(raizAVL, numeros[i]);
    }

    // início inserção Rubro

    for (int i = 0; i < tamanhoArray; i++) {
        raizRN = inserirRN(raizRN, numeros[i]);
    }



    free(numeros);
    printf("A altura do node mais profundo das avores eh:\n");
    printf("AVL: %i\n", maxAlturaAVL(raizAVL));
    printf("Rubro-Negra: %i\n", maxAlturaRN(raizRN));

    destruirArvoreRN(raizRN);
    raizRN = NULL;

    destruirArvoreAVL(raizAVL);
    raizAVL = NULL;

}
