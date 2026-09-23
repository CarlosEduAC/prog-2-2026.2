# Lista de Exercícios

## Exercício 1: Validador de Regras de Segurança de Senha

Em vez de verificar uma string inteira com ponteiros, você construirá um validador caractere a caractere utilizando funções auxiliares especializadas.

Requisitos:
Crie o conjunto de funções:

bool eh_maiuscula(char c): Retorna true se o caractere for uma letra maiúscula ('A' a 'Z').

bool eh_digito(char c): Retorna true se o caractere for um número ('0' a '9').

bool eh_especial(char c): Retorna true se o caractere for um símbolo especial (ex: @, #, $, %, &, *).

int pontuar_caractere(char c): Retorna 3 pontos se for especial, 2 se for maiúscula, 1 se for dígito e 0 para outros caracteres.

int calcular_forca_senha(int tam_senha, int pontos_acumulados): Retorna o nível de segurança (1: Fraca, 2: Média, 3: Forte) com base no tamanho mínimo de 8 caracteres e no total de pontos.

Assinaturas Obrigatórias:

'''c
bool eh_maiuscula(char c);
bool eh_digito(char c);
bool eh_especial(char c);
int pontuar_caractere(char c);
int calcular_forca_senha(int tam_senha, int pontos_acumulados);
'''

## Exercício 2: Simulador de Controle de Elevador

Simule a lógica de controle de um elevador de prédio residencial.

Requisitos:
bool requisicao_valida(int andar_destino, int total_andares): Retorna true se o andar solicitado existe no prédio (ex: entre 0 e total_andares).

int determinar_direcao(int andar_atual, int andar_destino): Retorna 1 para subindo, -1 para descendo e 0 se já estiver no andar.

int calcular_tempo_viagem(int andar_atual, int andar_destino, int tempo_por_andar): Retorna o tempo em segundos para realizar o percurso.

int processar_deslocamento(int andar_atual, int andar_destino): Imprime o trajeto andar por andar e retorna o novo andar_atual.

## Exercício 3: Motor de Combate RPG por Turnos

Crie um sistema modular que gerencie o combate entre um Herói e um Monstro.

Requisitos:
Decomponha a lógica de combate em funções puras:

1. '''int calcular_dano_causado(int ataque, int defesa_defensor, bool eh_critico)''': O dano base é $(ataque - defesa_defensor)$.
   a. Se o resultado for menor ou igual a zero, o dano mínimo é 1.
   b. Se eh_critico for verdadeiro, o dano final é dobrado.
2. '''int aplicar_dano(int hp_atual, int dano)''': Subtrai o dano do HP. Se o HP resultar em valor negativo, retorna 0.
3. '''bool personagem_esta_vivo(int hp)''': Retorna true se o HP for maior que zero.
4. '''int executar_rodada(int hp_heroi, int atq_heroi, int def_heroi, int hp_monstro, int atq_monstro, int def_monstro, bool heroi_ataca_primeiro)''':
   a. Executa a troca de ataques da rodada respeitando quem tem a iniciativa.
   b. Retorna o novo estado do combate codificado (1: Herói venceu, 2: Monstro venceu, 0: Ambos continuam vivos).
