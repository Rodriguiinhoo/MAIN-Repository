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

// Funcao para ler um ficheiro e carregar as antenas, armazenando as antenas numa lista
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

    // Ler o ficheiro linha por linha
    while (fgets(linha, sizeof(linha), file)) {  
        for (int y = 0; linha[y] != '\n' && linha[y] != '\0'; y++) {  // Iterar pelas colunas
            if (linha[y] == 'A' || linha[y] == '0') {  
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

// Funcao para inserir uma antena nova na lista de antenas
/**
    \brief Função para inserir uma antena na lista de antenas
    \param lista Lista de antenas
    \param frequencia Frequencia da antena
    \param x Coordenada x da antena
    \param y Coordenada y da antena
    \return Retorna a lista de antenas com a nova antena inserida
*/
Antena* inserirAntenaInicio(Antena *lista, int frequencia, int x, int y){
    Antena *nova = (Antena *)malloc(sizeof(Antena));
    if (nova == NULL){
        printf("Erro ao alocar memoria para a antena\n");
        return lista;
    }
    nova->frequencia = frequencia;
    nova->x = x;
    nova->y = y;
    nova->prox = lista; // insere no início da lista
    return nova;
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
    // olhe nao sei fazer
    //zona para implementacao das zonas de efeito nefasto
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