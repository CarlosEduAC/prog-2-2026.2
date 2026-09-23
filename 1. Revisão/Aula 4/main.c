#include <stdio.h>
#include <string.h>

// Definição do tipo Aluno
typedef struct {
    int matricula;
    char nome[50];
    float n1;
    float n2;
    float media;
} Aluno;

// Função auxiliar para calcular a média
float calcular_media(float n1, float n2) {
    return (n1 + n2) / 2.0f;
}

int main(void) {
    Aluno a;

    strcpy(a.nome, ""); // Inicializa o nome como uma string vazia

    printf("=== CADASTRO DE ALUNO ===\n\n");

    // 1. Lendo a Matrícula
    printf("Digite a matricula: ");
    scanf("%d", &a.matricula);

    // Limpa o caractere de nova linha '\n' deixado pelo scanf no buffer do teclado
    getchar();

    // 2. Lendo o Nome (suporta nomes compostos com espaços)
    printf("Digite o nome completo: ");
    fgets(a.nome, sizeof(a.nome), stdin);
    // Remove a quebra de linha '\n' capturada pelo fgets
    a.nome[strcspn(a.nome, "\n")] = '\0';

    // 3. Lendo as Notas
    printf("Digite a Nota 1: ");
    scanf("%f", &a.n1);

    printf("Digite a Nota 2: ");
    scanf("%f", &a.n2);

    // 4. Calculando e Armazenando a Média na Struct
    a.media = calcular_media(a.n1, a.n2);

    // 5. Exibindo os Dados no Terminal
    printf("\n=========================================\n");
    printf("             FICHA DO ALUNO              \n");
    printf("=========================================\n");
    printf("Matricula : %d\n", a.matricula);
    printf("Nome      : %s\n", a.nome);
    printf("Notas     : %.1f e %.1f\n", a.n1, a.n2);
    printf("Media     : %.2f\n", a.media);
    printf("Situacao  : %s\n", (a.media >= 7.0f) ? "APROVADO" : "REPROVADO");
    printf("=========================================\n");

    return 0;
}