#include <stdio.h>
#include <stdbool.h>

// 1. Calcula o dano causado respeitando o dano mínimo e crítico
int calcular_dano_causado(int ataque, int defesa_defensor, bool eh_critico) {
    int dano_base = ataque - defesa_defensor;

    if (dano_base <= 0) {
        dano_base = 1; // Dano mínimo garantido
    }

    if (eh_critico) {
        dano_base *= 2; // Dobra o dano em acertos críticos
    }

    return dano_base;
}

// 2. Aplica o dano ao HP impedindo valores negativos
int aplicar_dano(int hp_atual, int dano) {
    int novo_hp = hp_atual - dano;
    return (novo_hp < 0) ? 0 : novo_hp;
}

// 3. Verifica se o participante continua vivo
bool personagem_esta_vivo(int hp) {
    return hp > 0;
}

// 4. Executa uma rodada completa de combate
int executar_rodada(int hp_heroi, int atq_heroi, int def_heroi,
                    int hp_monstro, int atq_monstro, int def_monstro,
                    bool heroi_ataca_primeiro) {

    // TURNO DO PRIMEIRO ATACANTE
    if (heroi_ataca_primeiro) {
        printf("\n[ TURNO ] O Heroi ataca primeiro!\n");
        int dano = calcular_dano_causado(atq_heroi, def_monstro, false);
        hp_monstro = aplicar_dano(hp_monstro, dano);
        printf("-> Heroi causou %d de dano! HP do Monstro: %d\n", dano, hp_monstro);

        if (!personagem_esta_vivo(hp_monstro)) {
            return 1; // Herói venceu nesta rodada
        }

        // Contra-ataque do Monstro
        dano = calcular_dano_causado(atq_monstro, def_heroi, false);
        hp_heroi = aplicar_dano(hp_heroi, dano);
        printf("-> Monstro contra-atacou causando %d de dano! HP do Heroi: %d\n", dano, hp_heroi);

        if (!personagem_esta_vivo(hp_heroi)) {
            return 2; // Monstro venceu
        }

    } else {
        printf("\n[ TURNO ] O Monstro ataca primeiro!\n");
        int dano = calcular_dano_causado(atq_monstro, def_heroi, false);
        hp_heroi = aplicar_dano(hp_heroi, dano);
        printf("-> Monstro causou %d de dano! HP do Heroi: %d\n", dano, hp_heroi);

        if (!personagem_esta_vivo(hp_heroi)) {
            return 2; // Monstro venceu
        }

        // Contra-ataque do Herói (com chance de ataque crítico ativado)
        dano = calcular_dano_causado(atq_heroi, def_monstro, true);
        hp_monstro = aplicar_dano(hp_monstro, dano);
        printf("-> Heroi contra-atacou com GOLPE CRITICO causando %d de dano! HP do Monstro: %d\n", dano, hp_monstro);

        if (!personagem_esta_vivo(hp_monstro)) {
            return 1; // Herói venceu
        }
    }

    return 0; // Ambos continuam vivos ao final da rodada
}

int main(void) {
    // Estado do Herói
    int hp_heroi = 100, atq_heroi = 25, def_heroi = 10;

    // Estado do Monstro
    int hp_monstro = 80, atq_monstro = 20, def_monstro = 5;

    int rodada = 1;
    int resultado = 0;

    printf("=== INICIO DO COMBATE ===\n");
    printf("Heroi   : HP %d | ATQ %d | DEF %d\n", hp_heroi, atq_heroi, def_heroi);
    printf("Monstro : HP %d | ATQ %d | DEF %d\n", hp_monstro, atq_monstro, def_monstro);

    while (resultado == 0) {
        printf("\n---------------------------------");
        printf("\nRODADA %d", rodada);

        // Alterna quem ataca primeiro com base no número da rodada (ímpar: Herói, par: Monstro)
        bool heroi_primeiro = (rodada % 2 != 0);

        resultado = executar_rodada(hp_heroi, atq_heroi, def_heroi,
                                    hp_monstro, atq_monstro, def_monstro,
                                    heroi_primeiro);

        // Atualiza HPs fictícios apenas para demonstrar a progressão de rodadas no laço
        hp_heroi -= 5;
        hp_monstro -= 15;
        rodada++;
    }

    printf("\n=================================\n");
    if (resultado == 1) {
        printf("[ VITORIA ] O Heroi derrotou o Monstro!\n");
    } else {
        printf("[ DERROTA ] O Monstro derrotou o Heroi!\n");
    }

    return 0;
}