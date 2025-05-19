# MAIN-Repository
Este e o meu Repositorio Principal.

# Trabalho Pratico

# 📡 Sistema de Gestão de Antenas com Grafos  
*Trabalho Prático da disciplina de Estruturas de Dados Avançadas*  

## 📌 Descrição  
Sistema em C que modela conexões entre antenas usando **grafos** e **listas encadeadas**, com operações de inserção, remoção e análise de custos.  

## Autor
 | Numero | Nome |
 |--------|---------------------------------|
 | 31502  | Rodrigo Henrique Silva Pinheiro |

## 📂 Estrutura do Projeto  
MAIN-Repository/

├── doc/                        # Documentação
│   └── Relatorio em LaTex  
├── doxdoc/                     # Documentação
│   └── documentacao em doxygen         
├── include/                    # Cabeçalhos (.h) públicos  
│   ├── dados.h                 # Estruturas de dados  
│   ├── grafo_antenas.h         # Operações do grafo  
│   └── lista_antenas.h         # Manipulação de listas  
├── src/                        # Código-fonte (.c)  
│   ├── grafo_antenas.c         # Implementação do grafo  
│   ├── lista_antenas.c         # Implementação das listas  
│   └── main.c                  # Programa principal  
├── antenas.txt                 # Arquivo de entrada (dados)  
├── Makefile                    # Configuração de compilação  
└── README.md                   # Documentação  

## Compilar e Executar o Programa 
    Para compilar o Programa use o comando:

        Make

    Para Executar o Programa use o comando:

        Make run 
    
    Para limpar os executaveis use:

        make clean