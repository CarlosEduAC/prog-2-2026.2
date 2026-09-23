# Backtracking Básico e Estruturas Auto-Referenciadas

## Do Processamento Direto à Tomada de Decisões

Nas aulas anteriores, a recursão seguia um caminho linear ou de divisão direta (como somar um vetor ou fazer busca binária).

"E quando o algoritmo precisa testar uma decisão e, se der errado, voltar atrás e tentar outra opção?"

### A Analogia do Labirinto

Imagine caminhar por um labirinto:

1. Você chega a um cruzamento e escolhe ir para a Esquerda.
2. Continua andando até bater em um Muro sem saída.
3. Você desfaz o último passo (volta até o cruzamento) e tenta a Direita.
4. Esse processo de "avançar, testar, recuar em caso de falha e tentar o próximo caminho" é o Backtracking.

## A Mecânica do Backtracking

O Backtracking é um refinamento da busca por força bruta. Ele utiliza a própria Stack de chamadas do C para lembrar de onde viemos e para onde devemos voltar.

```txt

                      MECÂNICA DO BACKTRACKING

                         [ ESTADO INICIAL ]
                                │
                 ┌──────────────┴──────────────┐
                 ▼                             ▼
           [ Opção 1 ]                    [ Opção 2 ]
                 │                             │
          ┌──────┴──────┐                ┌─────┴─────┐
          ▼             ▼                ▼           ▼
      [ SUCESSO ]    [ FALHA ]       [ SUCESSO ]  [ FALHA ]
                        │
                  (VOLTA ATRÁS)
                  Desfaz estado

```

### O Modelo Mental de Código

Toda função com Backtracking segue um padrão claro de 4 etapas:

1. Validação: O estado atual é uma solução válida? (Caso Base de Sucesso) ou um caminho inválido? (Caso Base de Falha).
2. Escolha: Marcar o estado atual como visitado ou alterar uma variável de controle.
3. Exploração: Fazer a chamada recursiva para os próximos passos possíveis.
4. Desfazimento (Unmake Choice): Se a chamada recursiva retornar false (caminho sem saída), desfazer a alteração do estado atual para que outros caminhos possam tentar usá-lo.

## Resolvendo um Labirinto Matriz

Como encontrar um caminho em uma matriz 3 X 3 saindo de [0] [0] até [2] [2].

[Código do Labirinto](main.c)

## Estruturas Auto-Referenciadas

### O que é uma Estrutura Auto-Referenciada?

É uma struct que contém em seus campos um ponteiro apontando para o mesmo tipo da própria estrutura.

```c

// Definição do Nó (Node) de uma Estrutura Auto-Referenciada
typedef struct No {
    int dado;               // O valor armazenado (carga útil)
    struct No *proximo;     // PONTEIRO PARA O PRÓXIMO NÓ DO MESMO TIPO!
} No;

```

### O Elo entre Recursão, Heap e o struct No *

Transição mental do vetor contíguo para o encadeamento dinâmico:

```txt

1. VETOR DINÂMICO (Memória Contígua no Heap):
   [ Dado 0 ][ Dado 1 ][ Dado 2 ]  <-- Espaço precisa ser vizinho na RAM

2. LISTA ENCADEADA (Estrutura Auto-Referenciada no Heap):
   ┌─────────┐      ┌─────────┐      ┌──────────┐
   │ Dado: 10│      │ Dado: 20│      │ Dado: 30 │
   │ prox: ──┼────> │ prox: ──┼────> │ prox:NULL│
   └─────────┘      └─────────┘      └──────────┘

```

Percorrer uma lista ligada nada mais é do que aplicar uma função recursiva:

```c

void imprimir_lista_recursiva(const No *no_atual) {
    if (no_atual == NULL) return; // Caso Base: Fim da Lista

    printf("%d -> ", no_atual->dado);
    imprimir_lista_recursiva(no_atual->proximo); // Passo Recursivo!
}

```
