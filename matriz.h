#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

// Estrutura celula para criacao da estrutura matriz
typedef struct celula {
  int linha, coluna;
  struct celula* direita;
  struct celula* abaixo;
  int valor;  // Valor do elemento na posicao (linha, coluna)
} Celula;

// Estrutura matriz com lista encadeada dupla circular
typedef struct {
  int nlinhas, ncolunas;  // Armazena numero de linhas e colunas de uma matriz
  Celula* cabeca;         // Ponteiro do tipo Celula para cabeca da matriz
} Matriz;

// Funcao auxiliar para criar matriz vazia
// Pre-condicao: Ponteiro para cabeca da matriz nao nulo e numero de colunas a serem criadas
// Pos-condicao: Retorna a cabeca da lista encadeada com o numero de colunas que foi solicitado
Celula* cria_direita(Celula* cabeca, Celula* c, int n);

// Funcao auxiliar para criar matriz vazia
// Pre-condicao: Ponteiro para cabeca da matriz nao nulo e numero de linhas a serem criadas
// Pos-condicao: Retorna a cabeca da lista encadeada com o numero de linhas que foi solicitado
Celula* cria_abaixo(Celula* cabeca, Celula* c, int n);

// Cria uma matriz vazia devidamente inicializada
// Pre-condicao: Nenhuma
// Pos-condicao: Retorna um ponteiro do tipo Matriz
Matriz* cria_matriz(int nlinhas, int ncolunas);

// Insere um elemento do tipo celula na matriz esparsa
// Pre-condicao: Ponteiro para Matriz nao nulo
// Pos-condicao: Retorna a Matriz com o elemento inserido
Matriz* inserir(Matriz* M, int linha, int coluna, int info);

// Funcao auxiliar que busca um elemento atraves de sua posicao(mxn) numa estrutra Matriz
// Pre-condicao: Posicao valida
// Pos-condicao: Retorna o valor do elemento
int busca(Matriz* M, int linha, int coluna);

// Soma os elementos de duas matrizes
// Pre-condicao: As matrizes devem posssuir mesma ordem
// Pos-condicao: Retorna nova matriz gerada pela soma
Matriz* somar(Matriz* A, Matriz* B);

// Subtrai os elementos de duas matrizes
// Pre-condicao: As matrizes devem posssuir mesma ordem
// Pos-condicao: Retorna nova matriz gerada pela subtracao
Matriz* subtrair(Matriz* A, Matriz* B);

// Multiplica duas matrizes
// Pre-condicao: As matrizes devem posssuir ordens compativeis
// Pos-condicao: Retorna nova matriz gerada pela multiplicaco
Matriz* multiplicar(Matriz* A, Matriz* B);

// Gera a transposta de uma Matriz
// Pre-condicao: Nenhuma
// Pos-condicao: Retorna a matriz gerada
Matriz* transposta(Matriz* M);

// Retorna 1 se a matriz for simetrica e 0 se nao for
// Pre-condicao: Nenhuma
// Pos-condicao: Retorna 0 ou 1
int simetrica(Matriz* M);

// Imprime na tela se uma matriz eh simetrica ou nao
// Pre-condicao: Matriz deve ser de ordem compativel (nxn)
// Pos-condicao: Imprime na tela sim ou nao
void is_simetrica(Matriz* M);

// Carrega apenas uma matriz para memoria a partir de um arquivo .txt
// Pre-condicao: Arquivo .txt
// Pos-condicao: Retorna a matriz lida
Matriz* ler_matriz(char arq[20], int flag);

// Carrega por passagem de parametro apenas duas matrizes para memoria a partir de um arquivo .txt
// Pre-condicao: Arquivo .txt e duas matrizes
// Pos-condicao: Altera as duas matrizes passadas para as matrizes lidas
void ler_matriz2(Matriz** A, Matriz** B, char arq[20], int flag);

// Imprime todos os elementos de uma estrutura Matriz
// Pre-condicao: Nenhuma
// Pos-condicao: Imprime todos os elementos da Matriz
void imprime(Matriz* M);

#endif  // MATRIZ_H_INCLUDED