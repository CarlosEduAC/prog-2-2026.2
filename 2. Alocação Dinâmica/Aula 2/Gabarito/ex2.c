#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int linhas, colunas;

    printf("Informe a quantidade de alunos (linhas): ");
    scanf("%d", &linhas);
    printf("Informe a quantidade de avaliações (colunas): ");
    scanf("%d", &colunas);

    if (linhas <= 0 || colunas <= 0) return 1;

    // 1. Aloca o vetor de ponteiros para as linhas (float**)
    float **notas = (float **) malloc(linhas * sizeof(float *));
    if (notas == NULL) {
        printf("[ERRO] Falha ao alocar vetor de linhas.\n");
        return 1;
    }

    // 2. Aloca o vetor de notas para cada aluno (linha)
    for (int i = 0; i < linhas; i++) {
        notas[i] = (float *) malloc(colunas * sizeof(float));
        if (notas[i] == NULL) {
            printf("[ERRO] Falha ao alocar colunas para a linha %d.\n", i);
            // Desaloca o que já foi alocado antes de sair
            for (int j = 0; j < i; j++) free(notas[j]);
            free(notas);
            return 1;
        }
    }

    // 3. Preenchimento da Matriz
    for (int i = 0; i < linhas; i++) {
        printf("\n--- Notas do Aluno %d ---\n", i + 1);
        for (int j = 0; j < colunas; j++) {
            printf("Nota %d: ", j + 1);
            scanf("%f", &notas[i][j]);
        }
    }

    // 4. Cálculo e Exibição das Médias
    printf("\n================ RESUMO DA TURMA ================\n");
    for (int i = 0; i < linhas; i++) {
        float soma = 0.0;
        for (int j = 0; j < colunas; j++) {
            soma += notas[i][j];
        }
        float media = soma / colunas;
        printf("Aluno %d - Média: %.2f\n", i + 1, media);
    }

    // 5. Desalocação na ORDEM INVERSA
    // Primeiro libera cada linha...
    for (int i = 0; i < linhas; i++) {
        free(notas[i]);
        notas[i] = NULL;
    }
    // Depois libera o ponteiro principal de linhas...
    free(notas);
    notas = NULL;

    printf("\n[SUCESSO] Matriz desalocada da memória RAM!\n");
    return 0;
}