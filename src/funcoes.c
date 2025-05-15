/*!
    * \file funcoes.c
    * \brief Implementação das funções de manipulação de antenas
    *   Implementa funcoes:
    *      - criarAntena
    *      - inserirAntena
    *      - removerAntena
    *      - listarAntenas
    *      - carregarAntenasDeFicheiro
    * 
    * \author Rodrigo Henrique Silva Pinheiro
    * \date 2025-03-25
    *
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "dados.h"
#include "funcoes.h"
#include  <ctype.h>
#include <string.h>


/**
    \brief Função para carregar as antenas de um ficheiro
    \param nomeficheiro Nome do ficheiro a ser lido
    \return Retorna a lista de antenas lidas do ficheiro
*/
Antena* lerFicheiro(const char *nomeFicheiro) {
    FILE *file = fopen(nomeFicheiro, "r");
    if (!file) {
        printf("Erro ao abrir o ficheiro!\n");
        return NULL;
    }

    Antena *lista = NULL;
    char linha[100];  // Buffer maior, se o ficheiro for maior que 20 caracteres por linha
    int x = 0;        // Contador de linhas (coordenada X)
    int y = 0;        // Contador de colunas (coordenada Y)

    // Ler o ficheiro linha por linha
    while (fgets(linha, sizeof(linha), file)) {  
        for (int y = 0; linha[y] != '\n' && linha[y] != '\0'; y++) { // Percorre cada caractere da linha
            if (linha[y] == 'A' || linha[y] == '0') {  // Verifica se é A ou 0
                // Criar uma nova antena
                Antena *nova = (Antena*)malloc(sizeof(Antena));
                if (nova == NULL) {
                    printf("Erro ao alocar memória para uma nova antena!\n");
                    fclose(file);
                    return NULL;
                }
                nova->y = y;  // Y é a coluna
                nova->x = x;  // X é a linha
                nova->frequencia = linha[y];  // Guardar a frequência (A ou 0)
                nova->prox = lista;           // Adicionar à lista
                lista = nova;
            }
        }
        x++;  // Avança para a próxima linha
    }
    fclose(file);
    return lista;
}

/**
 * @brief Insere uma antena na lista de forma ordenada (por X e Y)
 * 
 * @param lista Lista de antenas (pode ser NULL se lista vazia)
 * @param frequencia Frequência da antena (caractere)
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Antena* Nova cabeça da lista
 */
Antena* inserirAntenaOrdenada(Antena *lista, char frequencia, int x, int y) {

    Antena *nova = (Antena *)malloc(sizeof(Antena));
    if (nova == NULL) {
        printf("Erro ao alocar memória para a antena\n");
        return lista;
    }
    
    // Preenche os dados da nova antena
    nova->frequencia = frequencia;
    nova->x = x;
    nova->y = y;
    nova->prox = NULL;

    // Caso 1: Lista vazia ou nova antena deve ser a primeira
    if (lista == NULL || (x < lista->x) || (x == lista->x && y < lista->y)) {
        nova->prox = lista;
        return nova;
    }

    // Caso 2: Busca a posição correta na lista
    Antena *atual = lista;
    while (atual->prox != NULL && 
          ((atual->prox->x < x) || (atual->prox->x == x && atual->prox->y < y))) {
        atual = atual->prox;
    }

    // Insere a nova antena na posição encontrada
    nova->prox = atual->prox;
    atual->prox = nova;

    return lista;
}


/**
 * @brief  Funcao para adicionar um efeito nefasto a lista de efeitos nefastos
 * 
 * @param lista 
 * @param frequencia 
 * @param x 
 * @param y 
 * @return EfeitoNefasto* 
 */
EfeitoNefasto* adicionarEfeito(EfeitoNefasto *lista, int frequencia, int x, int y) {
    EfeitoNefasto *novo = (EfeitoNefasto *)malloc(sizeof(EfeitoNefasto));
    if (novo == NULL) {
        printf("Erro ao alocar memória para o efeito nefasto.\n");
        return lista;
    }

    novo->frequencia = frequencia;
    novo->x = x;
    novo->y = y;
    novo->prox = lista;

    return novo;
}

/**
 * @brief Funcao para detetar em que locais existem efeitos nefastos
 * 
 * @param lista Lista de antenas
 * @return Retorna a lista de efeitos nefastos 
 */
EfeitoNefasto* calcularEfeitosNefastos(Antena *listaAntenas) {
    EfeitoNefasto *listaEfeitos = NULL;
    
    // Percorre todas as combinações de pares de antenas
    for (Antena *antena1 = listaAntenas; antena1 != NULL; antena1 = antena1->prox) {
        for (Antena *antena2 = antena1->prox; antena2 != NULL; antena2 = antena2->prox) {
            
            // Verifica se as antenas têm a mesma frequência
            if (antena1->frequencia == antena2->frequencia) {
                
                // Verifica alinhamento horizontal (mesma linha)
                if (antena1->x == antena2->x) {
                    int distancia = abs(antena1->y - antena2->y);
                    
                    if (distancia <= 1) { 
                        int y_efeito1 = antena1->y + 1;
                        int y_efeito2 = antena1->y + 1;
                        
                        // Adiciona os efeitos nefastos à lista
                        listaEfeitos = adicionarEfeito(listaEfeitos, antena1->frequencia, antena1->x, y_efeito1);
                        listaEfeitos = adicionarEfeito(listaEfeitos, antena1->frequencia, antena1->x, y_efeito2);
                    }
                }
                
                // Verifica alinhamento vertical (mesma coluna)
                if (antena1->y == antena2->y) {
                    int distancia = abs(antena1->x - antena2->x);
                    
                    if (distancia <= 1) {
                        int x_efeito1 = antena1->x + 1;
                        int x_efeito2 = antena1->x + 1;
                        
                        // Adiciona os efeitos nefastos à lista
                        listaEfeitos = adicionarEfeito(listaEfeitos, antena1->frequencia, x_efeito1, antena1->y);
                        listaEfeitos = adicionarEfeito(listaEfeitos, antena1->frequencia, x_efeito2, antena1->y);
                    }
                }
                
                // Verifica alinhamento diagonal (mesma inclinação)
                if (abs(antena1->x - antena2->x) == abs(antena1->y - antena2->y)) {
                    int distancia = abs(antena1->x - antena2->x);
                    
                    if (distancia <= 1) {
                        // Calcula pontos intermediários na diagonal
                        int x_efeito1 = antena1->x - 1;
                        int y_efeito1 = antena1->y - 1;
                        int x_efeito2 = antena1->x + 1;
                        int y_efeito2 = antena1->y + 1;
                        
                        // Adiciona os efeitos nefastos à lista
                        listaEfeitos = adicionarEfeito(listaEfeitos, antena1->frequencia, x_efeito1, y_efeito1);
                        listaEfeitos = adicionarEfeito(listaEfeitos, antena1->frequencia, x_efeito2, y_efeito2);
                    }
                }
            }
        }
    }
    
    return listaEfeitos;
}


/**
 * @brief  Lista todas as antenas
 * 
 * @param listaAntenas 
 */
void listarAntenas(Antena *listaAntenas) {
    printf("LISTA DE ANTENAS:\n");
    printf("Frequência |    X    |    Y\n");
    printf("-----------------------------------------\n");

    for (Antena *a = listaAntenas; a != NULL; a = a->prox) {
        printf("     %c      |   %3d   |   %3d\n", a->frequencia, a->x, a->y);
    }

    printf("=========================================\n");
}

/**
 * @brief  Lista todos os efeitos nefastos
 * 
 * @param listaEfeitos 
 */
void listarEfeitos(EfeitoNefasto *listaEfeitos) {
    printf("LISTA DE EFEITOS NEFASTOS:\n");
    printf("Frequência |    X    |    Y\n");
    printf("-----------------------------------------\n");

    for (EfeitoNefasto *e = listaEfeitos; e != NULL; e = e->prox) {
        printf("     %c      |   %3d   |   %3d\n", e->frequencia, e->x, e->y);
    }

    printf("=========================================\n");
}

void adicionarArestas(Grafo* g) {
    for (CreateVertice* v1 = g->listvertices; v1 != NULL; v1 = v1->proxvertice) {
        for (CreateVertice* v2 = v1->proxvertice; v2 != NULL; v2 = v2->proxvertice) {
            if (v1->antena->frequencia == v2->antena->frequencia) {
                // criar aresta v1 -> v2
                Aresta* novaAresta1 = (Aresta*)malloc(sizeof(Aresta));
                novaAresta1->destino = v2;
                // criar aresta v2 -> v1 (grafo não direcionado)
                Aresta* novaAresta2 = (Aresta*)malloc(sizeof(Aresta));
                novaAresta2->destino = v1;
            }
        }
    }
}

Grafo* criarGrafo(Antena* listaAntenas) {
    Grafo *g = (Grafo*)malloc(sizeof(Grafo));
    g->listvertices = NULL;

    // 1. Para cada antena na lista, cria um vértice
    for (Antena *a = listaAntenas; a != NULL; a = a->prox) {
        CreateVertice *v = (CreateVertice*)malloc(sizeof(CreateVertice));
        v->antena = a;
        v->arestas = NULL;
        v->proxvertice = g->listvertices;
        g->listvertices = v;
    }

    // 2. Criar arestas entre antenas com mesma frequência
    for ( CreateVertice *v1 = g->listvertices; v1 != NULL; v1 = v1->proxvertice) {
        for ( CreateVertice *v2 = v1->proxvertice; v2 != NULL; v2 = v2->proxvertice) {
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

void dfs(CreateVertice *v, int *visitado, int **matrizVisitados, int linhas, int colunas) {
    int x = v->antena->x;
    int y = v->antena->y;
    if (matrizVisitados[x][y]) return;
    matrizVisitados[x][y] = 1;
    printf("(%d, %d)\n", x, y);
    for (Aresta *a = v->arestas; a != NULL; a = a->proxaresta) { 
        dfs(a->destino, visitado, matrizVisitados, linhas, colunas);
    }
}

void bfs(CreateVertice *inicio, int linhas, int colunas) {
    int visitado[linhas][colunas];
    memset(visitado, 0, sizeof(visitado));

    CreateVertice *fila[100];
    int frente = 0, tras = 0;

    fila[tras++] = inicio;

    while (frente < tras) { 
        CreateVertice *v = fila[frente++]; 
        int x = v->antena->x, y = v->antena->y;

        if (visitado[x][y]) continue;
        visitado[x][y] = 1;
        printf("(%d, %d)\n", x, y);
        
        for (Aresta *a = v->arestas; a != NULL; a = a->proxaresta) {
            fila[tras++] = a->destino;
        }
    }
}

void intersecoes(CreateVertice *grafo, char f1, char f2) {
    for (CreateVertice *v1 = grafo; v1 != NULL; v1 = v1->proxvertice) {
        for (CreateVertice *v2 = grafo; v2 != NULL; v2 = v2->proxvertice) {
            if (v1 != v2 && v1->antena->frequencia == f1 && v2->antena->frequencia == f2) {
                if (v1->antena->x == v2->antena->x && v1->antena->y == v2->antena->y) {
                    printf("Interseção em (%d, %d)\n", v1->antena->x, v1->antena->y);
                }
            }
        }
    }
}

/**
 * @brief  Liberta a memória da lista de antenas
 * 
 * @param lista 
 */
void libertarListaAntenas(Antena *lista) {
    while (lista) {
        Antena *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

/**
 * @brief  Liberta a memória da lista de efeitos nefastos
 * 
 * @param lista 
 */
void libertarListaEfeitos(EfeitoNefasto *lista) {
    while (lista) {
        EfeitoNefasto *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}