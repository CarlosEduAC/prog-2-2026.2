#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char placa[8];
    int ano;
    float preco;
} Veiculo;

int main(void) {
    // 1. Ponteiro na Stack
    Veiculo *v = NULL;

    // 2. Alocação no Heap
    v = (Veiculo *) malloc(sizeof(Veiculo));

    // 3. Verificação de segurança
    if (v == NULL) {
        printf("Erro ao alocar memoria no Heap!\n");
        return 1;
    }

    // 4. Leitura dos dados usando o operador seta (->)
    printf("=== CADASTRO DE VEICULO (HEAP) ===\n");
    printf("Digite a placa (ex: ABC1D23): ");
    fgets(v->placa, sizeof(v->placa), stdin);
    v->placa[strcspn(v->placa, "\n")] = '\0'; // Remove o \n

    printf("Digite o ano: ");
    scanf("%d", &v->ano);

    printf("Digite o preco (R$): ");
    scanf("%f", &v->preco);

    // 5. Exibição dos dados
    printf("\n=== DADOS DO VEICULO CADASTRADO ===\n");
    printf("Placa : %s\n", v->placa);
    printf("Ano   : %d\n", v->ano);
    printf("Preco : R$ %.2f\n", v->preco);

    // 6. Desalocação obrigatória
    free(v);
    v = NULL;

    return 0;
}