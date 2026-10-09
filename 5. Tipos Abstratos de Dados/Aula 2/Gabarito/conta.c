#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int numero_conta;
    float saldo;
    float limite_cheque_especial;
} ContaBancaria;

ContaBancaria* conta_criar(int numero, float limite) {
    if (numero <= 0) return NULL;

    ContaBancaria *c = (ContaBancaria *) malloc(sizeof(ContaBancaria));
    if (c == NULL) return NULL; // Teste defensivo de alocação

    c->numero_conta = numero;
    c->saldo = 0.0f;
    // Garantia da Invariante: limite nunca é negativo
    c->limite_cheque_especial = (limite > 0.0f) ? limite : 0.0f;

    return c;
}

bool conta_sacar(ContaBancaria *c, float valor) {
    // Proteção contra ponteiros nulos e valores de saque inválidos
    if (c == NULL || valor <= 0.0f) return false;

    // Checagem da Invariante: Saldo final não pode ultrapassar o cheque especial
    float saldo_resultante = c->saldo - valor;
    if (saldo_resultante < -c->limite_cheque_especial) {
        return false; // Operação bloqueada por violação de regra de negócio
    }

    c->saldo = saldo_resultante;
    return true;
}

// Diagnóstico de Falhas:
// Ausência de teste contra NULL: Se o malloc falhar, c->numero_conta gera um erro de Segmentation Fault.

// Invariante de limite violada: Permite limites negativos no construtor.

// Invariante de saldo violada: Permite saques ilimitados sem respeitar o limite do cheque especial ou valores de saque negativos.