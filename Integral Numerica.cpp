#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Função para calcular o valor da função integranda
float calcularIntegrando(float x) {
    return sqrt(6 * x - 5);
}

// Função para realizar a integração por Trapezios
float realizarTrapeziosRepetida() {
    float limiteInferior, limiteSuperior;
    int numSubintervalos;
    float resultado;
    float tamanhoSubintervalo, soma;
    int i;

    printf("Digite o limite inferior: ");
    scanf("%f", &limiteInferior);

    printf("Digite o limite superior: ");
    scanf("%f", &limiteSuperior);

    printf("Digite o número de subintervalos: ");
    scanf("%d", &numSubintervalos);

    if (numSubintervalos <= 0) {
        printf("O número de subintervalos deve ser um valor positivo.\n");
        exit(1);
    }

    // Calcula o tamanho de cada subintervalo
    tamanhoSubintervalo = (limiteSuperior - limiteInferior) / numSubintervalos;
    soma = 0;

    // Realiza a soma dos valores da função integranda em cada subintervalo
    for (i = 1; i <= numSubintervalos - 1; i++) {
        soma += calcularIntegrando(limiteInferior + tamanhoSubintervalo * i);
    }

    // Aplica a fórmula da integração por Trapezios para obter o resultado final
    resultado = (tamanhoSubintervalo / 2.0) * (calcularIntegrando(limiteInferior) + calcularIntegrando(limiteSuperior) + 2 * soma);

    return resultado;
}

// Função para realizar a integração por Quadratura Gaussiana
float realizarQuadraturaGaussiana() {
    float coeficienteA, coeficienteB;
    float integral = 0;
    float *coeficientes, *pontos;
    float limitanteInicial, limitanteFinal;
    int numPontos, i;
    FILE *arquivo;
    char nomeArquivo[15] = {"QG_grau_.txt"};

    printf("Escreva a quantidade de pontos: ");
    scanf("%i", &numPontos);
    
    // Modifica o nome do arquivo de acordo com o número de pontos
    if (numPontos == 10) {
        nomeArquivo[8] = 'd';
    } else {
        nomeArquivo[8] = numPontos + '0';
    }

    printf("Nome do arquivo: %s\n", nomeArquivo);
    printf("Escreva o limitante inicial: ");
    scanf("%f", &intervaloInicial);
    printf("Escreva o limitante final: ");
    scanf("%f", &intervaloFinal);

    coeficienteA = (limitanteFinal - limitanteInicial) / 2;
    coeficienteB = (limitanteFinal + limitanteInicial) / 2;

    // Aloca memória para os arrays de coeficientes e pontos
    float n = numPontos - 1;
    coeficientes = malloc(n * sizeof(float));
    pontos = malloc(n * sizeof(float));

    // Abre o arquivo de tabela de quadratura gaussiana
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo != NULL) {
        // Lê os coeficientes e pontos do arquivo
        for (i = 0; i < numPontos; i++) {
            fscanf(arquivo, "%f %f", &pontos[i], &coeficientes[i]);
            printf("\nCoeficiente: %f\nPonto: %f", coeficientes[i], pontos[i]);
        }

        // Calcula a integral usando a Quadratura Gaussiana
        for (i = 0; i < numPontos; i++) {
            integral += coeficientes[i] * calcularIntegrando(coeficienteA * pontos[i] + coeficienteB); // A[i]*f(t[i])  onde  x=((b-a)/2)t + (b-a)/2
            printf("\nSomatório atual: %f", integral);
        }
        integral *= coeficienteA; //dx= (b-a)/2 dt 
        return integral;
    }

    printf("\nArquivo não encontrado. Fechando o programa.\n\n");
    exit(1);
}

// Função principal
int main() {
    int escolha;
    float resultado;

    while (1) {
        printf("Escolha uma das opções abaixo:\n");
        printf("1. Realizar Integração por Trapezios\n");
        printf("2. Realizar Integração por Quadratura Gaussiana\n");
        printf("3. Sair\n");
        printf("\nEscolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                resultado = realizarTrapeziosRepetida();
                printf("O resultado da integração é aproximadamente: %f\n", resultado);
                break;

            case 2:
                resultado = realizarQuadraturaGaussiana();
                printf("O resultado da integração é aproximadamente: %f\n", resultado);
                break;

            case 3:
                exit(0);
                break;

            default:
                printf("\nOpção inválida!!\n\n");
        }

        system("PAUSE");
    }

    return 0;
}
