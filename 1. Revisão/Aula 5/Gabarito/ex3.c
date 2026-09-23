#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int id;
    float salario;
    char cargo[30];
} Funcionario;

bool reajustar_salario(Funcionario *f, float percentual_aumento);

int main(void) {
    Funcionario f1 = {101, 3500.00f, "Desenvolvedor C"};

    printf("=== DADOS DO FUNCIONARIO ===\n");
    printf("ID: %d | Cargo: %s | Salario: R$ %.2f\n\n", f1.id, f1.cargo, f1.salario);

    printf("Aplicando aumento de 10%%...\n");

    // Passagem do endereço da struct (&f1)
    if (reajustar_salario(&f1, 10.0f)) {
        printf("[ SUCESSO ] Novo Salario: R$ %.2f\n", f1.salario);
    } else {
        printf("[ ERRO ] Percentual de aumento invalido.\n");
    }

    return 0;
}

bool reajustar_salario(Funcionario *f, float percentual_aumento) {
    if (percentual_aumento <= 0.0f) {
        return false; // Aumento inválido
    }

    // Acesso ao membro da struct apontada via operador seta (->)
    f->salario += f->salario * (percentual_aumento / 100.0f);
    return true;
}