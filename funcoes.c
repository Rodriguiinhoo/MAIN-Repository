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

#include "funcoes.h"
#include "dados.h"

// Funcao para ler um ficheiro e carregar as antenas, aramzenando as antenas numa lista
/*!
    \brief Função para carregar as antenas de um ficheiro
    \param nomeficheiro Nome do ficheiro a ser lido
    \return Retorna a lista de antenas lidas do ficheiro
*/

Antena* carregarAntenasDeFicheiro(const char *nomeficheiro){
    FILE *f = fopen(nomeficheiro, "r");
    if(f == NULL){
        printf("Erro ao abrir o ficheiro %s\n", nomeficheiro);
        return NULL;
    }
    
    Antena *lista = NULL;
    char linha[10]; // 10 caracteres é suficiente para guardar uma linha com 3 inteiros e 2 caracteres
    int y = 0;

    while (fgets(linha, sizeof(linha), f)){
        for(int x = 0; linha[x] != '\0' && linha[x] != '\n'; x++){
            if (linha[x] != '.'){ //Assumir que . e um espaco vazio
                lista = inserirAntena(lista, linha[x], x , y);
            }
        }
        y++; // Incrementar a linha, fazendo com que a proxima linha seja a linha seguinte e a contar do 0;
    }
    fclose(f);
    return lista;
}

// Funcao para inserir uma antena nova na lista de antenas
/*!
    \brief Função para inserir uma antena na lista de antenas
    \param lista Lista de antenas
    \param frequencia Frequencia da antena
    \param x Coordenada x da antena
    \param y Coordenada y da antena
    \return Retorna a lista de antenas com a nova antena inserida
*/
Antena* inserirAntenaInicio(Antena *lista, char frequencia, int x, int y){
    Antena *nova = (Antena *)malloc(sizeof(Antena));
    if (nova == NULL){
        printf("Erro ao alocar memoria para a antena\n");
        return lista;
    }
    nova->frequencia = frequencia;
    nova->x = x;
    nova->y = y;
    nova->prox = lista; // insere no inicio da lista
    return nova; // Retorna a nova antena que foi inserida
}

// Funcao auxiliar para iterar a lista de antenas
/*!
    \brief Função auxiliar para listar as antenas
    \param lista Lista de antenas
*/
void listarAntenas(Antena *lista){
    while(lista){
        lista = lista->prox; // Avanca para a proxima antena, ou seja, itera as linhas da lista
    }
}

// Função para calcular locais de efeito nefasto (futura implementação)
EfeitoNefasto* calcularEfeitosNefastos(Antena *lista) {
    
    // Implementar a função para calcular os locais de efeito nefasto
    return NULL;
}

// Listar os efeitos nefastos
void listarEfeitosNefastos(EfeitoNefasto *lista) {
    while (lista) {
        lista = lista->prox; // Avanca para a proxima antena, ou seja, itera as linhas da lista de efeitos nefastos
    }
}

// Funções para liberar memória das listas
void libertarListaAntenas(Antena *lista) {
    while (lista) {
        Antena *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

void libertarListaEfeitos(EfeitoNefasto *lista) {
    while (lista) {
        EfeitoNefasto *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}
