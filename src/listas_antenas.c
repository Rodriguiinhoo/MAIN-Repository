/*!
    * \file funcoes.c
    * \brief Implementação das funções de manipulação de antenas
    *   Implementa funcoes:
    *      - criarAntena
    *      - inserirAntena
    *      - listarAntenas
    *      - listarEfeitos
    *     - calcularEfeitosNefastos
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
#include  <ctype.h>
#include <string.h>

#include "../include/lista_antenas.h"
#include "../include/dados.h"


/**
    \brief Função para carregar as antenas de um ficheiro
    \param nomeficheiro Nome do ficheiro a ser lido
    \return Retorna a lista de antenas lidas do ficheiro
*/
Antena* lerFicheiro(const char *nomeFicheiro) {
    FILE *file = fopen(nomeFicheiro, "r");

    Antena *lista = NULL;
    char linha[100];  // Buffer maior, se o ficheiro for maior que 20 caracteres por linha
    int x = 0;        // Contador de linhas (coordenada X)
    int y = 0;        // Contador de colunas (coordenada Y)
    // Ler o ficheiro linha por linha
    while (fgets(linha, sizeof(linha), file)) {  
        for (y = 0; linha[y] != '\n' && linha[y] != '\0'; y++) { // Percorre cada caractere da linha
            if (linha[y] == 'A' || linha[y] == '0') {  // Verifica se é A ou 0
                // Criar uma nova antena
                Antena *nova = (Antena*)malloc(sizeof(Antena));
                nova->y = y;  // Y é a coluna
                nova->x = x;  // X é a linha
                nova->frequencia = linha[y];  // Guardar a frequência (A ou 0)
                lista = inserirAntenaOrdenada(lista, nova->frequencia, nova->x, nova->y);
                free(nova); // nova já foi copiada para dentro da lista ordenada
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
    while (atual->prox != NULL && ((atual->prox->x < x) || (atual->prox->x == x && atual->prox->y < y))) {
        atual = atual->prox;
    }
    // Insere a nova antena na posição encontrada
    nova->prox = atual->prox;
    atual->prox = nova;

    return lista;
}

/**
 * @brief  Remove uma antena da lista com base na frequência e coordenadas
 * 
 * @param lista Lista de antenas
 * @param frequencia Frequência da antena a remover
 * @param x Coordenada X da antena a remover
 * @param y Coordenada Y da antena a remover
 * @return Antena* Nova cabeça da lista (pode ser NULL se lista ficar vazia)
 */
Antena* removerAntenaPorDados(Antena *lista, char frequencia, int x, int y) {
    Antena *anterior = NULL, *atual = lista;
    while (atual) {
        if (atual->frequencia == frequencia && atual->x == x && atual->y == y) {
            if (anterior)
                anterior->prox = atual->prox;
            else
                lista = atual->prox;
            free(atual);
            return lista;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return lista;
}


/**
 * @brief  Funcao para adicionar um efeito nefasto a lista de efeitos nefastos de forma ordenada
 * 
 * @param lista 
 * @param frequencia 
 * @param x 
 * @param y 
 * @return EfeitoNefasto* 
 */
EfeitoNefasto* adicionarEfeitoOrdenado(EfeitoNefasto *lista, int frequencia, int x, int y) {
    EfeitoNefasto *novo = (EfeitoNefasto *)malloc(sizeof(EfeitoNefasto));
    novo->frequencia = frequencia;
    novo->x = x;
    novo->y = y;

    // Caso 1: Inserir no início
    if (lista == NULL || (x < lista->x) || (x == lista->x && y < lista->y)) {
        novo->prox = lista;
        return novo;
    }

    // Caso 2: Inserir no meio/fim
    EfeitoNefasto *atual = lista;
    while (atual->prox != NULL && ((atual->prox->x < x) || (atual->prox->x == x && atual->prox->y < y))) {
        atual = atual->prox;
    }
    
    novo->prox = atual->prox;
    atual->prox = novo;
    return lista;
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
                    if (distancia <= 2) { 
                        int y_efeito1 = antena1->y + 1;
                        int y_efeito2 = antena1->y + 1;
                        
                        // Adiciona os efeitos nefastos à lista
                        listaEfeitos = adicionarEfeitoOrdenado(listaEfeitos, antena1->frequencia, antena1->x, y_efeito1);
                        listaEfeitos = adicionarEfeitoOrdenado(listaEfeitos, antena1->frequencia, antena1->x, y_efeito2);
                    }
                }
                
                // Verifica alinhamento vertical (mesma coluna)
                if (antena1->y == antena2->y) {
                    int distancia = abs(antena1->x - antena2->x);
                    if (distancia <= 2) {
                        int x_efeito1 = antena1->x + 1;
                        int x_efeito2 = antena1->x + 1;
                        
                        // Adiciona os efeitos nefastos à lista
                        listaEfeitos = adicionarEfeitoOrdenado(listaEfeitos, antena1->frequencia, x_efeito1, antena1->y);
                        listaEfeitos = adicionarEfeitoOrdenado(listaEfeitos, antena1->frequencia, x_efeito2, antena1->y);
                    }
                }
                
                // Verifica alinhamento diagonal (mesma inclinação)
                if (abs(antena1->x - antena2->x) == abs(antena1->y - antena2->y)) {
                    int distancia = abs(antena1->x - antena2->x);
                    
                    if (distancia <= 2) {
                        // Calcula pontos intermediários na diagonal
                        int x_efeito1 = antena1->x - 1;
                        int y_efeito1 = antena1->y - 1;
                        int x_efeito2 = antena1->x + 1;
                        int y_efeito2 = antena1->y + 1;
                        
                        // Adiciona os efeitos nefastos à lista
                        listaEfeitos = adicionarEfeitoOrdenado(listaEfeitos, antena1->frequencia, x_efeito1, y_efeito1);
                        listaEfeitos = adicionarEfeitoOrdenado(listaEfeitos, antena1->frequencia, x_efeito2, y_efeito2);
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