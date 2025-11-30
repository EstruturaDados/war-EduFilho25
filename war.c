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

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
