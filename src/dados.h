/*! 
    * \file dados.h
    * \brief Arquivo com a definição de  duas estruturas:Antena e Efeito Nefasto de uma cidade
    * 
    * Arquivo com a definição da estrutura Antena e da estrutura Efeito Nefasto de uma cidade
    *
    * \author Rodrigo Pinheiro
    * \date 2025
*/

#ifndef DADOS_H
#define DADOS_H

typedef struct Antena {
    char frequencia;
    int x, y;
    int aux;
    struct Antena* prox;
} Antena;

typedef struct EfeitoNefasto {
    char frequencian;
    int x, y;
    int aux;
    struct EfeitoNefasto* prox;
} EfeitoNefasto;

#endif // DADOS_H
