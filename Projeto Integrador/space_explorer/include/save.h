#ifndef SAVE_H
#define SAVE_H

#include <stdbool.h>

typedef struct {
    float defensor_x;
    int defensor_vida;
    int pontuacao;
    int fase_atual;
} EstadoJogoBinario;

bool carregar_configuracao_texto(const char *caminho, int *largura, int *altura);
bool salvar_jogo_binario(const char *caminho, const EstadoJogoBinario *estado);
bool carregar_jogo_binario(const char *caminho, EstadoJogoBinario *estado);

#endif