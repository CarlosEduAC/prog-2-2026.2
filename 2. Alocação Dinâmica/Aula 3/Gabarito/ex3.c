#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int numero_conta;
    char titular[40];
    float saldo;
} ContaBancaria;

bool transferir(ContaBancaria *origem, ContaBancaria *destino, float valor) {
    if (origem == NULL || destino == NULL || valor <= 0.0f) {
        return false;
    }

    if (origem->saldo < valor) {
        return false; // Saldo insuficiente
    }

    origem->saldo -= valor;
    destino->saldo += valor;
    return true;
}

int main(void) {
    // Alocação das duas contas no Heap
    ContaBancaria *c1 = (ContaBancaria *) malloc(sizeof(ContaBancaria));
    ContaBancaria *c2 = (ContaBancaria *) malloc(sizeof(ContaBancaria));

    if (c1 == NULL || c2 == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }

    // Inicialização da Conta 1
    c1->numero_conta = 101;
    strcpy(c1->titular, "Carlos Eduardo");
    c1->saldo = 1000.00f;

    // Inicialização da Conta 2
    c2->numero_conta = 202;
    strcpy(c2->titular, "Ana Maria");
    c2->saldo = 200.00f;

    printf("=== SALDOS INICIAIS ===\n");
    printf("%s: R$ %.2f\n", c1->titular, c1->saldo);
    printf("%s: R$ %.2f\n\n", c2->titular, c2->saldo);

    float valor_transf = 350.00f;
    printf("Transferindo R$ %.2f de %s para %s...\n\n", valor_transf, c1->titular, c2->titular);

    if (transferir(c1, c2, valor_transf)) {
        printf("[ SUCESSO ] Transferencia realizada!\n");
    } else {
        printf("[ ERRO ] Falha na transferencia.\n");
    }

    printf("\n=== SALDOS FINAIS ===\n");
    printf("%s: R$ %.2f\n", c1->titular, c1->saldo);
    printf("%s: R$ %.2f\n", c2->titular, c2->saldo);

    // Desalocação obrigatória
    free(c1); c1 = NULL;
    free(c2); c2 = NULL;

    return 0;
}