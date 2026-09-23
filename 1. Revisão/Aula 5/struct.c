#include <stdio.h>

typedef struct {
    int matricula;
    float n1;
    float n2;
    float media;
} Aluno;

// Recebe o ENDEREÇO da struct para economizar memória e alterar o original
void processar_aluno(Aluno *a) {
    // Seta (->) é o atalho para (*a).media
    a->media = (a->n1 + a->n2) / 2.0f;
}

int main(void) {
    Aluno a1 = {202601, 8.0f, 6.0f, 0.0f};

    printf("%d %f", a1.matricula, a1.n1);

    // Passamos o endereço da struct
    processar_aluno(&a1);

    printf("Matricula: %d | Media Calculada: %.2f\n", a1.matricula, a1.media);

    return 0;
}