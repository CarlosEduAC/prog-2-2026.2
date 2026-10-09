# Atividades

## Exercício 1: Encapsulamento de Placar de Jogador (Placar)

A biblioteca abaixo expõe os dados do jogador diretamente no arquivo .h, permitindo que o código cliente altere pontos e vidas de forma inválida (ex: pontuação negativa).

Código Original (placar_antigo.h):

```c

typedef struct {
    char nome[30];
    int pontos;
    int vidas;
} Placar;

```

**Sua Tarefa:**

Refatore o código dividindo-o em placar.h e placar.c:

1. Torne o typedef struct Placar Placar; um ponteiro opaco no .h.
2. Defina a struct Placar concretamente apenas dentro de placar.c.
3. Crie a função construtora Placar* placar_criar(const char *nome) que inicializa o jogador com 0 pontos e 3 vidas.
4. Crie funções de interface: void placar_adicionar_pontos(Placar *p, int qtd), void placar_remover_vida(Placar *p) e getters de leitura. Garantia de invariante: a pontuação e as vidas nunca podem ficar negativas.

## Exercício 2: Encapsulamento de Vetor Dinâmico (VetorDinamico)

Abaixo está um vetor dinâmico exposto. Como a estrutura é pública, o código cliente pode alterar o ponteiro interno dados ou os inteiros tamanho e capacidade, gerando dangling pointers e corrupção de memória.

Código Original (vetor_antigo.h):

```c

typedef struct {
    int *dados;
    int tamanho;
    int capacidade;
} VetorDinamico;

```

**Sua Tarefa:**

1. Encapsule a struct VetorDinamico utilizando ponteiro opaco no arquivo vetor.h.
2. Crie VetorDinamico* vetor_criar(int capacidade_inicial).
3. Implemente a inserção bool vetor_inserir(VetorDinamico *v, int elemento) que realiza o realocamento automático com realloc dentro de vetor.c quando o vetor estiver cheio, ocultando completamente a lógica de expansão do cliente.
4. Crie a função de destruição void vetor_destruir(VetorDinamico *v) que libera a memória do array e da estrutura.

## Exercício 3: Refatoração de Lista Simplesmente Encadeada Privada (ListaAlunos)

Um sistema escolar utiliza uma lista encadeada, mas expõe os nós (No) e a cabeça da lista no .h. O cliente consegue manipular ponteiros de próximo (->proximo) manualmente, quebrando o encadeamento.

Código Original (lista_antiga.h):

```c

typedef struct No {
    int matricula;
    float nota;
    struct No *proximo;
} No;

typedef struct {
    No *cabeca;
    int quantidade;
} ListaAlunos;

```

**Sua Tarefa:**

1. Esconda totalmente a struct No e a struct ListaAlunos dentro do arquivo de implementação lista_alunos.c. O arquivo lista_alunos.h deve conter apenas a declaração do ponteiro opaco typedef struct ListaAlunos ListaAlunos;.
2. O cliente não deve ter acesso nem saber que existem nós encadeados (No).
3. Implemente as funções:

- ListaAlunos* lista_criar(void);

- bool lista_inserir(ListaAlunos *l, int matricula, float nota);

- float lista_buscar_nota(const ListaAlunos *l, int matricula);

- void lista_destruir(ListaAlunos *l);
