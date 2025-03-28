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

// Funcao para ler um ficheiro e carregar as antenas, armazenando as antenas numa lista
/**
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
                lista = inserirAntenaInicio(lista, linha[x], x , y);
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


EfeitoNefasto *adicionarEfeito(EfeitoNefasto *lista, char frequencia, int x, int y) {
    // Aloca memória para o novo nó
    EfeitoNefasto *novo = (EfeitoNefasto *)malloc(sizeof(EfeitoNefasto));
    if (novo == NULL) {
        printf("Erro ao alocar memória para efeito nefasto.\n");
        return lista;
    }

    // Preenche os dados do novo efeito
    novo->frequencian = frequencia;
    novo->x = x;
    novo->y = y;
    novo->prox = lista; // Insere no início da lista

    return novo;
}

/**
 * @brief Funcao para detetar em que locais existem efeitos nefastos
 * 
 * @param lista 
 * @return Retorna a lista de efeitos nefastos 
 */

// Função para calcular os efeitos nefastos
EfeitoNefasto* calcularEfeitosNefastos(Antena *lista) {
    EfeitoNefasto *efeitos = NULL;

    for (Antena *a1 = lista; a1; a1 = a1->prox) {
        for (Antena *a2 = a1->prox; a2; a2 = a2->prox) { // Evita comparações redundantes
            if (a1->frequencia == a2->frequencia) { // Só comparam antenas com a mesma frequência
                // Caso estejam na mesma linha (y é igual)
                if (a1->y == a2->y) {
                    int menorX = (a1->x < a2->x) ? a1->x : a2->x;
                    int maiorX = (a1->x > a2->x) ? a1->x : a2->x;

                    // Adiciona efeitos antes da primeira antena e depois da segunda
                    efeitos = adicionarEfeito(efeitos, menorX - 1, a1->y); // Antes da primeira antena
                    efeitos = adicionarEfeito(efeitos, maiorX + 1, a1->y); // Depois da segunda antena
                }
                // Caso estejam na mesma coluna (x é igual)
                else if (a1->x == a2->x) {
                    int menorY = (a1->y < a2->y) ? a1->y : a2->y;
                    int maiorY = (a1->y > a2->y) ? a1->y : a2->y;

                    // Adiciona efeitos acima da primeira antena e abaixo da segunda
                    efeitos = adicionarEfeito(efeitos, a1->x, menorY - 1); // Acima da primeira antena
                    efeitos = adicionarEfeito(efeitos, a1->x, maiorY + 1); // Abaixo da segunda antena
                }
                // Caso estejam na mesma diagonal
                else if (abs(a1->x - a2->x) == abs(a1->y - a2->y)) {
                    int menorX = (a1->x < a2->x) ? a1->x : a2->x;
                    int maiorX = (a1->x > a2->x) ? a1->x : a2->x;
                    int menorY = (a1->y < a2->y) ? a1->y : a2->y;
                    int maiorY = (a1->y > a2->y) ? a1->y : a2->y;

                    // Adiciona efeitos nas posições diagonais adjacentes
                    efeitos = adicionarEfeito(efeitos, menorX - 1, menorY - 1); // Antes da primeira antena (diagonal superior esquerda)
                    efeitos = adicionarEfeito(efeitos, maiorX + 1, maiorY + 1); // Depois da segunda antena (diagonal inferior direita)
                }
            }
        }
    }

    return efeitos;
}

/**
 * @brief funcao para listar efeitos nefastos
 * 
 * @param lista 
 */
void listarEfeitosNefastos(EfeitoNefasto *lista) {
    if (lista == NULL) {
        printf("Nenhum efeito nefasto encontrado.\n");
        return;
    }

    printf("Efeitos nefastos detectados:\n");
    for (EfeitoNefasto *atual = lista; atual != NULL; atual = atual->prox) {
        printf("Frequência: %c | Posição: (%d, %d)\n", atual->frequencian, atual->x, atual->y);
    }
}

void listarAntenasEEfeitos(Antena *listaAntenas, EfeitoNefasto *listaEfeitos) {
    printf("======================================================================\n");
    printf("|   Antenas                        |   Efeitos Nefastos                  |\n");
    printf("======================================================================\n");
    printf("|  Frequência  |    X    |    Y    |  |  Frequência  |    X    |    Y    |\n");
    printf("======================================================================\n");

    Antena *a = listaAntenas;
    EfeitoNefasto *e = listaEfeitos;

    while (a != NULL || e != NULL) {
        printf("|      %c      |   %3d   |   %3d   |  |      %c      |   %3d   |   %3d   |\n",
               (a != NULL) ? a->frequencia : ' ', (a != NULL) ? a->x : 0, (a != NULL) ? a->y : 0,
               (e != NULL) ? e->frequencian : ' ', (e != NULL) ? e->x : 0, (e != NULL) ? e->y : 0);

        if (a != NULL) a = a->prox;
        if (e != NULL) e = e->prox;
    }

    printf("======================================================================\n");
}



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
