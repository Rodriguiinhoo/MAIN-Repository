#include <stdio.h>
#include "funcoes.h"
#include "funcoes.c"

// Função principal
int main() {
    Antena *listaAntenas = NULL;

    listaAntenas = carregarAntenasDeFicheiro("antenas.txt");
    
    // Listar as antenas
    printf("Lista de Antenas:\n");
    Antena *aux = listarAntenas; // Ponteiro auxiliar para percorrer a lista
    while (aux) {
        printf("Frequência: %c | Coordenadas: (%d, %d)\n", aux->frequencia, aux->x, aux->y);
        aux = aux->prox;
    }
    return 0;
}

