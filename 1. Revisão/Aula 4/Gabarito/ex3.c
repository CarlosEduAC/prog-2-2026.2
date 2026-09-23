#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define TOTAL_CONTAS 3

typedef struct {
    int numero_conta;
    char nome_titular[50];
    float saldo;
} ContaBancaria;

// Modifica a struct original usando o operador seta (->)
bool realizar_deposito(ContaBancaria *c, float valor) {
    if (valor <= 0) return false;
    c->saldo += valor;
    return true;
}

bool realizar_saque(ContaBancaria *c, float valor) {
    if (valor <= 0 || c->saldo < valor) return false;
    c->saldo -= valor;
    return true;
}

// Retorna o índice no vetor
int buscar_conta(const ContaBancaria contas[], int tam, int num_procurado) {
    for (int i = 0; i < tam; i++) {
        if (contas[i].numero_conta == num_procurado) {
            return i; // Encontrado no índice 'i'
        }
    }
    return -1; // Não encontrado
}

int main(void) {
    ContaBancaria banco[TOTAL_CONTAS] = {
        {1001, "Carlos Silva", 1500.00f},
        {1002, "Mariana Costa", 3200.50f},
        {1003, "Roberto Alves", 450.00f}
    };

    int conta_busca = 1002;
    int idx = buscar_conta(banco, TOTAL_CONTAS, conta_busca);

    if (idx != -1) {
        printf("Conta %d encontrada! Titular: %s | Saldo Atual: R$ %.2f\n",
               banco[idx].numero_conta, banco[idx].nome_titular, banco[idx].saldo);

        // Operação de Saque por referência
        printf("\nTentando sacar R$ 500.00...\n");
        if (realizar_saque(&banco[idx], 500.00f)) {
            printf("[ SUCESSO ] Saque realizado. Novo Saldo: R$ %.2f\n", banco[idx].saldo);
        } else {
            printf("[ ERRO ] Saque recusado (Saldo insuficiente ou valor invalido).\n");
        }

        // Operação de Depósito por referência
        printf("\nTentando depositar R$ 200.00...\n");
        if (realizar_deposito(&banco[idx], 200.00f)) {
            printf("[ SUCESSO ] Deposito realizado. Novo Saldo: R$ %.2f\n", banco[idx].saldo);
        }
    } else {
        printf("Conta %d nao foi encontrada no sistema.\n", conta_busca);
    }

    return 0;
}