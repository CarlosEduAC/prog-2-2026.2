#include <stdio.h>

typedef struct {
    int id;
    float nota;
} Aluno;

// Função que altera a struct original via Ponteiro (Seta ->)
void atualizar_nota(Aluno *a, float nova_nota) {
    a->nota = nova_nota; // Atalho limpo para (*a).nota = nova_nota;
}

int main(void) {
    Aluno a1 = {101, 6.0f};
    Aluno *ptr = &a1;

    printf("=== ACESSO DIRETO (VARIAVEL) ===\n");
    printf("ID: %d | Nota: %.1f\n\n", a1.id, a1.nota);

    // Alterando via função usando ponteiro
    atualizar_nota(&a1, 9.5f);

    printf("=== ACESSO VIA PONTEIRO (SETA) ===\n");
    // Lendo valores através do ponteiro usando '->'
    printf("ID: %d | Nota: %.1f\n", ptr->id, ptr->nota);

    return 0;
}