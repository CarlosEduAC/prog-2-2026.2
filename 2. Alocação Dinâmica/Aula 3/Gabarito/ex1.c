#include <stdio.h>
#include <stdlib.h> // Biblioteca necessária para malloc(), free() e NULL
#include <stdbool.h>

// ----------------------------------------------------------------------------
// FUNÇÕES DE OPERAÇÕES MATEMÁTICAS (OPERAM EXCLUSIVAMENTE VIA PONTEIROS NO HEAP)
// ----------------------------------------------------------------------------

void somar(const float *a, const float *b, float *res) {
    *res = *a + *b;
}

void subtrair(const float *a, const float *b, float *res) {
    *res = *a - *b;
}

void multiplicar(const float *a, const float *b, float *res) {
    *res = (*a) * (*b);
}

bool dividir(const float *a, const float *b, float *res) {
    // Validação de segurança: Impede divisão por zero
    if (*b == 0.0f) {
        return false;
    }
    *res = *a / *b;
    return true;
}

// ----------------------------------------------------------------------------
// FUNÇÃO PRINCIPAL (MAIN)
// ----------------------------------------------------------------------------

int main(void) {
    // 1. Declaramos os ponteiros na Stack e inicializamos com NULL (boa prática)
    float *num1 = NULL;
    float *num2 = NULL;
    float *resultado = NULL;

    // 2. Alocação Dinâmica no Heap para cada uma das variáveis
    num1 = (float *) malloc(sizeof(float));
    num2 = (float *) malloc(sizeof(float));
    resultado = (float *) malloc(sizeof(float));

    // 3. MANDAMENTO 1: Validação de segurança obrigatória contra falha na memória
    if (num1 == NULL || num2 == NULL || resultado == NULL) {
        printf("[ ERRO CRÍTICO ] Falha ao alocar memória no Heap!\n");

        // Garante a liberação de qualquer bloco que tenha sido alocado antes do erro
        free(num1);
        free(num2);
        free(resultado);
        return 1;
    }

    // 4. Leitura dos dados de entrada do usuário
    printf("=== CALCULADORA COM ALOCAÇÃO DINÂMICA NO HEAP ===\n\n");

    // Como 'num1' e 'num2' já são endereços de memória, NÃO usamos o operador '&' no scanf
    printf("Digite o primeiro numero: ");
    scanf("%f", num1);

    printf("Digite o segundo numero : ");
    scanf("%f", num2);

    printf("\n=================================================\n");
    printf("              RESULTADOS DAS OPERAÇÕES           \n");
    printf("=================================================\n");

    // Soma
    somar(num1, num2, resultado);
    printf("Soma          (%.2f + %.2f) = %.2f\n", *num1, *num2, *resultado);

    // Subtração
    subtrair(num1, num2, resultado);
    printf("Subtracao     (%.2f - %.2f) = %.2f\n", *num1, *num2, *resultado);

    // Multiplicação
    multiplicar(num1, num2, resultado);
    printf("Multiplicacao (%.2f * %.2f) = %.2f\n", *num1, *num2, *resultado);

    // Divisão com verificação de segurança
    if (dividir(num1, num2, resultado)) {
        printf("Divisao       (%.2f / %.2f) = %.2f\n", *num1, *num2, *resultado);
    } else {
        printf("Divisao       (%.2f / %.2f) = [ ERRO: Divisao por zero! ]\n", *num1, *num2);
    }

    printf("=================================================\n");

    // 5. MANDAMENTO 2: Desalocação obrigatória da memória no Heap
    free(num1);
    free(num2);
    free(resultado);

    // 6. MANDAMENTO 3: Redefinição dos ponteiros para NULL para evitar ponteiros pendentes
    num1 = NULL;
    num2 = NULL;
    resultado = NULL;

    printf("\n[ SUCESSO ] Toda a memoria do Heap foi desalocada corretamente.\n");

    return 0;
}