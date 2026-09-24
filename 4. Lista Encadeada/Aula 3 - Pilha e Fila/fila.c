#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int dado;
    struct No *proximo;
} No;

typedef struct {
    No *inicio; // Para remoção (Dequeue)
    No *fim;    // Para inserção (Enqueue)
    int qtd;
} Fila;

Fila* create(void) {
    Fila *f = (Fila *) malloc(sizeof(Fila));
    if (f == NULL) exit(1);
    f->inicio = NULL;
    f->fim = NULL;
    f->qtd = 0;
    return f;
}

// Enqueue (Enfileirar) - Inserção na Cauda -> O(1)
void enqueue(Fila *f, int valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) return;

    novo->dado = valor;
    novo->proximo = NULL;

    if (f->fim == NULL) { // Fila vazia
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->proximo = novo;
        f->fim = novo;
    }
    f->qtd++;
}

// Dequeue (Desenfileirar) - Remoção na Cabeça -> O(1)
bool dequeue(Fila *f, int *valor_out) {
    if (f->inicio == NULL) return false; // Fila Vazia (Underflow)

    No *temp = f->inicio;
    *valor_out = temp->dado;

    f->inicio = f->inicio->proximo;

    if (f->inicio == NULL) { // Se a fila ficou vazia
        f->fim = NULL;
    }

    free(temp);
    f->qtd--;
    return true;
}

int main(void) {
    printf("\nCriando fila...\n\n");

    Fila *f = create();
    int valor;

    printf("\033[0;31mFila antes de qualquer operação\033[0m\n");
    printf("Início da fila: %s\n", (f->inicio ? "Existe" : "Vazia"));
    printf("Fim da fila: %s\n", (f->fim ? "Existe" : "Vazia"));
    printf("Quantidade de elementos na fila: %d\n", f->qtd);
    printf("\n");

    printf("Enfileirando elementos...\n\n");
    enqueue(f, 10);
    enqueue(f, 20);
    enqueue(f, 30);

    printf("\033[0;31mFila após enfileirar elementos\033[0m\n");
    printf("Início da fila: %s\n", (f->inicio ? "Existe" : "Vazia"));
    printf("Fim da fila: %s\n", (f->fim ? "Existe" : "Vazia"));
    printf("Quantidade de elementos na fila: %d\n", f->qtd);
    printf("\n");

    printf("Desenfileirando elementos...\n\n");
    while (dequeue(f, &valor)) {
        printf("Desenfileirado: %d\n", valor);
    }

    printf("\033[0;31m\nFila após desenfileirar elementos\033[0m\n");
    printf("Início da fila: %s\n", (f->inicio ? "Existe" : "Vazia"));
    printf("Fim da fila: %s\n", (f->fim ? "Existe" : "Vazia"));
    printf("Quantidade de elementos na fila: %d\n", f->qtd);
    printf("\n");

    free(f);
    return 0;
}