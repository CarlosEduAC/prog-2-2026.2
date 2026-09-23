#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char titulo[50];
    char autor[40];
    int paginas;
    float preco;
} Livro;

void preencher_livro(Livro *l) {
    printf("--- CADASTRO DE LIVRO ---\n");
    printf("Titulo: ");
    fgets(l->titulo, sizeof(l->titulo), stdin);
    l->titulo[strcspn(l->titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(l->autor, sizeof(l->autor), stdin);
    l->autor[strcspn(l->autor, "\n")] = '\0';

    printf("Numero de Paginas: ");
    scanf("%d", &l->paginas);

    printf("Preco (R$): ");
    scanf("%f", &l->preco);
}

void exibir_livro(const Livro *l) {
    printf("\n=== FICHA DO LIVRO ===\n");
    printf("Titulo  : %s\n", l->titulo);
    printf("Autor   : %s\n", l->autor);
    printf("Paginas : %d\n", l->paginas);
    printf("Preco   : R$ %.2f\n", l->preco);
}

int main(void) {
    Livro *l = (Livro *) malloc(sizeof(Livro));

    if (l == NULL) {
        printf("Erro ao alocar memoria no Heap!\n");
        return 1;
    }

    preencher_livro(l);
    exibir_livro(l);

    free(l);
    l = NULL;

    return 0;
}