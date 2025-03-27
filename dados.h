/*! 
    * \file dados.h
    * \brief Arquivo com a definição de  duas estruturas:Antena e Efeito Nefasto de uma cidade
    * 
    * Arquivo com a definição da estrutura Antena e da estrutura Efeito Nefasto de uma cidade
    *
    * \author Rodrigo Pinheiro
    * \date 2025
*/

#define DADOS_H
// Definição da estrutura Antena
typedef struct Antena {
    char frequencia;
    int x, y;
    int aux;
    struct Antena* prox;
} Antena;

// Definição da estrutura Efeito Nefasto
typedef struct EfeitoNefasto {
    char tipo;
    int x, y;
    int aux;
    struct EfeitoNefasto* prox;
} EfeitoNefasto;
