#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ESTOQUE 5

// 1. Definição do Registro
typedef struct {
    int codigo;
    char nome[40];
    int quantidade;
    float preco;
} Produto;

// 2. Protótipos das Funções
void exibir_menu(void);
bool cadastrar_produto(Produto *p, int cod, char *nome, int qtd, float preco);
void listar_estoque(Produto *estoque, int total);
int buscar_por_codigo(Produto *estoque, int total, int cod);
bool realizar_venda(Produto *p, int qtd_venda);

int main(void) {
    Produto estoque[MAX_ESTOQUE];
    int total_cadastrados = 0;
    int opcao;

    do {
        exibir_menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa a quebra de linha '\n' do buffer

        switch (opcao) {
            case 1: { // Cadastrar
                if (total_cadastrados >= MAX_ESTOQUE) {
                    printf("\n[ ERRO ] Limite do estoque atingido!\n");
                    break;
                }

                int cod, qtd;
                float preco;
                char nome[40];

                printf("\n--- NOVO CADASTRO ---\n");
                printf("Codigo: ");
                scanf("%d", &cod);
                getchar();

                // Verifica se o código já existe
                if (buscar_por_codigo(estoque, total_cadastrados, cod) != -1) {
                    printf("[ ERRO ] Ja existe um produto com o codigo %d!\n", cod);
                    break;
                }

                printf("Nome do Produto: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; // Remove o \n

                printf("Quantidade inicial: ");
                scanf("%d", &qtd);

                printf("Preco unitario (R$): ");
                scanf("%f", &preco);

                // Passa o endereço da posição livre no vetor usando &
                if (cadastrar_produto(&estoque[total_cadastrados], cod, nome, qtd, preco)) {
                    total_cadastrados++;
                    printf("[ SUCESSO ] Produto cadastrado com sucesso!\n");
                }
                break;
            }

            case 2: // Listar
                listar_estoque(estoque, total_cadastrados);
                break;

            case 3: { // Realizar Venda (Baixa no Estoque)
                int cod, qtd_venda;
                printf("\n--- REGISTRAR VENDA ---\n");
                printf("Codigo do produto: ");
                scanf("%d", &cod);

                int idx = buscar_por_codigo(estoque, total_cadastrados, cod);
                if (idx == -1) {
                    printf("[ ERRO ] Produto nao encontrado!\n");
                    break;
                }

                printf("Quantidade a vender: ");
                scanf("%d", &qtd_venda);

                // Passamos o endereço do produto encontrado via ponteiro
                if (realizar_venda(&estoque[idx], qtd_venda)) {
                    printf("[ SUCESSO ] Venda realizada! Novo estoque: %d unidades.\n", estoque[idx].quantidade);
                } else {
                    printf("[ ERRO ] Estoque insuficiente ou quantidade invalida!\n");
                }
                break;
            }

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// ----------------------------------------------------------------------------
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ----------------------------------------------------------------------------

void exibir_menu(void) {
    printf("\n=========================================\n");
    printf("        MINISSISTEMA DE ESTOQUE          \n");
    printf("=========================================\n");
    printf("1. Cadastrar Produto\n");
    printf("2. Listar Estoque Completo\n");
    printf("3. Realizar Venda (Dar Baixa)\n");
    printf("0. Sair\n");
    printf("-----------------------------------------\n");
}

// Preenche a struct apontada pelo ponteiro 'p' usando o operador seta (->)
bool cadastrar_produto(Produto *p, int cod, char *nome, int qtd, float preco) {
    if (cod <= 0 || qtd < 0 || preco <= 0.0f) return false;

    p->codigo = cod;
    strcpy(p->nome, nome);
    p->quantidade = qtd;
    p->preco = preco;

    return true;
}

void listar_estoque(Produto *estoque, int total) {
    printf("\n=================================================================\n");
    printf("%-8s %-25s %-12s %-10s\n", "COD", "NOME", "QTD ESTOQUE", "PRECO");
    printf("-----------------------------------------------------------------\n");

    if (total == 0) {
        printf("Nenhum produto cadastrado no estoque.\n");
    } else {
        for (int i = 0; i < total; i++) {
            printf("%-8d %-25s %-12d R$ %-8.2f\n",
                   estoque[i].codigo, estoque[i].nome, estoque[i].quantidade, estoque[i].preco);
        }
    }
    printf("=================================================================\n");
}

int buscar_por_codigo(Produto *estoque, int total, int cod) {
    for (int i = 0; i < total; i++) {
        if (estoque[i].codigo == cod) {
            return i; // Retorna o índice no vetor
        }
    }
    return -1; // Não encontrado
}

bool realizar_venda(Produto *p, int qtd_venda) {
    if (qtd_venda <= 0 || p->quantidade < qtd_venda) {
        return false; // Saldo insuficiente
    }

    p->quantidade -= qtd_venda; // Altera o estoque na memória RAM original
    return true;
}