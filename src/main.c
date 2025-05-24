/**
 * \file main.c
 * \author Rodrigo Henrique Silva Pinheiro, a31502@alunos.ipca.pt, LESI 
 * \version 0.1
 * \date 2025-03-28
 * 
 * @copyright Copyright (c) 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "lista_antenas.h"
#include "grafo_antenas.h"
#include <string.h>

int menu() {
    int opcao;
    printf("\n================= MENU =========================\n");
    printf(" 1.  Carregar antenas de um ficheiro\n");
    printf(" 2.  Inserir Antena \n");
    printf(" 3.  Remover Antena\n");
    printf(" 4.  Calcular efeitos nefastos\n");
    printf(" 5.  Listar antenas\n");
    printf(" 6.  Listar efeitos nefastos\n");
    printf(" 7.  Criar grafo\n");
    printf(" 8.  Busca em Profundidade DFS\n");
    printf(" 9.  Sair\n");
    printf("================================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}
 
/**
* @brief  Função principal do programa que interage com o utilizador e executa as operações
* 
* @return int 
*/
 // Função principal
 int main() {

    Antena *listaAntenas = NULL; // Inicializa a lista de antenas como NULL
    EfeitoNefasto *listaEfeitos = NULL; // Inicializa a lista de efeitos nefastos como NULL
    Grafo *g = NULL; // Inicializa o grafo como NULL


    int opcao;
    do {
        opcao = menu();
        switch (opcao) {
 
            case 1: {
                listaAntenas = NULL; // Importante para evitar acessos inválidos
                // carrega as antenas para a lista
                listaAntenas = lerFicheiro("antenas.txt");
                if (listaAntenas != NULL) {
                    printf("Antenas carregadas com sucesso!\n");
                } else {
                    printf("Erro ao carregar as antenas do ficheiro.\n");
                }
                break;
             }
 
             case 2: {

                char frequencia;
                int x, y;
                printf("Digite a frequência da antena: ");
                scanf(" %c", &frequencia);
                printf("Digite a coordenada X: ");
                scanf("%d", &x);
                printf("Digite a coordenada Y: ");
                scanf("%d", &y);
                // chama a função para inserir a antena
                listaAntenas = inserirAntenaOrdenada(listaAntenas, frequencia, x, y);
                printf("Antena inserida com sucesso!\n");
                break;
            }
            case 3: {
                char frequencia;
                int x, y;
                printf("Digite a frequência da antena a remover: ");
                scanf(" %c", &frequencia);
                printf("Digite a coordenada X: ");
                scanf("%d", &x);
                printf("Digite a coordenada Y: ");
                scanf("%d", &y);
                // chama a função para remover a antena
                listaAntenas = removerAntenaPorDados(listaAntenas, frequencia, x, y);
                printf("Antena removida com sucesso!\n");
                break;
            }

            case 4:
                listaEfeitos = calcularEfeitosNefastos(listaAntenas);
                printf("Efeitos nefastos calculados com sucesso!\n");
                break;
         
            case 5:
                if (listaAntenas == NULL)
                printf("Erro ao listar as antenas\n");
                else 
                listarAntenas(listaAntenas);
                break;
            
            case 6:

                if (listaEfeitos == NULL)
                printf("Erro ao listar Efeitos\n");
                else
                listarEfeitos(listaEfeitos);
                break;

            case 7: { // Criar o grafo
            if (g == NULL) {
                g = criarGrafo(listaAntenas);
                if (g != NULL) {
                    printf("Grafo criado com sucesso!\n");
                } else {
                    printf("Erro ao criar o grafo.\n");
                }
             } else {
                printf("Grafo já criado!\n");
            }
            break;
            }  
               
            case 8: { // DFS
            int idOrigem;
            printf("ID da antena origem para DFS: ");
            scanf("%d", &idOrigem);
            Vertice *v = g->listvertices;
            int idx = 0;
            while (v != NULL && idx < idOrigem) {
            v = v->proxvertice;
            idx++;
            }
            if (v != NULL) {
            resetarVisitados(g); // Garante que todos estão como não visitados
            dfs(v);           // Passa o vértice para dfs
            } else {
            printf("Antena não encontrada.\n");
            }
            break;
            }
        
            case 9:{
                 printf("A sair do programa...\n");
                 printf(" A memoria sera libertada automaticamente\n");
                exit(9); // Sair do programa
                break;
            }   
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

    } while (opcao != 9); // Continua até que o utilizador escolha sair

    // Liberta memória antes de sair
    libertarListaAntenas(listaAntenas);
    libertarListaEfeitos(listaEfeitos);
    libertarGrafo(g) ;
    return 0;
}