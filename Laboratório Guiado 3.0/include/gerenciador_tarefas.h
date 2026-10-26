#ifndef GERENCIADOR_TAREFAS_H
#define GERENCIADOR_TAREFAS_H

#include <stdbool.h>

// DECLARAÇÃO INCOMPLETA (Ponteiro Opaco)
typedef struct GerenciadorTarefas GerenciadorTarefas;

// Contrato da Biblioteca
GerenciadorTarefas* gerenciador_criar(int capacidade_maxima);
void gerenciador_destruir(GerenciadorTarefas *gt);

bool gerenciador_adicionar_tarefa(GerenciadorTarefas *gt, int pid, const char *nome_processo, int prioridade);
bool gerenciador_executar_proxima_tarefa(GerenciadorTarefas *gt, int *pid_executado_out);

int gerenciador_get_total_pendentes(const GerenciadorTarefas *gt);
int gerenciador_get_capacidade(const GerenciadorTarefas *gt);

#endif