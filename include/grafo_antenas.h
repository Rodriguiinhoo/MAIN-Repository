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
 * @param matrizVisitados Matriz de controle de visitados.
 */
void dfs(Vertice *v, int matrizVisitados[100][100]);

/**
 * @brief Realiza busca em largura (BFS) a partir de um vértice.
 * @param v Vértice inicial.
 * @param matrizVisitados Matriz de controle de visitados.
 */
void bfs(Vertice *v, int matrizVisitados[100][100]);

/**
 * @brief Procura interseções entre antenas de duas frequências.
 * @param grafo Lista de vértices do grafo.
 * @param f1 Primeira frequência.
 * @param f2 Segunda frequência.
 */
void intersecoes(Vertice *grafo, char f1, char f2);

/**
 * @brief Guarda o grafo em um ficheiro binário.
 * @param grafo Ponteiro para o grafo.
 * @param nomeFicheiro Nome do ficheiro.
 * @return 1 se sucesso, 0 caso contrário.
 */
int guardarGrafoBinario(Grafo *grafo, const char *nomeFicheiro);

/**
 * @brief Carrega um grafo de um ficheiro binário.
 * @param nomeFicheiro Nome do ficheiro.
 * @return Ponteiro para o grafo carregado.
 */
Grafo* carregarGrafoBinario(const char *nomeFicheiro);

/**
 * @brief Liberta toda a memória ocupada pelo grafo.
 * @param grafo Ponteiro para o grafo.
 */
void libertarGrafo(Grafo *grafo);

#endif