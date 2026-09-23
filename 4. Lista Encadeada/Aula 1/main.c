#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct No {
    int dado;
    struct No *proximo;
} No;

// Protótipos das Operações
No* criar_no(int valor);
void inserir_inicio(No **head, int valor);
void inserir_fim(No **head, int valor);
void imprimir_lista(const No *head);
bool buscar(const No *head, int valor);
bool remover(No **head, int valor);
void liberar_lista(No **head);
int tamanho_lista(const No *head);

int main(void) {
    No *head = NULL; // Inicialmente a lista está VAZIA

    printf("=== INSERÇÃO NO INÍCIO (O(1)) ===\n");
    inserir_inicio(&head, 30);
    inserir_inicio(&head, 20);
    inserir_inicio(&head, 10);
    imprimir_lista(head); // Exibe: 10 -> 20 -> 30 -> NULL

    printf("\n=== INSERÇÃO NO FIM (O(n)) ===\n");
    inserir_fim(&head, 40);
    imprimir_lista(head); // Exibe: 10 -> 20 -> 30 -> 40 -> NULL

    printf("\n=== TAMANHO DA LISTA ===\n");
    printf("Tamanho da lista: %d\n", tamanho_lista(head));

    printf("\n=== BUSCA ===\n");
    int chave = 20;
    printf("Buscando %d: %s\n", chave, buscar(head, chave) ? "Encontrado!" : "Nao encontrado.");

    printf("\n=== REMOÇÃO ===\n");
    printf("Removendo 20...\n");
    remover(&head, 20);
    imprimir_lista(head); // Exibe: 10 -> 30 -> 40 -> NULL

    printf("\n=== TAMANHO DA LISTA ===\n");
    printf("Tamanho da lista: %d\n", tamanho_lista(head));

    // Desalocação completa da lista no Heap
    liberar_lista(&head);
    printf("\nMemoria liberada com sucesso. Head agora vale: %p\n", (void*)head);

    return 0;
}

// ----------------------------------------------------------------------------
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ----------------------------------------------------------------------------

// Função Auxiliar: Cria um novo nó isolado no Heap
No* criar_no(int valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        printf("[ ERRO ] Falha ao alocar memoria para o no!\n");
        exit(1);
    }
    novo->dado = valor;
    novo->proximo = NULL;
    return novo;
}

// 1. Inserção no Início - Complexidade O(1)
void inserir_inicio(No **head, int valor) {
    No *novo = criar_no(valor);
    novo->proximo = *head; // O novo nó aponta para o antigo primeiro
    *head = novo;          // O ponteiro head da main passa a ser o novo nó
}

// 2. Inserção no Fim - Complexidade O(n)
void inserir_fim(No **head, int valor) {
    No *novo = criar_no(valor);

    // Se a lista estiver vazia, o novo nó vira o head
    if (*head == NULL) {
        *head = novo;
        return;
    }

    // Percorre até o último nó (aquele cujo proximo == NULL)
    No *atual = *head;
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }

    atual->proximo = novo; // Conecta o último nó ao novo nó
}

// 3. Impressão da Lista - Recorrendo de nó em nó
void imprimir_lista(const No *head) {
    const No *atual = head;
    printf("Head -> ");
    while (atual != NULL) {
        printf("[%d] -> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

// 4. Busca Linear
bool buscar(const No *head, int valor) {
    const No *atual = head;
    while (atual != NULL) {
        if (atual->dado == valor) return true;
        atual = atual->proximo;
    }
    return false;
}

// 5. Remoção de um Nó por Valor
bool remover(No **head, int valor) {
    if (*head == NULL) return false; // Lista vazia

    No *atual = *head;
    No *anterior = NULL;

    // Caso Especial: O elemento a ser removido é o PRIMEIRO nó
    if (atual->dado == valor) {
        *head = atual->proximo; // Atualiza o head para o segundo nó
        free(atual);
        return true;
    }

    // Busca o elemento guardando a referência do nó anterior
    while (atual != NULL && atual->dado != valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return false; // Elemento não encontrado

    // Desconecta o nó da lista e conecta o anterior ao próximo do atual
    anterior->proximo = atual->proximo;
    free(atual);
    return true;
}

// 6. Desalocação da Lista (Evitando Memory Leak)
void liberar_lista(No **head) {
    No *atual = *head;
    No *proximo_no = NULL;

    while (atual != NULL) {
        proximo_no = atual->proximo; // Salva a referência do próximo antes de dar free!
        free(atual);
        atual = proximo_no;
    }

    *head = NULL; // Limpa o ponteiro da main
}

int tamanho_lista(const No *head) {
    int tamanho = 0;

    const No *atual = head;

    while (atual != NULL) {
        tamanho++;
        atual = atual->proximo;
    }

    return tamanho;
}