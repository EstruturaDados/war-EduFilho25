#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    int i;

    if (strstr(missao, "Conquistar 3 territorios seguidos") != NULL) {
        int seguidos = 0;
        for (i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 0) {
                seguidos++;
                if (seguidos >= 3) {
                    return 1;
                }
            } else {
                seguidos = 0;
            }
        }
        return 0;
    }

    if (strstr(missao, "Eliminar todas as tropas da cor Vermelho") != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }

    if (strstr(missao, "Eliminar todas as tropas da cor Azul") != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }

    if (strstr(missao, "pelo menos 2 tropas") != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (mapa[i].tropas < 2) {
                return 0;
            }
        }
        return 1;
    }

    if (strstr(missao, "Nao deixar nenhum territorio com 0 tropas") != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (mapa[i].tropas <= 0) {
                return 0;
            }
        }
        return 1;
    }

    return 0;
}

int main() {
    srand(time(NULL));

    Territorio mapa[5] = {
        {"A", "Vermelho", 3},
        {"B", "Azul", 2},
        {"C", "Vermelho", 4},
        {"D", "Azul", 1},
        {"E", "Vermelho", 2}
    };

    int tamanhoMapa = 5;

    char *missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor Vermelho",
        "Eliminar todas as tropas da cor Azul",
        "Manter todos os territorios com pelo menos 2 tropas",
        "Nao deixar nenhum territorio com 0 tropas"
    };

    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    char *missaoJogador1 = malloc(120);
    char *missaoJogador2 = malloc(120);

    if (!missaoJogador1 || !missaoJogador2) {
        printf("Erro ao alocar memoria\n");
        return 1;
    }

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    printf("Missao Jogador 1: %s\n", missaoJogador1);
    printf("Missao Jogador 2: %s\n", missaoJogador2);

    if (verificarMissao(missaoJogador1, mapa, tamanhoMapa)) {
        printf("Jogador 1 cumpriu a missao\n");
    } else {
        printf("Jogador 1 ainda nao cumpriu a missao\n");
    }

    if (verificarMissao(missaoJogador2, mapa, tamanhoMapa)) {
        printf("Jogador 2 cumpriu a missao\n");
    } else {
        printf("Jogador 2 ainda nao cumpriu a missao\n");
    }

    free(missaoJogador1);
    free(missaoJogador2);

    return 0;
}
