# Pilhas (LIFO) e Filas (FIFO) Dinâmicas em C

Nas listas, podíamos inserir e remover em qualquer posição. Agora, imporemos regras estritas de onde a entrada e a saída de dados podem acontecer.

```txt

                PILHA (LIFO)                                       FILA (FIFO)
   Last-In, First-Out (Último a entrar,              First-In, First-Out (Primeiro a entrar,
            primeiro a sair)                                 primeiro a sair)

          │  [Dado C]  │  ▲ Topo (Pop)            Entrada (Enqueue)             Saída (Dequeue)
          ├────────────┤  │                           (Fim/Tail)                 (Início/Head)
          │  [Dado B]  │  │                               │                            ▲
          ├────────────┤  │                               ▼                            │
          │  [Dado A]  │  │                       ┌──────────────┬──────────────┬──────────────┐
          └────────────┘  ┴ Push                  │   Dado C     │   Dado B     │   Dado A     │
            (Fundo)                               └──────────────┴──────────────┴──────────────┘

```

Analogias do Mundo Real

- Pilha (LIFO): Uma pilha de pratos ou o histórico do navegador ("Botão Voltar").
- Fila (FIFO): Uma fila de banco ou a fila de processamento de tarefas do sistema operacional.

## Definição

### Pilha

É uma estrutura do tipo FILO (First In Last Out), ou seja, o primeiro elemento inserido será o último a ser removido. Cada elemento da estrutura, pode armazenar um ou vários dados e um ponteiro para o próximo elemento, o que permite o encadeamento e mantêm uma estrutura linear.

Qualquer estrutura do tipo possui um ponteiro denominado TOPO, onde todas operações de inserção e remoção acontecem.

Serão abordadas as seguintes operações:

• Inserir na pilha (Push);
• Consultar toda pilha (Peek);
• Remover elemento da pilha (Pop);
• Esvaziar pilha (Clear).

Uma Pilha Dinâmica nada mais é do que uma Lista Simplesmente Encadeada onde todas as inserções e remoções acontecem exclusivamente na cabeça (topo).

[Código da Pilha Dinâmica](pilha.c)

### Fila

É uma estrutura do tipo FIFO (First In First Out), ou seja, o primeiro elemento inserido será o primeiro a ser removido. Cada elemento da estrutura pode armazenar um ou vários dados e um ponteiro para o próximo elemento, o que permite o encadeamento e mantêm uma estrutura linear.

A estrutura do tipo fila possui um ponteiro denominado INICIO, onde todas operações de remoção acontecem e outro denominado FIM, onde acontecem as inserções.

Serão abordadas as seguintes operações:

• Inserir na fila;
• Consultar toda fila;
• Remover elemento;
• Esvaziar fila.

Para manter a remoção no início e a inserção no fim ambas em O(1), a Fila Dinâmica exige dois ponteiros: inicio (Head) e fim (Tail).

[Código da Fila Dinâmica](fila.c)

## Prática Guiada no Laboratório

Desafio no Laboratório: Crie uma função `bool verificar_parenteses(const char *expressao)` que use uma Pilha de char para verificar se os parênteses () de uma expressão matemática estão corretamente balanceados.

Exemplo válido: ((2 + 3) * 5) -> true
Exemplo inválido: )(2 + 3)( -> false ou ((2 + 3) -> false

## Comparativo

| TAD   | Operação de Entrada | Operação de Saída   | Complexidade    |
|-------|---------------------|---------------------|-----------------|
| Pilha | push (no topo)      | pop (do topo)       | O(1) para ambos |
| Fila  | enqueue (no fim)    | dequeue (do início) | O(1) para ambos |
