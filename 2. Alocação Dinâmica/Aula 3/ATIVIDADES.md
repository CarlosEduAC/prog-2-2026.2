# Atividades

## Exercício 1: Calculadora com Ponteiros no Heap

Escreva um programa que aloque dinamicamente no Heap espaço para três números reais (float): num1, num2 e resultado.

1. Leia os valores de num1 e num2 do usuário.
2. Crie funções simples para as 4 operações básicas (soma, subtração, multiplicação e divisão) que recebam esses ponteiros e gravem o retorno no ponteiro resultado.
3. Garanta que a divisão por zero seja tratada (retornando false ou exibindo um alerta).
4. Libere os três ponteiros ao final.

## Exercício 2: Cadastro de Livro

Defina a estrutura Livro:

```c

typedef struct {
    char titulo[50];
    char autor[40];
    int paginas;
    float preco;
} Livro;

```

1. Na main(), declare um ponteiro Livro *l = NULL;.
2. Aloque espaço dinamicamente para 1 Livro no Heap.
3. Crie a função void preencher_livro(Livro *l) que leia os dados do teclado e preencha os campos usando o operador seta (->).
4. Crie a função void exibir_livro(const Livro *l) para imprimir a ficha formatada.
5. Verifique os retornos de NULL e libere a memória no final.

## Exercício 3: Conta Bancária com Transferência

Defina a estrutura ContaBancaria:

```c

typedef struct {
    int numero_conta;
    char titular[40];
    float saldo;
} ContaBancaria;

```

1. Aloque dinamicamente no Heap duas contas: c1 e c2.
2. Preencha os dados das duas contas (ex: Conta 101 com R$ 1000.00 e Conta 202 com R$ 200.00).
3. Crie a função bool transferir(ContaBancaria *origem, ContaBancaria* destino, float valor) que:
    - Verifique se a conta de origem tem saldo suficiente.
    - Debite da conta de origem e credite na de destino usando ->.
    - Retorne true se a operação for bem-sucedida ou false caso contrário.

4. Teste a transferência na main(), exiba os saldos atualizados e desaloque ambas as contas.
