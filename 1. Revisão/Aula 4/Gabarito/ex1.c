#include <stdio.h>
#include <string.h>

typedef struct {
    char titulo[80];
    char autor[50];
    int ano_publicacao;
    float preco;
} Livro;

void exibir_livro(Livro livro) {
    printf("Titulo: %s\n", livro.titulo);
    printf("Autor : %s\n", livro.autor);
    printf("Ano   : %d | Preco: R$ %.2f\n", livro.ano_publicacao, livro.preco);
    printf("-----------------------------------\n");
}

int main(void) {
    Livro livro1, livro2;

    // Cadastro do Livro 1
    strcpy(livro1.titulo, "Dom Casmurro");
    strcpy(livro1.autor, "Machado de Assis");
    livro1.ano_publicacao = 1899;
    livro1.preco = 34.90;

    // Cadastro do Livro 2
    strcpy(livro2.titulo, "1984");
    strcpy(livro2.autor, "George Orwell");
    livro2.ano_publicacao = 1949;
    livro2.preco = 42.50;

    printf("=== LIVRO MAIS ANTIGO ===\n");
    if (livro1.ano_publicacao < livro2.ano_publicacao) {
        exibir_livro(livro1);
    } else {
        exibir_livro(livro2);
    }

    return 0;
}