#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gerenciador_tarefas.h"

static void checar(bool condicao, const char *nome_teste) {
    if (condicao) {
        printf(" [ PASS ] %s\n", nome_teste);
    } else {
        printf(" [ FAIL ] %s\n", nome_teste);
    }
}

int main(void) {
    printf("========================================================\n");
    printf("   LABORATÓRIO PRÁTICO: GERENCIADOR DE TAREFAS (TAD)    \n");
    printf("========================================================\n\n");

    printf("--- FASE 1: Testando Construtor e Destrutor ---\n");
    GerenciadorTarefas *gt = gerenciador_criar(3);
    checar(gt != NULL, "Instanciacao do TAD no Heap");
    checar(gerenciador_get_capacidade(gt) == 3, "Capacidade configurada para 3");
    checar(gerenciador_get_total_pendentes(gt) == 0, "Total de pendentes inicial e 0");

    printf("\n--- FASE 2: Testando Insercao e Invariantes ---\n");
    bool ok1 = gerenciador_adicionar_tarefa(gt, 101, "HTTP_Server", 2);
    bool ok2 = gerenciador_adicionar_tarefa(gt, 102, "DB_Backup", 5);  // Maior prioridade
    bool ok3 = gerenciador_adicionar_tarefa(gt, 103, "Log_Writer", 1);
    checar(ok1 && ok2 && ok3, "Insercao de 3 tarefas validas");
    checar(gerenciador_get_total_pendentes(gt) == 3, "Total de pendentes atualizado para 3");

    // Teste de Invariante: Estouro de capacidade
    bool ok_estouro = gerenciador_adicionar_tarefa(gt, 104, "Render", 10);
    checar(!ok_estouro, "Invariante: Rejeitar 4a tarefa (limite e 3)");

    printf("\n--- FASE 3: Testando Selecao por Prioridade (static) ---\n");
    int pid_exec;
    gerenciador_executar_proxima_tarefa(gt, &pid_exec);
    checar(pid_exec == 102, "Executar tarefa de MAIOR prioridade primeiro (PID 102)");

    gerenciador_executar_proxima_tarefa(gt, &pid_exec);
    checar(pid_exec == 101, "Executar segunda maior prioridade (PID 101)");

    checar(gerenciador_get_total_pendentes(gt) == 1, "Restante de pendentes atualizado para 1");

    printf("\n--- FASE 4: Liberacao de Memoria ---\n");
    gerenciador_destruir(gt);
    printf(" -> Memoria desalocada com sucesso.\n\n");

    return 0;
}
