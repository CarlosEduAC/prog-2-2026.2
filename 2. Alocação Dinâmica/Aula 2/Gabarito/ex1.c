#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char placa[9];
    int ano;
    float preco;
} Veiculo;

int main(void) {
    int n, adicional, op;

    printf("Quantos veículos deseja cadastrar inicialmente? ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    // 1. Alocação inicial usando calloc
    Veiculo *v = (Veiculo *) calloc(n, sizeof(Veiculo));
    if (v == NULL) {
        printf("[ERRO] Falha ao alocar memória!\n");
        return 1;
    }

    // 2. Leitura dos N veículos
    for (int i = 0; i < n; i++) {
        printf("\n--- Veículo %d ---\n", i + 1);
        printf("Placa: ");
        scanf("%8s", v[i].placa);
        printf("Ano: ");
        scanf("%d", &v[i].ano);
        printf("Preço: ");
        scanf("%f", &v[i].preco);
    }

    // 3. Pergunta Bônus: Redimensionar
    printf("\nDeseja cadastrar mais veículos? (1 - Sim / 0 - Não): ");
    scanf("%d", &op);

    if (op == 1) {
        printf("Quantos veículos a mais deseja adicionar? ");
        scanf("%d", &adicional);

        if (adicional > 0) {
            int novo_total = n + adicional;
            Veiculo *temp = (Veiculo *) realloc(v, novo_total * sizeof(Veiculo));

            if (temp == NULL) {
                printf("[ERRO] Não foi possível expandir o cadastro.\n");
            } else {
                v = temp;
                // Leitura dos novos veículos a partir do índice 'n'
                for (int i = n; i < novo_total; i++) {
                    printf("\n--- Veículo %d ---\n", i + 1);
                    printf("Placa: ");
                    scanf("%8s", v[i].placa);
                    printf("Ano: ");
                    scanf("%d", &v[i].ano);
                    printf("Preço: ");
                    scanf("%f", &v[i].preco);
                }
                n = novo_total; // Atualiza o total
            }
        }
    }

    // 4. Exibição formatada
    printf("\n================ LISTA DE VEÍCULOS ================\n");
    for (int i = 0; i < n; i++) {
        printf("ID: %d | Placa: %-8s | Ano: %d | Preço: R$ %.2f\n",
               i + 1, v[i].placa, v[i].ano, v[i].preco);
    }

    // 5. Liberação de memória
    free(v);
    v = NULL;

    printf("\n[SUCESSO] Memória liberada com sucesso.\n");
    return 0;
}