# Tipos Abstratos de Dados (TADs) & Encapsulamento em C

## Abstração vs. Encapsulamento

Diferença entre como pensamos em um objeto e como o programamos em nível de máquina. Usamos structs abertas: o programa cliente acessa campos como aluno.nome ou node->proximo diretamente. Se o cliente pode alterar qualquer campo sem restrição, não há garantia de integridade.

- **Abstração**: Focar no que o tipo de dados faz (suas operações/comportamentos), ignorando como ele é representado internamente na memória.
- **Encapsulamento**: Proibir o acesso direto aos membros internos da estrutura, forçando qualquer interação a passar por uma interface pública de funções (médodos/funções do TAD).

```txt

                    CÓDIGO CLIENTE (main.c)
                             │
                             ▼  Chama apenas funções públicas: defensor_criar(), defensor_causar_dano()
           ┌───────────────────────────────────┐
           │     INTERFACE PÚBLICA (.h)        │  <-- Contrato (O que o TAD faz)
           └───────────────────────────────────┘
                             │
                             ▼  Modifica a memória internamente
           ┌───────────────────────────────────┐
           │ IMPLEMENTAÇÃO PRIVADA (.c)        │  <-- Oculto do cliente (Como faz)
           │ struct Defensor { int x, vida; }; │
           └───────────────────────────────────┘

```

## A Anatomia de um TAD em C

C não possui palavras-chave como private ou public de linguagens orientadas a objetos. Em C, a privacidade é construída através da organização do sistema de arquivos de cabeçalho (.h) e de código fonte (.c).

### O Problema do Acesso Direto (Sem TAD)

```c

// Estrutura EXPOSTA no .h (Abordagem Ruim)
typedef struct {
    int x;
    int vida;
} Defensor;

// No main.c, o aluno ou programador cliente faz:
Defensor d;
d.vida = -999; // QUEBROU A INVARIANTE! Não passou por nenhuma validação.

```

### A Solução com TAD

Para criar um TAD em C, declaramos apenas o typedef struct incompleto no arquivo de cabeçalho (.h), escondendo os membros concretos no arquivo de implementação (.c).

## Ponteiros Opacos (Opaque Pointers) e Invariantes de Estado

Um ponteiro opaco é um ponteiro para uma estrutura cuja definição completa não foi exposta ao arquivo que o consome.

### 1. O Arquivo de Cabeçalho / Contrato (defensor.h)

```c

#ifndef DEFENSOR_H
#define DEFENSOR_H

#include <stdbool.h>

// DECLARAÇÃO INCOMPLETA (Ponteiro Opaco)
// O cliente sabe que 'Defensor' existe, mas NÃO sabe o que há dentro dele!
typedef struct Defensor Defensor;

// Funções Construtoras e Destrutoras (Gerenciamento do Heap)
Defensor* defensor_criar(int x_inicial, int vida_inicial);
void defensor_destruir(Defensor *d);

// Interface de Operações (Comportamento)
void defensor_causar_dano(Defensor *d, int dano);
int defensor_get_vida(const Defensor *d);

#endif

```

### 2. O Arquivo de Implementação (defensor.c)

```c

#include "defensor.h"
#include <stdlib.h>

// DEFINIÇÃO CONCRETA (Privada apenas dentro deste arquivo .c)
struct Defensor {
    int x;
    int vida;
};

Defensor* defensor_criar(int x_inicial, int vida_inicial) {
    Defensor *d = (Defensor *) malloc(sizeof(Defensor));
    if (d == NULL) return NULL; // Validação de memória

    d->x = x_inicial;
    // Garantia da Invariante de Estado: Vida nunca pode iniciar negativa
    d->vida = (vida_inicial > 0) ? vida_inicial : 100;

    return d;
}

void defensor_causar_dano(Defensor *d, int dano) {
    if (d == NULL || dano <= 0) return;

    d->vida -= dano;
    if (d->vida < 0) d->vida = 0; // Proteção contra estado inválido
}

int defensor_get_vida(const Defensor *d) {
    if (d == NULL) return 0;
    return d->vida;
}

void defensor_destruir(Defensor *d) {
    if (d != NULL) {
        free(d);
    }
}

```

## Prática Guiada no Laboratório

Tentem quebrar o encapsulamento no main.c para provar o erro de compilação disparado pelo GCC.

Por exemplo, tentem acessar diretamente os campos da estrutura `Defensor`:

```c

// main.c
#include <stdio.h>
#include "defensor.h"

int main(void) {
    Defensor *d = defensor_criar(400, 100);

    // TESTE DE ENCAPSULAMENTO:
    // Descomente a linha abaixo e tente compilar com gcc:
    // printf("Vida direta: %d\n", d->vida);

    // O compilador vai emitir o erro:
    // "error: dereferencing pointer to incomplete type 'Defensor'"

    defensor_causar_dano(d, 30);
    printf("Vida via Interface do TAD: %d\n", defensor_get_vida(d));

    defensor_destruir(d);
    return 0;
}

```

### Por que isso é revolucionário?

Se no futuro decidirmos mudar a variável vida de int para float dentro de defensor.c, nenhuma linha do main.c precisará ser alterada ou recompilada por quebra de tipo! O contrato no .h permanece idêntico.

## Conexão com o Projeto Integrador

| Sem TADs (Código Frágil)                                   | Com TADs (Código Profissional)                                                             |
|------------------------------------------------------------|--------------------------------------------------------------------------------------------|
| O main.c acessa tiro->proximo ou canhao->vida diretamente. | Toda alteração de estado é feita via contrato (tiros_adicionar(), defensor_causar_dano()). |
| Risco alto de corromper ponteiros na RAM por erro no loop. | Ponteiros mantidos ocultos no Heap, inacessíveis fora do seu .c.                           |
| Arquivo monolítico com 1500 linhas impossível de depurar.  | Módulos pequenos, testáveis e com responsabilidade única.                                  |
