#include "gerenciador_tarefas.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Struct privada para cada Tarefa
typedef struct {
    int pid;
    char nome[32];
    int prioridade;
    bool ativa;
} Tarefa;

// Struct concreta privada do TAD
struct GerenciadorTarefas {
    Tarefa *fila_processos;
    int capacidade;
    int qtd_pendentes;
};

// =============================================================================
// DESAFIO 3: Função Auxiliar Privada (Oculta do Linker)
// =============================================================================
static int encontrar_indice_maior_prioridade(const GerenciadorTarefas *gt) {
    // TODO 1: Declare variaveis para guardar a maior prioridade vista (-1) e seu indice (-1).
    // TODO 2: Percorra o vetor 'fila_processos' ate a capacidade maxima.
    // TODO 3: Se a tarefa estiver ativa E sua prioridade for maior que a 'maior prioridade' atual:
    //         - Atualize a maior prioridade e guarde o indice.
    // TODO 4: Retorne o indice encontrado (ou -1 se nenhuma tarefa ativa for encontrada).
    return -1;
}

// =============================================================================
// DESAFIO 1: Construtor Seguro com Rollback e Destrutor
// =============================================================================
GerenciadorTarefas* gerenciador_criar(int capacidade_maxima) {
    // TODO 1: Valide se capacidade_maxima > 0. Se invalido, retorne NULL.

    // TODO 2: Aloque a estrutura principal 'GerenciadorTarefas' com malloc.
    //         Se falhar, retorne NULL.

    // TODO 3: Aloque o vetor 'fila_processos' no Heap com calloc para 'capacidade_maxima' elementos.
    //         ROLLBACK: Se o calloc falhar, voce DEVE dar free() na estrutura alocada no TODO 2
    //         antes de retornar NULL!

    // TODO 4: Inicialize os campos 'capacidade' e 'qtd_pendentes' (que inicia em 0).
    // TODO 5: Retorne o ponteiro alocado.
    return NULL;
}

void gerenciador_destruir(GerenciadorTarefas *gt) {
    // TODO 1: Defesa contra NULL.
    // TODO 2: Libere primeiro o vetor interno 'fila_processos'.
    // TODO 3: Libere a estrutura principal 'gt'.
}

// =============================================================================
// DESAFIO 2: Insercao Defensiva e Invariantes
// =============================================================================
bool gerenciador_adicionar_tarefa(GerenciadorTarefas *gt, int pid, const char *nome_processo, int prioridade) {
    // TODO 1: Validacao defensiva completa:
    //         - gt != NULL
    //         - pid > 0
    //         - nome_processo != NULL
    //         - prioridade >= 0
    //         - qtd_pendentes < capacidade (Invariante de Limite!)
    //         Se alguma falhar, retorne false.

    // TODO 2: Encontre o primeiro slot livre no vetor (onde .ativa == false).
    // TODO 3: Preencha os dados do slot:
    //         - pid
    //         - strncpy para copiar o nome com seguranca (max 31 chars + '\0')
    //         - prioridade
    //         - ativa = true
    // TODO 4: Incremente 'qtd_pendentes' e retorne true.

    return false;
}

bool gerenciador_executar_proxima_tarefa(GerenciadorTarefas *gt, int *pid_executado_out) {
    // TODO 1: Valide se gt != NULL, se qtd_pendentes > 0 e se pid_executado_out != NULL.

    // TODO 2: Chame a funcao estatica 'encontrar_indice_maior_prioridade(gt)'.
    //         Se o indice retornado for -1, retorne false.

    // TODO 3: Atribua o PID do processo encontrado ao ponteiro de saida (*pid_executado_out).
    // TODO 4: Marque a tarefa naquele indice como inativa (.ativa = false).
    // TODO 5: Decremente 'qtd_pendentes' e retorne true.

    return false;
}

// Getters de Leitura
int gerenciador_get_total_pendentes(const GerenciadorTarefas *gt) {
    return gt ? gt->qtd_pendentes : 0;
}

int gerenciador_get_capacidade(const GerenciadorTarefas *gt) {
    return gt ? gt->capacidade : 0;
}
