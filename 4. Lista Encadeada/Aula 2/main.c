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

// Protótipos das Operações
Lista* criar_lista(void);
No* criar_no(int valor);
void inserir_inicio(Lista *l, int valor);
void inserir_fim(Lista *l, int valor);
void imprimir_inicio_fim(const Lista *l);
void imprimir_fim_inicio(const Lista *l);
bool remover(Lista *l, int valor);
void liberar_lista(Lista *l);
void inserir_apos(Lista *l, int chave, int novo_valor);

int main(void) {
    Lista *l = criar_lista();

    printf("=== INSERÇÃO NO INÍCIO E NO FIM (O(1)) ===\n");
    inserir_inicio(l, 20); // Lista: 20
    inserir_inicio(l, 10); // Lista: 10 <-> 20
    inserir_fim(l, 30);    // Lista: 10 <-> 20 <-> 30
    inserir_fim(l, 40);    // Lista: 10 <-> 20 <-> 30 <-> 40

    printf("\nImpressao do Inicio ao Fim:\n");
    imprimir_inicio_fim(l); // 10 <-> 20 <-> 30 <-> 40

    printf("\nImpressao do Fim ao Inicio (Navegacao Inversa):\n");
    imprimir_fim_inicio(l); // 40 <-> 30 <-> 20 <-> 10

    printf("\n=== REMOÇÃO DE ELEMENTOS ===\n");
    printf("Removendo 10 (Inicio)...\n");
    remover(l, 10);
    imprimir_inicio_fim(l); // 20 <-> 30 <-> 40

    printf("Removendo 40 (Fim)...\n");
    remover(l, 40);
    imprimir_inicio_fim(l); // 20 <-> 30

    printf("Removendo 30 (Meio)...\n");
    remover(l, 30);
    imprimir_inicio_fim(l); // 20

    liberar_lista(l);

    // // Teste 1: Inserir no MEIO (Inserir 25 após o 20)
    // printf("\n--- Teste 1: Inserir 25 apos o 20 (Meio) ---\n");
    // inserir_apos(l, 20, 25);
    // imprimir_lista(l); // Esperado: 10 <-> 20 <-> 25 <-> 30

    // // Teste 2: Inserir no FIM (Inserir 40 após o 30 - testando reajuste da TAIL)
    // printf("\n--- Teste 2: Inserir 40 apos o 30 (Tail) ---\n");
    // inserir_apos(l, 30, 40);
    // imprimir_lista(l); // Esperado: 10 <-> 20 <-> 25 <-> 30 <-> 40 (Tail vira 40)

    // // Teste 3: Chave inexistente
    // printf("\n--- Teste 3: Tentativa com chave inexistente (99) ---\n");
    // inserir_apos(l, 99, 100);


    return 0;
}

// ----------------------------------------------------------------------------
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ----------------------------------------------------------------------------

Lista* criar_lista(void) {
    Lista *l = (Lista *) malloc(sizeof(Lista));
    if (l == NULL) exit(1);
    l->head = NULL;
    l->tail = NULL;
    l->qtd = 0;
    return l;
}

No* criar_no(int valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) exit(1);
    novo->dado = valor;
    novo->anterior = NULL;
    novo->proximo = NULL;
    return novo;
}

// Inserção no Início - Complexidade O(1)
void inserir_inicio(Lista *l, int valor) {
    No *novo = criar_no(valor);

    if (l->head == NULL) { // Lista vazia
        l->head = novo;
        l->tail = novo;
    } else {
        novo->proximo = l->head;
        l->head->anterior = novo;
        l->head = novo;
    }
    l->qtd++;
}

// Inserção no Fim - Complexidade O(1) graças ao ponteiro 'tail'
void inserir_fim(Lista *l, int valor) {
    No *novo = criar_no(valor);

    if (l->tail == NULL) { // Lista vazia
        l->head = novo;
        l->tail = novo;
    } else {
        novo->anterior = l->tail;
        l->tail->proximo = novo;
        l->tail = novo;
    }
    l->qtd++;
}

// Impressão da Cabeça para a Cauda
void imprimir_inicio_fim(const Lista *l) {
    const No *atual = l->head;
    printf("Head <-> ");
    while (atual != NULL) {
        printf("[%d] <-> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL (Qtd: %d)\n", l->qtd);
}

// Impressão da Cauda para a Cabeça (Demonstra o uso do ponteiro 'anterior')
void imprimir_fim_inicio(const Lista *l) {
    const No *atual = l->tail;
    printf("Tail <-> ");
    while (atual != NULL) {
        printf("[%d] <-> ", atual->dado);
        atual = atual->anterior;
    }
    printf("NULL\n");
}

// Remoção Arbitrária (Ajuste dos 4 Ponteiros Possíveis)
bool remover(Lista *l, int valor) {
    if (l->head == NULL) return false;

    No *atual = l->head;

    // Busca o nó a ser removido
    while (atual != NULL && atual->dado != valor) {
        atual = atual->proximo;
    }

    if (atual == NULL) return false; // Não encontrado

    // Ajusta o ponteiro do nó ANTERIOR
    if (atual->anterior != NULL) {
        atual->anterior->proximo = atual->proximo;
    } else {
        l->head = atual->proximo; // O nó removido era o head
    }

    // Ajusta o ponteiro do nó PRÓXIMO
    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    } else {
        l->tail = atual->anterior; // O nó removido era o tail
    }

    free(atual);
    l->qtd--;
    return true;
}

// Desalocação Completa no Heap
void liberar_lista(Lista *l) {
    No *atual = l->head;
    No *proximo_no = NULL;

    while (atual != NULL) {
        proximo_no = atual->proximo;
        free(atual);
        atual = proximo_no;
    }

    free(l);
}










// ----------------------------------------------------------------------------
// SOLUÇÃO DO EXERCÍCIO: inserir_apos
// ----------------------------------------------------------------------------
void inserir_apos(Lista *l, int chave, int novo_valor) {
    // 1. Validação: Lista nula ou vazia
    if (l == NULL || l->head == NULL) {
        printf("[ AVISO ] Lista vazia ou invalida. Impossivel buscar a chave %d.\n", chave);
        return;
    }

    // 2. Busca pelo nó que contém o valor 'chave'
    No *atual = l->head;
    while (atual != NULL && atual->dado != chave) {
        atual = atual->proximo;
    }

    // Se a chave não for encontrada na lista
    if (atual == NULL) {
        printf("[ AVISO ] Chave %d nao encontrada na lista.\n", chave);
        return;
    }

    // 3. Cria o novo nó
    No *novo = criar_no(novo_valor);

    // Salva a referência do nó que atualmente vem depois de 'atual'
    No *proximo_no = atual->proximo;

    // 4. Ajuste dos 4 ELOS DE PONTEIROS:

    // ELO 1: O 'proximo' do novo nó aponta para o próximo nó antigo
    novo->proximo = proximo_no;

    // ELO 2: O 'anterior' do novo nó aponta para o nó 'atual' (a chave)
    novo->anterior = atual;

    // ELO 3: O 'proximo' do nó 'atual' passa a apontar para o novo nó
    atual->proximo = novo;

    // ELO 4 (TRATAMENTO DE BORDA):
    // Se o nó encontrado ERA O ÚLTIMO (tail), o novo nó passa a ser o novo tail!
    if (atual == l->tail) {
        l->tail = novo;
    } else {
        // Se NÃO era o último, o 'anterior' do nó seguinte deve apontar para o novo nó
        proximo_no->anterior = novo;
    }

    // 5. Incrementa a quantidade total de elementos na lista
    l->qtd++;
}