# Persistência em Arquivos Texto

## Teoria de I/O, Ponteiro FILE e Buffers em RAM

### 1. O Conceito de Stream (Fluxo de Dados)

Em C, a linguagem não conversa diretamente com os setores do disco ou com o sistema de arquivos (EXT4, NTFS, APFS). Ela utiliza uma abstração chamada Stream (fluxo sequencial de bytes).

```c

PROGRAMA (C)                MECANISMO DE I/O                DISCO / SSD
┌──────────────┐           ┌───────────────────┐           ┌──────────────────┐
│ Variables na │ ──write──>│ Buffer em RAM     │ ──flush──>│ Arquivo Físico   │
│ Memória RAM  │ <──read───│ (Estrutura FILE)  │ <──fetch──│ "config.txt"     │
└──────────────┘           └───────────────────┘           └──────────────────┘

```

### 2. O Tipo Opaco FILE

O tipo FILE (definido em <stdio.h>) é uma estrutura que guarda o estado atual da conexão entre o programa e o arquivo no disco. Seus campos internos incluem:

- O ponteiro para o buffer de memória RAM intermediário.

- O indicador de posição de leitura/escrita (file position indicator / cursor).

- Flags de estado de erro e de fim de arquivo (EOF).

Atenção: Como a estrutura FILE é mantida e gerenciada pelo Sistema Operacional, nós nunca alocamos ou declaramos um FILE diretamente na pilha (stack). Usamos sempre um ponteiro (FILE *) retornado por fopen().

### 3. A Importância do fclose() e o Flush de Memória

Escrever em um arquivo não grava instantaneamente no SSD. Os dados são acumulados em um buffer na RAM para otimizar o desempenho de I/O.

- Chamar fclose(arq) força o descarregamento do buffer no disco (flush), atualiza o tamanho do arquivo no sistema operacional e libera a tabela de descritores de arquivo mantida pelo kernel.

- Se o programa encerrar sem fechar o arquivo, os últimos dados gravados podem ser perdidos ou corrompidos.

## Modos de Abertura com fopen()

A função fopen() estabelece a ponte entre o caminho do arquivo no sistema operacional e a estrutura FILE* no C:

```c

FILE *fopen(const char *caminho_do_arquivo, const char *modo);

```

### Análise Categórica dos Modos para Arquivos Texto

| Modo | Nome            | Comportamento se o arquivo EXISTIR       | Comportamento se o arquivo NÃO EXISTIR | Posição do Cursor Inicial             |
|------|-----------------|------------------------------------------|----------------------------------------|---------------------------------------|
| "r"  | Read (Leitura)  | Abre para leitura normalmente.           | Retorna NULL (Falha).                  | Início do arquivo (byte 0)            |
| "w"  | Write (Escrita) | TRUNCA (Apaga todo o conteúdo anterior)! | Cria um novo arquivo vazio.            | Início do arquivo (byte 0)            |
| "a"  | Append (Anexo)  | Preserva o conteúdo existente.           | Cria um novo arquivo.                  | Fim do arquivo                        |
| "r+" | Read/Write      | Abre para leitura e escrita sem apagar.  | Retorna NULL (Falha).                  | Início do arquivo                     |
| "w+" | Write/Read      | TRUNCA o arquivo e permite reler.        | Cria um novo arquivo.                  | Início do arquivo                     |
| "a+" | Append/Read     | Preserva o conteúdo e permite leitura.   | Cria um novo arquivo.                  | Fim (para escrita) / Início (leitura) |

Regra: Todo retorno de fopen() deve ser verificado contra NULL antes de qualquer chamada subsequente de I/O.

## Mecânica de Leitura e Escrita Formatada

1. Escrita Formatada com fprintf()

A função fprintf() funciona analogamente ao printf(), porém direcionando a saída formatada de caracteres para o fluxo de dados do arquivo.

```c

int fprintf(FILE *stream, const char *formato, ...);

```

```c

FILE *arq = fopen("config.txt", "w");
if (arq != NULL) {
    int largura = 800;
    int altura = 600;
    // Grava texto plano formatado no buffer do arquivo
    fprintf(arq, "LARGURA=%d\nALTURA=%d\n", largura, altura);
    fclose(arq);
}

```

2. Leitura Formatada com fscanf() e Verificação de Tokenizacão

A função fscanf() faz o parsing (análise léxica) do texto plano no disco e tenta converter os caracteres numéricos para variáveis no C.

```c

int fscanf(FILE *stream, const char *formato, ...);

```

O Segredo do Valor de Retorno do fscanf():

O fscanf() retorna um inteiro representando a quantidade exata de especificadores de formato (%d, %s, %f) convertidos e atribuídos com sucesso.

```c

FILE *arq = fopen("config.txt", "r");
if (arq != NULL) {
    int largura, altura;

    // Tentamos ler DOIS inteiros (%d ... %d)
    int itens_lidos = fscanf(arq, "LARGURA=%d\nALTURA=%d", &largura, &altura);

    if (itens_lidos == 2) {
        printf("Leitura realizada com sucesso: %dx%d\n", largura, altura);
    } else {
        printf("Erro de sintaxe ou arquivo corrompido!\n");
    }

    fclose(arq);
}

```

## Padrão Defensivo: Parsing, EOF e Fallback Automático

### O Fluxograma de Inicialização Defensiva

Quando uma aplicação inicializa e precisa carregar preferências em texto:

```txt

                  ┌───────────────────────────────┐
                  │ Tenta abrir com fopen(...,"r")│
                  └──────────────┬────────────────┘
                                 │
                   ┌─────────────┴─────────────┐
                   ▼                           ▼
          [ Ponteiro é NULL ]         [ Ponteiro VÁLIDO ]
                   │                           │
                   ▼                           ▼
      1. Tenta criar com "w"         1. Tenta ler com fscanf()
      2. Escreve valores Padrão      2. Valida se lidos == esperados
      3. Define variáveis locais     3. Se inválido, usa Fallback

```

Implementação Teórico-Prática do Módulo:

```c

#include <stdio.h>
#include <stdbool.h>

bool carregar_configuracao_defensiva(const char *caminho, int *largura_out, int *altura_out) {
    if (caminho == NULL || largura_out == NULL || altura_out == NULL) {
        return false;
    }

    FILE *arq = fopen(caminho, "r");

    // CASO 1: Arquivo não existe no disco -> Criar arquivo padrão com modo "w"
    if (arq == NULL) {
        arq = fopen(caminho, "w");
        if (arq == NULL) {
            return false; // Erro de permissão de escrita no SO
        }

        // Escreve os valores padrão (800x600)
        fprintf(arq, "LARGURA=800\nALTURA=600\n");
        fclose(arq);

        // Define os valores de saída
        *largura_out = 800;
        *altura_out = 600;
        return true;
    }

    // CASO 2: Arquivo existe -> Tenta realizar a leitura e parsing
    int lidos = fscanf(arq, "LARGURA=%d\nALTURA=%d", largura_out, altura_out);

    // Validação contra parsing parcial ou arquivo corrompido
    if (lidos != 2) {
        // Fallback: Se o arquivo no disco estiver corrompido, aplica o padrão
        *largura_out = 800;
        *altura_out = 600;
    }

    fclose(arq);
    return true;
}

```

## Relação com o Projeto Final

- Independência de Recompilação: O usuário ou designer do jogo pode abrir o arquivo config.txt no Bloco de Notas ou VS Code, alterar LARGURA=1024 e ALTURA=768, e o jogo iniciará na nova resolução sem precisar recompilar o código C.

- Resiliência a Falhas: Se o usuário deletar acidentalmente o arquivo config.txt, o jogo não entra em crash: o mecanismo de fallback recria o arquivo com os valores padrão de fábrica (800x600).
