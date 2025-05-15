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
     struct Antena *prox; ///< Ponteiro para a próxima antena na lista.
 } Antena;

 typedef struct CreateVertice{
       Antena *antena; ///< Ponteiro para a antena associada ao vértice.
       struct CreateVertice *proxvertice; ///< Ponteiro para o próximo vértice na lista.
       struct Aresta *arestas; ///< Ponteiro para a lista de arestas do vértice.
 } CreateVertice;

   typedef struct Aresta{
         CreateVertice *destino; ///< Ponteiro para o vértice de destino da aresta.
         struct Aresta *proxaresta; ///< Ponteiro para a próxima aresta na lista.
   } Aresta;

   typedef struct Grafo{
         CreateVertice *listvertices; ///< Ponteiro para a lista de vértices do grafo.
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