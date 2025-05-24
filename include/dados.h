/*!
 * \file dados.h
 * \brief Arquivo com a definição de duas estruturas: Antena e Efeito Nefasto de uma cidade.
 * 
 * Arquivo com a definição da estrutura Antena e da estrutura Efeito Nefasto de uma cidade.
 * 
 * \author Rodrigo Pinheiro
 * \date 2025
 */

 #ifndef DADOS_H
 #define DADOS_H
 
 /**
  * \brief Estrutura que representa uma antena.
  * 
  * A estrutura Antena contém informações sobre a frequência e a posição
  * (x, y) de uma antena. A variável `prox` é um ponteiro para a próxima
  * antena na lista encadeada.
  */
 typedef struct Antena {
     char frequencia; ///< Frequência da antena.
     int x, y;      ///< Coordenadas da antena (x, y).
     struct Antena *prox; ///< permite criar um ponteiro para o proximo elemento da lista ligada das antenas
 } Antena;

/**
  * @brief Estrutura que representa um vértice do grafo.
  *  * Esta estrutura contém um ponteiro para a antena associada ao vértice,
  *  * um ponteiro para o próximo vértice na lista e um ponteiro para a lista de arestas.
  */
typedef struct Vertice {
    Antena *antena; ///< Ponteiro para antena que vai ser associada ao vertice
    struct Vertice *proxvertice; ///< Ponteiro para o proximo vértice na lista.
    struct Aresta *arestas; ///< Ponteiro para a lista de arestas do vértice.
    int visitado; ///< Flag para indicar se o vértice foi visitado (usado em algoritmos de busca).
} Vertice;

/**
* @brief  Estrutura que representa uma aresta do grafo.
*  * Esta estrutura contém um ponteiro para o vértice de destino e um ponteiro
*  * para a próxima aresta na lista de arestas do vértice.
*/
typedef struct Aresta{
   Vertice *destino; ///< Ponteiro para o vértice de destino da aresta.
   struct Aresta *proxaresta; ///< Ponteiro para a próxima aresta na lista.
} Aresta;

/**
 * @brief Estrutura que representa um grafo.
 * Esta estrutura contém um ponteiro para a lista de vértices do grafo.
 * Cada vértice pode ter várias arestas que o conectam a outros vértices.
 */
typedef struct Grafo{
      Vertice *listvertices; ///< Ponteiro para a lista de vértices do grafo.
} Grafo;


 /**
  * \brief Estrutura que representa um efeito nefasto.
  * 
  * A estrutura EfeitoNefasto contém informações sobre a frequência e a posição
  * (x, y) do efeito. A variável `prox` é um ponteiro para o próximo efeito na lista.
  */
 typedef struct EfeitoNefasto {
     char frequencia; ///< Frequência associada ao efeito nefasto.
     int x, y;       ///< Coordenadas (x, y) do efeito nefasto.
     struct EfeitoNefasto* prox; ///< Ponteiro para o próximo efeito na lista.
 } EfeitoNefasto;
 
 #endif // DADOS_H