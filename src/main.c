/**
 * \file main.c
 * \author Rodrigo Henrique Silva Pinheiro, a31502@alunos.ipca.pt, LESI 
 * \version 0.1
 * \date 2025-03-28
 * 
 * @copyright Copyright (c) 2025
 */

 #include <stdio.h>
 #include "funcoes.h"
 #include "dados.h"


 int menu(){
     printf("=================Menu===========================\n");
     int opcao;
     printf("1. Carregar antenas de um ficheiro\n");
     printf("2. Inserir Antena\n");
     printf("3. Calcular efeitos nefastos\n");
     printf("4. Listar antenas\n");
     printf("5. Listar Efeitos Nefastos\n");
     printf("6. Libertar memoria da lista de antenas\n");
     printf("7. Libertar a memoria da lista de efeitos nefastos");
     printf("8. Sair\n");
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
     do {
         opcao = menu();
         switch (opcao) {
 
             case 1: {
                 char nomeficheiro[100];
                 printf("Digite o nome do ficheiro: ");
                 scanf("%99s", nomeficheiro);
             
                 // Liberar memória da lista antiga antes de carregar uma nova
                 libertarListaAntenas(listaAntenas);
                 listaAntenas = NULL; 
             
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
                 listaAntenas = inserirAntenaInicio(listaAntenas, frequencia, x, y);
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
                 printf("Memória da lista de antenas liberada com sucesso!\n");
                 break;
         
             case 7:
                 libertarListaEfeitos(listaEfeitos);
                 listaEfeitos = NULL;  // Importante para evitar acessos inválidos
                 printf("Memória da lista de efeitos nefastos liberada com sucesso!\n");
                 break;
 
             case 8:
                 printf("Saindo do programa...\n");
                 break;
 
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