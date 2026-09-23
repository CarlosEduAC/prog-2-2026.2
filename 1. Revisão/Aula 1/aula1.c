#include <stdio.h>

void iniciar_projeto() {
    printf("======================================\n");
    printf("           Sistema de Aluno      ");
}

float calcular_media(float nota1, float nota2);

int main() {
    iniciar_projeto();

    int matricula;
    float nota1, nota2, media;

    printf("Digite a matricula do aluno: ");

    if(scanf("%d", &matricula) != 1) {
        printf("Erro: Entrada inválida para a matricula.\n");
        return 1;
    }

    printf("Digite as duas notas do aluno: ");
    if(scanf("%f %f", &nota1, &nota2) != 2) {
        printf("Erro: Entrada inválida para as notas.\n");
        return 1;
    }

    media = calcular_media(nota1, nota2);

    printf("======================================");

    printf("\nMatricula: %d\n", matricula);
    printf("Nota 1: %.2f\n", nota1);
    printf("Nota 2: %.2f\n", nota2);

    if (media >= 6.0) {
        printf("Media: %.2f - Aprovado\n", media);
    } else if (media >= 4.0) {
        printf("Media: %.2f - VS\n", media);
    } else {
        printf("Media: %.2f - Reprovado\n", media);
    }

    switch (media >= 6.0) {
        case 1:
            printf("Parabéns! Você foi aprovado.\n");
            break;
        case 0:
            if (media >= 4.0) {
                printf("Você está em recuperação.\n");
            } else {
                printf("Infelizmente, você foi reprovado.\n");
            }
            break;
    }
    return 0;
}

float calcular_media(float nota1, float nota2) {
    return (nota1 + nota2) / 2;
}