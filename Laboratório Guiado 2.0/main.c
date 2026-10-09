#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Dados do Pedido
typedef struct {
    int id;
    char cliente[40];
    float valor;
} Pedido;

// 1. Nó para Fila e Lista Dupla
typedef struct No {
    Pedido dado;
    struct No *anterior;
    struct No *proximo;
} No;

// 2. Fila Dinâmica de Atendimento (FIFO)
typedef struct {
    No *inicio;
    No *fim;
    int qtd;
} FilaProcessamento;

// 3. Lista Duplamente Encadeada de Histórico
typedef struct {
    No *head;
    No *tail;
    int qtd;
} ListaHistorico;

// 4. Pilha Dinâmica para Ações de Undo (LIFO)
typedef struct NoPilha {
    int id_pedido_afetado;
    char tipo_acao[20]; // "PROCESSAR" ou "CANCELAR"
    struct NoPilha *proximo;
} NoPilha;

typedef struct {
    NoPilha *topo;
    int qtd;
} PilhaUndo;

void receber_pedido(FilaProcessamento *f, int id, const char *cliente, float valor);
void registrar_undo(PilhaUndo *p, int id_pedido, const char *acao);
bool processar_proximo_pedido(FilaProcessamento *f, ListaHistorico *h, PilhaUndo *u);
void exibir_historico_recursivo_inverso(const No *no_atual);
bool desfazer_ultima_acao(FilaProcessamento *f, ListaHistorico *h, PilhaUndo *u);
void liberar_nos_recursivo(No *atual);
void destruir_sistema(FilaProcessamento *f, ListaHistorico *h, PilhaUndo *u);

int main(void) {
    FilaProcessamento *fila = (FilaProcessamento *) malloc(sizeof(FilaProcessamento));
    ListaHistorico *historico = (ListaHistorico *) malloc(sizeof(ListaHistorico));
    PilhaUndo *pilha_undo = (PilhaUndo *) malloc(sizeof(PilhaUndo));

    if (fila == NULL || historico == NULL || pilha_undo == NULL) return 1;

    fila->inicio = fila->fim = NULL; fila->qtd = 0;
    historico->head = historico->tail = NULL; historico->qtd = 0;
    pilha_undo->topo = NULL; pilha_undo->qtd = 0;

    printf("=== 1. RECEBENDO PEDIDOS NO SISTEMA ===\n");
    receber_pedido(fila, 101, "Ana Silva", 150.0f);
    receber_pedido(fila, 102, "Bruno Costa", 89.90f);
    receber_pedido(fila, 103, "Carla Souza", 420.50f);

    printf("\n=== 2. PROCESSANDO ATENDIMENTOS ===\n");
    processar_proximo_pedido(fila, historico, pilha_undo); // Processa 101
    processar_proximo_pedido(fila, historico, pilha_undo); // Processa 102

    printf("\n=== 3. HISTÓRICO DE PROCESSADOS (RECURSIVO INVERSO) ===\n");
    exibir_historico_recursivo_inverso(historico->tail);

    printf("\n=== 4. EXECUTANDO OPERAÇÃO UNDO (DESFAZER) ===\n");
    desfazer_ultima_acao(fila, historico, pilha_undo); // Desfaz 102

    printf("\n=== 5. HISTÓRICO DE PROCESSADOS APÓS UNDO ===\n");
    exibir_historico_recursivo_inverso(historico->tail);

    destruir_sistema(fila, historico, pilha_undo);
    return 0;
}

// Inserção na Fila de Processamento

void receber_pedido(FilaProcessamento *f, int id, const char *cliente, float valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        printf("[ ERRO ] Falha ao alocar memoria para o pedido!\n");
        return;
    }

    novo->dado.id = id;
    strcpy(novo->dado.cliente, cliente);
    novo->dado.valor = valor;
    novo->anterior = NULL;
    novo->proximo = NULL;

    if (f->fim == NULL) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->proximo = novo;
        novo->anterior = f->fim;
        f->fim = novo;
    }
    f->qtd++;
    printf("[ LOG ] Pedido #%d enfileirado para o cliente %s.\n", id, cliente);
}

// Processamento e Transferência entre Estruturas

void registrar_undo(PilhaUndo *p, int id_pedido, const char *acao) {
    NoPilha *novo = (NoPilha *) malloc(sizeof(NoPilha));
    if (novo == NULL) return;

    novo->id_pedido_afetado = id_pedido;
    strcpy(novo->tipo_acao, acao);
    novo->proximo = p->topo;
    p->topo = novo;
    p->qtd++;
}

bool processar_proximo_pedido(FilaProcessamento *f, ListaHistorico *h, PilhaUndo *u) {
    if (f->inicio == NULL) {
        printf("[ AVISO ] Nenhum pedido pendente na fila para processar.\n");
        return false;
    }

    // 1. Desenfileira da Fila (FIFO)
    No *removido = f->inicio;
    f->inicio = f->inicio->proximo;
    if (f->inicio != NULL) {
        f->inicio->anterior = NULL;
    } else {
        f->fim = NULL;
    }
    f->qtd--;

    // 2. Insere na Lista Dupla de Histórico (Tail)
    removido->proximo = NULL;
    removido->anterior = h->tail;

    if (h->tail == NULL) {
        h->head = removido;
        h->tail = removido;
    } else {
        h->tail->proximo = removido;
        h->tail = removido;
    }
    h->qtd++;

    // 3. Empilha a ação na Pilha de Undo (LIFO)
    registrar_undo(u, removido->dado.id, "PROCESSAR");

    printf("[ SUCESSO ] Pedido #%d processado e movido para o historico!\n", removido->dado.id);
    return true;
}

// Exibição Recursiva do Histórico Inverso

void exibir_historico_recursivo_inverso(const No *no_atual) {
    // CASO BASE: Ponteiro nulo (atingiu o início da lista)
    if (no_atual == NULL) {
        return;
    }

    // AÇÃO: Imprime o pedido atual
    printf("  -> Pedido #%d | Cliente: %-15s | Valor: R$ %.2f\n",
           no_atual->dado.id, no_atual->dado.cliente, no_atual->dado.valor);

    // PASSO RECURSIVO: Avança para o nó anterior
    exibir_historico_recursivo_inverso(no_atual->anterior);
}

// Operação de Desfazer

bool desfazer_ultima_acao(FilaProcessamento *f, ListaHistorico *h, PilhaUndo *u) {
    if (u->topo == NULL) {
        printf("[ AVISO ] Nenhuma acao no historico de Undo para desfazer.\n");
        return false;
    }

    // 1. Pop na Pilha de Undo (LIFO)
    NoPilha *acao = u->topo;
    u->topo = u->topo->proximo;
    u->qtd--;

    int id_alvo = acao->id_pedido_afetado;
    free(acao);

    // 2. Localiza o pedido na Lista Dupla de Histórico
    No *atual = h->head;
    while (atual != NULL && atual->dado.id != id_alvo) {
        atual = atual->proximo;
    }

    if (atual == NULL) return false;

    // 3. Remove o nó da Lista Dupla
    if (atual->anterior != NULL) atual->anterior->proximo = atual->proximo;
    else h->head = atual->proximo;

    if (atual->proximo != NULL) atual->proximo->anterior = atual->anterior;
    else h->tail = atual->anterior;

    h->qtd--;

    // 4. Reinsere o pedido no INÍCIO da Fila de Processamento
    atual->anterior = NULL;
    atual->proximo = f->inicio;

    if (f->inicio != NULL) {
        f->inicio->anterior = atual;
    } else {
        f->fim = atual;
    }
    f->inicio = atual;
    f->qtd++;

    printf("[ UNDO ] Acao desfeita! Pedido #%d devolvido para a fila de atendimento.\n", id_alvo);
    return true;
}

// Desalocação Dinâmica Completa

void liberar_nos_recursivo(No *atual) {
    if (atual == NULL) return; // Caso Base

    No *proximo = atual->proximo;
    free(atual);
    liberar_nos_recursivo(proximo); // Passo Recursivo
}

void destruir_sistema(FilaProcessamento *f, ListaHistorico *h, PilhaUndo *u) {
    // Libera os nós da Fila e da Lista Dupla
    liberar_nos_recursivo(f->inicio);
    liberar_nos_recursivo(h->head);

    // Libera a Pilha de Undo
    NoPilha *atual_p = u->topo;
    while (atual_p != NULL) {
        NoPilha *temp = atual_p->proximo;
        free(atual_p);
        atual_p = temp;
    }

    // Libera as estruturas descritoras
    free(f);
    free(h);
    free(u);
    printf("\n[ MEMÓRIA ] Toda a memoria do Heap foi liberada com sucesso!\n");
}