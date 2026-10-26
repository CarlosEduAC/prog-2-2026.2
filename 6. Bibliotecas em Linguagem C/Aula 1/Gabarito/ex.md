# Soluções

## 1

Caso A:

- Etapa do Pipeline: Compilador (Etapa 2 - Análise Semântica/Sintática).

- Causa Técnica: O compilador analisou a definição interna da struct Defensor e verificou que o membro pontos não existe dentro do tipo. Trata-se de uma violação da verificação de tipos e sintaxe.

- Correção: Alterar o nome da variável no código para um membro existente (ex: d->vida -= dano;) ou criar a propriedade pontos na struct Defensor dentro do arquivo .c.

Caso B:

- Etapa do Pipeline: Linker / Ligador (Etapa 4) (indicado por ld: symbol(s) not found).

- Causa Técnica: A main.c chamou a função tiros_adicionar, o pré-processador aceitou a declaração no .h e o compilador gerou a instrução em main.o. Porém, na fase de costurar os arquivos objetos (.o), o Linker procurou pelo código binário real da função e não encontrou, pois o arquivo tiro.c não foi passado no comando de compilação.

- Correção: Incluir o arquivo de implementação no comando do GCC: gcc -Wall main.c defensor.c tiro.c -o jogo.

## 2

1. Etapa do Erro: Compilador (Etapa 2).

2. Explicação: O Pré-processador não valida tipos em C; ele apenas executa comandos de colagem textual. Ele colou o conteúdo do inimigo.h duas vezes dentro do arquivo intermediário expandido (main.i). Quem tentou traduzir main.i para código binário e percebeu que havia duas declarações idênticas da struct Inimigo no mesmo escopo foi o Compilador.

3. Código Corrigido (inimigo.h):

```c

#ifndef INIMIGO_H
#define INIMIGO_H

typedef struct {
    float x, y;
    int vida;
} Inimigo;

#endif // INIMIGO_H

```

## 3

1. Explicação: A main.c incluiu o cabeçalho save.h via -Iinclude. Ao encontrar o protótipo da função no .h, o Compilador aceitou a chamada e criou uma pendência na tabela de símbolos de main.o, assumindo que a função seria fornecida mais tarde.

2. Etapa do Erro: Linker / Ligador (ld).

3. Correção no Comando: O aluno esqueceu de compilar e vincular o arquivo de implementação src/save.c. O comando correto é:

```bash

gcc -Wall -Iinclude main.c src/save.c -o jogo

```
