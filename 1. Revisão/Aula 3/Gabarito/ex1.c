#include <stdio.h>
#include <stdbool.h>

// 1. Verifica se o caractere é letra maiúscula
bool eh_maiuscula(char c) {
    return (c >= 'A' && c <= 'Z');
}

// 2. Verifica se o caractere é um dígito numérico
bool eh_digito(char c) {
    return (c >= '0' && c <= '9');
}

// 3. Verifica se o caractere é um símbolo especial
bool eh_especial(char c) {
    return (c == '@' || c == '#' || c == '$' || c == '%' || c == '&' || c == '*');
}

// 4. Retorna a pontuação do caractere com base na sua categoria
int pontuar_caractere(char c) {
    if (eh_especial(c))   return 3;
    if (eh_maiuscula(c))  return 2;
    if (eh_digito(c))     return 1;
    return 0; // Letras minúsculas ou outros caracteres
}

// 5. Calcula o nível final de força da senha
int calcular_forca_senha(int tam_senha, int pontos_acumulados) {
    if (tam_senha < 8) {
        return 1; // Fraca (Requisito de tamanho não atingido)
    }

    if (pontos_acumulados >= 10) return 3; // Forte
    if (pontos_acumulados >= 5)  return 2; // Média
    return 1;                              // Fraca
}

int main(void) {
    char c;
    int tam_senha = 0;
    int pontos_acumulados = 0;

    printf("Digite a senha (pressione Enter ao finalizar): ");

    // Leitura simulada caractere por caractere via buffer do teclado
    while ((c = getchar()) != '\n' && c != EOF) {
        tam_senha++;
        pontos_acumulados += pontuar_caractere(c);
    }

    int nivel = calcular_forca_senha(tam_senha, pontos_acumulados);

    printf("\n--- RESULTADO DA ANALISE ---\n");
    printf("Tamanho da senha : %d caracteres\n", tam_senha);
    printf("Pontuacao total  : %d pontos\n", pontos_acumulados);
    printf("Nivel de Forca   : ");

    switch (nivel) {
        case 1: printf("FRACA (Minimo 8 caracteres e variacao de tipos)\n"); break;
        case 2: printf("MEDIA\n"); break;
        case 3: printf("FORTE\n"); break;
    }

    return 0;
}