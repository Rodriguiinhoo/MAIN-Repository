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
 * @param nomeFicheiro 
 * @return Grafo* 
 */
void dfs(Vertice *v, int matrizVisitados[100][100]) {
    int x = v->antena->x;
    int y = v->antena->y;
    if (matrizVisitados[x][y]) return;
    matrizVisitados[x][y] = 1;
    printf("(%d, %d)\n", x, y);
    for (Aresta *a = v->arestas; a != NULL; a = a->proxaresta) { 
        dfs(a->destino, matrizVisitados);
    }
}

/**
 * @brief Realiza uma busca em largura (BFS) no grafo
 * 
 * @param v 
 * @param matrizVisitados 
 */
void bfs(Vertice *v, int matrizVisitados[100][100]) {
    Vertice *fila[100];
    int frente = 0, tras = 0;
    fila[tras++] = v;

    while (frente < tras) { 
        Vertice *v = fila[frente++]; 
        int x = v->antena->x, y = v->antena->y;

        if (matrizVisitados[x][y]) continue;
        matrizVisitados[x][y] = 1;
        printf("(%d, %d)\n", x, y);
        
        for (Aresta *a = v->arestas; a != NULL; a = a->proxaresta) {
            fila[tras++] = a->destino;
        }
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
 * @brief  Encontra todos os caminhos entre dois vértices
 * 
 * @param grafo 
 * @param f1 
 * @param f2 
 */
void intersecoes(Vertice *grafo, char f1, char f2) {
    int encontrou = 0;
    if (grafo == NULL) {
        printf("Grafo vazio!\n");
        return;
    }
    for (Vertice *v1 = grafo; v1 != NULL; v1 = v1->proxvertice) {
        for (Vertice *v2 = grafo; v2 != NULL; v2 = v2->proxvertice) {
            if (v1 != v2 && v1->antena->frequencia == f1 && v2->antena->frequencia == f2) {
                if (v1->antena->x == v2->antena->x && v1->antena->y == v2->antena->y) {
                    printf("Interseção em (%d, %d)\n", v1->antena->x, v1->antena->y);
                    encontrou = 1;
                }
            }
        }
    }
    if (!encontrou) {
        printf("Nenhuma interseção encontrada entre as frequências %c e %c.\n", f1, f2);
    }
}

/**
 * @brief guarda um grafo dentro ficheiro binário
 * 
 * @param grafo 
 * @param nomeFicheiro 
 * @return int 
 */
int guardarGrafoBinario(Grafo *grafo, const char *nomeFicheiro) {
    if (!grafo || !nomeFicheiro) return 0;

    FILE *f = fopen(nomeFicheiro, "wb");
    if (!f) {
        printf("Erro ao abrir o ficheiro para escrita!\n");
        return 0;
    }

    // Contar vértices
    int numVertices = 0;
    for (Vertice *v = grafo->listvertices; v != NULL; v = v->proxvertice)
        numVertices++;

    fwrite(&numVertices, sizeof(int), 1, f);

    // Guardar antenas
    Vertice **verticesArray = (Vertice **)malloc(numVertices * sizeof(Vertice *));
    int idx = 0;
    for (Vertice *v = grafo->listvertices; v != NULL; v = v->proxvertice) {
        verticesArray[idx++] = v;
        fwrite(&(v->antena->frequencia), sizeof(char), 1, f);
        fwrite(&(v->antena->x), sizeof(int), 1, f);
        fwrite(&(v->antena->y), sizeof(int), 1, f);
    }

    // Guardar arestas (como índices)
    for (int i = 0; i < numVertices; i++) {
        // Contar arestas
        int numArestas = 0;
        for (Aresta *a = verticesArray[i]->arestas; a != NULL; a = a->proxaresta)
            numArestas++;
        fwrite(&numArestas, sizeof(int), 1, f);

        for (Aresta *a = verticesArray[i]->arestas; a != NULL; a = a->proxaresta) {
            // Encontrar índice do destino
            int idxDestino = -1;
            for (int j = 0; j < numVertices; j++) {
                if (a->destino == verticesArray[j]) {
                    idxDestino = j;
                    break;
                }
            }
            fwrite(&idxDestino, sizeof(int), 1, f);
        }
    }

    free(verticesArray);
    fclose(f);
    return 1;
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