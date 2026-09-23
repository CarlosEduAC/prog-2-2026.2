#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Para a função abs() (valor absoluto)

// 1. Valida se o andar solicitado existe no prédio
bool requisicao_valida(int andar_destino, int total_andares) {
    return (andar_destino >= 0 && andar_destino <= total_andares);
}

// 2. Determina o sentido de deslocamento
int determinar_direcao(int andar_atual, int andar_destino) {
    if (andar_destino > andar_atual) return 1;  // Subindo
    if (andar_destino < andar_atual) return -1; // Descendo
    return 0;                                   // Já está no mesmo andar
}

// 3. Calcula o tempo estimado da viagem em segundos
int calcular_tempo_viagem(int andar_atual, int andar_destino, int tempo_por_andar) {
    int andares_percorridos = abs(andar_destino - andar_atual);
    return andares_percorridos * tempo_por_andar;
}

// 4. Executa a movimentação no terminal e retorna o novo andar do elevador
int processar_deslocamento(int andar_atual, int andar_destino) {
    int direcao = determinar_direcao(andar_atual, andar_destino);

    if (direcao == 0) {
        printf("[ ELEVADOR ] Voce ja esta no andar %d.\n", andar_atual);
        return andar_atual;
    }

    printf("[ ELEVADOR ] Iniciando deslocamento do andar %d para o %d...\n", andar_atual, andar_destino);

    int andar_temp = andar_atual;
    while (andar_temp != andar_destino) {
        andar_temp += direcao;
        printf(" -> Passando pelo %dº andar...\n", andar_temp);
    }

    printf("[ ELEVADOR ] Chegou ao andar %d!\n", andar_destino);
    return andar_destino; // Retorna a nova posição do elevador
}

int main(void) {
    int total_andares = 10;
    int andar_atual = 0; // Térreo
    int tempo_por_andar = 3; // 3 segundos por andar
    int destino;

    printf("=== SISTEMA DE CONTROLE DE ELEVADOR ===\n");
    printf("Predio com %d andares (0 a %d)\n\n", total_andares, total_andares);

    printf("Digite o andar desejado: ");
    scanf("%d", &destino);

    if (!requisicao_valida(destino, total_andares)) {
        printf("[ ERRO ] Andar %d invalido para este predio.\n", destino);
    } else {
        int tempo = calcular_tempo_viagem(andar_atual, destino, tempo_por_andar);
        printf("Tempo estimado de viagem: %d segundos.\n\n", tempo);

        // Atualiza a posição do elevador na main através do retorno da função
        andar_atual = processar_deslocamento(andar_atual, destino);
    }

    return 0;
}