## Laboratório Prático: Gerenciador de Tarefas e Processos em C (TADs & Bibliotecas)

**Carga Horária:** 100 minutos (1h40min)

**Tópicos:** Tipos Abstratos de Dados (TADs), Ponteiros Opacos, Bibliotecas, Modificador `static`, Alocação Dinâmica com Rollback e Programação Defensiva.

---

## 1. Apresentação do Desafio

Neste laboratório, você atuará como desenvolvedor de sistemas operacionais responsável por construir a biblioteca interna de um **Gerenciador de Tarefas e Processos** (`TAD GerenciadorTarefas`).

O objetivo é projetar um módulo seguro, modular e encapsulado, capaz de alocar um vetor dinâmico de processos no Heap, inserir tarefas respeitando limites rígidos de capacidade, selecionar e executar a tarefa de **maior prioridade** e garantir que nenhuma memória alocada seja vazada ao final da execução.

### Requisitos Arquiteturais

* **Encapsulamento Estrito:** A estrutura interna da `struct GerenciadorTarefas` e da `struct Tarefa` deve ser mantida oculta do código cliente (`main.c`) utilizando **Ponteiros Opacos**.
* **Ligação Interna (*Internal Linkage*):** Funções de busca e apoio devem ser ocultadas do *Linker* utilizando o modificador **`static`**.
* **Gestão Defensiva de Memória:** O construtor do TAD deve tratar falhas de alocação de memória executando mecanismo de ***rollback*** para evitar *memory leaks*.

---

## 2. Estrutura do Projeto

O seu ambiente de trabalho está organizado na seguinte estrutura de diretórios:

```text
lab_gerenciador/
├── include/
│   └── gerenciador_tarefas.h   # Contrato público (Include Guards + Ponteiro Opaco)
├── src/
│   └── gerenciador_tarefas.c   # Sua implementação (A ser preenchida)
├── main.c                       # Suíte de testes automatizada do aluno
└── README.md                    # Este guia de instruções
```

---

## 3. O que Você Tem Disponível (*Starter Kit*)

Você **não** precisa alterar os arquivos `include/gerenciador_tarefas.h` nem `main.c`. Trabalhe estudando a interface pública e os testes automatizados fornecidos.

### 3.1. Arquivo de Cabeçalho (`include/gerenciador_tarefas.h`)

Contém o contrato rígido da biblioteca com a declaração incompleta do tipo opaco e protótipos das funções:

```c
#ifndef GERENCIADOR_TAREFAS_H
#define GERENCIADOR_TAREFAS_H

#include <stdbool.h>

// DECLARAÇÃO INCOMPLETA (Ponteiro Opaco)
typedef struct GerenciadorTarefas GerenciadorTarefas;

// Construtor e Destrutor no Heap
GerenciadorTarefas* gerenciador_criar(int capacidade_maxima);
void gerenciador_destruir(GerenciadorTarefas *gt);

// Operações de Interface
bool gerenciador_adicionar_tarefa(GerenciadorTarefas *gt, int pid, const char *nome_processo, int prioridade);
bool gerenciador_executar_proxima_tarefa(GerenciadorTarefas *gt, int *pid_executado_out);

// Getters de Leitura
int gerenciador_get_total_pendentes(const GerenciadorTarefas *gt);
int gerenciador_get_capacidade(const GerenciadorTarefas *gt);

#endif // GERENCIADOR_TAREFAS_H
```

### 3.2. Suíte de Testes do Aluno (`main.c`)

Fornece um executor visual dos testes da sua biblioteca:

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gerenciador_tarefas.h"

static void checar(bool condicao, const char *nome_teste) {
    if (condicao) {
        printf(" [ PASS ] %s\n", nome_teste);
    } else {
        printf(" [ FAIL ] %s\n", nome_teste);
    }
}

int main(void) {
    printf("========================================================\n");
    printf("   LABORATÓRIO PRÁTICO: GERENCIADOR DE TAREFAS (TAD)    \n");
    printf("========================================================\n\n");

    printf("--- FASE 1: Testando Construtor e Destrutor ---\n");
    GerenciadorTarefas *gt = gerenciador_criar(3);
    checar(gt != NULL, "Instanciacao do TAD no Heap");
    checar(gerenciador_get_capacidade(gt) == 3, "Capacidade configurada para 3");
    checar(gerenciador_get_total_pendentes(gt) == 0, "Total de pendentes inicial e 0");

    printf("\n--- FASE 2: Testando Insercao e Invariantes ---\n");
    bool ok1 = gerenciador_adicionar_tarefa(gt, 101, "HTTP_Server", 2);
    bool ok2 = gerenciador_adicionar_tarefa(gt, 102, "DB_Backup", 5);  // Maior prioridade
    bool ok3 = gerenciador_adicionar_tarefa(gt, 103, "Log_Writer", 1);
    checar(ok1 && ok2 && ok3, "Insercao de 3 tarefas validas");
    checar(gerenciador_get_total_pendentes(gt) == 3, "Total de pendentes atualizado para 3");

    // Teste de Invariante: Estouro de capacidade
    bool ok_estouro = gerenciador_adicionar_tarefa(gt, 104, "Render", 10);
    checar(!ok_estouro, "Invariante: Rejeitar 4a tarefa (limite e 3)");

    printf("\n--- FASE 3: Testando Selecao por Prioridade (static) ---\n");
    int pid_exec;
    gerenciador_executar_proxima_tarefa(gt, &pid_exec);
    checar(pid_exec == 102, "Executar tarefa de MAIOR prioridade primeiro (PID 102)");

    gerenciador_executar_proxima_tarefa(gt, &pid_exec);
    checar(pid_exec == 101, "Executar segunda maior prioridade (PID 101)");

    checar(gerenciador_get_total_pendentes(gt) == 1, "Restante de pendentes atualizado para 1");

    printf("\n--- FASE 4: Liberacao de Memoria ---\n");
    gerenciador_destruir(gt);
    printf(" -> Memoria desalocada com sucesso.\n\n");

    return 0;
}
```

---

## 4. O que Você Deve Desenvolver

Você deve implementar **exclusivamente** o arquivo `src/gerenciador_tarefas.c`, completando os blocos demarcados com `TODO`:

```c
#include "gerenciador_tarefas.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Struct privada para cada Tarefa
typedef struct {
    int pid;
    char nome[32];
    int prioridade;
    bool ativa;
} Tarefa;

// Struct concreta privada do TAD
struct GerenciadorTarefas {
    Tarefa *fila_processos;
    int capacidade;
    int qtd_pendentes;
};

// =============================================================================
// DESAFIO 3: Função Auxiliar Privada (Oculta do Linker)
// =============================================================================
static int encontrar_indice_maior_prioridade(const GerenciadorTarefas *gt) {
    // TODO 1: Declare variaveis para guardar a maior prioridade vista (-1) e seu indice (-1).
    // TODO 2: Percorra o vetor 'fila_processos' ate a capacidade maxima.
    // TODO 3: Se a tarefa estiver ativa E sua prioridade for maior que a 'maior prioridade' atual:
    //         - Atualize a maior prioridade e guarde o indice.
    // TODO 4: Retorne o indice encontrado (ou -1 se nenhuma tarefa ativa for encontrada).
    return -1;
}

// =============================================================================
// DESAFIO 1: Construtor Seguro com Rollback e Destrutor
// =============================================================================
GerenciadorTarefas* gerenciador_criar(int capacidade_maxima) {
    // TODO 1: Valide se capacidade_maxima > 0. Se invalido, retorne NULL.

    // TODO 2: Aloque a estrutura principal 'GerenciadorTarefas' com malloc.
    //         Se falhar, retorne NULL.

    // TODO 3: Aloque o vetor 'fila_processos' no Heap com calloc para 'capacidade_maxima' elementos.
    //         ROLLBACK: Se o calloc falhar, voce DEVE dar free() na estrutura alocada no TODO 2
    //         antes de retornar NULL!

    // TODO 4: Inicialize os campos 'capacidade' e 'qtd_pendentes' (que inicia em 0).
    // TODO 5: Retorne o ponteiro alocado.
    return NULL;
}

void gerenciador_destruir(GerenciadorTarefas *gt) {
    // TODO 1: Defesa contra NULL.
    // TODO 2: Libere primeiro o vetor interno 'fila_processos'.
    // TODO 3: Libere a estrutura principal 'gt'.
}

// =============================================================================
// DESAFIO 2: Insercao Defensiva e Invariantes
// =============================================================================
bool gerenciador_adicionar_tarefa(GerenciadorTarefas *gt, int pid, const char *nome_processo, int prioridade) {
    // TODO 1: Validacao defensiva completa:
    //         - gt != NULL
    //         - pid > 0
    //         - nome_processo != NULL
    //         - prioridade >= 0
    //         - qtd_pendentes < capacidade (Invariante de Limite!)
    //         Se alguma falhar, retorne false.

    // TODO 2: Encontre o primeiro slot livre no vetor (onde .ativa == false).
    // TODO 3: Preencha os dados do slot:
    //         - pid
    //         - strncpy para copiar o nome com seguranca (max 31 chars + '\0')
    //         - prioridade
    //         - ativa = true
    // TODO 4: Incremente 'qtd_pendentes' e retorne true.

    return false;
}

bool gerenciador_executar_proxima_tarefa(GerenciadorTarefas *gt, int *pid_executado_out) {
    // TODO 1: Valide se gt != NULL, se qtd_pendentes > 0 e se pid_executado_out != NULL.

    // TODO 2: Chame a funcao estatica 'encontrar_indice_maior_prioridade(gt)'.
    //         Se o indice retornado for -1, retorne false.

    // TODO 3: Atribua o PID do processo encontrado ao ponteiro de saida (*pid_executado_out).
    // TODO 4: Marque a tarefa naquele indice como inativa (.ativa = false).
    // TODO 5: Decremente 'qtd_pendentes' e retorne true.

    return false;
}

// Getters de Leitura
int gerenciador_get_total_pendentes(const GerenciadorTarefas *gt) {
    return gt ? gt->qtd_pendentes : 0;
}

int gerenciador_get_capacidade(const GerenciadorTarefas *gt) {
    return gt ? gt->capacidade : 0;
}
```

---

## 5. Instruções de Compilação, Execução e Validação

### Step 1: Compilando a Aplicação

Abra o terminal no diretório raiz do projeto e execute o comando abaixo para realizar a compilação separada conectando a pasta de cabeçalhos `include/`:

```bash
gcc -Wall -Wextra -std=c99 -Iinclude main.c src/gerenciador_tarefas.c -o lab_exec
```

### Step 2: Executando os Testes Automatizados

Rode o binário gerado para conferir o status de cada fase:

```bash
./lab_exec
```

*Saída Esperada ao concluir todos os TODOs:*

```txt
 [ PASS ] Instanciacao do TAD no Heap
 [ PASS ] Capacidade configurada para 3
 [ PASS ] Total de pendentes inicial e 0
 [ PASS ] Insercao de 3 tarefas validas
 [ PASS ] Total de pendentes atualizado para 3
 [ PASS ] Invariante: Rejeitar 4a tarefa (limite e 3)
 [ PASS ] Executar tarefa de MAIOR prioridade primeiro (PID 102)
 [ PASS ] Executar segunda maior prioridade (PID 101)
 [ PASS ] Restante de pendentes atualizado para 1
```

## 6. Critérios de Avaliação e Checklist

Antes de entregar, certifique-se de preencher todos os itens do checklist:

* [ ] **Ponteiro Opaco:** A `struct GerenciadorTarefas` não foi movida para o `.h`.
* [ ] **Testes de Invariante:** Tentativas de exceder a capacidade ou inserir ponteiros `NULL`/PIDs inválidos retornam `false` sem *crash*.
* [ ] **Mecanismo de Rollback:** Se o `calloc` falhar no construtor, a estrutura alocada no `malloc` é liberada antes do retorno de `NULL`.
* [ ] **Ligação Interna (*Internal Linkage*):** A função `encontrar_indice_maior_prioridade` utiliza a palavra-chave `static`.
