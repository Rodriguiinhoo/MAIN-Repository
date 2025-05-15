/*!
 * \file funcoes.h
 * \brief Ficheiro header com as funções.
 * \author Rodrigo Henrique Silva Pinheiro
 * \date 2025-03-25
 */

 #ifndef FUNCOES_H
 #define FUNCOES_H
 
 #include "dados.h"
 
 // Menu principal
 int menu();
 
 /*!
  * \brief Carrega antenas de um ficheiro.
  * \param nomeficheiro Nome do ficheiro a ser lido.
  * \return Retorna a lista de antenas carregadas.
  */
Antena* lerFicheiro(const char *nomeFicheiro);

 /*!
  * \brief Insere uma antena no início da lista.
  * \param lista Lista de antenas.
  * \param frequencia Frequência da antena.
  * \param x Coordenada X da antena.
  * \param y Coordenada Y da antena.
  * \param posicao Posição da antena na lista.
  * \return Retorna a lista de antenas com a nova antena inserida.
  */
Antena* inserirAntena(Antena *lista, int frequencia, int x, int y, int posicao);
 
 /**
  * @brief Construct a new adicionar Efeito object
  * 
  * @param lista 
  * @param frequencia 
  * @param x 
  * @param y 
  */
EfeitoNefasto* adicionarEfeito(EfeitoNefasto *lista, int frequencia, int x, int y);

 /**
  * \brief Calcula os locais com efeitos nefastos.
  * \param lista Lista de antenas.
  * \return Retorna a lista de efeitos nefastos calculados.
  */
EfeitoNefasto* calcularEfeitosNefastos(Antena *lista);

// Adicione estas declarações em funcoes.h
Grafo* criarGrafo(Antena* listaAntenas);

void dfs(CreateVertice *v, int *visitado, int **matrizVisitados, int linhas, int colunas);

void bfs(CreateVertice *inicio, int linhas, int colunas);

void intersecoes(CreateVertice *grafo, char f1, char f2);
 
 /**
  * \brief Lista todas as antenas.
  * \param lista Lista de antenas.
  */
void listarAntenas(Antena *lista);
 
 /**
  * \brief Lista todos os efeitos nefastos.
  * \param lista Lista de efeitos nefastos.
  */
void listarEfeitos(EfeitoNefasto *lista);
 
 /**
  * \brief Liberta a memória da lista de antenas.
  * \param lista Lista de antenas.
  */
void libertarListaAntenas(Antena *lista);
 
 /**
  * \brief Liberta a memória da lista de efeitos nefastos.
  * \param lista Lista de efeitos.
  */
void libertarListaEfeitos(EfeitoNefasto *lista);
 
 #endif // FUNCOES_H