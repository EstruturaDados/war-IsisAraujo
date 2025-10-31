#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Territorio
{
  char nome[50];
  char corExercito[30];
  int tropas;
  int conquistado; // 1 se o território já foi conquistado
};

// Função para simular uma batalha entre dois territórios
void simularBatalha(struct Territorio *atacante, struct Territorio *defensor)
{
  int dadoAtaque = rand() % 6 + 1; // valor entre 1 e 6
  int dadoDefesa = rand() % 6 + 1;

  printf("\n=== BATALHA ===\n");
  printf("%s (A) [%d tropas] vs %s (D) [%d tropas]\n",
         atacante->nome, atacante->tropas,
         defensor->nome, defensor->tropas);
  printf("Dado de Ataque: %d | Dado de Defesa: %d\n", dadoAtaque, dadoDefesa);

  if (dadoAtaque >= dadoDefesa)
  {
    defensor->tropas--;
    printf(">> O atacante venceu a rodada!\n");
    if (defensor->tropas <= 0)
    {
      printf(">> O território %s foi conquistado!\n", defensor->nome);
      defensor->conquistado = 1;
      defensor->tropas = atacante->tropas - 1; // transfere parte das tropas
      atacante->tropas = 1;                    // deixa 1 tropa no território original
    }
  }
  else
  {
    atacante->tropas--;
    printf(">> O defensor resistiu ao ataque!\n");
  }
}

// Função para mostrar o estado atual do mapa
void mostrarMapa(struct Territorio *territorios, int n)
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

int main()
{
  srand(time(NULL)); // inicializa números aleatórios
  int n = 5;
  struct Territorio *territorios = calloc(n, sizeof(struct Territorio));

  // Cadastro
  for (int i = 0; i < n; i++)
  {
    printf("Digite o nome do território %d: ", i + 1);
    fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
    territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

    printf("Digite a cor do exército: ");
    fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
    territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

    printf("Digite o número de tropas: ");
    scanf("%d", &territorios[i].tropas);
    getchar(); // limpa buffer
    territorios[i].conquistado = 0;
    printf("\n");
  }

  int atacante, defensor;
  char continuar;

  do
  {
    mostrarMapa(territorios, n);

    printf("Escolha o território atacante (1 a %d): ", n);
    scanf("%d", &atacante);
    printf("Escolha o território defensor (1 a %d): ", n);
    scanf("%d", &defensor);
    getchar();

    if (atacante == defensor || territorios[atacante - 1].tropas <= 0)
    {
      printf("Movimento inválido. Escolha territórios diferentes e com tropas disponíveis.\n");
    }
    else
    {
      simularBatalha(&territorios[atacante - 1], &territorios[defensor - 1]);
    }

    printf("\nDeseja realizar outra batalha? (s/n): ");
    scanf(" %c", &continuar);
    getchar();

  } while (continuar == 's' || continuar == 'S');

  free(territorios);
  printf("\nFim da simulação.\n");
  return 0;
}
