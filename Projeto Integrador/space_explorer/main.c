#include "raylib.h"
#include "defensor.h"
#include "tiro.h"
#include "inimigo.h"
#include "save.h"
#include "ranking.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Estado do Game Loop (Máquina de Estados Finita)
typedef enum {
    TELA_MENU,
    TELA_JOGO,
    TELA_PAUSA,
    TELA_RANKING,
    TELA_GAME_OVER
} EstadoJogo;

// Função auxiliar para reabastecer a Fila de Spawn de Inimigos (FIFO)
void carregar_onda_inimigos(FilaInimigos *f, int largura_tela) {
    for (int i = 0; i < 15; i++) {
        // Posição Y inicial em -30.0f (logo acima do topo da tela)
        float pos_x = 60.0f + (rand() % (largura_tela - 120));
        bool aglomerado = (i % 3 == 0); // 1 a cada 3 é aglomerado
        float velocidade = 1.5f + ((rand() % 15) / 10.0f);
        fila_inimigos_enqueue(f, pos_x, -30.0f, velocidade, aglomerado);
    }
}

int main(void) {
    srand((unsigned int)time(NULL));

    int largura = 800, altura = 600;
    carregar_configuracao_texto("config.txt", &largura, &altura);

    InitWindow(largura, altura, "Space Defender - Retro Edition");
    SetTargetFPS(60);

    // Estado Inicial da Aplicação
    EstadoJogo estado_atual = TELA_MENU;

    // Instancia os TADs Principais
    Defensor *canhao = defensor_criar(largura / 2.0f - 20, altura - 40, 5.0f);
    GerenciadorTiros *tiros = tiros_criar();
    FilaInimigos *spawn_queue = fila_inimigos_criar();
    AtivosInimigos *inimigos_tela = ativos_inimigos_criar();

    int pontuacao = 0;
    float tempo_spawn = 0.0f;

    // Carrega a primeira onda na Fila de Spawn
    carregar_onda_inimigos(spawn_queue, largura);

    // Game Loop Principal
    while (!WindowShouldClose()) {

        // =====================================================================
        // 1. ATUALIZAÇÃO / LÓGICA DE CADA TELA
        // =====================================================================
        switch (estado_atual) {

            case TELA_MENU:
                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ONE)) {
                    estado_atual = TELA_JOGO;
                }
                if (IsKeyPressed(KEY_TWO)) {
                    // Carrega save do arquivo binário se existir
                    EstadoJogoBinario salvo;
                    if (carregar_jogo_binario("savegame.bin", &salvo)) {
                        pontuacao = salvo.pontuacao;
                        estado_atual = TELA_JOGO;
                    }
                }
                if (IsKeyPressed(KEY_THREE)) {
                    estado_atual = TELA_RANKING;
                }
                if (IsKeyPressed(KEY_FOUR)) {
                    CloseWindow();
                    return 0;
                }
                break;

            case TELA_JOGO:
                // Tecla ESC ou P abre o Menu de Pausa
                if (IsKeyPressed(KEY_P)) {
                    estado_atual = TELA_PAUSA;
                    break;
                }

                // Atualização do Canhão Defensor
                defensor_atualizar(canhao, largura);

                // Disparo de tiros (ESPAÇO)
                if (IsKeyPressed(KEY_SPACE)) {
                    tiros_adicionar(tiros, defensor_get_x(canhao) + 18, defensor_get_y(canhao) - 10, -8.0f);
                }

                // SPAWN: Desenfileira da Fila (FIFO) a cada 0.8s e coloca na Tela
                tempo_spawn += GetFrameTime();
                if (tempo_spawn >= 0.8f && fila_inimigos_qtd(spawn_queue) > 0) {
                    float x, y, vel; bool aglomerado;
                    if (fila_inimigos_dequeue(spawn_queue, &x, &y, &vel, &aglomerado)) {
                        ativos_inimigos_adicionar(inimigos_tela, x, y, vel, aglomerado);
                    }
                    tempo_spawn = 0.0f;
                }

                // Se a fila esvaziar, recarrega uma nova onda
                if (fila_inimigos_qtd(spawn_queue) == 0) {
                    carregar_onda_inimigos(spawn_queue, largura);
                }

                // Processa colisões e soma pontuação
                pontuacao += ativos_inimigos_processar_colisoes(inimigos_tela, tiros);

                // F9: Salva o estado do jogo em binário
                if (IsKeyPressed(KEY_F9)) {
                    EstadoJogoBinario estado = {
                        defensor_get_x(canhao), defensor_get_vida(canhao), pontuacao, 1
                    };
                    salvar_jogo_binario("savegame.bin", &estado);
                }

                // Checa Game Over (Integridade do canhão zerada)
                if (defensor_get_vida(canhao) <= 0) {
                    estado_atual = TELA_GAME_OVER;
                }
                break;

            case TELA_PAUSA:
                if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ENTER)) {
                    estado_atual = TELA_JOGO;
                }
                if (IsKeyPressed(KEY_M)) {
                    estado_atual = TELA_MENU;
                }
                break;

            case TELA_RANKING:
                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_M) || IsKeyPressed(KEY_ESCAPE)) {
                    estado_atual = TELA_MENU;
                }
                break;

            case TELA_GAME_OVER:
                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_M)) {
                    // Reinicia o estado para uma nova partida
                    pontuacao = 0;
                    estado_atual = TELA_MENU;
                }
                break;
        }

        // =====================================================================
        // 2. RENDERIZAÇÃO NA TELA DE ACORDO COM O ESTADO
        // =====================================================================
        BeginDrawing();
        ClearBackground(BLACK);

        switch (estado_atual) {

            case TELA_MENU:
                DrawText("SPACE DEFENDER", largura / 2 - MeasureText("SPACE DEFENDER", 40) / 2, 100, 40, GREEN);
                DrawText("Retro Edition", largura / 2 - MeasureText("Retro Edition", 20) / 2, 150, 20, DARKGREEN);

                DrawText("[1] Iniciar Novo Jogo", largura / 2 - 120, 260, 20, RAYWHITE);
                DrawText("[2] Carregar Jogo (Save Binario)", largura / 2 - 120, 300, 20, RAYWHITE);
                DrawText("[3] Ver Ranking / High Scores", largura / 2 - 120, 340, 20, RAYWHITE);
                DrawText("[4] Sair", largura / 2 - 120, 380, 20, RED);

                DrawText("Pressione o numero da opcao desejada", largura / 2 - MeasureText("Pressione o numero da opcao desejada", 15) / 2, 480, 15, GRAY);
                break;

            case TELA_JOGO:
                // Renderização do jogo ativo
                defensor_renderizar(canhao);
                tiros_atualizar_e_renderizar(tiros, altura);
                ativos_inimigos_atualizar_e_renderizar(inimigos_tela, altura);

                // HUD Superior
                DrawText(TextFormat("Vida: %d%%", defensor_get_vida(canhao)), 10, 10, 20, GREEN);
                DrawText(TextFormat("Pontos: %d", pontuacao), 10, 35, 20, GOLD);
                DrawText(TextFormat("Undo (Pilha Z): %d", defensor_get_qtd_undo(canhao)), 10, 60, 20, SKYBLUE);
                DrawText(TextFormat("Fila Spawn: %d", fila_inimigos_qtd(spawn_queue)), 10, 85, 20, YELLOW);

                DrawText("[A/D] Mover | [ESPAÇO] Atirar | [Z] Undo | [P] Pausa | [F9] Save", 10, altura - 25, 14, GRAY);
                break;

            case TELA_PAUSA:
                DrawText("JOGO PAUSADO", largura / 2 - MeasureText("JOGO PAUSADO", 40) / 2, 200, 40, GOLD);
                DrawText("Pressione [P] para Continuar", largura / 2 - MeasureText("Pressione [P] para Continuar", 20) / 2, 280, 20, RAYWHITE);
                DrawText("Pressione [M] para Voltar ao Menu Principal", largura / 2 - MeasureText("Pressione [M] para Voltar ao Menu Principal", 18) / 2, 320, 18, GRAY);
                break;

            case TELA_RANKING:
                DrawText("HALL DA FAMA - TOP SCORES", largura / 2 - MeasureText("HALL DA FAMA - TOP SCORES", 30) / 2, 80, 30, GOLD);

                // Exemplo estático de exibição da lista ordenada com QuickSort
                RegistroScore mocks[3] = { {"PILOTO_ALPHA", 3500}, {"CADETE_BETA", 2100}, {"RECRUTA", 900} };
                ranking_ordenar_quicksort(mocks, 0, 2);

                for (int i = 0; i < 3; i++) {
                    DrawText(TextFormat("%d. %s - %d pts", i + 1, mocks[i].nome, mocks[i].pontos),
                             largura / 2 - 120, 180 + (i * 40), 20, GREEN);
                }

                DrawText("Pressione [ENTER] ou [M] para Voltar", largura / 2 - MeasureText("Pressione [ENTER] ou [M] para Voltar", 18) / 2, 450, 18, RAYWHITE);
                break;

            case TELA_GAME_OVER:
                DrawText("GAME OVER", largura / 2 - MeasureText("GAME OVER", 50) / 2, 180, 50, RED);
                DrawText(TextFormat("Pontuacao Final: %d", pontuacao), largura / 2 - MeasureText(TextFormat("Pontuacao Final: %d", pontuacao), 25) / 2, 260, 25, GOLD);
                DrawText("Pressione [ENTER] para Voltar ao Menu", largura / 2 - MeasureText("Pressione [ENTER] para Voltar ao Menu", 18) / 2, 350, 18, RAYWHITE);
                break;
        }

        EndDrawing();
    }

    // Liberação de Memória sem Vazamentos
    defensor_destruir(canhao);
    tiros_destruir(tiros);
    fila_inimigos_destruir(spawn_queue);
    ativos_inimigos_destruir(inimigos_tela);
    CloseWindow();

    return 0;
}