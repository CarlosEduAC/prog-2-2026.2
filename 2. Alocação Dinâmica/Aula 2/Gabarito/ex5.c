#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n_turmas;

    printf("Digite a quantidade de turmas: ");
    if (scanf("%d", &n_turmas) != 1 || n_turmas <= 0) return 1;

    // 1. Aloca o vetor de ponteiros principais (quantidade de turmas)
    float **turmas = (float **) malloc(n_turmas * sizeof(float *));
    if (turmas == NULL) {
        printf("[ERRO] Falha ao alocar vetor de turmas.\n");
        return 1;
    }

    // Vetor aux para guardar o tamanho de cada turma (necessário para a exibição/desalocação)
    int *qtd_alunos = (int *) malloc(n_turmas * sizeof(int));
    if (qtd_alunos == NULL) {
        free(turmas);
        return 1;
    }

    // 2. Aloca cada linha com seu tamanho específico
    for (int i = 0; i < n_turmas; i++) {
        printf("\nQuantos alunos tem na Turma %d? ", i + 1);
        scanf("%d", &qtd_alunos[i]);

        // Cada linha recebe um tamanho INDIVIDUAL no Heap
        turmas[i] = (float *) malloc(qtd_alunos[i] * sizeof(float));
        if (turmas[i] == NULL) {
            printf("[ERRO] Falha ao alocar memória para a turma %d!\n", i + 1);
            // Libera o que já foi alocado antes de fechar
            for (int j = 0; j < i; j++) free(turmas[j]);
            free(turmas);
            free(qtd_alunos);
            return 1;
        }

        // Leitura das notas da turma atual
        for (int j = 0; j < qtd_alunos[i]; j++) {
            printf("  Nota do Aluno %d: ", j + 1);
            scanf("%f", &turmas[i][j]);
        }
    }

    // 3. Exibição e Cálculo das Médias
    printf("\n================ RESUMO DAS TURMAS ================\n");
    for (int i = 0; i < n_turmas; i++) {
        float soma = 0;
        for (int j = 0; j < qtd_alunos[i]; j++) {
            soma += turmas[i][j];
        }
        float media = (qtd_alunos[i] > 0) ? (soma / qtd_alunos[i]) : 0;
        printf("Turma %d (%d Alunos) -> Média Geral: %.2f\n", i + 1, qtd_alunos[i], media);
    }

    // 4. DESALOCAÇÃO COMPLETA
    // Primeiro: Libera cada vetor interno de notas
    for (int i = 0; i < n_turmas; i++) {
        free(turmas[i]);
        turmas[i] = NULL;
    }

    // Segundo: Libera os vetores do nível superior
    free(turmas);
    turmas = NULL;

    free(qtd_alunos);
    qtd_alunos = NULL;

    printf("\n[SUCESSO] Matriz irregular desalocada com sucesso!\n");
    return 0;
}