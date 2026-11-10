# Atividades

## Exercício 1 (Arquivos Texto): Leitura Defensiva com Fallback e Log de Transações

Um sistema de caixa eletrônico precisa carregar o saldo atual a partir do arquivo de texto saldo.txt no formato:

```txt

SALDO=1500.50

```

Escreva a função float carregar_saldo(const char *caminho_saldo, float saldo_padrao) que:

1. Tente abrir o arquivo em modo de leitura ("r").

2. Se o arquivo não existir ou se o fscanf falhar em ler o valor SALDO=%f (retorno diferente de 1), crie o arquivo em modo de escrita ("w"), grave o valor de saldo_padrao e retorne esse valor padrão.

3. Se o arquivo for lido com sucesso, retorne o saldo lido.

4. Garanta o fechamento do arquivo com fclose em qualquer cenário de saída.

## Exercício 2 (Arquivos Binários): Leitura e Escrita de Estruturas com fwrite e fread

Em um sistema de inventário de loja, cada produto é representado por:

```c

typedef struct {
    int id;
    char nome[30];
    float preco;
    int quantidade;
} Produto;

```

Sua Tarefa:

1. Escreva a função bool salvar_produto_binario(const char *caminho, const Produto*p) que abra o arquivo em modo de anexo binário ("ab") e grave a struct de produto inteira no fim do arquivo usando fwrite.
2. Escreva a função int contar_produtos_cadastrados(const char *caminho) que abra o arquivo em modo de leitura binária ("rb") e determine quantos produtos estão gravados no arquivo utilizando as funções fseek e ftell (sem usar laços de repetição while).

## Exercício 3 (Binário): Validação de Cabeçalho (Magic Number) e Edição Direta com fseek

Para evitar abrir arquivos corrompidos ou inválidos, um banco de dados binário de usuários (usuarios.bin) grava no início do arquivo um cabeçalho de 8 bytes:

- magic_number: 0x44425359 (Equivalente à sigla "DBSY" em hexadecimal) — 4 bytes
- versao: 1 — 4 bytes

Seguido pelo payload de usuários:

```c

typedef struct {
    uint32_t magic_number;
    uint32_t versao;
} HeaderBanco;

typedef struct {
    int id_usuario;
    float saldo_pontos;
} Usuario;

```

Escreva a função bool creditar_pontos_usuario(const char *caminho, int indice_usuario, float pontos_extra) que:

1. Abra o arquivo em modo de leitura e escrita binária ("rb+").
2. Leia o HeaderBanco e valide se o magic_number == 0x44425359 e versao == 1. Se for inválido, feche o arquivo e retorne false.
3. Use fseek para mover o cursor de leitura/escrita diretamente para a posição do registro indicado por indice_usuario (lembre-se de pular o tamanho do cabeçalho!).
4. Leia o registro do usuário com fread, adicione pontos_extra ao campo saldo_pontos.
5. Recue o cursor do arquivo com fseek (posição atual - sizeof(Usuario)) e sobrescreva o registro atualizado no disco usando fwrite.
6. Feche o arquivo e retorne true.
