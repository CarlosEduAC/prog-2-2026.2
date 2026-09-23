#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int dado;
    struct No *anterior;
    struct No *proximo;
} No;

typedef struct {
    No *head;
    No *tail;
    int qtd;
} Lista;

// Funções Auxiliares de Suporte
Lista* criar_lista(void) {
    Lista *l = (Lista *) malloc(sizeof(Lista));
    if (l == NULL) exit(1);
    l->head = NULL;
    l->tail = NULL;
    l->qtd = 0;
    return l;
}

void inserir_fim(Lista *l, int valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) exit(1);
    novo->dado = valor;
    novo->proximo = NULL;
    novo->anterior = l->tail;

    if (l->tail == NULL) {
        l->head = novo;
        l->tail = novo;
    } else {
        l->tail->proximo = novo;
        l->tail = novo;
    }
    l->qtd++;
}

void imprimir_lista(const Lista *l) {
    const No *atual = l->head;
    printf("Head <-> ");
    while (atual != NULL) {
        printf("[%d] <-> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL (Total: %d)\n", l->qtd);
}

// Solução do Exercício 1: Troca do Primeiro com o Último Nó

void trocar_primeiro_ultimo(Lista *l) {
    // Casos de Borda: Lista vazia ou com apenas 1 nó não precisa trocar
    if (l == NULL || l->head == NULL || l->head == l->tail) {
        return;
    }

    No *p = l->head; // Primeiro nó
    No *u = l->tail; // Último nó

    // Caso Especial: Lista com exatamente 2 elementos
    if (p->proximo == u) {
        p->proximo = NULL;
        p->anterior = u;
        u->proximo = p;
        u->anterior = NULL;
    }
    // Caso Geral: Lista com 3 ou mais elementos
    else {
        No *segundo = p->proximo;
        No *penultimo = u->anterior;

        // Ajusta o antigo primeiro (p) na posição do último
        p->proximo = NULL;
        p->anterior = penultimo;
        penultimo->proximo = p;

        // Ajusta o antigo último (u) na posição do primeiro
        u->anterior = NULL;
        u->proximo = segundo;
        segundo->anterior = u;
    }

    // Atualiza os ponteiros de extremidade da struct Lista
    l->head = u;
    l->tail = p;
}

// Solução do Exercício 2: Busca Bidirecional Otimizada

No* buscar_otimizado(const Lista *l, int valor, int posicao_estimada) {
    if (l == NULL || l->head == NULL) return NULL;

    // Se a posição estimada está no primeiro meio da lista -> Começa do HEAD
    if (posicao_estimada < l->qtd / 2) {
        No *atual = l->head;
        while (atual != NULL) {
            if (atual->dado == valor) return atual;
            atual = atual->proximo;
        }
    }
    // Se a posição estimada está no segundo meio -> Começa do TAIL
    else {
        No *atual = l->tail;
        while (atual != NULL) {
            if (atual->dado == valor) return atual;
            atual = atual->anterior;
        }
    }

    return NULL; // Não encontrado
}

// Solução do Exercício 3: Remoção de Todos os Pares

int remover_pares(Lista *l) {
    if (l == NULL || l->head == NULL) return 0;

    No *atual = l->head;
    int removidos = 0;

    while (atual != NULL) {
        No *proximo_no = atual->proximo; // Salva o próximo antes de apagar

        if (atual->dado % 2 == 0) {
            // Ajusta o nó anterior
            if (atual->anterior != NULL) {
                atual->anterior->proximo = atual->proximo;
            } else {
                l->head = atual->proximo; // O removido era o head
            }

            // Ajusta o nó próximo
            if (atual->proximo != NULL) {
                atual->proximo->anterior = atual->anterior;
            } else {
                l->tail = atual->anterior; // O removido era o tail
            }

            free(atual);
            l->qtd--;
            removidos++;
        }

        atual = proximo_no; // Avança para o próximo nó salvo
    }

    return removidos;
}

int main(void) {
    Lista *l = criar_lista();

    inserir_fim(l, 10);
    inserir_fim(l, 15);
    inserir_fim(l, 20);
    inserir_fim(l, 25);
    inserir_fim(l, 30);

    printf("Lista Original:\n");
    imprimir_lista(l); // 10 <-> 15 <-> 20 <-> 25 <-> 30

    printf("\n--- Teste Ex 1: Trocar Primeiro com Ultimo ---\n");
    trocar_primeiro_ultimo(l);
    imprimir_lista(l); // 30 <-> 15 <-> 20 <-> 25 <-> 10

    printf("\n--- Teste Ex 2: Busca Otimizada ---\n");
    No *res = buscar_otimizado(l, 25, 3);
    if (res) printf("Valor 25 encontrado no no: %p\n", (void*)res);

    printf("\n--- Teste Ex 3: Remover Pares ---\n");
    int qtd_rem = remover_pares(l);
    printf("Foram removidos %d nos pares.\n", qtd_rem);
    imprimir_lista(l); // 15 <-> 25

    return 0;
}