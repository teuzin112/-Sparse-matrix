#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"

// Realiza todas as funcoes do menu na tela
// Pre-condicao: nenhuma
// Pos-condicao: Menu na tela
void menu() {
  int buf = -1;
  while (buf != 0) {
    printf("1 - Somar duas matrizes\n");
    printf("2 - Subtrair duas matrizes\n");
    printf("3 - Multiplicar duas matrizes\n");
    printf("4 - Gerar transposta de uma matriz\n");
    printf("5 - Determinar simetria de uma matriz\n");
    printf("6 - Executar arquivo\n");
    printf("0 - Terminar execucao\n");
    printf("- - - - - - - - - - - - - - - - - - -\n");

    scanf("%d", &buf);
    if (buf == 0) break;
    char arq[20];
    if (buf == 1) {
      printf("Entre com o nome do arquivo de texto(arquivo.txt) a ser lido ou seu caminho completo: ");
      scanf("%s[^\n]", arq);
      system("cls");

      Matriz* A;
      Matriz* B;
      ler_matriz2(&A, &B, arq, 0);

      imprime(A);
      int i;
      for (i = 0; i <= A->ncolunas; i++)
        printf("-----");
      printf("\n");
      imprime(B);
      for (i = 0; i <= B->ncolunas; i++)
        printf("-----");
      printf("\n");
      imprime(somar(A, B));
    }

    if (buf == 2) {
      printf("Entre com o nome do arquivo de texto(arquivo.txt) a ser lido ou seu caminho completo: ");
      scanf("%s[^\n]", arq);
      system("cls");

      Matriz* A;
      Matriz* B;
      ler_matriz2(&A, &B, arq, 0);

      imprime(A);
      int i;
      for (i = 0; i <= A->ncolunas; i++)
        printf("-----");
      printf("\n");
      imprime(B);
      for (i = 0; i <= B->ncolunas; i++)
        printf("-----");
      printf("\n");
      imprime(subtrair(A, B));
    }

    if (buf == 3) {
      printf("Entre com o nome do arquivo de texto(arquivo.txt) a ser lido ou seu caminho completo: ");
      scanf("%s[^\n]", arq);
      system("cls");

      Matriz* A;
      Matriz* B;
      ler_matriz2(&A, &B, arq, 0);

      imprime(A);
      int i;
      for (i = 0; i <= A->ncolunas; i++)
        printf("-----");
      printf("\n");
      imprime(B);
      for (i = 0; i <= B->ncolunas; i++)
        printf("-----");
      printf("\n");
      imprime(multiplicar(A, B));
    }

    if (buf == 4) {
      printf("Entre com o nome do arquivo de texto(arquivo.txt) a ser lido ou seu caminho completo: ");
      scanf("%s[^\n]", arq);
      system("cls");

      Matriz* M = ler_matriz(arq, 0);

      imprime(M);
      int i;
      for (i = 0; i <= M->ncolunas; i++)
        printf("-----");
      printf("\n");
      imprime(transposta(M));
    }
    if (buf == 5) {
      printf("Entre com o nome do arquivo de texto(arquivo.txt) a ser lido ou seu caminho completo: ");
      scanf("%s[^\n]", arq);
      system("cls");

      Matriz* M = ler_matriz(arq, 0);

      imprime(M);
      int i;
      for (i = 0; i <= M->ncolunas; i++)
        printf("-----");
      printf("\n");
      is_simetrica(M);
    }
    if (buf == 6) {
      printf("Entre com o nome do arquivo de texto(arquivo.txt) a ser lido ou seu caminho completo: ");
      scanf("%s[^\n]", arq);
      system("cls");

      FILE* f;
      char str[20];
      f = fopen(arq, "r");
      fscanf(f, "%s ", str);
      fclose(f);

      int i;
      if (strcmp(str, "soma") == 0) {
        Matriz* A;
        Matriz* B;
        ler_matriz2(&A, &B, arq, 1);

        imprime(A);
        for (i = 0; i <= A->ncolunas; i++)
          printf("-----");
        printf("\n");
        imprime(B);
        for (i = 0; i <= B->ncolunas; i++)
          printf("-----");
        printf("\n");
        imprime(somar(A, B));
      }
      if (strcmp(str, "subtracao") == 0) {
        Matriz* A;
        Matriz* B;
        ler_matriz2(&A, &B, arq, 1);

        imprime(A);
        for (i = 0; i <= A->ncolunas; i++)
          printf("-----");
        printf("\n");
        imprime(B);
        for (i = 0; i <= B->ncolunas; i++)
          printf("-----");
        printf("\n");
        imprime(subtrair(A, B));
      }
      if (strcmp(str, "multiplicacao") == 0) {
        Matriz* A;
        Matriz* B;
        ler_matriz2(&A, &B, arq, 1);

        imprime(A);
        for (i = 0; i <= A->ncolunas; i++)
          printf("-----");
        printf("\n");
        imprime(B);
        for (i = 0; i <= B->ncolunas; i++)
          printf("-----");
        printf("\n");
        imprime(multiplicar(A, B));
      }
      if (strcmp(str, "transposta") == 0) {
        Matriz* M = ler_matriz(arq, 1);

        imprime(M);
        for (i = 0; i <= M->ncolunas; i++)
          printf("-----");
        printf("\n");
        imprime(transposta(M));
      }
      if (strcmp(str, "simetrica") == 0) {
        Matriz* M = ler_matriz(arq, 1);

        imprime(M);
        for (i = 0; i <= M->ncolunas; i++)
          printf("-----");
        printf("\n");
        is_simetrica(M);
      }
    }
    printf("Pressione ENTER para voltar ao menu\n");
    getchar();
    getchar();
    system("cls");
  }
}

int main() {
  menu();

  return 0;
}
