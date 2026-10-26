#ifndef MATH_GAME_H
#define MATH_GAME_H

#include <stdbool.h>

// Função pública: Limita um valor entre min e max (Clamping)
float math_clamp(float valor, float min, float max);

// Função pública: Checa colisão entre dois pontos por raio
bool math_colisao_circulos(float x1, float y1, float r1, float x2, float y2, float r2);

#endif