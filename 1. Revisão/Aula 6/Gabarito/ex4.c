#include <stdio.h>

#define ALTURA 3
#define LARGURA 4

// A quantidade de colunas (LARGURA) é obrigatória na assinatura!
void aplicar_limiar(int img[][LARGURA], int linhas, int limiar) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (img[i][j] < limiar) {
                img[i][j] = 0;   // Preto
            } else {
                img[i][j] = 255; // Branco
            }
        }
    }
}

void exibir_imagem(int img[][LARGURA], int linhas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < LARGURA; j++) {
            printf("%3d ", img[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    // Matriz de Pixels (Escala de Cinza de 0 a 255)
    int imagem[ALTURA][LARGURA] = {
        { 45, 180, 210,  12},
        { 90, 128,  30, 240},
        {200,  15,  85, 190}
    };

    printf("=== IMAGEM ORIGINAL (ESCALA DE CINZA) ===\n");
    exibir_imagem(imagem, ALTURA);

    int limiar_corte = 128; // Valores abaixo de 128 viram 0, acima ou igual viram 255
    printf("\nAplicando filtro de limiarizacao (Corte = %d)...\n\n", limiar_corte);

    aplicar_limiar(imagem, ALTURA, limiar_corte);

    printf("=== IMAGEM BINARIZADA (PRETO E BRANCO) ===\n");
    exibir_imagem(imagem, ALTURA);

    return 0;
}