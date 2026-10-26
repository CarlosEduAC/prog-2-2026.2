# Modularização, Incluidores e Escopo de Ligação

## O Pipeline de Compilação em C

Em linguagens interpretadas (como Python ou JavaScript), o código-fonte é lido e executado linha por linha em tempo de execução. Em C, por outro lado, o código passa por uma cadeia de transformação em 4 etapas bem definidas antes de poder ser executado pelo processador.

Quando você executa um comando como gcc -Wall main.c nave.c -o jogo, o compilador executa quatro programas distintos em sequência sob o capô:

```txt

[1] ARQUIVOS DE TEXTO          [2] CÓDIGO EXPANDIDO           [3] CÓDIGO ASSEMBLY
  ┌──────────────────┐           ┌──────────────────┐           ┌──────────────────┐
  │  main.c / nave.c │ ───────>  │     main.i       │ ───────>  │     main.s       │
  │     nave.h       │  Pré-     │ (Sem #includes   │  Compi-   │ (Instruções da   │
  └──────────────────┘  proces-  │  ou #defines)    │  lador    │  CPU/Arquitetura)│
                        sador    └──────────────────┘  (cc1)    └──────────────────┘
                                                                          │
                                                                          │ Assemblador
                                                                          ▼ (as)
  [5] EXECUTÁVEL FINAL           [4] ARQUIVOS OBJETO (BINÁRIOS ISOLADOS)
  ┌──────────────────┐           ┌──────────────────┐    ┌──────────────────┐
  │  space_defender  │ <───────  │      main.o      │    │      nave.o      │
  │ (Pronto para a   │  Linker   │ (Contém tabela   │    │ (Contém código   │
  │  CPU executar)   │   (ld)    │  de símbolos)    │    │  da nave em bin) │
  └──────────────────┘           └──────────────────┘    └──────────────────┘

```

### 1. Pré-processador (cpp)

O pré-processador é um manipulador de texto. Ele não entende a sintaxe do C (não sabe o que é um if, um for ou uma variável). Ele apenas procura por linhas que começam com o caractere # e realiza substituições textuais.

O que ele faz:

- #include <arquivo.h>: Copia todo o conteúdo de arquivo.h e cola literalmente no lugar da linha do #include.

- #define NOME VALOR: Substitui todas as ocorrências de NOME por VALOR no código.

- Remoção de comentários: Remove todos os comentários (// e /* */), substituindo-os por espaços em branco.

- Compilação condicional: Processa diretivas como #ifdef e #ifndef.

**Como visualizar:** Se rodar gcc -E main.c -o main.i, você verá o arquivo gerado pelo pré-processador. Um arquivo de 20 linhas que inclui <stdio.h> pode saltar para mais de 1.000 linhas de texto bruto.

### 2. Compilador (cc1)

O compilador pega o texto expandido gerado pelo pré-processador (.i) e o traduz para código Assembly (.s), que é a representação em texto legível das instruções de baixo nível específicas da arquitetura da CPU (x86_64, ARM64/Apple Silicon, etc.).

O que ele faz:

- Análise sintática e semântica (checa se faltam ponto e vírgula, tipos incompatíveis, variáveis não declaradas).

- Aplica otimizações de código (ex: flag -O2 ou -O3).

- Emite avisos do compilador (-Wall, -Wextra).

**Como visualizar:** Rode gcc -S main.c -o main.s para gerar o arquivo em linguagem Assembly.

### 3. Assemblador (as)

O assemblador converte o arquivo Assembly (.s) em linguagem de máquina (código binário puro de zeros e umes). O resultado é um Arquivo Objeto (.o).

O que ele faz:

- Traduz instruções de texto (como MOV, ADD, PUSH) para opcodes binários da CPU.

- Cria uma Tabela de Símbolos dentro do .o. Essa tabela lista:
  - As funções e variáveis que este arquivo fornece para o mundo externo.
  - As funções e variáveis que este arquivo precisa, mas que estão definidas em outros arquivos (símbolos não resolvidos).

**Atenção:** Neste ponto, cada módulo .c é compilado de forma 100% isolada. O arquivo main.o ainda não sabe onde está o código real da função defensor_criar(), apenas sabe que precisará dela.

### 4. Ligador / Linker (ld)

O Linker pega todos os arquivos objetos isolados (main.o, defensor.o, tiro.o) e as bibliotecas externas (como a Raylib ou a biblioteca matemática -lm) e costura tudo junto em um único executável.

O que ele faz:

- Resolve a Tabela de Símbolos: encontra a chamada para defensor_criar() feita em main.o e a conecta ao endereço real da função compilada dentro de defensor.o.

- Organiza o mapa de memória do executável final.

> Onde ocorrem os erros mais comuns?

- Se você errar a sintaxe C: Erro no Compilador (Etapa 2).

- Se você declarar uma função no .h mas esquecer de escrever o código dela no .c: Erro no Linker (Etapa 4) (Undefined symbols for architecture...).

## Guardas de Inclusão (Include Guards)

Para entender a necessidade dos guardas de inclusão, precisamos lembrar o que o Pré-processador (Etapa 1) faz: ele copia e cola o conteúdo dos arquivos de cabeçalho (.h).

### O Problema: Inclusão Dupla e Redefinição de Tipos

Em um projeto modularizado como o Space Defender, é natural que múltiplos arquivos de cabeçalho precisem das mesmas definições.

Imagine o seguinte cenário de dependência:

```txt

                  ┌──────────────┐
                  │   config.h   │ (Define a struct ConfigJanela)
                  └──────────────┘
                    ▲          ▲
         #include   │          │ #include
   ┌────────────────┴─┐      ┌─┴────────────────┐
   │    defensor.h    │      │    inimigo.h     │
   └──────────────────┘      └──────────────────┘
            ▲                          ▲
   #include │                          │ #include
   ┌────────┴──────────────────────────┴────────┐
   │                  main.c                    │
   └────────────────────────────────────────────┘

```

Se o main.c incluir defensor.h e inimigo.h, veja o que o pré-processador faz visualmente:

```c

// O pré-processador lê o main.c:

#include "defensor.h"
// --> Expande defensor.h, que faz #include "config.h"
// --> O conteúdo de config.h é colado aqui:
struct ConfigJanela {
    int largura;
    int altura;
};

#include "inimigo.h"
// --> Expande inimigo.h, que TAMBÉM faz #include "config.h"
// --> O conteúdo de config.h é colado AQUI DE NOVO:
struct ConfigJanela {  // <-- ERRO FATAL DO COMPILADOR!
    int largura;       // "error: redefinition of 'struct ConfigJanela'"
    int altura;
};

```

Como o C proíbe redefinir a mesma struct ou typedef mais de uma vez no mesmo arquivo compilado, a compilação é abortada.

### A Solução: A Lógica da Guarda de Inclusão

A guarda de inclusão funciona como um trinco de segurança do pré-processador. Ela usa três diretivas para garantir que o conteúdo do arquivo só seja lido uma única vez por unidade de compilação.

A estrutura padrão é:

```c

#ifndef CONFIG_H    // 1. "Se a 'marquinha' CONFIG_H AINDA NÃO foi definida..."
#define CONFIG_H    // 2. "Defina a 'marquinha' CONFIG_H agora mesmo!"

// -----------------------------------------------------------------------------
// CONTEÚDO DO CABEÇALHO (Declarações de structs, protótipos de funções, etc.)
// -----------------------------------------------------------------------------
typedef struct {
    int largura;
    int altura;
} ConfigJanela;

#endif              // 3. "Fim do bloco condicional"

```

### Como o Pré-processador interpreta o arquivo na prática?

1. Primeira vez que config.h é encontrado (via defensor.h):
   - O pré-processador testa #ifndef CONFIG_H. Como a constante CONFIG_H ainda não existe, a condição é Verdadeira.
   - Ele entra no bloco, executa #define CONFIG_H (registrando a constante na memória do pré-processador) e cola o código da struct ConfigJanela.

2. Segunda vez que config.h é encontrado (via inimigo.h):
   - O pré-processador testa #ifndef CONFIG_H.
   - Desta vez, a constante CONFIG_H já foi registrada no passo anterior! A condição é Falsa.
   - O pré-processador salta todo o conteúdo direto para o #endif, ignorando o arquivo completamente.
   - Resultado: O código não é duplicado e o erro de redefinição desaparece.

### Convenção de Nomenclatura das Guardas

Por convenção internacional, a constante da guarda deve ser única para cada arquivo no projeto, escrita em letras maiúsculas derivadas do próprio nome do arquivo:

```c

// Para o arquivo include/defensor.h:
#ifndef DEFENSOR_H
#define DEFENSOR_H

// ... código ...

#endif

// Para o arquivo include/tiro.h:
#ifndef TIRO_H
#define TIRO_H

// ... código ...

#endif

```

Alternativa: #pragma once

Você também encontrará em muitos códigos modernos a diretiva:

```c

#pragma once

```

- Diferença: O #pragma once instrui o compilador a incluir o arquivo apenas uma vez. É mais curto e atua direto no sistema de arquivos.
- Recomendação didática: Embora o #pragma once funcione na maioria dos compiladores atuais (GCC, Clang, MSVC), aprender e utilizar a estrutura clássica #ifndef / #define / #endif é fundamental para que você compreenda o funcionamento do pré-processador e garanta adesão ao padrão ANSI C99 estrito.

## O Modificador static e Escopo de Ligação

Em C, o modificador static possui significados diferentes dependendo do contexto. No nível de módulo/biblioteca (.c), ele define a ligação interna (internal linkage).

### Onde usar static na criação de bibliotecas?

Sempre que criarmos funções auxiliares privadas que ajudam a implementar o módulo, mas que não devem ser visíveis para o Linker nem chamadas por outros arquivos.

```c

// src/ranking.c
#include "ranking.h"

// FUNÇÃO PRIVADA (STATIC): Visível APENAS dentro de src/ranking.c
// NENHUM outro arquivo .c conseguirá chamá-la ou vinculá-la pelo Linker!
static int particionar_quicksort(RegistroScore *vetor, int inicio, int fim) {
    int pivo = vetor[fim].pontos;
    // ... lógica do particionamento ...
    return i + 1;
}

// FUNÇÃO PÚBLICA (INTERFACE DO CABEÇALHO):
void ranking_ordenar(RegistroScore *vetor, int qtd) {
    if (vetor == NULL || qtd <= 1) return;
    // Utiliza a função auxiliar estática privada
    particionar_quicksort(vetor, 0, qtd - 1);
}

```

## Prática Guiada no Laboratório

[src/math_game.h](src/math_game.h)
[src/math_game.c](src/math_game.c)
