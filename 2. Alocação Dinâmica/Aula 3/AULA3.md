# Refatoração do Minissistema de Estoque com Alocação Dinâmica

## O Diagnóstico do Sistema Antigo vs. O Novo Projeto

```txt

ABORDAGEM ANTIGA (STACK)                 NOVA ABORDAGEM (HEAP DINÂMICO)
┌──────────────────────────────┐          ┌──────────────────────────────┐
│ Produto estoque[MAX_ESTOQUE];│          │ Produto *estoque = NULL;     │
│ • Tamanho fixo (ex: 5)       │  ────>   │ • Capacidade inicial = 2     │
│ • Compilação engessada       │          │ • Expansão automática com    │
│ • Risco de desperdício       │          │   realloc() sob demanda      │
└──────────────────────────────┘          └──────────────────────────────┘

```

## A Nova Estrutura de Dados e o Conceito de Capacidade

Para gerenciar um vetor dinâmico no Heap precisamos controlar duas variáveis inteiras na main():

```txt

Visualização da RAM:

                estoque (Ponteiro no Heap)
 ┌─────────────┬─────────────┬─────────────┬─────────────┐
 │ Produto [0] │ Produto [1] │  LIVRE [2]  │  LIVRE [3]  │
 └─────────────┴─────────────┴─────────────┴─────────────┘
 ▲                           ▲                           ▲
 │                           │                           │
 0                       quantidade (2)            capacidade (4)

 ````

Regra de Ouro da Expansão: Quando quantidade == capacidade, executamos realloc dobrando a capacidade.

[Refatoração do Minissistema](main.c)
