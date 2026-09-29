#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *proximo;
} No;

// Função Auxiliar para criar nós
No* criar_no(int valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) exit(1);
    novo->dado = valor;
    novo->proximo = NULL;
    return novo;
}

// Função Auxiliar para imprimir a lista
void imprimir_lista(const No *head) {
    const No *atual = head;
    printf("Head -> ");
    while (atual != NULL) {
        printf("[%d] -> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

// Solução do Exercício 1

void inserir_ordenado(No **head, int valor) {
    No *novo = criar_no(valor);

    // Caso 1: Lista vazia ou o novo elemento é menor que o primeiro (inserção no início)
    if (*head == NULL || valor < (*head)->dado) {
        novo->proximo = *head;
        *head = novo;
        return;
    }

    // Caso 2: Busca a posição de inserção no meio ou no fim
    No *atual = *head;
    while (atual->proximo != NULL && atual->proximo->dado < valor) {
        atual = atual->proximo;
    }

    // Conecta o novo nó entre 'atual' e 'atual->proximo'
    novo->proximo = atual->proximo;
    atual->proximo = novo;
}

// Solução do Exercício 2

void inverter_lista(No **head) {
    No *anterior = NULL;
    No *atual = *head;
    No *proximo = NULL;

    while (atual != NULL) {
        proximo = atual->proximo; // 1. Salva o próximo nó da sequência
        atual->proximo = anterior; // 2. Inverte a direção do elo
        anterior = atual;          // 3. Avança o ponteiro 'anterior'
        atual = proximo;           // 4. Avança o ponteiro 'atual'
    }

    *head = anterior; // Atualiza a cabeça para o novo primeiro elemento (antigo último)
}

// Solução do Exercício 3

No* fundir_listas(No *l1, No *l2) {
    // Caso de Borda: Se uma das listas for vazia, retorna a outra
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;

    No *head = NULL;

    // Define o primeiro nó da lista resultante
    if (l1->dado <= l2->dado) {
        head = l1;
        l1 = l1->proximo;
    } else {
        head = l2;
        l2 = l2->proximo;
    }

    No *atual = head;

    // Intercala os nós enquanto ambas as listas tiverem elementos
    while (l1 != NULL && l2 != NULL) {
        if (l1->dado <= l2->dado) {
            atual->proximo = l1;
            l1 = l1->proximo;
        } else {
            atual->proximo = l2;
            l2 = l2->proximo;
        }
        atual = atual->proximo;
    }

    // Anexa os nós restantes da lista que ainda não terminou
    if (l1 != NULL) atual->proximo = l1;
    if (l2 != NULL) atual->proximo = l2;

    return head;
}

int main(void) {
    No *l1 = NULL;
    No *l2 = NULL;

    // Teste Exercício 1: Inserção Ordenada
    inserir_ordenado(&l1, 30);
    inserir_ordenado(&l1, 10);
    inserir_ordenado(&l1, 20);
    printf("Lista 1 Ordenada: ");
    imprimir_lista(l1); // 10 -> 20 -> 30

    // Teste Exercício 2: Inversão
    inverter_lista(&l1);
    printf("Lista 1 Invertida: ");
    imprimir_lista(l1); // 30 -> 20 -> 10

    // Reinverte para manter a ordem para o teste 3
    inverter_lista(&l1);

    // Preenche Lista 2
    inserir_ordenado(&l2, 25);
    inserir_ordenado(&l2, 5);
    printf("Lista 2 Ordenada: ");
    imprimir_lista(l2); // 5 -> 25

    // Teste Exercício 3: Fusão
    No *fundida = fundir_listas(l1, l2);
    printf("Listas Fundidas : ");
    imprimir_lista(fundida); // 5 -> 10 -> 20 -> 25 -> 30

    return 0;
}