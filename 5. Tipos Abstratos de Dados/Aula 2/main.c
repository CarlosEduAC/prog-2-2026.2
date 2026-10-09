#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Inclui a interface pública do TAD Inventário
#include "inventario.h"

// Função auxiliar para formatar a saída dos testes
static void testar_condicao(bool resultado_esperado, bool resultado_obtido, const char *descricao) {
    if (resultado_esperado == resultado_obtido) {
        printf(" [ PASS ] %s\n", descricao);
    } else {
        printf(" [ FAIL ] %s\n", descricao);
    }
}

int main(void) {
    printf("========================================================\n");
    printf("   LABORATÓRIO GUIADO: TAD INVENTÁRIO ESPACIAL DEFENSIVO\n");
    printf("========================================================\n\n");

    // -------------------------------------------------------------------------
    // 1. TESTE DE CONSTRUTOR SEGURO
    // -------------------------------------------------------------------------
    printf("--- 1. Testando Construtor e Validações de Entrada ---\n");

    // Tenta criar com capacidade inválida (<= 0)
    InventarioEspacial *inv_invalido = inventario_criar(0);
    testar_condicao(true, inv_invalido == NULL, "Rejeitar criacao com capacidade <= 0");

    // Cria inventário válido para 10 itens totais
    InventarioEspacial *inv = inventario_criar(10);
    testar_condicao(true, inv != NULL, "Instanciar inventario no Heap com capacidade 10");

    // -------------------------------------------------------------------------
    // 2. TESTE DE PRESERVAÇÃO DE INVARIANTES DE ESTADO
    // -------------------------------------------------------------------------
    printf("\n--- 2. Testando Blindagem de Invariantes ---\n");

    // Adição válida: 3 unidades do item ID 1 (ex: Mísseis)
    bool ok1 = inventario_adicionar_item(inv, 1, 3);
    testar_condicao(true, ok1, "Adicionar 3 Misseis (ID 1)");
    testar_condicao(true, inventario_get_qtd_item(inv, 1) == 3, "Verificar quantidade de Misseis (Esperado: 3)");

    // Adição válida: 4 unidades do item ID 2 (ex: Células de Energia)
    bool ok2 = inventario_adicionar_item(inv, 2, 4);
    testar_condicao(true, ok2, "Adicionar 4 Celulas de Energia (ID 2)");

    // Tentativa de quebrar a invariante: quantidade negativa
    bool ok_negativo = inventario_adicionar_item(inv, 1, -5);
    testar_condicao(false, ok_negativo, "Invariante: Rejeitar adicao de quantidade negativa (-5)");

    // Tentativa de estourar a capacidade máxima (Já temos 3 + 4 = 7 itens, limite é 10)
    // Tentar adicionar 5 itens (7 + 5 = 12 > 10) deve falhar!
    bool ok_estouro = inventario_adicionar_item(inv, 1, 5);
    testar_condicao(false, ok_estouro, "Invariante: Rejeitar estouro de capacidade (7 + 5 > 10)");

    // Verifica se a quantidade se manteve intacta após as tentativas inválidas
    testar_condicao(true, inventario_get_qtd_item(inv, 1) == 3, "Verificar integridade do estado apos falhas");

    // -------------------------------------------------------------------------
    // 3. TESTE DE PROGRAMAÇÃO DEFENSIVA (PONTEIROS NULOS)
    // -------------------------------------------------------------------------
    printf("\n--- 3. Testando Resiliencia a Ponteiros Nulos (NULL) ---\n");

    bool ok_null = inventario_adicionar_item(NULL, 1, 2);
    testar_condicao(false, ok_null, "Resiliencia: Operar em ponteiro NULL retorna false sem crash");

    int qtd_null = inventario_get_qtd_item(NULL, 1);
    testar_condicao(true, qtd_null == 0, "Resiliencia: Leitura em ponteiro NULL retorna 0");

    // -------------------------------------------------------------------------
    // 4. DESALOCAÇÃO SEGURA DE MEMÓRIA (DESTRUTOR)
    // -------------------------------------------------------------------------
    printf("\n--- 4. Liberação de Memória no Heap ---\n");
    inventario_destruir(inv);
    printf(" -> inventario_destruir() executado com sucesso.\n");

    // Destruição defensiva de ponteiro nulo (não deve causar Segmentation Fault)
    inventario_destruir(NULL);
    printf(" -> inventario_destruir(NULL) executado sem erros.\n");

    printf("\n========================================================\n");
    printf(" [ SUCESSO ] Prática de Laboratório Concluída!\n");
    printf("========================================================\n\n");

    return 0;
}