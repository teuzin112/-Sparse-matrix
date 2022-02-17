#include "matriz.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funcao auxiliar para criar matriz vazia
// Pre-condicao: Ponteiro para cabeca da matriz nao nulo e numero de colunas a serem criadas
// Pos-condicao: Retorna a cabeca da lista encadeada com o numero de colunas que foi solicitado
Celula* cria_direita(Celula* cabeca, Celula* c, int n) {
  if (n == 0)  // Contador para condicao de parada
    return cabeca;

  Celula* aux = (Celula*)malloc(sizeof(Celula));
  aux->linha = 0;
  aux->coluna = -1;
  aux->abaixo = aux;
  c = aux;
  c->direita = cria_direita(cabeca, c->direita, n - 1);
  return aux;
}

// Funcao auxiliar para criar matriz vazia
// Pre-condicao: Ponteiro para cabeca da matriz nao nulo e numero de linhas a serem criadas
// Pos-condicao: Retorna a cabeca da lista encadeada com o numero de linhas que foi solicitado
Celula* cria_abaixo(Celula* cabeca, Celula* c, int n) {
  if (n == 0)  // Contador para condicao de parada
    return cabeca;

  Celula* aux = (Celula*)malloc(sizeof(Celula));
  aux->linha = -1;
  aux->coluna = 0;
  aux->direita = aux;
  c = aux;
  c->abaixo = cria_abaixo(cabeca, c->abaixo, n - 1);
  return aux;
}

// Cria uma matriz vazia devidamente inicializada
// Pre-condicao: Nenhuma
// Pos-condicao: Retorna um ponteiro do tipo Matriz
Matriz* cria_matriz(int nlinhas, int ncolunas) {
  Matriz* M = (Matriz*)malloc(sizeof(Matriz));
  M->nlinhas = nlinhas;
  M->ncolunas = ncolunas;

  Celula* cabeca = (Celula*)malloc(sizeof(Celula));
  cabeca->linha = -1;
  cabeca->coluna = -1;
  cabeca->direita = NULL;
  cabeca->abaixo = NULL;
  cabeca->direita = cria_direita(cabeca, cabeca->direita, ncolunas);
  cabeca->abaixo = cria_abaixo(cabeca, cabeca->abaixo, nlinhas);

  M->cabeca = cabeca;

  return M;
}

// Insere um elemento do tipo celula na matriz esparsa em uma posicao que tenha um elemento de valor 0
// Pre-condicao: Ponteiro para Matriz nao nulo e posicao valida
// Pos-condicao: Retorna a Matriz com o elemento inserido
Matriz* inserir(Matriz* M, int linha, int coluna, int info) {
  if (info == 0)
    return M;

  if (linha > M->nlinhas || coluna > M->ncolunas) {
    printf("Posicao de matriz invalida: (%dx%d)\n\n", linha, coluna);
    return M;
  }

  if (busca(M, linha, coluna) != 0) {
    printf("Posicao (%dx%d) ja esta ocupada pelo elemento %d\n\n", linha, coluna, busca(M, linha, coluna));
    return M;
  }

  Celula* c = (Celula*)malloc(sizeof(Celula));    // Variavel para percorrer a Matriz
  Celula* aux = (Celula*)malloc(sizeof(Celula));  // Variavel auxiliar que sera inserida na Matriz
  aux->valor = info;
  aux->linha = linha;
  aux->coluna = coluna;

  int i;
  for (i = 0, c = M->cabeca; i < linha; i++)
    c = c->abaixo;

  while (c->direita->linha != -1 && c->direita->coluna < coluna)
    c = c->direita;

  aux->direita = c->direita;
  c->direita = aux;

  for (i = 0, c = M->cabeca; i < coluna; i++)
    c = c->direita;

  while (c->abaixo->coluna != -1 && c->abaixo->linha < linha)
    c = c->abaixo;

  aux->abaixo = c->abaixo;
  c->abaixo = aux;

  return M;
}

// Funcao auxiliar que busca um elemento atraves de sua posicao(mxn) numa estrutra Matriz
// Pre-condicao: Posicao valida
// Pos-condicao: Retorna o valor do elemento
int busca(Matriz* M, int linha, int coluna) {
  if (linha > M->nlinhas || coluna > M->ncolunas) {
    printf("Posicao invalida (%dx%d)\n\n", linha, coluna);
    return (int)NULL;
  }

  Celula* c;
  Celula* aux;

  for (c = M->cabeca->abaixo; c != M->cabeca; c = c->abaixo) {
    for (aux = c->direita; aux != c; aux = aux->direita) {
      if (aux->linha == linha && aux->coluna == coluna)
        return aux->valor;
    }
  }
  return 0;
}

// Soma os elementos de duas matrizes
// Pre-condicao: As matrizes devem posssuir mesma ordem
// Pos-condicao: Retorna nova matriz gerada pela soma
Matriz* somar(Matriz* A, Matriz* B) {
  if (A->nlinhas != B->nlinhas || A->ncolunas != B->ncolunas) {
    printf("As matrizes devem possuir mesma ordem\n\n");
    return NULL;
  }

  int nl = A->nlinhas;
  int nc = B->ncolunas;
  Matriz* M = cria_matriz(nl, nc);

  int i, j, aux;
  for (i = 1; i <= nl; i++)
    for (j = 1; j <= nc; j++) {
      aux = busca(A, i, j) + busca(B, i, j);
      if (aux != 0)
        M = inserir(M, i, j, aux);
    }
  return M;
}

// Subtrai os elementos de duas matrizes
// Pre-condicao: As matrizes devem posssuir mesma ordem
// Pos-condicao: Retorna nova matriz gerada pela subtracao
Matriz* subtrair(Matriz* A, Matriz* B) {
  int nl = A->nlinhas;
  int nc = B->ncolunas;
  Matriz* M = cria_matriz(nl, nc);

  int i, j, aux;
  for (i = 1; i <= nl; i++)
    for (j = 1; j <= nc; j++) {
      aux = busca(A, i, j) - busca(B, i, j);
      if (aux != 0)
        M = inserir(M, i, j, aux);
    }
  return M;
}

// Multiplica duas matrizes
// Pre-condicao: As matrizes devem posssuir ordens compativeis
// Pos-condicao: Retorna nova matriz gerada pela multiplicaco
Matriz* multiplicar(Matriz* A, Matriz* B) {
  int nl = A->nlinhas;
  int nc = B->ncolunas;
  Matriz* M = cria_matriz(nl, nc);

  int i, j, k, aux;
  for (i = 1; i <= nl; i++)
    for (j = 1; j <= nc; j++) {
      aux = 0;
      for (k = 1; k <= B->nlinhas; k++)
        aux += busca(A, i, k) * busca(B, k, j);

      if (aux != 0)
        M = inserir(M, i, j, aux);
    }
  return M;
}

// Gera a transposta de uma Matriz
// Pre-condicao: Nenhuma
// Pos-condicao: Retorna a matriz gerada
Matriz* transposta(Matriz* M) {
  Matriz* T = cria_matriz(M->ncolunas, M->nlinhas);

  int i, j;
  for (i = 1; i <= M->ncolunas; i++)
    for (j = 1; j <= M->nlinhas; j++)
      T = inserir(T, i, j, busca(M, j, i));

  return T;
}

// Retorna 1 se a matriz for simetrica e 0 se nao for
// Pre-condicao: Nenhuma
// Pos-condicao: Retorna 0 ou 1
int simetrica(Matriz* M) {
  int i, j;
  for (i = 1; i <= M->ncolunas; i++)
    for (j = 1; j <= M->nlinhas; j++)
      if (busca(M, i, j) != busca(M, j, i))
        return 0;
  return 1;
}

// Imprime na tela se uma matriz eh simetrica ou nao
// Pre-condicao: Matriz deve ser de ordem compativel (nxn)
// Pos-condicao: Imprime na tela sim ou nao
void is_simetrica(Matriz* M) {
  if (simetrica(M))
    printf("simetrica: SIM\n");
  else
    printf("simetrica: NAO\n");
}

// Carrega apenas uma matriz para memoria a partir de um arquivo .txt
// Pre-condicao: Arquivo .txt
// Pos-condicao: Retorna a matriz lida
Matriz* ler_matriz(char arq[20], int flag) {
  FILE* f = fopen(arq, "r");
  if (f == NULL)
    printf("erro ao abrir arquivo\n");

  char str[20];
  if (flag) fscanf(f, "%s ", str);

  int nl, nc, valor;
  fscanf(f, "%dx%d ", &nl, &nc);
  Matriz* M = cria_matriz(nl, nc);
  printf("%dx%d\n", M->nlinhas, M->ncolunas);

  char* info;
  int linha, coluna;
  while (!feof(f)) {
    fscanf(f, "%s ", str);

    if (strcmp(str, "fim") == 0)
      break;

    info = strtok(str, ",");
    linha = atoi(info);

    info = strtok(NULL, ",");
    coluna = atoi(info);

    info = strtok(NULL, ",");
    valor = atoi(info);

    M = inserir(M, linha, coluna, valor);
  }
  fclose(f);
  return M;
}

// Carrega por passagem de parametro apenas duas matrizes para memoria a partir de um arquivo .txt
// Pre-condicao: Arquivo .txt e duas matrizes
// Pos-condicao: Altera as duas matrizes passadas para as matrizes lidas
void ler_matriz2(Matriz** A, Matriz** B, char arq[20], int flag) {
  FILE* f = fopen(arq, "r");
  if (f == NULL)
    printf("erro ao abrir arquivo\n");

  char str[20];
  if (flag) fscanf(f, "%s ", str);

  int nl, nc, valor;
  fscanf(f, "%dx%d ", &nl, &nc);
  *A = cria_matriz(nl, nc);

  char* info;
  int linha, coluna;
  while (!feof(f)) {
    fscanf(f, "%s ", str);

    if (strcmp(str, "fim") == 0)
      break;

    info = strtok(str, ",");
    linha = atoi(info);

    info = strtok(NULL, ",");
    coluna = atoi(info);

    info = strtok(NULL, ",");
    valor = atoi(info);

    *A = inserir(*A, linha, coluna, valor);
  }

  fscanf(f, "%dx%d ", &nl, &nc);
  *B = cria_matriz(nl, nc);
  while (!feof(f)) {
    fscanf(f, "%s ", str);

    if (strcmp(str, "fim") == 0)
      break;

    info = strtok(str, ",");
    linha = atoi(info);

    info = strtok(NULL, ",");
    coluna = atoi(info);

    info = strtok(NULL, ",");
    valor = atoi(info);

    *B = inserir(*B, linha, coluna, valor);
  }
  fclose(f);
}

// Imprime todos os elementos de uma Matriz
// Pre-condicao: Nenhuma
// Pos-condicao: Imprime todos os elementos da Matriz
void imprime(Matriz* M) {
  Celula* c;
  Celula* aux;

  int i;

  for (c = M->cabeca->abaixo; c != M->cabeca; c = c->abaixo) {
    for (i = 0, aux = c->direita; aux != c; i++) {
      if (aux->coluna - 1 == i) {
        printf("%5.d", aux->valor);
        aux = aux->direita;
      } else
        printf("    0");
    }
    for (; i < M->ncolunas; i++)
      printf("    0");
    printf("\n");
  }
  printf("\n");
}
