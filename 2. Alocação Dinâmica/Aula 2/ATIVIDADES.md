# Atividades

## Exercício 1: Vetor Dinâmico de Registros com Redimensionamento

A oficina da [atividade anterior](../Aula%201/ATIVIDADES.md) cresceu. Agora o usuário deve informar quantos veículos deseja cadastrar inicialmente.

1. Reaproveite a struct Veiculo da última aula.
2. Pergunte ao usuário quantos veículos ele deseja cadastrar (N).
3. Aloque dinamicamente no Heap um vetor para N veículos usando malloc ou calloc.
4. Faça a verificação de segurança contra NULL.
5. Preencha os dados dos N veículos via teclado usando sintaxe de vetor (v[i].placa, v[i].ano, etc.).
6. Pergunta bônus ao usuário: "Deseja cadastrar mais veículos? (1-Sim / 0-Não)". Se sim, peça a quantidade adicional e use realloc para expandir o vetor.
7. Exiba a lista completa e libere a memória com free(v).

## Exercício 2: Matriz Dinâmica (Notas da Turma)

Crie um sistema que armazene a matriz de notas de uma turma de programação.

1. Solicite ao usuário a quantidade de Alunos (L) e a quantidade de Avaliações (C).
2. Aloque dinamicamente uma matriz float **notas de dimensões L×C:
    - Primeiro aloque o vetor de ponteiros de linhas: malloc(L * sizeof(float *))
    - Em um laço for, aloque cada linha com as colunas: malloc(C * sizeof(float))
3. Verifique se as alocações foram bem-sucedidas.
4. Preencha as notas de cada aluno e exiba a média individual de cada um.
5. Desalocação: Faça o processo inverso do free (libere cada linha dentro de um laço for e, por fim, libere o ponteiro principal).

## Exercício 3: Inversão de Vetor com Alocação

Crie um programa que:

1. Peça ao usuário o tamanho N de um vetor de números inteiros.
2. Aloque o vetor dinamicamente no Heap e preencha-o com valores informados pelo usuário.
3. Crie uma função int* inverte_vetor(int *v, int n) que aloque um segundo vetor no Heap, copie os elementos do primeiro vetor em ordem inversa para este novo vetor e o retorne.
4. Na main, exiba o vetor invertido e certifique-se de liberar ambos os vetores alocados ao final.

## Exercício 4: Vetor Dinâmico "Sem Fim" (Leitura Até Digitar -1)

Escreva um programa em C que leia inteiros digitados pelo usuário até que ele digite o número -1 (que não deve ser armazenado).

1. O vetor deve começar com tamanho inicial 2 (malloc ou calloc).
2. À medida que o usuário for digitando e o vetor encher, use realloc para dobrar o tamanho do vetor dinamicamente.
3. Ao final da leitura, exiba:
    - Os elementos digitados;
    - O número de elementos armazenados;
    - O tamanho final do espaço alocado no Heap.
4. Libere a memória.

## Exercício 5: Matriz Esparsa ou Irregular (Vetor de Tamanhos Diferentes)

Na vida real, nem toda matriz é retangular! Crie um programa em C para armazenar as notas de N turmas.

1. Peça ao usuário quantas turmas existem.
2. Para cada turma i, peça a quantidade de alunos que aquela turma possui (Ki).
3. Aloque dinamicamente uma matriz irregular float **turmas onde cada linha representa uma turma e possui um tamanho próprio de colunas de acordo com a quantidade de alunos daquela turma específica.
4. Preencha as notas, exiba a média por turma e libere toda a memória corretamente.
