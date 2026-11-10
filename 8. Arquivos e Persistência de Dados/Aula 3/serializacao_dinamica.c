#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// Estrutura com dados dinâmicos na RAM
typedef struct {
    int id;
    int pontuacao;
    char *nome_jogador;   // String alocada no Heap (tamanho arbitrário)
    int *inventario_ids;  // Vetor alocado no Heap (quantidade arbitrária)
    uint32_t total_itens; // Quantidade de elementos no vetor
} PerfilJogador;

// =============================================================================
// FUNÇÃO DE SERIALIZAÇÃO (Gravação em Disco com Prefixo de Tamanho)
// =============================================================================
bool salvar_perfil(const char *caminho, const PerfilJogador *perfil) {
    if (caminho == NULL || perfil == NULL) return false;

    FILE *arq = fopen(caminho, "wb");
    if (arq == NULL) return false;

    // 1. Grava campos primitivos de tamanho fixo
    if (fwrite(&perfil->id, sizeof(int), 1, arq) != 1 ||
        fwrite(&perfil->pontuacao, sizeof(int), 1, arq) != 1) {
        fclose(arq);
        return false;
    }

    // 2. Grava a string dinâmica (Length-Prefixed)
    // Calcula o comprimento do texto (sem o terminador '\0' para economizar disco)
    uint32_t tam_nome = (perfil->nome_jogador != NULL) ? (uint32_t)strlen(perfil->nome_jogador) : 0;

    // 2.1 Grava o comprimento do texto (4 bytes)
    if (fwrite(&tam_nome, sizeof(uint32_t), 1, arq) != 1) {
        fclose(arq);
        return false;
    }

    // 2.2 Grava os caracteres brutos do texto
    if (tam_nome > 0) {
        if (fwrite(perfil->nome_jogador, sizeof(char), tam_nome, arq) != tam_nome) {
            fclose(arq);
            return false;
        }
    }

    // 3. Grava o vetor dinâmico de inteiros (Length-Prefixed)
    // 3.1 Grava a quantidade de itens no vetor (4 bytes)
    if (fwrite(&perfil->total_itens, sizeof(uint32_t), 1, arq) != 1) {
        fclose(arq);
        return false;
    }

    // 3.2 Grava o bloco contíguo de inteiros
    if (perfil->total_itens > 0 && perfil->inventario_ids != NULL) {
        if (fwrite(perfil->inventario_ids, sizeof(int), perfil->total_itens, arq) != perfil->total_itens) {
            fclose(arq);
            return false;
        }
    }

    fclose(arq);
    return true;
}

// =============================================================================
// FUNÇÃO DE DESSERIALIZAÇÃO (Leitura do Disco e Reconstrução no Heap)
// =============================================================================
bool carregar_perfil(const char *caminho, PerfilJogador *perfil_out) {
    if (caminho == NULL || perfil_out == NULL) return false;

    FILE *arq = fopen(caminho, "rb");
    if (arq == NULL) return false;

    // 1. Lê campos primitivos de tamanho fixo
    if (fread(&perfil_out->id, sizeof(int), 1, arq) != 1 ||
        fread(&perfil_out->pontuacao, sizeof(int), 1, arq) != 1) {
        fclose(arq);
        return false;
    }

    // 2. Lê a string dinâmica
    // 2.1 Lê o comprimento prefixado
    uint32_t tam_nome = 0;
    if (fread(&tam_nome, sizeof(uint32_t), 1, arq) != 1) {
        fclose(arq);
        return false;
    }

    // 2.2 Aloca a memória exata necessária no Heap (+ 1 para o '\0')
    perfil_out->nome_jogador = (char *) malloc(tam_nome + 1);
    if (perfil_out->nome_jogador == NULL) {
        fclose(arq);
        return false;
    }

    // 2.3 Lê os caracteres gravados e adiciona o terminador de string
    if (tam_nome > 0) {
        if (fread(perfil_out->nome_jogador, sizeof(char), tam_nome, arq) != tam_nome) {
            free(perfil_out->nome_jogador);
            fclose(arq);
            return false;
        }
    }
    perfil_out->nome_jogador[tam_nome] = '\0';

    // 3. Lê o vetor dinâmico de inteiros
    // 3.1 Lê a quantidade prefixada de elementos
    if (fread(&perfil_out->total_itens, sizeof(uint32_t), 1, arq) != 1) {
        free(perfil_out->nome_jogador);
        fclose(arq);
        return false;
    }

    // 3.2 Aloca o vetor no Heap e lê os elementos em lote
    if (perfil_out->total_itens > 0) {
        perfil_out->inventario_ids = (int *) malloc(perfil_out->total_itens * sizeof(int));
        if (perfil_out->inventario_ids == NULL) {
            free(perfil_out->nome_jogador); // Rollback
            fclose(arq);
            return false;
        }

        if (fread(perfil_out->inventario_ids, sizeof(int), perfil_out->total_itens, arq) != perfil_out->total_itens) {
            free(perfil_out->nome_jogador);
            free(perfil_out->inventario_ids);
            fclose(arq);
            return false;
        }
    } else {
        perfil_out->inventario_ids = NULL;
    }

    fclose(arq);
    return true;
}

// =============================================================================
// FUNÇÃO UTILITÁRIA PARA LIBERAÇÃO DO HEAP
// =============================================================================
void liberar_perfil(PerfilJogador *perfil) {
    if (perfil != NULL) {
        free(perfil->nome_jogador);
        free(perfil->inventario_ids);
        perfil->nome_jogador = NULL;
        perfil->inventario_ids = NULL;
    }
}

// =============================================================================
// PROGRAMA PRINCIPAL DE DEMONSTRAÇÃO E VALIDAÇÃO
// =============================================================================
int main(void) {
    const char *arquivo_save = "jogador.bin";

    printf("=== ETAPA 1: Preparando dados originais no Heap ===\n");

    PerfilJogador jogador_original;
    jogador_original.id = 1001;
    jogador_original.pontuacao = 48500;

    // Alocação dinâmica da string
    const char *nome = "Capitao_Astral_99";
    jogador_original.nome_jogador = (char *) malloc(strlen(nome) + 1);
    strcpy(jogador_original.nome_jogador, nome);

    // Alocação dinâmica do vetor de inventário (ex: 4 itens)
    jogador_original.total_itens = 4;
    jogador_original.inventario_ids = (int *) malloc(jogador_original.total_itens * sizeof(int));
    jogador_original.inventario_ids[0] = 501; // Laser Duplo
    jogador_original.inventario_ids[1] = 502; // Escudo Defletor
    jogador_original.inventario_ids[2] = 505; // Bomba de Plasma
    jogador_original.inventario_ids[3] = 999; // Kit de Reparo

    printf("Nome Original: %s (Tam: %zu chars)\n", jogador_original.nome_jogador, strlen(jogador_original.nome_jogador));
    printf("Total de Itens: %u\n", jogador_original.total_itens);

    // Salvando
    printf("\n=== ETAPA 2: Serializando para '%s' ===\n", arquivo_save);
    if (salvar_perfil(arquivo_save, &jogador_original)) {
        printf("[OK] Dados gravados com sucesso.\n");
    } else {
        printf("[ERRO] Falha ao gravar arquivo.\n");
        liberar_perfil(&jogador_original);
        return 1;
    }

    // Libera a memória original para provar que a leitura independe do estado anterior
    liberar_perfil(&jogador_original);

    // Carregando
    printf("\n=== ETAPA 3: Desserializando a partir do disco ===\n");
    PerfilJogador jogador_recuperado;
    if (carregar_perfil(arquivo_save, &jogador_recuperado)) {
        printf("[OK] Arquivo lido e estruturas reconstruídas no Heap.\n");
        printf("ID: %d\n", jogador_recuperado.id);
        printf("Pontos: %d\n", jogador_recuperado.pontuacao);
        printf("Nome: %s\n", jogador_recuperado.nome_jogador);
        printf("Itens no Inventario (%u itens): ", jogador_recuperado.total_itens);
        for (uint32_t i = 0; i < jogador_recuperado.total_itens; i++) {
            printf("[%d] ", jogador_recuperado.inventario_ids[i]);
        }
        printf("\n");
    } else {
        printf("[ERRO] Falha ao ler arquivo binário.\n");
        return 1;
    }

    // Desalocação segura da estrutura carregada
    liberar_perfil(&jogador_recuperado);
    printf("\n[OK] Memória do Heap desalocada sem vazamentos.\n");

    return 0;
}