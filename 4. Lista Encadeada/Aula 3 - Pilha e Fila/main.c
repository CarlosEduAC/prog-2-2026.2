#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    char dado;
    struct No *proximo;
} No;

typedef struct {
    No *topo;
    int qtd;
} Pilha;

Pilha* create(void) {
    Pilha *p = (Pilha *) malloc(sizeof(Pilha));
    if (p == NULL) exit(1);
    p->topo = NULL;
    p->qtd = 0;
    return p;
}

void push(Pilha *p, char valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return;

    novo->dado = valor;
    novo->proximo = p->topo;
    p->topo = novo;
    p->qtd++;
}

bool pop(Pilha *p, char *valor_out) {
    if (p->topo == NULL) return false; // Pilha Vazia (Underflow)

    No *temp = p->topo;
    *valor_out = temp->dado;

    p->topo = p->topo->proximo;
    free(temp);
    p->qtd--;
    return true;
}

void clear(Pilha *p) {
    No *atual = p->topo;
    while (atual != NULL) {
        No *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    p->topo = NULL;
    p->qtd = 0;
}

bool verificar_parenteses(const char *expr) {
    Pilha *p = create(); // Supondo Pilha adaptada para 'char'

    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(') push(p, '(');

        else if (expr[i] == ')') {
            char dummy;

            if (!pop(p, &dummy)) {
                clear(p);
                return false;
            } // Fecha sem abrir
        }
    }

    bool ok = (p->qtd == 0); // Vazia no final = balanceada
    clear(p);
    return ok;
}

int main(void) {
    const char *expressao = "((2 + 3) * 5)";
    const char *expressao2 = ")(2 + 3)( ";
    const char *expressao3 = "((2 + 3)";

    if (verificar_parenteses(expressao)) {
        printf("Expressao balanceada\n");
    } else {
        printf("Expressao nao balanceada\n");
    }

    if (verificar_parenteses(expressao2)) {
        printf("Expressao 2 balanceada\n");
    } else {
        printf("Expressao 2 nao balanceada\n");
    }

    if (verificar_parenteses(expressao3)) {
        printf("Expressao 3 balanceada\n");
    } else {
        printf("Expressao 3 nao balanceada\n");
    }

    return 0;
}