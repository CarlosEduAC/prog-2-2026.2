#include "save.h"
#include <stdio.h>

bool carregar_configuracao_texto(const char *caminho, int *largura, int *altura) {
    FILE *arq = fopen(caminho, "r");
    if (!arq) {
        arq = fopen(caminho, "w");
        if (!arq) return false;
        fprintf(arq, "LARGURA=800\nALTURA=600\n");
        fclose(arq);
        *largura = 800;
        *altura = 600;
        return true;
    }

    fscanf(arq, "LARGURA=%d\nALTURA=%d", largura, altura);
    fclose(arq);
    return true;
}

bool salvar_jogo_binario(const char *caminho, const EstadoJogoBinario *estado) {
    FILE *arq = fopen(caminho, "wb");
    if (!arq) return false;

    size_t q = fwrite(estado, sizeof(EstadoJogoBinario), 1, arq);
    fclose(arq);
    return q == 1;
}

bool carregar_jogo_binario(const char *caminho, EstadoJogoBinario *estado) {
    FILE *arq = fopen(caminho, "rb");
    if (!arq) return false;

    size_t q = fread(estado, sizeof(EstadoJogoBinario), 1, arq);
    fclose(arq);
    return q == 1;
}