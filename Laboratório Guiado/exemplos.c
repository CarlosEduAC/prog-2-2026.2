#include <stdio.h>

typedef struct {
    int codigo;         // Identificador único do produto
    char nome[40];      // Descrição/Nome comercial
    int quantidade;     // Unidades disponíveis em estoque
    float preco;        // Valor unitário em Reais
} Produto;

#define MAX_ESTOQUE 5

Produto cadastrar_produto () {
    Produto aux;


    return aux;
}


int main(void) {
    int opcao;
    int quantidade_produtos = 0;

    Produto estoque[MAX_ESTOQUE];


    do {
        printf("\n=========================================\n");
        printf("                  MEU MENU                 \n");
        printf("===========================================\n");
        printf("1. Opção A\n");
        printf("2. Opção B\n");
        printf("0. Finalizar\n");
        printf("-----------------------------------------\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 0: printf("\nEncerrando o sistema...\n"); break;
            case 1: estoque[quantidade_produtos] = cadastrar_produto(); getchar(); break;
            case 2: printf("\nOpção B\n"); getchar(); break;
            default: printf("\nDigite uma opção válida!\n");
        }

    } while(opcao != 0);

    return 0;
}