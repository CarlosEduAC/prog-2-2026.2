# Persistência Binária em C com fwrite e fread (savegame.bin)

## Texto vs. Binário — O Dump Direto da RAM

### 1. O que é um Arquivo Texto?

Em arquivos de texto (.txt), o compilador e as funções como fprintf convertem os dados em memória para caracteres ASCII/UTF-8.

- O número inteiro 12345678 ocupa 4 bytes no tipo int da RAM.
- Ao salvar em texto com fprintf(f, "%d", 12345678), o C converte o valor em 8 caracteres de texto ('1', '2', '3', ...), gastando 8 bytes no disco.

### 2. O que é um Arquivo Binário?

Um arquivo binário é uma cópia idêntica (bit a bit) do bloco de memória RAM diretamente para a mídia de armazenamento.

- O mesmo número 12345678 é salvo exatamente como os seus 4 bytes binários reais na RAM: 0x00 0xBC 0x61 0x4E.

| Critério                  | Arquivo Texto (.txt)                                   | Arquivo Binário (.bin)                       |
|---------------------------|--------------------------------------------------------|----------------------------------------------|
| Formato no Disco          | Caracteres legíveis por humanos                        | Representação nativa da memória RAM          |
| Desempenho de I/O         | Lento (exige conversão texto $\leftrightarrow$ número) | Ultrarrápido (cópia direta por DMA)          |
| Tamanho do Arquivo        | Variável e geralmente maior                            | Fixo, compacto e previsível                  |
| Segurança por Obscuridade | Editável no Bloco de Notas                             | Requer visualizador Hexadecimal (Hex Viewer) |

## As Funções de Bloco: fwrite() e fread()

Diferente de fprintf/fscanf, as funções binárias trabalham com blocos brutos de memória especificados pelo seu endereço de memória (void *), tamanho do elemento (size_t size) e quantidade (size_t count).

```c

size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
size_t fread(void *ptr, size_t size, size_t count, FILE *stream);

```

**Atenção:** Ambas as funções retornam a quantidade de elementos lidos/gravados com sucesso (deve ser igual a count), e NÃO o número de bytes retornado!

**Exemplo Básico:** Gravando e Lendo uma struct Completa

```c

typedef struct {
    int nivel;
    int pontos;
    float vida;
} EstadoJogo;

// 1. GRAVAÇÃO (Modo "wb" - Write Binary)
void salvar_exemplo(EstadoJogo *e) {
    FILE *f = fopen("save.bin", "wb");
    if (f != NULL) {
        // Grava 1 bloco com o tamanho exato da struct
        fwrite(e, sizeof(EstadoJogo), 1, f);
        fclose(f);
    }
}

// 2. LEITURA (Modo "rb" - Read Binary)
bool carregar_exemplo(EstadoJogo *e_out) {
    FILE *f = fopen("save.bin", "rb");
    if (f == NULL) return false;

    size_t lidos = fread(e_out, sizeof(EstadoJogo), 1, f);
    fclose(f);

    return (lidos == 1); // Retorna true se leu o bloco inteiro
}

```

Além de fprintf, fscanf, fwrite e fread, a biblioteca padrão do C (<stdio.h>) fornece um conjunto essencial de funções para navegação, manipulação de posição e checagem de estado em arquivos.

Abaixo está o detalhamento teórico dessas funções, divididas por categoria de uso.

### 1. Funções de Posicionamento e Navegação no Arquivo

Quando um arquivo é aberto, o Sistema Operacional mantém um indicador de posição interno (chamado de cursor do arquivo). Sempre que uma leitura ou escrita é feita, esse cursor avança automaticamente. As funções abaixo permitem consultar e mover esse cursor manualmente para qualquer ponto do arquivo.

```txt

                fseek(arq, 0, SEEK_SET)          fseek(arq, 0, SEEK_END)
                          │                                │
                          ▼                                ▼
       Início do Arquivo  [00][01][02][03]...[98][99]  Fim do Arquivo
                                      ▲
                                      │
                               ftell(arq) = Byte 3

```

A. fseek() — Deslocamento Manual do Cursor

Move o cursor de leitura/escrita para uma posição específica. Funciona tanto para arquivos de texto quanto para arquivos binários (onde é amplamente utilizada para acesso aleatório/direto).

```c

int fseek(FILE *stream, long offset, int origin);

```

- offset: Número de bytes a deslocar (pode ser positivo para avançar ou negativo para recuar).
- origin: Ponto de referência inicial para o deslocamento. Aceita uma das 3 constantes:
  - SEEK_SET: Início do arquivo (byte 0).
  - SEEK_CUR: Posição atual do cursor.
  - SEEK_END: Fim do arquivo (posição final).
- Retorno: Retorna 0 em caso de sucesso e um valor diferente de 0 se houver erro (ex: tentar recuar para antes do byte 0).

Exemplo Prático (Acesso Direto ao Registro 5 de um Arquivo Binário):

```c

// Move o cursor direto para o 5º elemento sem precisar ler os anteriores
fseek(arq, 4 * sizeof(DadosSave), SEEK_SET);
fread(&dados, sizeof(DadosSave), 1, arq);

```

B. ftell() — Consulta da Posição Atual

Retorna a posição atual do cursor em bytes a partir do início do arquivo.

```c

long ftell(FILE *stream);

```

Uso Clássico (Descobrir o Tamanho de um Arquivo Binário):

```c

fseek(arq, 0, SEEK_END);    // Move o cursor até o fim do arquivo
long tamanho = ftell(arq);  // Retorna a posição (que é o total de bytes!)
fseek(arq, 0, SEEK_SET);    // Retorna o cursor ao início para leitura

```

C. rewind() — Reinicialização do Cursor

Reseta o cursor de leitura/escrita de volta ao início do arquivo (byte 0) e limpa as flags de erro do arquivo.

```c

void rewind(FILE *stream);

```

> É um atalho equivalente a executar fseek(stream, 0, SEEK_SET); e limpar o estado de erro.

### 2. Funções Específicas para Leitura/Escrita em Arquivos Texto

Para manipulação de texto orientada a linhas ou caracteres individuais, a biblioteca padrão oferece funções mais leves e eficientes do que o fscanf/fprintf.

A. Leitura e Escrita Linha a Linha: fgets() e fputs()

- fgets(): Lê uma linha inteira de texto até encontrar uma quebra de linha (\n), o fim do arquivo (EOF) ou atingir o limite do buffer passado.

```c

char *fgets(char *str, int size, FILE *stream);

```

**Invariante de Segurança:** Diferente da antiga e perigosa gets(), o fgets() exige o parâmetro size para evitar estouro de buffer (buffer overflow).

- fputs(): Escreve uma string de texto no arquivo (sem adicionar \n automaticamente).

```c

int fputs(const char *str, FILE *stream);

```

B. Leitura e Escrita Caractere a Caractere: fgetc() e fputc()

- fgetc(): Lê um único caractere (1 byte) do arquivo e avança o cursor. Retorna o caractere como int para conseguir representar o valor de EOF (-1) em caso de fim de arquivo ou erro.

```c

int fgetc(FILE *stream);

```

- fputc(): Escreve um único caractere no arquivo.

```c

int fputc(int ch, FILE *stream);

```

### 3. Funções de Checagem de Estado e Erros

Ao operar com I/O de disco, erros de leitura/escrita ou término prematuro de dados podem acontecer. As funções abaixo inspecionam o estado da estrutura FILE*.

A. feof() — Teste de Fim de Arquivo (End Of File)

Testa se o indicador de fim de arquivo foi ativado na última operação de leitura.

```c

int feof(FILE *stream);

```

Atenção Crítica: A função feof() não adivinha se o próximo byte é o fim do arquivo. Ela só retorna verdadeiro (true) depois que uma tentativa de leitura tentou ler além do último byte do arquivo. Por isso, nunca use while (!feof(arq)) como condição principal de laço!

Forma Incorreta (Gera duplicação do último item):

```c

// ERRADO! O laço executa uma vez a mais no final
while (!feof(arq)) {
    fscanf(arq, "%d", &valor);
    printf("%d\n", valor);
}

```

Forma Correta (Checa o retorno do I/O):

```c

// CORRETO! O laço depende do sucesso real da função de leitura
while (fscanf(arq, "%d", &valor) == 1) {
    printf("%d\n", valor);
}

```

B. ferror() e clearerr() — Detecção e Limpeza de Erros

- ferror(): Verifica se ocorreu algum erro físico ou de permissão de I/O na última operação com o arquivo.

```c

int ferror(FILE *stream);

```

- clearerr(): Limpa os indicadores internos de erro e de fim de arquivo (EOF) da estrutura FILE*.

```c

void clearerr(FILE *stream);

```

C. fflush() — Forçamento de Descarregamento do Buffer

Força a gravação imediata de todos os dados pendentes no buffer da memória RAM para o disco físico/SSD sem precisar fechar o arquivo com fclose().

```c

int fflush(FILE *stream);

```

> É indispensável em sistemas de logs e salvamento automático (autosave) para garantir que os dados fiquem salvos em disco mesmo se o programa sofrer um encerramento inesperado logo em seguida.
