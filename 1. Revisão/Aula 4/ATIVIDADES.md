# Atividades da Aula 4

## Exercício 1: Gestão de Biblioteca (Manipulação Básica de struct)

Crie um programa que defina uma estrutura Livro contendo:

* titulo (string de até 80 caracteres)
* autor (string de até 50 caracteres)
* ano_publicacao (inteiro)
* preco (float)

Implemente uma função void exibir_livro(Livro l) que receba um livro por valor e imprima seus dados formatados. No main(), cadastre 2 livros manualmente e exiba as informações do livro mais antigo.

## Exercício 2: Controle de Frota de Veículos (Vetor de structs e Busca)

Uma empresa de transporte precisa controlar sua frota. Defina a estrutura Veiculo com os campos: placa (string), modelo (string), ano (inteiro) e quilometragem (float).

Escreva um programa que:

1. Permita o cadastro de um vetor de 4 veículos via entrada do usuário.
2. Implemente a função float calcular_media_km(const Veiculo frota[], int tam) que retorne a quilometragem média dos veículos.
3. Imprima a placa e o modelo de todos os veículos que possuem quilometragem acima da média calculada.

## Exercício 3: Sistema Bancário de Contas Correntes (Processamento e Atualização)

Crie uma estrutura ContaBancaria composta por:

* numero_conta (inteiro)
* nome_titular (string de até 50 caracteres)
* saldo (float)

Desenvolva as seguintes funções:

1. bool realizar_deposito(ContaBancaria *c, float valor): Adiciona o valor ao saldo se valor > 0.
2. bool realizar_saque(ContaBancaria *c, float valor): Deduz o valor do saldo apenas se houver saldo suficiente (saldo >= valor).
3. int buscar_conta(const ContaBancaria contas[], int tam, int num_procurado): Retorna o índice da conta no vetor ou -1 se não for encontrada.

No main(), crie um vetor com 3 contas, simule uma operação de busca e realize um saque e um depósito utilizando a passagem por referência (ponteiro para struct).
