#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "placar.h"
#include "vetor.h"
#include "lista_alunos.h"

// Funções auxiliares para formatação de testes no console
static void test_header(const char *titulo) {
    printf("\n==================================================\n");
    printf("  TESTANDO TAD: %s\n", titulo);
    printf("==================================================\n");
}

static void test_assert(bool condicao, const char *mensagem) {
    if (condicao) {
        printf(" [ PASS ] %s\n", mensagem);
    } else {
        printf(" [ FAIL ] %s\n", mensagem);
    }
}

// ----------------------------------------------------------------------------
// 1. TESTES DO TAD PLACAR
// ----------------------------------------------------------------------------
void testar_tad_placar(void) {
    test_header("PLACAR");

    // Instanciação via construtor
    Placar *p = placar_criar("Comandante Silva");
    test_assert(p != NULL, "Instanciacao do Placar no Heap");
    test_assert(placar_get_pontos(p) == 0, "Pontuacao inicial deve ser 0");
    test_assert(placar_get_vidas(p) == 3, "Quantidade de vidas inicial deve ser 3");

    // Alteração de estado via contrato
    placar_adicionar_pontos(p, 500);
    test_assert(placar_get_pontos(p) == 500, "Adicao de 500 pontos");

    // Teste de invariante: adicao invalida (negativa) deve ser ignorada
    placar_adicionar_pontos(p, -200);
    test_assert(placar_get_pontos(p) == 500, "Invariante: Adicao negativa ignorada");

    // Remoção de vidas
    placar_remover_vida(p);
    test_assert(placar_get_vidas(p) == 2, "Remocao de 1 vida (restam 2)");

    // Teste de invariante: vidas nao podem ficar negativas
    placar_remover_vida(p);
    placar_remover_vida(p);
    placar_remover_vida(p); // 4a remocao
    test_assert(placar_get_vidas(p) == 0, "Invariante: Vidas nao ficam abaixo de 0");

    // Desalocação
    placar_destruir(p);
    printf(" -> Memoria do Placar liberada com sucesso.\n");
}

// ----------------------------------------------------------------------------
// 2. TESTES DO TAD VETOR DINÂMICO
// ----------------------------------------------------------------------------
void testar_tad_vetor(void) {
    test_header("VETOR DINAMICO");

    // Cria vetor com capacidade inicial pequena (2) para forçar o realloc oculto
    VetorDinamico *v = vetor_criar(2);
    test_assert(v != NULL, "Instanciacao do Vetor Dinamico no Heap");
    test_assert(vetor_get_tamanho(v) == 0, "Tamanho inicial deve ser 0");

    // Inserção com expansão dinâmica
    vetor_inserir(v, 10);
    vetor_inserir(v, 20);
    test_assert(vetor_get_tamanho(v) == 2, "Insercao de 2 elementos sem expansao");

    // 3a inserção: dispara o realloc transparente dentro do .c
    bool ok_expansao = vetor_inserir(v, 30);
    test_assert(ok_expansao && vetor_get_tamanho(v) == 3, "Expansao automatica via realloc ao exceder capacidade");

    // Leitura via ponteiro de saída (getters com validação de limites)
    int valor;
    bool ok_leitura = vetor_obter(v, 1, &valor);
    test_assert(ok_leitura && valor == 20, "Leitura do elemento no indice 1 (valor = 20)");

    // Teste de limite (out of bounds)
    bool ok_invalido = vetor_obter(v, 99, &valor);
    test_assert(!ok_invalido, "Invariante: Leitura fora dos limites rejeitada com seguranca");

    // Desalocação
    vetor_destruir(v);
    printf(" -> Memoria do Vetor Dinamico liberada com sucesso.\n");
}

// ----------------------------------------------------------------------------
// 3. TESTES DO TAD LISTA DE ALUNOS
// ----------------------------------------------------------------------------
void testar_tad_lista_alunos(void) {
    test_header("LISTA DE ALUNOS (ENCAPSULADA)");

    ListaAlunos *l = lista_criar();
    test_assert(l != NULL, "Instanciacao da Lista no Heap");

    // Inserção de elementos (Nós mantidos 100% ocultos no .c)
    lista_inserir(l, 202601, 8.5f);
    lista_inserir(l, 202602, 9.8f);
    lista_inserir(l, 202603, 7.0f);

    // Busca de dados via interface do TAD
    float nota_aluno = lista_buscar_nota(l, 202602);
    test_assert(nota_aluno == 9.8f, "Busca de nota por matricula existente (202602 -> 9.8)");

    // Busca de aluno inexistente
    float nota_inexistente = lista_buscar_nota(l, 999999);
    test_assert(nota_inexistente == -1.0f, "Busca por matricula inexistente retorna -1.0");

    // Desalocação encadeada
    lista_destruir(l);
    printf(" -> Memoria de todos os nos da Lista liberada com sucesso.\n");
}

// ----------------------------------------------------------------------------
// PONTO DE ENTRADA PRINCIPAL
// ----------------------------------------------------------------------------
int main(void) {
    printf("==================================================\n");
    printf("   SUITE DE TESTES E VALIDACAO DE TADS (C PURO)   \n");
    printf("==================================================\n");

    testar_tad_placar();
    testar_tad_vetor();
    testar_tad_lista_alunos();

    printf("\n==================================================\n");
    printf(" [ SUCESSO ] Todos os testes foram executados!\n");
    printf("==================================================\n\n");

    return 0;
}