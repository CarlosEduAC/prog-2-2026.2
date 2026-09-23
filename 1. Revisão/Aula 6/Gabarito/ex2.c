#include <stdio.h>
#include <stdbool.h>

#define FILEIRAS 4
#define COLUNAS 5

// O número de colunas é OBRIGATÓRIO na assinatura!
void exibir_sala(int sala[][COLUNAS], int fileiras) {
    printf("\n   --- TELA DO CINEMA ---\n     ");
    for (int j = 0; j < COLUNAS; j++) printf(" P%d ", j + 1);
    printf("\n");

    for (int i = 0; i < fileiras; i++) {
        printf("F%d  ", i + 1);
        for (int j = 0; j < COLUNAS; j++) {
            if (sala[i][j] == 0) {
                printf("[O] "); // Livre
            } else {
                printf("[X] "); // Ocupado
            }
        }
        printf("\n");
    }
    printf("\n");
}

bool reservar_assento(int sala[][COLUNAS], int f, int p) {
    // Converte entrada do usuário (1-based) para índice da matriz (0-based)
    int i = f - 1;
    int j = p - 1;

    // Validação de limites da matriz
    if (i < 0 || i >= FILEIRAS || j < 0 || j >= COLUNAS) {
        return false; // Assento inexistente
    }

    // Verifica disponibilidade
    if (sala[i][j] == 0) {
        sala[i][j] = 1; // Reserva
        return true;
    }

    return false; // Já ocupado
}

int main(void) {
    // 0 = Livre, 1 = Ocupado
    int cinema[FILEIRAS][COLUNAS] = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    printf("=== MAPA INICIAL DA SALA ===");
    exibir_sala(cinema, FILEIRAS);

    int fileira = 2, poltrona = 3; // Tentando reservar F2 P3 (Já ocupada)
    printf("Tentando reservar Fileira %d, Poltrona %d...\n", fileira, poltrona);

    if (reservar_assento(cinema, fileira, poltrona)) {
        printf("[ SUCESSO ] Assento reservado com sucesso!\n");
    } else {
        printf("[ ERRO ] Assento indisponivel ou invalido!\n");
    }

    // Segunda tentativa (Assento livre: F4 P5)
    fileira = 4; poltrona = 5;
    printf("\nTentando reservar Fileira %d, Poltrona %d...\n", fileira, poltrona);
    if (reservar_assento(cinema, fileira, poltrona)) {
        printf("[ SUCESSO ] Assento reservado com sucesso!\n");
    }

    printf("\n=== MAPA ATUALIZADO DA SALA ===");
    exibir_sala(cinema, FILEIRAS);

    return 0;
}