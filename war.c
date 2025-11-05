#include <stdio.h>
#include <string.h>

#define QTD_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 20

// Definição do molde (struct)
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[QTD_TERRITORIOS]; // Vetor com 5 territórios

    printf("=== CRIADOR DE MAPA MUNDI - JOGO WAR ===\n");

    // Entrada de dados
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("\n--- Território %d ---\n", i + 1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, TAM_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // Remove quebra de linha

        printf("Cor do território: ");
        fgets(mapa[i].cor, TAM_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa o buffer do teclado
    }

    // Exibição final
    printf("\n=== MAPA MUNDI CRIADO ===\n");
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }

    printf("\n=== Fim do programa ===\n");
    return 0;
}
