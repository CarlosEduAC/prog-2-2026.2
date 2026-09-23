#include <stdio.h>

#define TAM_FROTA 4

typedef struct {
    char placa[10];
    char modelo[30];
    int ano;
    float quilometragem;
} Veiculo;

float calcular_media_km(const Veiculo frota[], int tam) {
    float soma = 0.0f;
    for (int i = 0; i < tam; i++) {
        soma += frota[i].quilometragem;
    }
    return (tam > 0) ? (soma / tam) : 0.0f;
}

int main(void) {
    Veiculo frota[TAM_FROTA];

    printf("=== CADASTRO DE VEICULOS DA FROTA ===\n\n");
    for (int i = 0; i < TAM_FROTA; i++) {
        printf("--- Veiculo %d ---\n", i + 1);
        printf("Placa: ");
        scanf(" %9s", frota[i].placa);
        printf("Modelo: ");
        scanf(" %29s", frota[i].modelo);
        printf("Ano: ");
        scanf("%d", &frota[i].ano);
        printf("Quilometragem: ");
        scanf("%f", &frota[i].quilometragem);
    }

    float media_km = calcular_media_km(frota, TAM_FROTA);

    printf("\nQuilometragem media da frota: %.2f km\n", media_km);
    printf("\n=== VEICULOS COM KM ACIMA DA MEDIA ===\n");

    for (int i = 0; i < TAM_FROTA; i++) {
        if (frota[i].quilometragem > media_km) {
            printf("Modelo: %-15s | Placa: %-8s | KM: %.2f\n",
                   frota[i].modelo, frota[i].placa, frota[i].quilometragem);
        }
    }

    return 0;
}