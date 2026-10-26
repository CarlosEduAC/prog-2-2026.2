# Atividades

## Exercício 1: Investigando Logs do Terminal

Analise as duas saídas de terminal enviadas por alunos e identifique em qual etapa do pipeline a execução falhou:

Caso A:

```bash

$ gcc -Wall main.c defensor.c -o jogo
defensor.c: In function 'defensor_causar_dano':
defensor.c:42:12: error: 'struct Defensor' has no member named 'pontos'
   42 |     d->pontos -= dano;
      |        ^~~~~~

```

Caso B:

```bash

$ gcc -Wall main.c defensor.c -o jogo
Undefined symbols for architecture arm64:
  "_tiros_adicionar", referenced from:
      _main in main-3a2b1c.o
ld: symbol(s) not found for architecture arm64
clang: error: linker command failed with exit code 1

```

Sua Tarefa:

1. Indique a etapa exata em que o erro foi interrompido para o Caso A e o Caso B.
2. Explique a causa técnica de cada erro e como corrigi-los.

## Exercício 2: Inclusões Duplas sem Guardas

Um estudante criou um cabeçalho inimigo.h para o jogo, mas esqueceu de adicionar as guardas de inclusão (#ifndef / #define / #endif):

inimigo.h (sem guarda):

```c

typedef struct {
    float x, y;
    int vida;
} Inimigo;

```

main.c:

```c

#include "inimigo.h"
#include "inimigo.h" // Inclusão dupla acidental no código expandido

int main(void) {
    Inimigo i;
    return 0;
}

```

Ao rodar gcc main.c -o jogo, o terminal exibe:

```bash

main.c: In file included from main.c:2:
inimigo.h:1:16: error: redefinition of 'struct Inimigo'

```

Sua Tarefa:

1. Em qual etapa do pipeline o erro de "redefinição de tipo" efetivamente trava a execução?

2. Por que o Pré-processador não aponta o erro sozinho, mas sim a etapa seguinte?

3. Adicione as guardas de inclusão adequadas ao inimigo.h para resolver o problema.

## Exercício 3: Módulos Omitidos e Protótipos Incompletos

Um projeto modular possui a seguinte estrutura: main.c, include/save.h e src/save.c. O aluno tenta compilar o projeto pelo terminal com o comando:

```bash

gcc -Wall -Iinclude main.c -o jogo

```

O log do terminal retorna o seguinte erro final:

```bash

Undefined symbols for architecture x86_64:
  "_salvar_jogo_binario", referenced from:
      _main in main.o
ld: symbol(s) not found for architecture x86_64

```

Sua Tarefa:

1. Por que o código compilou a main.c sem reclamar da função salvar_jogo_binario, mas falhou no final?

2. Qual etapa do pipeline gerou esse erro (ld)?

3. O que faltou no comando do gcc para corrigir a compilação?
