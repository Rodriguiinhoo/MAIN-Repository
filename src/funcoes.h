/*!
 * \file funcoes.h
 * \brief Ficheiro header com as funções.
 * \author Rodrigo Henrique Silva Pinheiro
 * \date 2025-03-25
 */

#define FUNCOES_H

#include "dados.h"

Antena* carregarAntenasDeFicheiro(const char *nomeficheiro);
Antena* inserirAntenaInicio(Antena *lista, char frequencia, int x, int y);
void listarAntenas(Antena *lista);
// Calcular e listar locais com efeito nefasto
EfeitoNefasto* calcularEfeitosNefastos(Antena *lista);
void listarEfeitosNefastos(listaEfeitos);
// Libertar memória
void libertarListaAntenas(listaAntenas);
void libertarListaEfeitos(EfeitoNefasto *lista);