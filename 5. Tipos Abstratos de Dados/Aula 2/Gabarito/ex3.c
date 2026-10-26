#include <stdlib.h>
#include <string.h>

typedef struct {
    float x, y;
    float vida_util;
} Particula;

typedef struct {
    Particula *vetor_particulas;
    char *nome_emissor;
    int capacidade;
    int ativas;
} EmissorEfeitos;

EmissorEfeitos* emissor_criar(const char *nome, int capacidade_maxima) {
    // 1. Validação de entrada
    if (nome == NULL || capacidade_maxima <= 0) return NULL;

    // FASE 1: Alocação da Estrutura Principal
    EmissorEfeitos *ee = (EmissorEfeitos *) malloc(sizeof(EmissorEfeitos));
    if (ee == NULL) return NULL;

    ee->capacidade = capacidade_maxima;
    ee->ativas = 0;

    // FASE 2: Alocação do Vetor de Partículas
    ee->vetor_particulas = (Particula *) malloc(capacidade_maxima * sizeof(Particula));
    if (ee->vetor_particulas == NULL) {
        // ROLLBACK FASE 2: Libera a estrutura da Fase 1
        free(ee);
        return NULL;
    }

    // FASE 3: Alocação Dinâmica da String de Nome
    ee->nome_emissor = (char *) malloc((strlen(nome) + 1) * sizeof(char));
    if (ee->nome_emissor == NULL) {
        // ROLLBACK FASE 3: Libera tudo alocado nas Fases 1 e 2
        free(ee->vetor_particulas);
        free(ee);
        return NULL;
    }

    // Sucesso: Copia os dados com segurança
    strcpy(ee->nome_emissor, nome);
    return ee;
}

void emissor_destruir(EmissorEfeitos *ee) {
    if (ee != NULL) {
        free(ee->vetor_particulas); // Libera Bloco 1
        free(ee->nome_emissor);     // Libera Bloco 2
        free(ee);                   // Libera Estrutura
    }
}