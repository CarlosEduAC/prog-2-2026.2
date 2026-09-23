# Minissistema de Estoque

## Visão Geral e Objetivos de Aprendizagem

Neste laboratório guiado, você construirá um Minissistema de Gestão de Estoque em Terminal. O objetivo principal é consolidar, em uma única aplicação modularizada, os conceitos fundamentais de Programação de Computadores II:

- Registros (struct e typedef): Abstração de entidades do mundo real em blocos heterogêneos de dados.
- Ponteiros e Operador Seta (->): Passagem de parâmetros por referência para leitura e escrita eficiente de dados na memória.
- Aritmética e Acesso a Vetores: Manipulação segura de coleções de dados na memória RAM (Stack).
- Modularização: Organização de código através do uso de escopo local, funções puras e separação de responsabilidades.

## Arquitetura do Minissistema de Estoque

  ┌─────────────────────────────────────────────────────────────────┐
  │                    struct Produto (Registro)                    │
  │   • codigo (int)                                                │
  │   • nome (char[40])                                             │
  │   • quantidade (int)                                            │
  │   • preco (float)                                               │
  └─────────────────────────────────────────────────────────────────┘
                                   │
                                   ▼
  ┌─────────────────────────────────────────────────────────────────┐
  │                    Vetor de Structs na Stack                    │
  │   Produto estoque[MAX_PRODUTOS];                                │
  └─────────────────────────────────────────────────────────────────┘
                                   │
                                   ▼
  ┌─────────────────────────────────────────────────────────────────┐
  │                  Funções Modulares (Ponteiros)                  │
  │   • cadastrar_produto(Produto *p, ...)   <-- Passagem via '->'  │
  │   • buscar_produto(const Produto* e, ..) <-- Busca Linear       │
  │   • atualizar_estoque(Produto *p, ...)   <-- Alteração por Ref  │
  └─────────────────────────────────────────────────────────────────┘

### O Modelo de Dados (Produto)

```c
typedef struct {
    int codigo;         // Identificador único do produto
    char nome[40];      // Descrição/Nome comercial
    int quantidade;     // Unidades disponíveis em estoque
    float preco;        // Valor unitário em Reais
} Produto;
```

### O Estado do Sistema na Memória RAM

A aplicação manterá o controle de estado no início da função main():

1. Produto estoque[MAX_ESTOQUE];: Um vetor estático reservando espaço para os produtos na Stack.

2. int total_cadastrados = 0;: Uma variável inteira indicando a quantidade atual de itens armazenados no vetor.

## Módulos e Funções a Serem Implementados

Sua missão durante o laboratório é construir e integrar as seguintes funções:

1. cadastrar_produto(Produto *p, ...)

- Objetivo: Preencher os membros de uma estrutura Produto vazia.
- Mecanismo: Recebe o endereço de memória de uma posição do vetor e utiliza o operador seta (->) para escrever os dados diretamente na memória original.

2. listar_estoque(const Produto *estoque, int total)

- Objetivo: Percorrer o vetor e exibir uma tabela formatada no terminal com todos os itens cadastrados.
- Mecanismo: Usa a palavra-chave const para garantir que a listagem seja somente leitura, protegendo os dados contra alterações acidentais.

3. buscar_por_codigo(const Produto *estoque, int total, int cod)

- Objetivo: Realizar uma busca linear no vetor procurando por um produto com o código informado.
- Retorno: Retorna o índice (0 a total - 1) onde o produto se encontra no vetor, ou -1 caso o código não seja encontrado.

4. realizar_venda(Produto *p, int qtd_venda)

- Objetivo: Dar baixa no estoque de um produto existente.
- Mecanismo: Localiza o produto via ponteiro, valida se a quantidade a vender é menor ou igual ao estoque disponível e aplica a subtração diretamente na memória.

## Estrutura do Fluxo de Execução

O sistema funcionará através de um laço de repetição do-while controlado por um menu interativo switch-case:

```txt
=========================================
        MINISSISTEMA DE ESTOQUE
=========================================
1. Cadastrar Produto
2. Listar Estoque Completo
3. Realizar Venda (Dar Baixa)
0. Sair
-----------------------------------------
```

## Regras de Negócio e Validações Obrigatórias

Durante a codificação, seu programa deve obrigatoriamente tratar os seguintes cenários de borda:

1. Validação de Entrada: Códigos devem ser estritamente positivos (> 0), e preços/quantidades não podem ser negativos.
2. Impedimento de Códigos Duplicados: Antes de cadastrar um novo item, o sistema deve consultar a função buscar_por_codigo() para garantir que o código informado já não pertença a outro produto.
3. Controle de Limites do Vetor: O programa deve impedir o cadastro de novos produtos caso total_cadastrados atinja o limite MAX_ESTOQUE.
4. Proteção Contra Saldo Negativo: Nenhuma venda pode ser efetuada se a quantidade solicitada for maior do que o estoque atual disponível para aquele item.

## O Desafio Final de Reflexão

Ao concluir a implementação e validar o roteiro de testes, observe a limitação do sistema:

O que acontece se a empresa precisar cadastrar 100 produtos, mas compilamos o programa com #define MAX_ESTOQUE 5?

Como podemos transformar esse vetor de tamanho fixo em uma estrutura que cresce dinamicamente na memória conforme a necessidade do usuário?
