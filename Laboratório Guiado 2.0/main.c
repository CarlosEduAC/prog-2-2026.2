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