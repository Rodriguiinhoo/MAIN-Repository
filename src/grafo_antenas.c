/*!
    * \file grafo_antenas.c
    * \brief Implementação das funções de manipulação de antenas
    *   Implementa funcoes:
    *      - criarGrafo
    *      - adicionarArestas
    *     - dfs
    *     - bfs
    *      - resetarVisitados
    *      - intersecoes
    *      - guardarGrafoBinario
    * \author Rodrigo Henrique Silva Pinheiro
    * \date 2025-03-25
    *
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "dados.h"
#include  <ctype.h>
#include <string.h>

#include "../include/grafo_antenas.h"
#include "../include/dados.h"
#include "../include/lista_antenas.h"

/**
 * @brief  Adiciona arestas entre antenas com a mesma frequência
 * 
 * @param g 
 */
void adicionarArestas(Grafo* g) {
    for (Vertice* v1 = g->listvertices; v1 != NULL; v1 = v1->proxvertice) { // percorre a lista de vértices
        for (Vertice* v2 = v1->proxvertice; v2 != NULL; v2 = v2->proxvertice) { // percorre a lista de vértices a partir do próximo
            if (v1->antena->frequencia == v2->antena->frequencia) {
                // criar aresta v1 -> v2
                Aresta* novaAresta1 = (Aresta*)malloc(sizeof(Aresta));
                novaAresta1->destino = v2;
                novaAresta1->proxaresta = v1->arestas;
                v1->arestas = novaAresta1;

                // criar aresta v2 -> v1 (grafo não direcionado)
                Aresta* novaAresta2 = (Aresta*)malloc(sizeof(Aresta));
                novaAresta2->destino = v1;
                novaAresta2->proxaresta = v2->arestas;
                v2->arestas = novaAresta2;
            }
        }
    }
}

/**
 * @brief  Cria um grafo a partir de uma lista de antenas
 * 
 * @param listaAntenas 
 * @return Grafo* 
 */
Grafo* criarGrafo(Antena* listaAntenas) {
    Grafo *g = (Grafo*)malloc(sizeof(Grafo));
    g->listvertices = NULL;

    // 1. Para cada antena na lista, cria um vértice
    for (Antena *a = listaAntenas; a != NULL; a = a->prox) {
        Vertice *v = (Vertice*)malloc(sizeof(Vertice));
        v->antena = a;
        v->arestas = NULL;
        v->proxvertice = g->listvertices;
        g->listvertices = v;
    }

    // 2. Criar arestas entre antenas com mesma frequência
    for (Vertice *v1 = g->listvertices; v1 != NULL; v1 = v1->proxvertice) {
        for (Vertice *v2 = v1->proxvertice; v2 != NULL; v2 = v2->proxvertice) {
            if (v1->antena->frequencia == v2->antena->frequencia) {
                // Cria ligação v1 -> v2
                Aresta *a1 = (Aresta*)malloc(sizeof(Aresta));
                a1->destino = v2;
                a1->proxaresta = v1->arestas;
                v1->arestas = a1;

                // Cria ligação v2 -> v1
                Aresta *a2 = (Aresta*)malloc(sizeof(Aresta));
                a2->destino = v1;
                a2->proxaresta = v2->arestas;
                v2->arestas = a2;
            }
        }
    }

    return g;
}


/**
 * @brief Realiza uma busca em profundidade (DFS) no grafo
 * 
 * @param  v Vértice inicial
 * @return void
 */
void dfs(Vertice *v) {
    if (v->visitado) return;
    printf("(%d, %d)\n", v->antena->x, v->antena->y);
    v->visitado = 1;
    for (Aresta *a = v->arestas; a != NULL; a = a->proxaresta) {
        dfs(a->destino);
    }
}

/**
 * @brief  Reseta os vértices visitados
 * 
 * @param g 
 */
void resetarVisitados(Grafo *g) {
    for (Vertice *v = g->listvertices; v != NULL; v = v->proxvertice)
        v->visitado = 0;
}

/**
 * @brief liberta a memória alocada para o grafo
 * 
 * @param grafo 
 */
void libertarGrafo(Grafo *grafo) {
    if (grafo == NULL) return;

    Vertice *v = grafo->listvertices;
    while (v != NULL) {
        Aresta *a = v->arestas;
        while (a != NULL) {
            Aresta *temp = a;
            a = a->proxaresta;
            free(temp);
        }
        Vertice *temp = v;
        v = v->proxvertice;
        free(temp);
    }
    free(grafo);
}