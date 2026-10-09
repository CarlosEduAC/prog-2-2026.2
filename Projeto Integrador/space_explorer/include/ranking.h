#ifndef RANKING_H
#define RANKING_H

typedef struct {
    char nome[20];
    int pontos;
} RegistroScore;

void ranking_ordenar_quicksort(RegistroScore *vetor, int inicio, int fim);
void ranking_salvar_binario(const char *caminho, RegistroScore *vetor, int qtd);

#endif