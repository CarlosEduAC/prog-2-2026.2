#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CAPACIDADE_INICIAL 2

typedef struct {
    int codigo;
    char nome[40];
    int quantidade;
    float preco;
} Produto;

// Protótipos Atualizados
void exibir_menu(void);
bool cadastrar_produto(Produto *p, int cod, const char *nome, int qtd, float preco);
void listar_estoque(const Produto *estoque, int total);
int buscar_por_codigo(const Produto *estoque, int total, int cod);
bool realizar_venda(Produto *p, int qtd_venda);

int main(void) {
    int capacidade = CAPACIDADE_INICIAL;
    int total_cadastrados = 0;
    int opcao;

    // 1. Alocação Inicial do Vetor Dinâmico no Heap
    Produto *estoque = (Produto *) malloc(capacidade * sizeof(Produto));

    if (estoque == NULL) {
        printf("[ ERRO CRÍTICO ] Falha ao alocar memória inicial para o estoque!\n");
        return 1;
    }

    do {
        exibir_menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o \n do buffer

        switch (opcao) {
            case 1: { // Cadastrar com Expansão Dinâmica
                // Se o vetor encheu, dobramos a capacidade com realloc seguro
                if (total_cadastrados == capacidade) {
                    int nova_cap = capacidade * 2;
                    printf("\n[ MEMÓRIA ] Expansivel: Redimensionando de %d para %d posicoes...\n",
                           capacidade, nova_cap);

                    Produto *temp = (Produto *) realloc(estoque, nova_cap * sizeof(Produto));
                    if (temp == NULL) {
                        printf("[ ERRO ] Memoria insuficiente para expandir o estoque!\n");
                        break;
                    }
                    estoque = temp;
                    capacidade = nova_cap;
                }

                int cod, qtd;
                float preco;
                char nome[40];

                printf("\n--- NOVO CADASTRO ---\n");
                printf("Codigo: ");
                scanf("%d", &cod);
                getchar();

                if (buscar_por_codigo(estoque, total_cadastrados, cod) != -1) {
                    printf("[ ERRO ] Ja existe um produto com o codigo %d!\n", cod);
                    break;
                }

                printf("Nome do Produto: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Quantidade inicial: ");
                scanf("%d", &qtd);

                printf("Preco unitario (R$): ");
                scanf("%f", &preco);

                if (cadastrar_produto(&estoque[total_cadastrados], cod, nome, qtd, preco)) {
                    total_cadastrados++;
                    printf("[ SUCESSO ] Produto cadastrado! (%d/%d alocados)\n",
                           total_cadastrados, capacidade);
                }
                break;
            }

            case 2:
                listar_estoque(estoque, total_cadastrados);
                printf("  Capacidade total alocada no Heap: %d posicoes\n", capacidade);
                break;

            case 3: { // Venda (inalterada - opera via ponteiros)
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

                if (realizar_venda(&estoque[idx], qtd_venda)) {
                    printf("[ SUCESSO ] Venda realizada! Novo estoque: %d unidades.\n",
                           estoque[idx].quantidade);
                } else {
                    printf("[ ERRO ] Estoque insuficiente!\n");
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

    // 2. DESALOCAÇÃO OBRIGATÓRIA ANTES DE SAIR
    free(estoque);
    estoque = NULL;
    printf("[ MEMÓRIA ] Memoria do Heap liberada com sucesso!\n");

    return 0;
}

// ----------------------------------------------------------------------------
// IMPLENTAÇÃO DAS FUNÇÕES (Reaproveitadas com segurança)
// ----------------------------------------------------------------------------

void exibir_menu(void) {
    printf("\n=========================================\n");
    printf("     MINISSISTEMA DE ESTOQUE DINÂMICO     \n");
    printf("=========================================\n");
    printf("1. Cadastrar Produto\n");
    printf("2. Listar Estoque Completo\n");
    printf("3. Realizar Venda\n");
    printf("0. Sair\n");
    printf("-----------------------------------------\n");
}

bool cadastrar_produto(Produto *p, int cod, const char *nome, int qtd, float preco) {
    if (cod <= 0 || qtd < 0 || preco <= 0.0f) return false;
    p->codigo = cod;
    strcpy(p->nome, nome);
    p->quantidade = qtd;
    p->preco = preco;
    return true;
}

void listar_estoque(const Produto *estoque, int total) {
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

int buscar_por_codigo(const Produto *estoque, int total, int cod) {
    for (int i = 0; i < total; i++) {
        if (estoque[i].codigo == cod) return i;
    }
    return -1;
}

bool realizar_venda(Produto *p, int qtd_venda) {
    if (qtd_venda <= 0 || p->quantidade < qtd_venda) return false;
    p->quantidade -= qtd_venda;
    return true;
}