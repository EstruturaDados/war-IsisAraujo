#include <stdio.h>
#include <string.h>

#define QTD_TERRITORIOS 5

// Definição da struct
struct Territorio
{
  char nome[50];
  char corExercito[30];
  int tropas;
};

int main()
{
  struct Territorio territorios[QTD_TERRITORIOS];
  int i;

  // Cadastro dos territórios
  for (i = 0; i < QTD_TERRITORIOS; i++)
  {
    printf("Digite o nome do território %d: ", i + 1);
    fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
    territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove o \n

    printf("Digite a cor do exército: ");
    fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
    territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

    printf("Digite o número de tropas: ");
    scanf("%d", &territorios[i].tropas);
    getchar(); // limpa o buffer do teclado

    printf("\n");
  }

  // Exibição dos territórios cadastrados
  printf("=== ESTADO ATUAL DO MAPA ===\n");
  for (i = 0; i < QTD_TERRITORIOS; i++)
  {
    printf("Território %d:\n", i + 1);
    printf("  Nome: %s\n", territorios[i].nome);
    printf("  Cor do exército: %s\n", territorios[i].corExercito);
    printf("  Tropas: %d\n\n", territorios[i].tropas);
  }

  return 0;
}
