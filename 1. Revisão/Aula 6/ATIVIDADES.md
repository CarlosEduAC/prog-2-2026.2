# Atividades da Aula 6

## Exercício 1: Vetores (1D) — Sensor de Temperatura Industrial

Contexto: Um sensor lê a temperatura de uma máquina a cada hora durante um turno de 8 horas e armazena os valores em um vetor. Você deve criar um módulo em C que analise esses dados.

Requisitos:

1. Declare um vetor de float com 8 posições no main().
2. Crie uma função void analisar_temperaturas(const float *leituras, int tam, float* media, int *acima_limite) que:
    - Calcule a temperatura média do turno.
    - Conte quantas leituras ficaram acima de 37.5 ºC (alerta de superaquecimento).
    - Retorne esses dois valores para a main() usando ponteiros (passagem por referência).
3. Na main(), exiba a média e a quantidade de alertas detectados.

## Exercício 2: Matrizes (2D) — Sistema de Assentos do Cinema

Contexto: Um cinema possui uma sala pequena com 4 fileiras e 5 poltronas por fileira. A matriz guarda 0 para assento livre e 1 para assento ocupado.

Requisitos:

1. Declare e inicialize a matriz int sala[4][5] na main().
2. Crie a função void exibir_sala(int sala[][5], int fileiras) para imprimir o mapa do cinema na tela (usando [0] para livre e [X] para ocupado).
3. rie a função bool reservar_assento(int sala[][5], int f, int p) que:
    - Tente reservar a poltrona na fileira f e posição p.
    - Se estiver livre (0), altera para 1 e retorna true.
    - Se já estiver ocupada (1) ou o assento for inválido, retorna false.

## Exercício 3: Vetores (1D) — Filtro de Ruído em Sinal Digital

Contexto: Um dispositivo IoT capta dados de telemetria de um motor e armazena em um vetor. Leituras zeradas ou negativas são consideradas "ruídos de leitura" e devem ser descartadas, substituindo-as pela média dos valores válidos.

Requisitos:

1. Declare um vetor de float com 6 posições no main().
2. Crie a função int tratar_ruidos(float *sinal, int tam) que:
   - Calcule a média apenas dos valores estritamente positivos ($> 0$).
   - Substitua todos os valores inválidos ($\le 0$) do vetor por essa média calculada.
   - Retorne a quantidade de ruídos que foram corrigidos no vetor.
3. Na main(), exiba o vetor corrigido e quantos ruídos foram filtrados.

## Exercício 4: Matrizes (2D) — Processamento de Imagem Grayscale (Filtro Binarizador)

Contexto: Uma imagem em escala de cinza de $3 \times 4$ pixels é representada por uma matriz de inteiros com valores de 0 (preto absoluto) a 255 (branco absoluto). Um algoritmo de visão computacional precisa binarizar a imagem (transformá-la em apenas preto e branco puro) com base em um valor de limiar (threshold).

Requisitos:

1. Declare e inicialize a matriz int imagem[3][4] com valores entre 0 e 255.
2. Crie a função void aplicar_limiar(int img[][4], int linhas, int limiar) que:
   - Percorra toda a matriz.
   - Se o pixel for menor que o limiar, altera seu valor para 0 (Preto).
   - Se o pixel for maior ou igual ao limiar, altera seu valor para 255 (Branco).
3. Na main(), exiba a matriz antes e depois da aplicação do filtro.
