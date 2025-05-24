/**!
 * \file grafo_antenas.h
 * \brief Arquivo de cabeçalho para o grafo de antenas.
 */

#ifndef GRAFO_ANTENAS_H
#define GRAFO_ANTENAS_H

#include "dados.h"

/**
 * @brief Cria um grafo a partir de uma lista de antenas.
 * @param listaAntenas Ponteiro para a lista de antenas.
 * @return Ponteiro para o grafo criado.
 */
Grafo* criarGrafo(Antena* listaAntenas);

/**
 * @brief Realiza busca em profundidade (DFS) a partir de um vértice.
 * @param v Vértice inicial.
 */
void dfs(Vertice *v);

/**
 * @brief Funcao para adicionar arestas
 * 
 * @param g 
 */
void adicionarArestas(Grafo* g);

/**
 * @brief Funcao para resetar os Vertices visitados
 * 
 * @param g 
 */
void resetarVisitados(Grafo *g);

/**
 * @brief Liberta toda a memória ocupada pelo grafo.
 * @param grafo Ponteiro para o grafo.
 */
void libertarGrafo(Grafo *grafo);

#endif