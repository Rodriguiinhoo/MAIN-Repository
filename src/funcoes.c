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
Antena* carregarAntenasDeFicheiro(const char *nomeficheiro) {
    FILE *f = fopen(nomeficheiro, "r");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro %s\n", nomeficheiro);
        return NULL;
    }

    Antena *lista = NULL; // Inicializa a lista de antenas como vazia
    char linha[256];      // Buffer para armazenar cada linha do arquivo
    int y = 0;            // Coordenada Y (linha atual)

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), f)) {
        // Percorre cada caractere da linha
        for (int x = 0; linha[x] != '\n'; x++) {
            if (linha[x] != '.' ){ // Identifica antenas (caracteres diferentes de '.')
                lista = inserirAntenaInicio(lista, linha[x], x, y); // Adiciona à lista
            }
        }
        y++; // Incrementa a coordenada Y para a próxima linha
    }

    fclose(f); // Fecha o arquivo
    return lista; // Retorna a lista de antenas
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

/**
 * @brief funcao para adicionar um efeito nefasto
 * 
 * @param lista 
 * @param frequencia 
 * @param x 
 * @param y 
 * @return EfeitoNefasto* 
 */
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
                    
                    // Adiciona efeito se a distância entre antenas for pequena
                    if (maiorX - menorX < 1) {
                        efeitos = adicionarEfeito(efeitos, a1->frequencia, a1->x, a1->y);
                    }
                }
                // Caso estejam na mesma coluna (x é igual)
                else if (a1->x == a2->x) {
                    int menorY = (a1->y < a2->y) ? a1->y : a2->y;
                    int maiorY = (a1->y > a2->y) ? a1->y : a2->y;
                    
                    // Adiciona efeito se a distância entre antenas for pequena
                    if (maiorY - menorY < 1) {
                        efeitos = adicionarEfeito(efeitos, a1->frequencia, a1->x, a1->y);
                    }
                }
                // Caso estejam na mesma diagonal
                else if (abs(a1->x - a2->x) == abs(a1->y - a2->y)) {
                    int menorX = (a1->x < a2->x) ? a1->x : a2->x;
                    int maiorX = (a1->x > a2->x) ? a1->x : a2->x;
                    int menorY = (a1->y < a2->y) ? a1->y : a2->y;
                    int maiorY = (a1->y > a2->y) ? a1->y : a2->y;
                    
                    // Adiciona efeito se a distância entre antenas for pequena
                    if (maiorX - menorX < 1) {
                        efeitos = adicionarEfeito(efeitos, a1->frequencia, a1->x, a1->y);
                    }
                }
            }
        }
    }

    return efeitos;
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
        // Imprime os dados da antena ou espaços vazios se não houver mais antenas
        char freqAntena = (a != NULL) ? a->frequencia : ' ';
        int xAntena = (a != NULL) ? a->x : 0;
        int yAntena = (a != NULL) ? a->y : 0;

        // Imprime os dados do efeito nefasto ou espaços vazios se não houver mais efeitos
        char freqEfeito = (e != NULL) ? e->frequencian : ' ';
        int xEfeito = (e != NULL) ? e->x : 0;
        int yEfeito = (e != NULL) ? e->y : 0;

        // Imprime a linha formatada
        printf("|      %c      |   %3d   |   %3d   |  |      %c      |   %3d   |   %3d   |\n",
               freqAntena, xAntena, yAntena, freqEfeito, xEfeito, yEfeito);

        // Avança para o próximo nó em cada lista, se disponível
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
