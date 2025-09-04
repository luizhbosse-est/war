/*
 * Sistema de Cadastro de Territórios
 * 
 * Este programa implementa um sistema simples para cadastrar informações
 * de territórios usando estruturas de dados compostas em C.
 * 
 * Autor: Sistema Manus
 * Data: Setembro 2025
 */

#include <stdio.h>   // Biblioteca para entrada e saída de dados
#include <string.h>  // Biblioteca para manipulação de strings

/*
 * Definição da estrutura Territorio
 * 
 * Esta struct armazena as informações básicas de um território:
 * - nome: string com até 29 caracteres + terminador nulo
 * - cor: string com até 9 caracteres + terminador nulo para a cor do exército
 * - tropas: número inteiro representando a quantidade de tropas
 */
struct Territorio {
    char nome[30];  // Nome do território
    char cor[10];   // Cor do exército
    int tropas;     // Quantidade de tropas
};

/*
 * Função para exibir os dados de todos os territórios cadastrados
 * 
 * Parâmetros:
 * - territorios: vetor de estruturas Territorio
 * - quantidade: número de territórios a serem exibidos
 */
void exibirTerritorios(struct Territorio territorios[], int quantidade) {
    printf("\n");
    printf("=================================================\n");
    printf("           TERRITÓRIOS CADASTRADOS\n");
    printf("=================================================\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Território %d ---\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
    }
    
    printf("\n=================================================\n");
}

/*
 * Função principal do programa
 * 
 * Responsável por:
 * 1. Declarar o vetor de territórios
 * 2. Realizar o cadastro dos 5 territórios
 * 3. Exibir os dados cadastrados
 */
int main() {
    // Declaração do vetor para armazenar 5 territórios
    struct Territorio territorios[5];
    
    // Mensagem de boas-vindas e instruções
    printf("=================================================\n");
    printf("      SISTEMA DE CADASTRO DE TERRITÓRIOS\n");
    printf("=================================================\n");
    printf("Este sistema permite cadastrar 5 territórios.\n");
    printf("Para cada território, informe:\n");
    printf("- Nome (máximo 29 caracteres)\n");
    printf("- Cor do exército (máximo 9 caracteres)\n");
    printf("- Quantidade de tropas (número inteiro)\n");
    printf("=================================================\n\n");
    
    /*
     * Laço para cadastro dos 5 territórios
     * 
     * Para cada território, solicita ao usuário:
     * - Nome do território
     * - Cor do exército
     * - Quantidade de tropas
     */
    for (int i = 0; i < 5; i++) {
        printf("--- Cadastro do Território %d ---\n", i + 1);
        
        // Entrada do nome do território
        printf("Digite o nome do território: ");
        scanf("%29s", territorios[i].nome);  // Limita a 29 caracteres para evitar overflow
        
        // Entrada da cor do exército
        printf("Digite a cor do exército: ");
        scanf("%9s", territorios[i].cor);    // Limita a 9 caracteres para evitar overflow
        
        // Entrada da quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\nTerritório %d cadastrado com sucesso!\n\n", i + 1);
    }
    
    /*
     * Exibição dos dados cadastrados
     * 
     * Chama a função exibirTerritorios para mostrar todos os
     * territórios cadastrados de forma organizada
     */
    exibirTerritorios(territorios, 5);
    
    printf("\nCadastro finalizado com sucesso!\n");
    printf("Obrigado por usar o Sistema de Cadastro de Territórios.\n");
    
    return 0;  // Retorna 0 indicando execução bem-sucedida
}