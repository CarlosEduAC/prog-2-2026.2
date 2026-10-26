# Atividades

## Exercício 1: Diagnóstico e Resolução de Colisão de Símbolos (Multiple Definition)

Um estudante criou dois módulos para o Space Defender: src/defensor.c e src/inimigo.c. Ambos os arquivos possuem uma função auxiliar chamada validar_posicao() para checar se uma entidade está dentro das bordas da janela.

Em src/defensor.c:

```c

#include "defensor.h"

bool validar_posicao(float x, float y) {
    return (x >= 0 && x <= 800 && y >= 0 && y <= 600);
}

```

Em src/inimigo.c:

```c

#include "inimigo.h"

bool validar_posicao(float x, float y) {
    return (x >= -50 && x <= 850 && y >= -50 && y <= 650);
}

```

Ao compilar com gcc main.c src/defensor.c src/inimigo.c -o jogo, o terminal exibe o seguinte erro:

```txt

duplicate symbol '_validar_posicao' in:
    defensor.o
    inimigo.o
ld: 1 duplicate symbol for architecture arm64

```

Sua Tarefa:

1. Explique por que o compilador permitiu que ambos os arquivos gerassem seus objetos (.o), mas a execução falhou na etapa do Linker (ld).

2. Altere o código de ambos os arquivos para resolver o erro sem precisar mudar o nome de nenhuma das duas funções.

## Exercício 2: Encapsulamento de Algoritmos Internos no TAD

Considere o módulo de gerenciamento de tiros (src/tiro.c). Ele utiliza uma Lista Duplamente Encadeada e precisa de duas funções utilitárias:

1. alocar_no_tiro(float x, float y, float vel_y): aloca um nó individual de disparo no Heap.
2. remover_no_tiro(GerenciadorTiros *gt, NoTiro *no): desconecta e libera a memória de um nó em $O(1)$.

Nenhuma dessas duas funções deve ser exposta no cabeçalho include/tiro.h, pois o código cliente (main.c) não deve manipular nós diretamente.

Sua Tarefa:

1. Escreva o protótipo e a implementação dessas duas funções auxiliares dentro do src/tiro.c, aplicando as boas práticas de encapsulamento no nível de arquivo (internal linkage).

2. Escreva a função pública void tiros_adicionar(GerenciadorTiros *gt, float x, float y, float vel_y) que faz uso seguro dessas auxiliares estáticas.

## Exercício 3: Ocultação de Variáveis Globais de Módulo

Em um sistema de registro de áudio e logs do jogo (src/logger.c), é necessária uma variável global que conte quantas mensagens de log já foram gravadas no disco durante a execução.

Se declarada sem o modificador static, qualquer outro arquivo do projeto poderia ler ou alterar o contador diretamente via extern int contador_logs;.

Sua Tarefa:

1. Implemente o arquivo src/logger.c contendo uma variável contador_logs que seja estritamente privada a este arquivo.

2. Crie as funções públicas void logger_registrar(const char *mensagem) (que incrementa o contador) e int logger_get_total(void) (que permite apenas a leitura controlada do total).