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

int contadorRotacaoDireitaRN = 0;
int contadorRotacaoEsquerdaRN = 0;
int contadorRotacaoDireitaAVL = 0;
int contadorRotacaoEsquerdaAVL = 0;


int main() {
    int opc = -1;
    int is_active;

    while (opc != 0) {
        printf("\n====== MENU DE TESTES ======\n");
        printf("1) Insercao de elementos aleatorios\n");
        printf("2) Insercao de elementos em ordem (crescente/decrescente)\n");
        printf("3) Busca de elementos da arvore\n");
        printf("4) Remocao de elementos da arvore\n");
        printf("5) Altura maxima\n");
        printf("6) Caso realista\n");
        printf("0) Encerrar programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opc);
        
        switch(opc) {
            case 1:
                // INSERÇÃO ALEATORIA
                // a Inserção é O(log n), logo a Inserção de "n" elementos é O(n*log n), mas como "n" é muito grande e cresce bem mais rapido que "log n", fica difícil ver no teste impírico.
                contadorRotacaoDireitaRN = 0;
                contadorRotacaoEsquerdaRN = 0;
                contadorRotacaoDireitaAVL = 0;
                contadorRotacaoEsquerdaAVL = 0;
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
                contadorRotacaoDireitaRN = 0;
                contadorRotacaoEsquerdaRN = 0;
                contadorRotacaoDireitaAVL = 0;
                contadorRotacaoEsquerdaAVL = 0;
                caso1_2();
                break;

            case 3:
                // BUSCA ELEMENTOS DA ARVORE
                // a Busca é O(log n), logo a busca de "n" elementos é O(n * log n).
                contadorRotacaoDireitaRN = 0;
                contadorRotacaoEsquerdaRN = 0;
                contadorRotacaoDireitaAVL = 0;
                contadorRotacaoEsquerdaAVL = 0;
                caso1_3();
                break;
            
            case 4:
                // REMOÇÃO ELEMENTOS DA ARVORE
                // a Remoção também é (log n) e com "n" elementos fica O(n * log n), mas ela tem uma diferença
                // Quando a Remoção é muito grande, a AVL fica mais rapida, pois a busca da AVL é mais rapida e o balanceamento é menos relevante
                // Mas quando a Remoção é pequena, a Rubro-Negra é mais rápida, pois exige menos balanceamentos
                contadorRotacaoDireitaRN = 0;
                contadorRotacaoEsquerdaRN = 0;
                contadorRotacaoDireitaAVL = 0;
                contadorRotacaoEsquerdaAVL = 0;
                caso1_4();
                break;

            case 5:
                // ALTURA MÁXIMA
                contadorRotacaoDireitaRN = 0;
                contadorRotacaoEsquerdaRN = 0;
                contadorRotacaoDireitaAVL = 0;
                contadorRotacaoEsquerdaAVL = 0;
                caso1_5();
                break;

            case 6:
                // CASO REALISTA
                contadorRotacaoDireitaRN = 0;
                contadorRotacaoEsquerdaRN = 0;
                contadorRotacaoDireitaAVL = 0;
                contadorRotacaoEsquerdaAVL = 0;
                caso1_6();
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
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

    printf("Digite o expoente de 10 (ex: 6 para inserir 1.000.000 elementos). Recomenda-se no maximo 7: ");
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
        int* numeros = gerarNumerosAleatorios(tamanhoArray, 0, 0);
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
        printf(" elementos na arvore AVL = %.6f segundos.\n", tempoExecucao);

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
        printf(" elementos na arvore Rubro = %.6f segundos.\n", tempoExecucao);

        free(numeros);
        destruirArvoreRN(raizRN);
        raizRN = NULL;

        destruirArvoreAVL(raizAVL);
        raizAVL = NULL;
    }

    printf("\n================== TEMPO MEDIO ==================\n");
    printf("| Arvore       | Tempo (segundos)               |\n");
    printf("|--------------|--------------------------------|\n");
    printf("| AVL          | %.6f                       |\n", mediaTempo(testes, tempoMedioAVL));
    printf("| Rubro-Negra  | %.6f                       |\n", mediaTempo(testes, tempoMedioRubro));
    printf("=================================================\n");
    //printf("%i\n%i\n%i\n%i\n", contadorRotacaoDireitaAVL, contadorRotacaoEsquerdaAVL, contadorRotacaoDireitaRN, contadorRotacaoEsquerdaRN);
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
    printf("Digite o expoente de 10 (ex: 6 para inserir 1.000.000 elementos). Recomenda-se no maximo 7: ");
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
    numeros = gerarNumerosAleatorios(tamanhoArray, 0, 0);

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
    printf(" elementos na arvore AVL = %.6f segundos.\n", tempoExecucao);

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
    printf(" elementos na arvore Rubro = %.6f segundos.\n", tempoExecucao);

    free(numeros);
    destruirArvoreRN(raizRN);
    raizRN = NULL;

    destruirArvoreAVL(raizAVL);
    raizAVL = NULL;

    printf("\nTempo de execucao media:\n");
    printf(" AVL:%.6f segundos\n", tempoMedioAVL);
    printf(" Rubro:%.6f segundos\n", tempoMedioRubro);
    tempoPrimeiraAVL = tempoMedioAVL;
    tempoPrimeiraRubro = tempoMedioRubro;
    tempoMedioAVL = 0;
    tempoMedioRubro = 0;

    // Segunda Arvore

    printf("---- Segunda arvore (MENOR) ----\n");
    printf("Digite o expoente de 10 (ex: 6 para inserir 1.000.000 elementos). Recomenda-se no maximo 7: ");
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
    numeros = gerarNumerosAleatorios(tamanhoArray, 0, 0);

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
    printf(" elementos na arvore AVL = %.6f segundos.\n", tempoExecucao);

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
    printf(" elementos na arvore Rubro = %.6f segundos.\n", tempoExecucao);

    free(numeros);
    destruirArvoreRN(raizRN);
    raizRN = NULL;

    destruirArvoreAVL(raizAVL);
    raizAVL = NULL;

    printf("\nTempo de execucao media:\n");
    printf(" AVL: %.6f segundos\n", tempoMedioAVL);
    printf(" Rubro: %.6f segundos\n", tempoMedioRubro);
    tempoSegundaAVL = tempoMedioAVL;
    tempoSegundaRubro = tempoMedioRubro;
    tempoMedioAVL = 0;
    tempoMedioRubro = 0;

    
    int espacosAVL = 23, espacosRN = 23, razaoAVL = (int) (tempoPrimeiraAVL / tempoSegundaAVL), razaoRN = (int) (tempoPrimeiraRubro / tempoSegundaRubro);
    while (razaoAVL / 10 >= 1)
    {
        espacosAVL--;
        razaoAVL = razaoAVL / 10;
    }
    while (razaoRN / 10 >= 1)
    {
        espacosRN--;
        razaoRN = razaoRN / 10;
    }
    printf("\n================ TEMPO RELATIVO =================\n");
    printf("| Arvore       | Primeira / Segunda             |\n");
    printf("|--------------|--------------------------------|\n");
    printf("| AVL          | %.6f", (float) tempoPrimeiraAVL / tempoSegundaAVL);
    for (int i = 0; i < espacosAVL; i++) {
        printf(" ");
    }
    printf("|\n");
    printf("| Rubro-Negra  | %.6f", (float) tempoPrimeiraRubro / tempoSegundaRubro);
    for (int i = 0; i < espacosRN; i++) {
        printf(" ");
    }
    printf("|\n");
    printf("=================================================\n");

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
    printf("Digite o expoente de 10 (ex: 6 para inserir 1.000.000 elementos). Recomenda-se no maximo 7: ");
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
    int *numeros = malloc(tamanhoArray * sizeof(int));
    printf("Digite a quantidade de vezes para testar: ");
    scanf("%i", &testes);
    if (is_crescente == 1) {
        for (int i = 0; i < tamanhoArray; i++) {
            numeros[i] = i;
        }
    } else {
        for (int i = 0; i < tamanhoArray; i++) {
            numeros[i] = tamanhoArray - i - 1;
        }
    }
    for (int j = 0; j < testes; j++) {
        // início inserção AVL
        // for (int i = 0; i < tamanhoArray; i++) {
        //     printf("%i ", numeros[i]);
        // }
        inicio = clock();
        for (int i = 0; i < tamanhoArray; i++) {
            raizAVL = inserirAVL(raizAVL, numeros[i]);
        }

        fim = clock();

        tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
        tempoMedioAVL += tempoExecucao;
        printf("Tempo de execucao para insercao de ");
        imprimirComPontos(tamanhoArray);
        printf(" elementos na arvore AVL = %.6f segundos.\n", tempoExecucao);

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
        printf(" elementos na arvore Rubro = %.6f segundos.\n", tempoExecucao);

        destruirArvoreRN(raizRN);
        raizRN = NULL;

        destruirArvoreAVL(raizAVL);
        raizAVL = NULL;
    }

    printf("\n================== TEMPO MEDIO ==================\n");
    printf("| Arvore       | Tempo (segundos)               |\n");
    printf("|--------------|--------------------------------|\n");
    printf("| AVL          | %.6f                       |\n", mediaTempo(testes, tempoMedioAVL));
    printf("| Rubro-Negra  | %.6f                       |\n", mediaTempo(testes, tempoMedioRubro));
    printf("=================================================\n");
    printf("Cuidado!\n");
    printf("Insercao ordenada gera muitas rotacoes previsiveis, favorecendo a localidade de memoria e predicao de branches, resultando em maior desempenho.\n");
    printf("Logo, ela eh mais rapida que a aleatoria devido ao funcionamento da memoria, porem analiticamente demora mais por gerar mais rotacoes.\n");

    //printf("%i\n%i\n%i\n%i\n", contadorRotacaoDireitaAVL, contadorRotacaoEsquerdaAVL, contadorRotacaoDireitaRN, contadorRotacaoEsquerdaRN);

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



    printf("Digite o expoente de 10 (ex: 6 para inserir 1.000.000 elementos). Recomenda-se no maximo 7: ");
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
    printf("Lembrando que o tempo de espera do algoritmo depende mais da criacao da arvore do que das buscas.\n");
    printf("Mas a arvore sera criada apenas uma vez.\n");

    tamanhoArray = expoencialDez(expoente);
    buscas = expoencialDez(buscas);
    int* numeros = gerarNumerosAleatorios(tamanhoArray, 0, 0);


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
        printf(" elementos na arvore AVL = %.6f segundos.\n", tempoExecucao);
    
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
        printf(" elementos na arvore Rubro = %.6f segundos.\n", tempoExecucao);
    }

    printf("\n================== TEMPO MEDIO ==================\n");
    printf("| Arvore       | Tempo (segundos)               |\n");
    printf("|--------------|--------------------------------|\n");
    printf("| AVL          | %.6f                       |\n", mediaTempo(testes, tempoMedioAVL));
    printf("| Rubro-Negra  | %.6f                       |\n", mediaTempo(testes, tempoMedioRubro));
    printf("=================================================\n");

    destruirArvoreAVL(raizAVL);
    destruirArvoreRN(raizRN);
}

void caso1_4() {
    clock_t inicio, fim;
    double tempoExecucaoAVL, tempoExecucaoRN;
    int tamanhoArray;
    int expoente, expoenteRemocoes;
    int remocoes;
    struct NodeAVL* raizAVL = NULL;
    struct NodeRN* raizRN = NULL;


    printf("Digite o expoente de 10 (ex: 6 para inserir 1.000.000 elementos). Recomenda-se no maximo 7: ");
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
    scanf("%i", &expoenteRemocoes);
    while(expoenteRemocoes > expoente) {
        printf("Nao da para fazer mais remocoes que o tamanho da arvore\n");
        printf("Digite novamente a quantidade de remocoes: ");
        scanf("%i", &remocoes);
    }

    tamanhoArray = expoencialDez(expoente);
    remocoes = expoencialDez(expoenteRemocoes);
    int* numeros = gerarNumerosAleatorios(tamanhoArray, 0, 0);


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
    
    tempoExecucaoAVL = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    // início Remocao Rubro
    inicio = clock();
    for (int i = 0; i < remocoes; i++) {
        raizRN = removerRN(raizRN, buscarRN(raizRN, numeros[i]), numeros[i]);
    }
    
    fim = clock();
    
    tempoExecucaoRN = (double)(fim - inicio) / CLOCKS_PER_SEC;

    int espacos = 11, razaoPonto = (int) (expoenteRemocoes/3);
    espacos = espacos - razaoPonto - expoenteRemocoes;

    printf("\n================== TEMPO MEDIO ==================\n");
    printf("| Arvore       | Tempo (segundos) | Remocoes    |\n");
    printf("|--------------|--------------------------------|\n");
    printf("| AVL          | %.6f         | ", tempoExecucaoAVL);
    imprimirComPontos(remocoes);
    for (int i = 0; i < espacos ; i++) {
        printf(" ");
    }
    printf("|\n");
    printf("| Rubro-Negra  | %.6f         | ", tempoExecucaoRN);
    imprimirComPontos(remocoes);
    for (int i = 0; i < espacos ; i++) {
        printf(" ");
    }
    printf("|\n");
    printf("=================================================\n");

    destruirArvoreAVL(raizAVL);
    destruirArvoreRN(raizRN);
}

void caso1_5() {
    int tamanhoArray;
    int expoente;
    struct NodeAVL* raizAVL = NULL;
    struct NodeRN* raizRN = NULL;

    printf("Digite o expoente de 10 (ex: 6 para inserir 1.000.000 elementos). Recomenda-se no maximo 7: ");
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
    int* numeros = gerarNumerosAleatorios(tamanhoArray, 0, 0);

    // início inserção AVL

    for (int i = 0; i < tamanhoArray; i++) {
        raizAVL = inserirAVL(raizAVL, numeros[i]);
    }

    // início inserção Rubro

    for (int i = 0; i < tamanhoArray; i++) {
        raizRN = inserirRN(raizRN, numeros[i]);
    }



    free(numeros);
    // printf("\nAltura maxima atingida em cada tipo de arvore:\n");
    // printf(" AVL: %i\n", maxAlturaAVL(raizAVL));
    // printf(" Rubro-Negra: %i\n", maxAlturaRN(raizRN));
    int alturaMaxAVL = maxAlturaAVL(raizAVL), alturaMaxRN = maxAlturaRN(raizRN);
    int espacosAVL = 30, espacosRN = 30;
    if (alturaMaxAVL > 10) {
        espacosAVL--;
    }
    if (alturaMaxRN > 10) {
        espacosRN--;
    }
    printf("\n================== ALTURA MAXIMA ===============\n");
    printf("| Arvore       | ALTURA                         |\n");
    printf("|--------------|--------------------------------|\n");
    printf("| AVL          | %i", alturaMaxAVL);
    for (int i = 0; i < espacosAVL; i++) {
        printf(" ");
    }
    printf("|\n");
    printf("| Rubro-Negra  | %i", alturaMaxRN);
    for (int i = 0; i < espacosRN; i++) {
        printf(" ");
    }
    printf("|\n");
    printf("=================================================\n");

    destruirArvoreRN(raizRN);
    raizRN = NULL;

    destruirArvoreAVL(raizAVL);
    raizAVL = NULL;

}

void caso1_6() {
    clock_t inicio, fim;
    double tempoExecucaoAVL = 0, tempoExecucaoRN = 0;
    int min, max;
    int seed;
    struct NodeAVL* raizAVL = NULL;
    struct NodeRN* raizRN = NULL;

    printf("A ideia deste teste eh que ocorra manipulacoes nas arvores, mas que elas mantenham em media um tamanho constante, que nem na realidade.\n");
    printf("Normalmente essas arvores ocorrem insercoes e remocoes varias vezes, porem sempre mantem em um certo tamanho.\n");
    printf("Para testes realisticos, recomenda-se estes testes:\n");
    printf("1. Pequeno: 100 - 1000\n");
    printf("2. Moderado: 1000 - 10000\n");
    printf("3. Grande: 10000 - 50000\n");
    printf("4. Extremo: 50000 - 65000\n");
    printf("Qual eh o tamanho minimo da arvore?\n");
    scanf("%i", &min);
    printf("Qual eh o tamanho maximo da arvore?\n");
    scanf("%i", &max);
    while (max <= 0 || min <= 0 || max <= min || max - min < 500) {
        printf("O maximo tem que ser maior que o minimo, os dois tem que ser maior que zero e a diferenca entre eles tem que ser no minimo 500\n");
        printf("Qual eh o tamanho minimo da arvore?\n");
        scanf("%i", &min);
        printf("Qual eh o tamanho maximo da arvore?\n");
        scanf("%i", &max);
    }
    printf("Qual a seed que gostaria de usar?\n");
    scanf("%i", &seed);
    while (seed < 0) {
        printf("A seed tem que ser inteira e positiva\n");
        printf("Qual a seed que gostaria de usar?\n");
        scanf("%i", &seed);
    }

    int intervalo = max - min;
    int operacoesPorLoop = intervalo / 10; // 10% do intervalo por loop, o minimo é 50
    int minOperacoes = intervalo / 50;
    if (operacoesPorLoop < 50) {
        operacoesPorLoop = 50;
    }
    if (minOperacoes < 10) {
        minOperacoes = 10;
    }
    int loops;
    int totalInsercaoAVL = 0, totalRemocaoAVL = 0;
    int totalInsercaoRN = 0, totalRemocaoRN = 0;
    if (operacoesPorLoop >= 5000) {
        loops = 200;
    } else if (operacoesPorLoop >= 1000) {
        loops = 1000;
    } else {
        loops = 10000; 
    }
    int tamanhoInicial = (max + min) / 2;
    int *numeros = gerarNumerosAleatorios(tamanhoInicial, 0, 0);

    // gerar arvores
    for (int i = 0; i < tamanhoInicial; i++) {
        raizAVL = inserirAVL(raizAVL, numeros[i]);
        raizRN = inserirRN(raizRN, numeros[i]);
    }

    // Loops Arvore AVL
    srand(seed);
    int tamanhoAVL = tamanhoInicial;
    for (int i = 0; i < loops; i++) {
        int maiorValor = maiorValorAVL(raizAVL);
        int *numerosAVL = malloc(tamanhoAVL * sizeof(int));
        int indice = 0;
        preencherArrayAVL(raizAVL, numerosAVL, &indice);

        int quantidadeInserir = rand() % (operacoesPorLoop - (operacoesPorLoop/5)) + (operacoesPorLoop/5);
        int quantidadeRemover = rand() % (operacoesPorLoop - (operacoesPorLoop/5)) + (operacoesPorLoop/5);

        if (tamanhoAVL + quantidadeInserir > max) {
            quantidadeInserir = max - tamanhoAVL;
        }
        if (tamanhoAVL - quantidadeRemover < min) {
            quantidadeRemover = tamanhoAVL - min;
        }
        totalInsercaoAVL += quantidadeInserir;
        totalRemocaoAVL += quantidadeRemover;

        int *inserir = gerarNumerosAleatorios(quantidadeInserir, 0, maiorValor + 1);
        int *remover = malloc(quantidadeRemover * sizeof(int));
        int *arrayRemoverRand = malloc(quantidadeRemover * sizeof(int));

        // Gerar índices únicos para remoção
        int j = 0;
        while (j < quantidadeRemover) {
            int temp = rand() % tamanhoAVL;
            int repetido = 0;
            for (int k = 0; k < j; k++) {
                if (arrayRemoverRand[k] == temp) {
                    repetido = 1;
                    break;
                }
            }
            if (!repetido) {
                arrayRemoverRand[j] = temp;
                j++;  // só incrementa se encontrou um número único
            }
            // se repetido == 1, o loop while repete e tenta novo temp
        }
        // Gerar um array com valores da arvore, usando o index do array de índices únicos, assim nao vai remover o mesmo index duas vezes
        for (int j = 0; j < quantidadeRemover; j++) {
            remover[j] = numerosAVL[arrayRemoverRand[j]];
        }
        
        inicio = clock();
        // Inserir valores
        for (int j = 0; j < quantidadeInserir; j++) {
            raizAVL = inserirAVL(raizAVL, inserir[j]);
        }
        // Remover valores
        for (int j = 0; j < quantidadeRemover; j++) {
            raizAVL = removerAVL(raizAVL, remover[j]);
        }

        fim = clock();
        tempoExecucaoAVL += ((double) (fim - inicio) / CLOCKS_PER_SEC);

        tamanhoAVL += quantidadeInserir - quantidadeRemover;

        free(numerosAVL);
        free(inserir);
        free(remover);
        free(arrayRemoverRand);
    }

    // Loops Arvore Rubro
    srand(seed);
    int tamanhoRN = tamanhoInicial;
    for (int i = 0; i < loops; i++) {
        int maiorValor = maiorValorRN(raizRN);
        int *numerosRN = malloc(tamanhoRN * sizeof(int));
        int indice = 0;
        preencherArrayRN(raizRN, numerosRN, &indice);

        int quantidadeInserir = rand() % (operacoesPorLoop - (operacoesPorLoop/5)) + (operacoesPorLoop/5);
        int quantidadeRemover = rand() % (operacoesPorLoop - (operacoesPorLoop/5)) + (operacoesPorLoop/5);

        if (tamanhoRN + quantidadeInserir > max) {
            quantidadeInserir = max - tamanhoRN;
        }
        if (tamanhoRN - quantidadeRemover < min) {
            quantidadeRemover = tamanhoRN - min;
        }
        totalInsercaoRN += quantidadeInserir;
        totalRemocaoRN += quantidadeRemover;

        int *inserir = gerarNumerosAleatorios(quantidadeInserir, 0, maiorValor + 1);
        int *remover = malloc(quantidadeRemover * sizeof(int));
        int *arrayRemoverRand = malloc(quantidadeRemover * sizeof(int));

        // Gerar índices únicos para remoção
        int j = 0;
        while (j < quantidadeRemover) {
            int temp = rand() % tamanhoRN;
            int repetido = 0;
            for (int k = 0; k < j; k++) {
                if (arrayRemoverRand[k] == temp) {
                    repetido = 1;
                    break;
                }
            }
            if (!repetido) {
                arrayRemoverRand[j] = temp;
                j++;  // só incrementa se encontrou um número único
            }
            // se repetido == 1, o loop while repete e tenta novo temp
        }
        // Gerar um array com valores da arvore, usando o index do array de índices únicos, assim nao vai remover o mesmo index duas vezes
        for (int j = 0; j < quantidadeRemover; j++) {
            remover[j] = numerosRN[arrayRemoverRand[j]];
        }
        
        inicio = clock();
        // Inserir valores
        for (int j = 0; j < quantidadeInserir; j++) {
            raizRN = inserirRN(raizRN, inserir[j]);
        }
        // Remover valores
        for (int j = 0; j < quantidadeRemover; j++) {
            raizRN = removerRN(raizRN, buscarRN(raizRN, remover[j]), remover[j]);
        }

        fim = clock();
        tempoExecucaoRN += ((double) (fim - inicio) / CLOCKS_PER_SEC);

        tamanhoRN += quantidadeInserir - quantidadeRemover;

        free(numerosRN);
        free(inserir);
        free(remover);
        free(arrayRemoverRand);
    }

    printf("Foram realizados ");
    imprimirComPontos(loops);
    printf(" loops.\n");

    printf("Na arvore AVL:\n");
    printf("  Insercoes: ");
    imprimirComPontos(totalInsercaoAVL);
    printf("\n  Remocoes: ");
    imprimirComPontos(totalRemocaoAVL);
    printf("\n");

    printf("Na arvore Rubro-Negra:\n");
    printf("  Insercoes: ");
    imprimirComPontos(totalInsercaoRN);
    printf("\n  Remocoes: ");
    imprimirComPontos(totalRemocaoRN);
    printf("\n");

    printf("A ideia eh que a quantidade de insercoes e remocoes sejam iguals entre as duas arvores, obviamente, mas foi printado os dois casos so para garatir\n");
    printf("\n");
    printf(" Tempo de insercao e remocao da AVL foi: %.6f\n", tempoExecucaoAVL);
    printf(" Tempo de insercao e remocao da Rubro foi: %.6f\n", tempoExecucaoRN);

    int espacosInsercaoAVL = 10, espacosInsercaoRN = 10;
    int tamanhoInsercaoAVL = 1, tempTotalInsercaoAVL = totalInsercaoAVL;
    int tamanhoInsercaoRN = 1, tempTotalInsercaoRN = totalInsercaoRN;
    while (tempTotalInsercaoAVL / 10 >= 1) {
        tamanhoInsercaoAVL++;
        tempTotalInsercaoAVL = tempTotalInsercaoAVL / 10;
    }
    tamanhoInsercaoAVL += (int) ((tamanhoInsercaoAVL - 1)/3);
    espacosInsercaoAVL = espacosInsercaoAVL - tamanhoInsercaoAVL;
    while (tempTotalInsercaoRN / 10 >= 1) {
        tamanhoInsercaoRN++;
        tempTotalInsercaoRN = tempTotalInsercaoRN / 10;
    }
    tamanhoInsercaoRN += (int) ((tamanhoInsercaoRN - 1)/3);
    espacosInsercaoRN = espacosInsercaoRN - tamanhoInsercaoRN;

    int espacosRemocaoAVL = 10, espacosRemocaoRN = 10;
    int tamanhoRemocaoAVL = 1, tempTotalRemocaoAVL = totalRemocaoAVL;
    int tamanhoRemocaoRN = 1, tempTotalRemocaoRN = totalRemocaoRN;
    while (tempTotalRemocaoAVL / 10 >= 1) {
        tamanhoRemocaoAVL++;
        tempTotalRemocaoAVL = tempTotalRemocaoAVL / 10;
    }
    tamanhoRemocaoAVL += (int) ((tamanhoRemocaoAVL - 1)/3);
    espacosRemocaoAVL = espacosRemocaoAVL - tamanhoRemocaoAVL;
    while (tempTotalRemocaoRN / 10 >= 1) {
        tamanhoRemocaoRN++;
        tempTotalRemocaoRN = tempTotalRemocaoRN / 10;
    }
    tamanhoRemocaoRN += (int) ((tamanhoRemocaoRN - 1)/3);
    espacosRemocaoRN = espacosRemocaoRN - tamanhoRemocaoRN;

    int espacosLoop = 7;
    int tamanhoLoop = 1, tempTotalLoop = loops;
    while (tempTotalLoop / 10 >= 1) {
        tamanhoLoop++;
        tempTotalLoop = tempTotalLoop / 10;
    }
    tamanhoLoop += (int) ((tamanhoLoop - 1)/3);
    espacosLoop = espacosLoop - tamanhoLoop;

    printf("\n============================ TEMPO MEDIO ===========================\n");
    printf("| Arvore       | Tempo (segundos) | Insercoes | Remocoes  | Loops  |\n");
    printf("|--------------|---------------------------------------------------|\n");
    printf("| AVL          | %.6f        ", tempoExecucaoAVL);

    if (tempoExecucaoAVL < 10 || tempoExecucaoRN < 10) {
        printf(" ");
    }
    printf("| ");
    imprimirComPontos(totalInsercaoAVL);
    for (int i = 0; i < espacosInsercaoAVL && espacosInsercaoRN; i++) {
        printf(" ");
    }
    printf("| ");
    imprimirComPontos(totalRemocaoAVL);
    for (int i = 0; i < espacosRemocaoAVL && espacosRemocaoRN; i++) {
        printf(" ");
    }
    printf("| ");
    imprimirComPontos(loops);
    for (int i = 0; i < espacosLoop; i++) {
        printf(" ");
    }
    printf("|\n");
    //
    printf("| Rubro-Negra  | %.6f        ", tempoExecucaoRN);

    if (tempoExecucaoAVL < 10 || tempoExecucaoRN < 10) {
        printf(" ");
    }
    printf("| ");
    imprimirComPontos(totalInsercaoRN);
    for (int i = 0; i < espacosInsercaoAVL && espacosInsercaoRN; i++) {
        printf(" ");
    }
    printf("| ");
    imprimirComPontos(totalRemocaoRN);
    for (int i = 0; i < espacosRemocaoAVL && espacosRemocaoRN; i++) {
        printf(" ");
    }
    printf("| ");
    imprimirComPontos(loops);
    for (int i = 0; i < espacosLoop; i++) {
        printf(" ");
    }
    printf("|\n");
    printf("====================================================================\n");
}   