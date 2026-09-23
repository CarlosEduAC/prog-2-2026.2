#include <stdio.h>

int main(void) {
    // Estoque real do caixa
    int notas_100 = 5;
    int notas_50  = 10;
    int notas_20  = 10;
    int notas_10  = 20;

    int opcao = 0;

    do {
        printf("\n=== CAIXA ELETRONICO ===\n");
        printf("1. Sacar\n");
        printf("2. Consultar Saldo do Caixa\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int valor_saque;
            printf("Digite o valor do saque: R$ ");
            scanf("%d", &valor_saque);

            if (valor_saque <= 0 || valor_saque % 10 != 0) {
                printf("[ ERRO ] Valor invalido! O caixa fornece apenas notas de 10, 20, 50 e 100.\n");
                continue;
            }

            // Simulação prévia usando variáveis temporárias
            int restante = valor_saque;

            int usar_100 = restante / 100;
            if (usar_100 > notas_100) usar_100 = notas_100;
            restante -= usar_100 * 100;

            int usar_50 = restante / 50;
            if (usar_50 > notas_50) usar_50 = notas_50;
            restante -= usar_50 * 50;

            int usar_20 = restante / 20;
            if (usar_20 > notas_20) usar_20 = notas_20;
            restante -= usar_20 * 20;

            int usar_10 = restante / 10;
            if (usar_10 > notas_10) usar_10 = notas_10;
            restante -= usar_10 * 10;

            // Se 'restante' for zero, o saque é viável
            if (restante == 0) {
                // Efetiva a dedução do estoque real
                notas_100 -= usar_100;
                notas_50  -= usar_50;
                notas_20  -= usar_20;
                notas_10  -= usar_10;

                printf("\n[ SUCESSO ] Saque de R$ %d realizado!\n", valor_saque);
                printf("Cédulas entregues:\n");
                if (usar_100 > 0) printf("- %d nota(s) de R$ 100\n", usar_100);
                if (usar_50 > 0)  printf("- %d nota(s) de R$ 50\n", usar_50);
                if (usar_20 > 0)  printf("- %d nota(s) de R$ 20\n", usar_20);
                if (usar_10 > 0)  printf("- %d nota(s) de R$ 10\n", usar_10);
            } else {
                printf("\n[ RECUSADO ] Nao e possivel fornecer este valor com as cedulas disponiveis.\n");
            }

        } else if (opcao == 2) {
            int total_caixa = (notas_100 * 100) + (notas_50 * 50) + (notas_20 * 20) + (notas_10 * 10);
            printf("\n=== SALDO EM CAIXA ===\n");
            printf("Total Disponivel: R$ %d\n", total_caixa);
            printf("Estoque de Cedulas:\n");
            printf("- R$ 100: %d\n", notas_100);
            printf("- R$ 50 : %d\n", notas_50);
            printf("- R$ 20 : %d\n", notas_20);
            printf("- R$ 10 : %d\n", notas_10);

        } else if (opcao != 3) {
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 3);

    printf("\nSessao encerrada. Obrigado!\n");
    return 0;
}