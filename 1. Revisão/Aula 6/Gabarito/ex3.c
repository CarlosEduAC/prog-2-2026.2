#include <stdio.h>

#define TAM_SINAL 6

int tratar_ruidos(float *sinal, int tam) {
    float soma = 0.0f;
    int qtd_validos = 0;
    int ruidos = 0;

    // 1ª Passada: Calcula a média apenas dos valores válidos
    for (int i = 0; i < tam; i++) {
        if (sinal[i] > 0.0f) {
            soma += sinal[i];
            qtd_validos++;
        } else {
            ruidos++;
        }
    }

    float media_valida = (qtd_validos > 0) ? (soma / qtd_validos) : 0.0f;

    // 2ª Passada: Substitui os ruídos pela média calculada
    for (int i = 0; i < tam; i++) {
        if (sinal[i] <= 0.0f) {
            sinal[i] = media_valida; // Modifica diretamente a RAM da main()
        }
    }

    return ruidos;
}

int main(void) {
    // Valores <= 0 representam ruídos de leitura do sensor
    float telemetria[TAM_SINAL] = {12.5f, -2.0f, 15.0f, 0.0f, 14.5f, 18.0f};

    printf("=== SINAL ORIGINAL ===\n");
    for (int i = 0; i < TAM_SINAL; i++) printf("[%.1f] ", telemetria[i]);
    printf("\n\nFiltrando ruidos...\n");

    int corrigidos = tratar_ruidos(telemetria, TAM_SINAL);

    printf("\n=== SINAL TRATADO ===\n");
    for (int i = 0; i < TAM_SINAL; i++) printf("[%.1f] ", telemetria[i]);

    printf("\n\nTotal de leituras incorretas tratadas: %d\n", corrigidos);

    return 0;
}