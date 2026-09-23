# Listas Encadeadas em C

As listas encadeadas são estruturas de dados lineares onde cada elemento (nó) contém um valor e um ponteiro para o próximo nó na sequência. Diferente dos arrays, as listas encadeadas não possuem tamanho fixo e permitem inserções e remoções dinâmicas de elementos.

## Vetores Dinâmicos vs. Listas Encadeadas

Características físicas na memória RAM entre um vetor dinâmico e uma lista encadeada:

```txt

1. VETOR DINÂMICO (Memória Contígua)
     ┌───────────┬───────────┬───────────┐
     │ Dado [0]  │ Dado [1]  │ Dado [2]  │  <-- Exige bloco único e contíguo na RAM
     └───────────┴───────────┴───────────┘      realloc() exige copiar tudo se a vizinhança encher.

  2. LISTA ENCADEADA (Memória Dispersa/Encadeada)
     ┌───────────┐      ┌───────────┐      ┌───────────┐
     │ Dado: 10  │      │ Dado: 20  │      │ Dado: 30  │
     │ prox ─────┼────> │ prox ─────┼────> │ prox: NULL│  <-- Cada nó mora em um endereço livre
     └───────────┘      └───────────┘      └───────────┘      qualquer do Heap!

```

Tabela Comparativa

| Operação / Característica | Vetor Dinâmico (realloc)         | Lista Simplesmente Encadeada           |
|---------------------------|----------------------------------|----------------------------------------|
| Alocação na RAM           | Bloco único e contíguo           | Blocos isolados espalhados no Heap     |
| Acesso por Índice         | $O(1)$ — Direto (v[i])           | $O(n)$ — Precisa percorrer elo por elo |
| Inserção no Início        | $O(n)$ — Move todos os elementos | $O(1)$ — Ajusta apenas 2 ponteiros     |
| Crescimento de Memória    | Redimensionamento custoso        | Cresce/encolhe nó por nó sem cópias    |

## Anatomia do Nó e o Ponteiro de Cabeça (Head)

Os dois elementos centrais de uma Lista Encadeada em C:

1. O Nó (struct No)

A célula básica que armazena a informação (dado) e o elo para o próximo elemento.

```c

typedef struct No {
    int dado;           // Carga útil do nó
    struct No *proximo; // Ponteiro para o próximo nó (Estrutura Auto-Referenciada)
} No;

```

2. O Ponteiro de Cabeça (Head)

Uma variável na main() que guarda apenas o endereço do primeiro nó da lista. Se a lista estiver vazia, head == NULL.

```txt

head ────> [ Dado: 10 | prox ] ────> [ Dado: 20 | prox ] ────> NULL

```

## Construindo a Lista Passo a Passo

As funções fundamentais.

1. Criar um novo nó
2. Inserir no início
3. Inserir no fim
4. Imprimir a lista
5. Buscar um elemento
6. Remover um elemento
7. Liberar a lista

[Implementação das funções](main.c)

## Ponteiro duplamente indireto (No **head)

### 1. Por que precisamos do Ponteiro de Ponteiro (No **head)?

Em C, todas as variáveis são passadas por valor (por cópia) para dentro de uma função.

Se a sua função na main() tem uma variável que guarda a cabeça da lista:

```c

No *head = NULL; // 'head' é um ponteiro que guarda o endereço do Nó 1

```

Se você passar apenas No *head para uma função de remoção:

```c

// ERRADO: Passagem por cópia!
void remover_primeiro(No *head) {
    if (head != NULL) {
        No *temp = head;
        head = head->proximo; //  Altera APENAS a cópia local do ponteiro!
        free(temp);
    }
}

```

O que acontece? A função altera a variável local head dentro do escopo dela, mas o ponteiro head original que está lá na main() continua apontando para o nó antigo que acabou de ser liberado com free(), gerando um ponteiro pendente (dangling pointer) e corrompendo a memória!

Para que uma função consiga alterar o valor que uma variável ponteiro guarda lá na main(), precisamos passar o endereço da variável ponteiro. O endereço de um No* é um No** (ponteiro para ponteiro).

### 2. Passo a Passo Visual da Remoção com No **head

Considere uma lista com 2 nós alocados no Heap:

```txt

Endereço de RAM na main():  0x1000
Conteúdo de 'head':        0x5000 (Endereço do Nó 1)

 [Stack da main]                    [Heap]
┌──────────────┐             ┌──────────────────┐      ┌──────────────────┐
│ head: 0x5000 ├───────────> │ Nó 1 (0x5000)    │      │ Nó 2 (0x7000)    │
└──────────────┘             │ dado: 10         │      │ dado: 20         │
                             │ proximo: 0x7000 ├────> │ proximo: NULL    │
                             └──────────────────┘      └──────────────────┘

```

Queremos remover o Nó 1 e fazer a variável head da main() guardar 0x7000 (endereço do Nó 2).

#### A Chamada da Função

Na main(), passamos o endereço de head usando o operador &:

```c

remover_primeiro(&head); // Passamos 0x1000

```

#### A Função de Remoção Passo a Passo

```c

void remover_primeiro(No **head) {
    // 1. Validação: A lista está vazia?
    // '*head' acessa o valor guardado na main (0x5000).
    if (*head == NULL) return;

    // 2. Salva o nó que será liberado em um ponteiro temporário
    No *temp = *head; // temp guarda 0x5000

    // 3. A MAGIA ACONTECE AQUI:
    // Atualiza a variável 'head' lá da main() para apontar para o SEGUNDO nó (0x7000)
    *head = (*head)->proximo;

    // 4. Libera a memória do nó antigo no Heap
    free(temp);
}

```

O Estado da Memória Após cada Linha:

1. No *temp =* head;
 temp aponta para 0x5000 (Nó 1).

2. *head = (*head)->proximo;
 Acessamos a variável head lá na main() e gravamos nela o valor de (*head)->proximo (que é 0x7000).
 Agora a main() já sabe que o primeiro nó é o Nó 2!

3. free(temp);
 O bloco no endereço 0x5000 é devolvido ao Sistema Operacional com segurança.

### 3. Comparativo da Sintaxe na Prática

| Operação         | O que significa na prática?                                                            |
|------------------|----------------------------------------------------------------------------------------|
| head             | O ponteiro de ponteiro (o endereço da variável da main()). Ex: 0x1000.                 |
| *head            | O ponteiro simples (o endereço do nó no Heap que a main() está apontando). Ex: 0x5000. |
| **head           | O valor armazenado dentro do struct do Nó (o dado inteiro do nó). Ex: 10.              |
| (*head)->proximo | O ponteiro para o próximo nó a partir da cabeça atual. Ex: 0x7000.                     |

### 4. Alternativa ao Uso de No **head

Retornar o novo ponteiro de cabeça:

```c

No* remover_primeiro(No *head) {
    if (head == NULL) return NULL;
    No *temp = head->proximo;
    free(head);
    return temp; // Retorna o novo head
}

// Na main(), você é OBRIGADO a reatribuir:
head = remover_primeiro(head);

```

## Prática Guiada

Crie uma função int contar_nos(const No *head) que retorne o tamanho atual da lista encadeada (quantidade total de nós alocados).

Dica: Percorra a lista com um ponteiro auxiliar e um contador inteiro até encontrar NULL.

## Conclusão

- Vantagem: A Lista Encadeada cresce e encolhe na memória Heap elemento por elemento, sem desperdício e sem realocações gigantescas de memória contígua.
- Ponteiro duplamente indireto (No **head): Usado quando a função precisa alterar o valor de head na main() (como na inserção no início ou na remoção do primeiro nó).
- Cuidado no free(): Nunca libere um nó sem antes salvar o ponteiro para o nó seguinte (proximo_no = atual->proximo), caso contrário você perde o restante da lista.
