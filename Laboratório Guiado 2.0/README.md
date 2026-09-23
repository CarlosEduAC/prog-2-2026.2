# Sistema de Logística de E-commerce e Desfazer de Pedidos (Undo)

Objetivo: Unificar Alocação Dinâmica, Structs, Recursividade, Listas Duplamente Encadeadas, Pilhas e Filas em uma única aplicação prática em C.

Ferramentas Exigidas: Compilador C (gcc ou clang), Terminal de Comando e Utilitário de Análise de Memória (valgrind).

Critério de Qualidade: O código deve ser compilado sem warnings (-Wall), não apresentar falhas de segmentação (Segmentation Fault) e apresentar zero vazamentos de memória ao final da execução.

## Contexto e Arquitetura do Sistema na Memória RAM

Você foi contratado para implementar o núcleo do motor de logística de uma plataforma de E-commerce. O sistema deve operar três estruturas conectadas no Heap:

1. Fila de Processamento (FIFO): Novos pedidos entram na cauda e aguardam serem processados por ordem de chegada.

2. Lista Duplamente Encadeada de Histórico: Pedidos processados são movidos para o histórico, permitindo navegação para a frente e para trás.

3.Pilha de Desfazer/Undo (LIFO): Guarda o histórico das ações recentes. Ao acionar o "Undo", a última ação é desfeita e o pedido retorna para a fila de processamento.

```txt

ESTRUTURA INTEGRADA DO SISTEMA LOGÍSTICO

 1. FILA DE PROCESSAMENTO (FIFO) ───> Enfileira pedidos novos aguardando envio
    Início ──> [ Pedido 101 ] <──> [ Pedido 102 ] <── Fim

 2. LISTA DUPLA DE PEDIDOS PROCESSADOS ───> Histórico ativo de entregas em rota
    Head <──> [ Ptr No_101 ] <──> [ Ptr No_102 ] <──> Tail

 3. PILHA DE DESFAZER / UNDO (LIFO) ───> Desfaz a última ação em caso de cancelamento
    Topo ──> [ Ação: Processou 102 ] ──> [ Ação: Processou 101 ]

```

## Declaração das Estruturas

Crie o arquivo sistema_logistica.c e inclua as definições de tipos básicas:

```c

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

```

## Roteiro de Implementação Passo a Passo

### Passo 1: Inserção na Fila de Processamento (Enqueue)

Implemente a função para cadastrar pedidos na cauda da Fila de Processamento (O(1)).

`void receber_pedido(FilaProcessamento *f, int id, const char *cliente, float valor);`

### Passo 2: Processamento e Transferência entre Estruturas

Implemente a função que retira da Fila (dequeue), insere na Lista Dupla (tail) e registra a ação na Pilha de Undo (push).

`void registrar_undo(PilhaUndo *p, int id_pedido, const char *acao);`
`bool processar_proximo_pedido(FilaProcessamento *f, ListaHistorico *h, PilhaUndo *u);`

### Passo 3: Exibição Recursiva do Histórico Inverso

Implemente uma função recursiva que percorra a Lista Duplamente Encadeada a partir da cauda (tail) em direção à cabeça (head).

`void exibir_historico_recursivo_inverso(const No *no_atual);`

### Passo 4: Operação de Desfazer (Undo)

Implemente a reversão da ação: desempilhe a última ação registrada, localize o pedido na Lista Dupla, remova-o e insira-o novamente no início da Fila de Processamento.

`bool desfazer_ultima_acao(FilaProcessamento *f, ListaHistorico *h, PilhaUndo *u);`

### Passo 5: Desalocação Dinâmica Completa (Recursiva)

Garanta a destruição de todas as estruturas e a liberação total da memória RAM alocada no Heap.

`void liberar_nos_recursivo(No *atual);`
`void destruir_sistema(FilaProcessamento *f, ListaHistorico *h, PilhaUndo *u);`

## Função Principal e Fluxo de Execução

```c

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

```

## Instruções de Compilação

Compilação com Flags de Depuração:

```bash
    gcc -g -Wall sistema_logistica.c -o sistema_logistica
```

Execução Padrão:

```bash
    ./sistema_logistica
```
