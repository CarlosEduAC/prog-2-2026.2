# Invariantes de Estado, Construtores e Gerenciamento de Erros em TADs

## Invariantes de Estado

Uma invariante é uma condição lógica que sempre deve ser verdadeira durante toda a vida útil de um Tipo Abstrato de Dados. Se a invariante for violada em qualquer momento, o TAD entra em um estado corrompido ou indefinido.

Exemplos no Projeto Space Defender:

- TAD Defensor: A integridade/vida do canhão nunca pode ser menor que 0 ou maior que 100.
- TAD FilaInimigos: O ponteiro inicio só pode ser NULL se o ponteiro fim também for NULL (fila vazia). A variável qtd deve ser rigorosamente igual ao número de nós alocados.
- TAD Tiro: A velocidade de um projétil do defensor não pode ser positiva (pois deve subir na tela, reduzindo $Y$).

Como Blindar Invariantes?

Em linguagens sem suporte nativo a contratos, blindamos invariantes através de validações internas dentro das funções do TAD (.c), impedindo que entradas inválidas alterem os campos da estrutura.

## Construtores e Destrutores Seguros

Em C, não existem as palavras-chave new ou delete. O construtor e o destrutor são funções convencionais do TAD responsáveis por alocar e desalocar memória no Heap.

Regras de Ouro de um Construtor Profissional:

1. Validação de Entrada: Verificar os parâmetros antes de alocar memória.

2. Checagem de Alocação: Testar obrigatoriamente se a chamada ao malloc/calloc retornou NULL.

3. Rollback em Falhas de Alocação Múltipla: Se o construtor aloca mais de um bloco (ex: a estrutura e um vetor interno), caso a segunda alocação falhe, a primeira deve ser liberada antes de retornar NULL.

### Exemplo de Construtor Seguro com Rollback

```c

TADComplexo* tad_complexo_criar(int capacidade_inicial) {
    if (capacidade_inicial <= 0) return NULL; // Validação de entrada

    TADComplexo *t = (TADComplexo *) malloc(sizeof(TADComplexo));
    if (t == NULL) return NULL; // Falha na alocação da struct principal

    t->dados = (int *) malloc(capacidade_inicial * sizeof(int));
    if (t->dados == NULL) {
        free(t); // ROLLBACK: Libera a struct principal se o vetor falhar!
        return NULL;
    }

    t->capacidade = capacidade_inicial;
    t->qtd = 0;
    return t;
}

```

## Estratégias de Gerenciamento de Erros em C

Como C não possui tratamento de exceções (try/catch), os TADs devem comunicar falhas ao cliente através de convenções claras no contrato (.h).

### 1. Retorno de Status (bool ou Códigos de Erro enum)

Usado em funções de modificação de estado (ex: enqueue, pop).

```c

typedef enum {
    TAD_OK = 0,
    TAD_ERRO_PONTEIRO_NULO,
    TAD_ERRO_MEMORIA_INSUFICIENTE,
    TAD_ERRO_LIMITE_EXCEDIDO
} StatusTAD;

StatusTAD defensor_recarregar_escudo(Defensor *d, int quantidade);

```

### 2. Ponteiro de Saída (Out Parameter)

A função retorna um bool indicando sucesso/falha e entrega o valor lido/processado por referência.

```c

// Exemplo clássico em Filas/Pilhas
bool fila_inimigos_dequeue(FilaInimigos *f, float *x_out, float *y_out);

```

## Prática Guiada no Laboratório

Desenvolva o TAD InventarioEspacial, aplicando validação de limites, invariantes e libertação completa de memória.

[main.c](main.c)

## Conexão com o Space Defender

O gerenciamento defensivo previne falhas graves no jogo:

- Invariante no TAD Defensor: Impede que a Reversão Temporal (Pilha Undo) tente restaurar posições negativas fora da janela da Raylib.

- Invariante no TAD FilaInimigos: Garante que o contador de inimigos restantes na HUD seja 100% fiel aos nós reais em memória, evitando que o jogo trave por tentar desenfileirar de uma fila vazia (underflow).
