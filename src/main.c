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
#include "funcoes.h"
#include "dados.h"
#include <string.h>

int menu(){
    printf("=================Menu===========================\n");
    int opcao;
    printf("1. Carregar antenas de um ficheiro\n");
    printf("2. Inserir Antena\n");
    printf("3. Calcular efeitos nefastos\n");
    printf("4. Listar antenas\n");
    printf("5. Listar Efeitos Nefastos\n");
    printf("6. Escrever Dados num ficheiros em formato tabular\n");
    printf("7. Libertar memoria da lista de antenas\n");
    printf("8. Libertar a memoria da lista de efeitos nefastos\n");
    printf("9. Criar grafo e executar operações\n");
    printf("10. Sair\n");
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
 
    int opcao;
    int opGrafo;
    do {
        opcao = menu();
        switch (opcao) {
 
            case 1: {
                // Carregar antenas e evitar erros no nome do ficheiro
                char nomeficheiro[100];
                printf("Digite o nome do ficheiro: ");
                scanf("%99s", nomeficheiro);
             
                // Liberar memória da lista antiga antes de carregar uma nova
                libertarListaAntenas(listaAntenas);
                listaAntenas = NULL; // Importante para evitar acessos inválidos
                // carrega as antenas para a lista
                listaAntenas = lerFicheiro(nomeficheiro);

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
        
                int posicao = 0;
                printf("Digite a posição da antena que deseja inserir, ou por defeito será inserida no início da lista\n");
                scanf("%d", &posicao);
                listaAntenas = inserirAntena(listaAntenas, frequencia, x, y, posicao);
                printf("Antena inserida com sucesso!\n");
                break;
            }

            case 3:
                listaEfeitos = calcularEfeitosNefastos(listaAntenas);
                printf("Efeitos nefastos calculados com sucesso!\n");
                break;
         
            case 4:
                if (listaAntenas == NULL)
                printf("Erro ao listar as antenas\n");
                else 
                listarAntenas(listaAntenas);
                break;
            
            case 5:

                if (listaEfeitos == NULL)
                printf("Erro ao listar Efeitos\n");
                else
                listarEfeitos(listaEfeitos);
                break;
 
            case 6:
                libertarListaAntenas(listaAntenas);
                listaAntenas = NULL;  // Importante para evitar acessos inválidos
                printf("Memória da lista de antenas libertada com sucesso!\n");
                break;

            case 7:
                libertarListaEfeitos(listaEfeitos);
                listaEfeitos = NULL;  // Importante para evitar acessos inválidos
                printf("Memória da lista de efeitos nefastos libertada com sucesso!\n");
                break;

            case 8:
                printf("A sair do programa...\n");
                exit(0); // Sair do programa
                break;

    case 9: {
        // Declarar e criar o grafo a partir da lista de antenas
        Grafo *g = criarGrafo(listaAntenas); // Certifique-se de que criarGrafo está implementada

        printf("Operações com o grafo:\n");
        printf("1. DFS a partir da primeira antena\n");
        printf("2. BFS a partir da primeira antena\n");
        printf("3. Interseções entre frequências\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opGrafo);

        switch(opGrafo) {
            case 1: {
                printf("DFS a partir da primeira antena:\n");
                int linhas = 10, colunas = 20; // Ajuste conforme sua matriz
                int **matrizVisitados = (int **)malloc(linhas * sizeof(int *));
                for(int i = 0; i < linhas; i++) {
                    matrizVisitados[i] = (int *)malloc(colunas * sizeof(int));
                    memset(matrizVisitados[i], 0, colunas * sizeof(int));
                }
                dfs(g->listvertices, NULL, matrizVisitados, linhas, colunas);
                // Libere a matriz de visitados após o uso
                for(int i = 0; i < linhas; i++) {
                    free(matrizVisitados[i]);
                }
                free(matrizVisitados);
                break;
            }
            case 2: {
                printf("BFS a partir da primeira antena:\n");
                bfs(g->listvertices, 10, 20); // Ajuste dimensões conforme necessário
                break;
            }
            case 3: {
                char f1, f2;
                printf("Digite a primeira frequência: ");
                scanf(" %c", &f1);
                printf("Digite a segunda frequência: ");
                scanf(" %c", &f2);
                intersecoes(g->listvertices, f1, f2);
                break;
            }
            default:
                printf("Opção inválida!\n");
                break;
        }
        // Libere o grafo após o uso, se necessário
        // liberarGrafo(g);
    }
            
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

    } while (opcao != 8);
 
    // Libera memória antes de sair
    libertarListaAntenas(listaAntenas);
    libertarListaEfeitos(listaEfeitos);
 
    return 0;
}