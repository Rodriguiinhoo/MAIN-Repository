/**!
 * \file grafo_antenas.h
 * \brief Arquivo de cabeçalho para o grafo de antenas.
 */

#ifndef LISTA_ANTENAS_H
#define LISTA_ANTENAS_H

#include "dados.h"

int menu();
Antena* lerFicheiro(const char *nomeFicheiro);
Antena* inserirAntenaOrdenada(Antena *lista, char frequencia, int x, int y);
EfeitoNefasto* calcularEfeitosNefastos(Antena *listaAntenas);
EfeitoNefasto* adicionarEfeitoOrdenado(EfeitoNefasto *lista, int frequencia, int x, int y);
void listarAntenas(Antena *listaAntenas);
void listarEfeitos(EfeitoNefasto *listaEfeitos);
void libertarListaAntenas(Antena *lista);
void libertarListaEfeitos(EfeitoNefasto *lista);
#endif