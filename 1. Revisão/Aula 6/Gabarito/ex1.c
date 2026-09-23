#include <stdio.h>

#define TAM_TURNO 8

void analisar_temperaturas(const float *leituras, int tam, float *media, int *acima_limite) {
    float soma = 0.0f;
    *acima_limite = 0;

    for (int i = 0; i < tam; i++) {
        soma += leituras[i]; // Equivalente a *(leituras + i)

        if (leituras[i] > 37.5f) {
            (*acima_limite)++;
        }
    }

    *media = soma / tam;
}

int main(void) {
    // Simulação de 8 leituras ao longo do dia
    float temperaturas[TAM_TURNO] = {35.2f, 36.0f, 37.8f, 38.1f, 36.5f, 39.0f, 37.0f, 35.8f};

    float media_final;
    int qtd_alertas;

    // Passagem do vetor (endereço base) e dos endereços das variáveis de retorno
    analisar_temperaturas(temperaturas, TAM_TURNO, &media_final, &qtd_alertas);

    printf("=== RELATORIO DE MONITORAMENTO ===\n");
    printf("Temperatura Media : %.2f ºC\n", media_final);
    printf("Alertas de Calor  : %d leitura(s) acima de 37.5 ºC\n", qtd_alertas);

    return 0;
}