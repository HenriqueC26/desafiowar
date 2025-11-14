#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -------------------------------------------------------
// Estrutura principal que representa um território
// -------------------------------------------------------
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// -------------------------------------------------------
// Vetor de missões disponíveis
// -------------------------------------------------------
#define TOTAL_MISSOES 5
char *missoesDisponiveis[TOTAL_MISSOES] = {
    "Conquistar 3 territórios consecutivos",
    "Eliminar todas as tropas da cor vermelha",
    "Controlar ao menos 4 territórios",
    "Ter mais de 20 tropas no total",
    "Conquistar um território chamado 'Capital'"
};

// -------------------------------------------------------
// Função para cadastrar os territórios dinamicamente
// -------------------------------------------------------
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    printf("\n=== Cadastro dos Territórios ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor (Ex: Vermelho, Azul...): ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa buffer
    }
}

// -------------------------------------------------------
// Exibe o estado atual de todos os territórios
// -------------------------------------------------------
void exibirMapa(Territorio *mapa, int qtd) {
    printf("\n=== Mapa Atual ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d - %-15s | Cor: %-10s | Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("-----------------------------\n");
}

// -------------------------------------------------------
// Função de ataque entre dois territórios
// -------------------------------------------------------
void atacar(Territorio *atacante, Territorio *defensor) {
    printf("\n=== Ataque: %s (%.10s) -> %s (%.10s) ===\n", 
            atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf(" Não é possível atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas < 2) {
        printf(" Tropas insuficientes para atacar (mínimo 2 tropas necessárias).\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf(" Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf(" O atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
    } else {
        printf(" O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
    }

    printf("\n--- Estado pós-batalha ---\n");
    printf("%s -> Tropas: %d | Cor: %s\n", atacante->nome, atacante->tropas, atacante->cor);
    printf("%s -> Tropas: %d | Cor: %s\n", defensor->nome, defensor->tropas, defensor->cor);
}

// -------------------------------------------------------
// Sorteia uma missão e copia para o destino
// -------------------------------------------------------
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// -------------------------------------------------------
// Exibe a missão do jogador
// -------------------------------------------------------
void exibirMissao(const char *missao) {
    printf("\n Sua missão: %s\n", missao);
}

// -------------------------------------------------------
// Verifica se a missão foi cumprida (lógica simplificada)
// -------------------------------------------------------
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    if (strcmp(missao, "Controlar ao menos 4 territórios") == 0) {
        int controle = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0)
                controle++;
        }
        return controle >= 4;
    }

    if (strcmp(missao, "Ter mais de 20 tropas no total") == 0) {
        int total = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0)
                total += mapa[i].tropas;
        }
        return total > 20;
    }

    if (strcmp(missao, "Conquistar um território chamado 'Capital'") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0 && strcmp(mapa[i].nome, "Capital") == 0)
                return 1;
        }
    }

    return 0;
}

// -------------------------------------------------------
// Libera memória alocada dinamicamente
// -------------------------------------------------------
void liberarMemoria(Territorio *mapa, char *missaoJogador) {
    free(mapa);
    free(missaoJogador);
    printf("\n Memória liberada com sucesso.\n");
}

// -------------------------------------------------------
// Função principal
// -------------------------------------------------------
int main() {
    srand(time(NULL));

    int qtd;
    printf("Digite o número de territórios que deseja cadastrar: ");
    scanf("%d", &qtd);
    getchar();

    Territorio *mapa = (Territorio *) calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    char *missaoJogador = (char *) malloc(100 * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memória para missão!\n");
        free(mapa);
        return 1;
    }

    atribuirMissao(missaoJogador, missoesDisponiveis, TOTAL_MISSOES);
    exibirMissao(missaoJogador);

    cadastrarTerritorios(mapa, qtd);

    int opcao;
    do {
        printf("\n=== MENU DE OPÇÕES ===\n");
        printf("1 - Exibir mapa\n");
        printf("2 - Atacar território\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                exibirMapa(mapa, qtd);
                break;

            case 2: {
                exibirMapa(mapa, qtd);
                int iAtacante, iDefensor;

                printf("Escolha o número do território atacante: ");
                scanf("%d", &iAtacante);
                printf("Escolha o número do território defensor: ");
                scanf("%d", &iDefensor);
                getchar();

                if (iAtacante < 1 || iAtacante > qtd || iDefensor < 1 || iDefensor > qtd) {
                    printf(" Opção inválida.\n");
                } else {
                    atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
                }
                break;
            }

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf(" Opção inválida.\n");
                break;
        }

        if (verificarMissao(missaoJogador, mapa, qtd)) {
            printf("\n Missão cumprida! O jogador venceu o jogo!\n");
            break;
        }

    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador);
    return 0;
}