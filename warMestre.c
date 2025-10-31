#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD_TERRITORIOS 5

// -----------------------------
// Estrutura do Território
// -----------------------------
typedef struct
{
    char nome[50];
    char corExercito[30];
    int tropas;
    int conquistado;
} Territorio;

// -----------------------------
// Protótipos das funções
// -----------------------------
void inicializarTerritorios(Territorio *territorios, int n);
void mostrarMapa(const Territorio *territorios, int n);
void simularBatalha(Territorio *atacante, Territorio *defensor);
void verificarMissao(const Territorio *territorios, int n, const char *missao);
int contarTerritoriosConquistados(const Territorio *territorios, int n);
void exibirMenu();

// -----------------------------
// Função principal
// -----------------------------
int main()
{
    srand(time(NULL));
    Territorio *territorios = calloc(QTD_TERRITORIOS, sizeof(Territorio));

    // Inicializa os territórios automaticamente
    inicializarTerritorios(territorios, QTD_TERRITORIOS);

    // Escolhe aleatoriamente uma missão
    const char *missoes[] = {
        "Destruir o exército Verde",
        "Conquistar 3 territórios"};
    const char *missaoAtual = missoes[rand() % 2];

    printf("=== MISSÃO ATUAL ===\n%s\n\n", missaoAtual);

    int opcao, atacante, defensor;

    do
    {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            mostrarMapa(territorios, QTD_TERRITORIOS);
            printf("Escolha o território atacante (1 a %d): ", QTD_TERRITORIOS);
            scanf("%d", &atacante);
            printf("Escolha o território defensor (1 a %d): ", QTD_TERRITORIOS);
            scanf("%d", &defensor);
            getchar();

            if (atacante == defensor || territorios[atacante - 1].tropas <= 0)
            {
                printf("Movimento inválido. Escolha territórios diferentes e válidos.\n");
            }
            else
            {
                simularBatalha(&territorios[atacante - 1], &territorios[defensor - 1]);
            }
            break;

        case 2:
            verificarMissao(territorios, QTD_TERRITORIOS, missaoAtual);
            break;

        case 0:
            printf("\nEncerrando o jogo...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    free(territorios);
    return 0;
}

// -----------------------------
// Funções auxiliares
// -----------------------------

void exibirMenu()
{
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missão\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

void inicializarTerritorios(Territorio *territorios, int n)
{
    const char *nomes[] = {"Norte", "Sul", "Leste", "Oeste", "Centro"};
    const char *cores[] = {"Azul", "Verde", "Vermelho", "Amarelo", "Roxo"};

    for (int i = 0; i < n; i++)
    {
        strcpy(territorios[i].nome, nomes[i]);
        strcpy(territorios[i].corExercito, cores[i]);
        territorios[i].tropas = rand() % 6 + 3; // entre 3 e 8 tropas
        territorios[i].conquistado = 0;
    }
}

void mostrarMapa(const Territorio *territorios, int n)
{
    printf("\n=== ESTADO ATUAL DO MAPA ===\n");
    for (int i = 0; i < n; i++)
    {
        printf("Território %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor: %s\n", territorios[i].corExercito);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("  Status: %s\n\n", territorios[i].conquistado ? "Conquistado" : "Em disputa");
    }
}

void simularBatalha(Territorio *atacante, Territorio *defensor)
{
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n=== BATALHA ===\n");
    printf("%s (A) [%d tropas] vs %s (D) [%d tropas]\n",
           atacante->nome, atacante->tropas,
           defensor->nome, defensor->tropas);
    printf("Dado Ataque: %d | Dado Defesa: %d\n", dadoAtaque, dadoDefesa);

    if (dadoAtaque >= dadoDefesa)
    {
        defensor->tropas--;
        printf(">> O atacante venceu!\n");
        if (defensor->tropas <= 0)
        {
            printf(">> O território %s foi conquistado!\n", defensor->nome);
            defensor->conquistado = 1;
            strcpy(defensor->corExercito, atacante->corExercito);
            defensor->tropas = atacante->tropas - 1;
            atacante->tropas = 1;
        }
    }
    else
    {
        atacante->tropas--;
        printf(">> O defensor resistiu!\n");
    }
}

int contarTerritoriosConquistados(const Territorio *territorios, int n)
{
    int contador = 0;
    for (int i = 0; i < n; i++)
    {
        if (territorios[i].conquistado)
            contador++;
    }
    return contador;
}

void verificarMissao(const Territorio *territorios, int n, const char *missao)
{
    printf("\n=== VERIFICANDO MISSÃO ===\n");
    if (strcmp(missao, "Destruir o exército Verde") == 0)
    {
        int verdeExiste = 0;
        for (int i = 0; i < n; i++)
        {
            if (strcmp(territorios[i].corExercito, "Verde") == 0 && territorios[i].tropas > 0)
                verdeExiste = 1;
        }
        if (!verdeExiste)
            printf("Parabéns! Você destruiu o exército Verde!\n");
        else
            printf("Ainda há tropas Verdes resistindo...\n");
    }
    else if (strcmp(missao, "Conquistar 3 territórios") == 0)
    {
        int conquistados = contarTerritoriosConquistados(territorios, n);
        if (conquistados >= 3)
            printf("Missão cumprida! Você conquistou 3 territórios!\n");
        else
            printf("Você tem %d territórios conquistados. Continue lutando!\n", conquistados);
    }
}
