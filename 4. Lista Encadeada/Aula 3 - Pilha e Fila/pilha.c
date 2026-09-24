#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int dado;
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

// Push (Empilhar) - Equivale à Inserção no Início -> O(1)
void push(Pilha *p, int valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return;

    novo->dado = valor;
    novo->proximo = p->topo;
    p->topo = novo;
    p->qtd++;
}

// Pop (Desempilhar) - Equivale à Remoção no Início -> O(1)
bool pop(Pilha *p, int *valor_out) {
    if (p->topo == NULL) return false; // Pilha Vazia (Underflow)

    No *temp = p->topo;
    *valor_out = temp->dado;

    p->topo = p->topo->proximo;
    free(temp);
    p->qtd--;
    return true;
}

// Peek (Consultar Topo sem remover) -> O(1)
bool peek(const Pilha *p, int *valor_out) {
    if (p->topo == NULL) return false;
    *valor_out = p->topo->dado;
    return true;
}

// Clear (Esvaziar Pilha) -> O(n)
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

int main(void) {
    printf("\nCriando pilha...\n\n");

    Pilha *p = create();
    int valor;

    printf("\033[0;31mPilha antes de qualquer operação\033[0m\n");
    printf("Topo da pilha: %s\n", (peek(p, &valor) ? "Existe" : "Vazia"));
    printf("Quantidade de elementos na pilha: %d\n", p->qtd);
    printf("\n");

    printf("Empilhando elementos na pilha...\n\n");

    push(p, 10);
    push(p, 20);
    push(p, 30);

    printf("\033[0;31mPilha após inserções\033[0m\n");
    printf("Topo da pilha: %s\n", (peek(p, &valor) ? "Existe" : "Vazia"));
    printf("Quantidade de elementos na pilha: %d\n", p->qtd);
    printf("\n");

    printf("Consultando o topo da pilha...\n\n");

    if (peek(p, &valor)) {
        printf("Topo da pilha: %d\n\n", valor);
    }

    printf("Desempilhando o topo da pilha...\n\n");

    if (pop(p, &valor)) {
        printf("Desempilhado: %d\n", valor);
    }

    printf("\n\033[0;31mPilha após desempilhamento\033[0m\n");

    printf("Topo da pilha: %s\n", (peek(p, &valor) ? "Existe" : "Vazia"));
    printf("Quantidade de elementos na pilha: %d\n", p->qtd);
    printf("\n");

    printf("Esvaziando a pilha...\n");
    clear(p);
    free(p);
    return 0;
}