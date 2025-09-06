/*
 * Sistema WAR Estruturado Final - Versão com Missões Estratégicas
 * 
 * Este programa implementa um sistema de guerra entre territórios com:
 * - Alocação dinâmica de memória
 * - Uso de ponteiros para manipulação de dados
 * - Simulação de ataques com dados aleatórios
 * - Transferência de controle de territórios
 * - Sistema de missões estratégicas individuais
 * - Verificação de condições de vitória
 * 
 * Autor: Sistema Manus
 * Data: Setembro 2025
 */

#include <stdio.h>   // Biblioteca para entrada e saída de dados
#include <stdlib.h>  // Biblioteca para alocação dinâmica e números aleatórios
#include <string.h>  // Biblioteca para manipulação de strings
#include <time.h>    // Biblioteca para semente de aleatoriedade

/*
 * Definição da estrutura Territorio
 * 
 * Esta struct armazena as informações de um território:
 * - nome: string com até 29 caracteres + terminador nulo
 * - cor: string com até 9 caracteres + terminador nulo para a cor do exército
 * - tropas: número inteiro representando a quantidade de tropas
 */
struct Territorio {
    char nome[30];  // Nome do território
    char cor[10];   // Cor do exército controlador
    int tropas;     // Quantidade de tropas
};

/*
 * Vetor global de missões estratégicas pré-definidas
 * 
 * Contém as diferentes missões que podem ser sorteadas para os jogadores
 */
char* missoesPredefinidas[] = {
    "Conquistar 3 territórios consecutivos",
    "Eliminar todas as tropas vermelhas do mapa",
    "Controlar pelo menos 4 territórios",
    "Ter mais de 2000 tropas no total",
    "Conquistar territórios de 3 cores diferentes",
    "Controlar todos os territórios de uma região"
};

#define TOTAL_MISSOES 6

// Variáveis globais para o sistema de missões
char* missaoJogador = NULL;  // Missão do jogador (alocada dinamicamente)
char corJogador[10];         // Cor do jogador atual

/*
 * Função para alocar memória dinamicamente para os territórios
 * 
 * Parâmetros:
 * - quantidade: número de territórios a serem alocados
 * 
 * Retorna:
 * - Ponteiro para o vetor de territórios alocado
 * - NULL em caso de erro na alocação
 */
struct Territorio* alocarTerritorios(int quantidade) {
    struct Territorio* mapa = (struct Territorio*)calloc(quantidade, sizeof(struct Territorio));
    
    if (mapa == NULL) {
        printf("Erro: Não foi possível alocar memória para os territórios!\n");
        return NULL;
    }
    
    printf("Memória alocada com sucesso para %d territórios.\n", quantidade);
    return mapa;
}

/*
 * Função para atribuir uma missão aleatória ao jogador
 * 
 * Parâmetros:
 * - destino: ponteiro para onde a missão será copiada (passagem por referência)
 * - missoes: vetor de strings com as missões disponíveis
 * - totalMissoes: número total de missões disponíveis
 */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indiceMissao = rand() % totalMissoes;
    strcpy(destino, missoes[indiceMissao]);
}

/*
 * Função para exibir a missão do jogador
 * 
 * Parâmetros:
 * - missao: string com a missão do jogador (passada por valor)
 */
void exibirMissao(char* missao) {
    printf("\n=== SUA MISSÃO ESTRATÉGICA ===\n");
    printf("Objetivo: %s\n", missao);
    printf("==============================\n");
}

/*
 * Função para verificar se a missão foi cumprida
 * 
 * Parâmetros:
 * - missao: string com a missão a ser verificada (passada por valor)
 * - mapa: ponteiro para o vetor de territórios
 * - tamanho: número de territórios no mapa
 * 
 * Retorna:
 * - 1 se a missão foi cumprida
 * - 0 se a missão ainda não foi cumprida
 */
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho) {
    // Missão 1: "Conquistar 3 territórios consecutivos"
    if (strcmp(missao, "Conquistar 3 territórios consecutivos") == 0) {
        int consecutivos = 0;
        int maxConsecutivos = 0;
        
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                consecutivos++;
                if (consecutivos > maxConsecutivos) {
                    maxConsecutivos = consecutivos;
                }
            } else {
                consecutivos = 0;
            }
        }
        return maxConsecutivos >= 3;
    }
    
    // Missão 2: "Eliminar todas as tropas vermelhas do mapa"
    if (strcmp(missao, "Eliminar todas as tropas vermelhas do mapa") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0 || strcmp(mapa[i].cor, "vermelho") == 0) {
                return 0; // Ainda existem territórios vermelhos
            }
        }
        return 1; // Não há mais territórios vermelhos
    }
    
    // Missão 3: "Controlar pelo menos 4 territórios"
    if (strcmp(missao, "Controlar pelo menos 4 territórios") == 0) {
        int territoriosControlados = 0;
        
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                territoriosControlados++;
            }
        }
        return territoriosControlados >= 4;
    }
    
    // Missão 4: "Ter mais de 2000 tropas no total"
    if (strcmp(missao, "Ter mais de 2000 tropas no total") == 0) {
        int totalTropas = 0;
        
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                totalTropas += mapa[i].tropas;
            }
        }
        return totalTropas > 2000;
    }
    
    // Missão 5: "Conquistar territórios de 3 cores diferentes"
    if (strcmp(missao, "Conquistar territórios de 3 cores diferentes") == 0) {
        // Simplificação: verificar se o jogador controla pelo menos 3 territórios
        int territoriosControlados = 0;
        
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                territoriosControlados++;
            }
        }
        return territoriosControlados >= 3;
    }
    
    // Missão 6: "Controlar todos os territórios de uma região"
    if (strcmp(missao, "Controlar todos os territórios de uma região") == 0) {
        // Simplificação: controlar metade dos territórios
        int territoriosControlados = 0;
        
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                territoriosControlados++;
            }
        }
        return territoriosControlados >= (tamanho / 2);
    }
    
    return 0; // Missão não reconhecida ou não cumprida
}

/*
 * Função para cadastrar os territórios usando ponteiros
 * 
 * Parâmetros:
 * - mapa: ponteiro para o vetor de territórios
 * - quantidade: número de territórios a serem cadastrados
 */
void cadastrarTerritorios(struct Territorio* mapa, int quantidade) {
    printf("\n=================================================\n");
    printf("           CADASTRO DE TERRITÓRIOS\n");
    printf("=================================================\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        
        // Entrada do nome do território usando ponteiro
        printf("Digite o nome do território: ");
        scanf("%29s", (mapa + i)->nome);  // Acesso via ponteiro
        
        // Entrada da cor do exército usando ponteiro
        printf("Digite a cor do exército: ");
        scanf("%9s", (mapa + i)->cor);    // Acesso via ponteiro
        
        // Entrada da quantidade de tropas usando ponteiro
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &((mapa + i)->tropas)); // Acesso via ponteiro
        
        printf("Território '%s' cadastrado com sucesso!\n", (mapa + i)->nome);
    }
}

/*
 * Função para exibir todos os territórios usando ponteiros
 * 
 * Parâmetros:
 * - mapa: ponteiro para o vetor de territórios
 * - quantidade: número de territórios a serem exibidos
 */
void exibirTerritorios(struct Territorio* mapa, int quantidade) {
    printf("\n=================================================\n");
    printf("           MAPA DE TERRITÓRIOS\n");
    printf("=================================================\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("\n[%d] Território: %s\n", i + 1, (mapa + i)->nome);
        printf("    Controlado por: %s\n", (mapa + i)->cor);
        printf("    Tropas: %d\n", (mapa + i)->tropas);
    }
    
    printf("\n=================================================\n");
}

/*
 * Função para selecionar um território para ataque ou defesa
 * 
 * Parâmetros:
 * - mapa: ponteiro para o vetor de territórios
 * - quantidade: número total de territórios
 * - acao: string indicando se é para "atacar" ou "defender"
 * 
 * Retorna:
 * - Índice do território selecionado (0-based)
 * - -1 em caso de seleção inválida
 */
int selecionarTerritorio(struct Territorio* mapa, int quantidade, char* acao) {
    int escolha;
    
    printf("\nSelecione um território para %s (1-%d): ", acao, quantidade);
    scanf("%d", &escolha);
    
    // Validação da entrada
    if (escolha < 1 || escolha > quantidade) {
        printf("Erro: Seleção inválida! Escolha entre 1 e %d.\n", quantidade);
        return -1;
    }
    
    return escolha - 1; // Retorna índice 0-based
}

/*
 * Função para simular um ataque entre territórios
 * 
 * Parâmetros:
 * - atacante: ponteiro para o território atacante
 * - defensor: ponteiro para o território defensor
 * 
 * Lógica:
 * - Simula rolagem de dados (1-6) para atacante e defensor
 * - Se atacante vencer: defensor muda de cor e recebe metade das tropas
 * - Se defensor vencer: atacante perde uma tropa
 */
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    // Simulação de dados de batalha (1 a 6)
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    
    printf("\n=================================================\n");
    printf("                SIMULAÇÃO DE BATALHA\n");
    printf("=================================================\n");
    printf("Atacante: %s (%s) - Dado: %d\n", atacante->nome, atacante->cor, dadoAtacante);
    printf("Defensor: %s (%s) - Dado: %d\n", defensor->nome, defensor->cor, dadoDefensor);
    printf("-------------------------------------------------\n");
    
    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("VITÓRIA DO ATACANTE!\n");
        printf("Território '%s' foi conquistado por %s!\n", defensor->nome, atacante->cor);
        
        // Transferir controle do território
        strcpy(defensor->cor, atacante->cor);
        
        // Transferir metade das tropas do atacante para o defensor
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
        
        printf("Tropas transferidas: %d\n", tropasTransferidas);
        printf("Tropas restantes do atacante: %d\n", atacante->tropas);
        
    } else {
        // Defensor vence
        printf("VITÓRIA DO DEFENSOR!\n");
        printf("Território '%s' resistiu ao ataque!\n", defensor->nome);
        
        // Atacante perde uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("O atacante perdeu 1 tropa. Tropas restantes: %d\n", atacante->tropas);
        } else {
            printf("O atacante não pode perder mais tropas (mínimo: 1).\n");
        }
    }
    
    printf("=================================================\n");
}

/*
 * Função para validar se um ataque é permitido
 * 
 * Parâmetros:
 * - atacante: ponteiro para o território atacante
 * - defensor: ponteiro para o território defensor
 * 
 * Retorna:
 * - 1 se o ataque é válido
 * - 0 se o ataque não é permitido
 */
int validarAtaque(struct Territorio* atacante, struct Territorio* defensor) {
    // Verificar se são territórios diferentes
    if (atacante == defensor) {
        printf("Erro: Um território não pode atacar a si mesmo!\n");
        return 0;
    }
    
    // Verificar se são da mesma cor (aliados)
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Territórios aliados (%s) não podem se atacar!\n", atacante->cor);
        return 0;
    }
    
    // Verificar se o atacante tem tropas suficientes
    if (atacante->tropas < 2) {
        printf("Erro: O atacante precisa ter pelo menos 2 tropas para atacar!\n");
        return 0;
    }
    
    return 1; // Ataque válido
}

/*
 * Função para gerenciar o loop de batalhas com verificação de missão
 * 
 * Parâmetros:
 * - mapa: ponteiro para o vetor de territórios
 * - quantidade: número total de territórios
 */
void gerenciarBatalhas(struct Territorio* mapa, int quantidade) {
    int continuar = 1;
    int indiceAtacante, indiceDefensor;
    char opcao;
    
    printf("\n=================================================\n");
    printf("           MODO DE BATALHA ATIVADO\n");
    printf("=================================================\n");
    
    while (continuar) {
        // Exibir mapa atual
        exibirTerritorios(mapa, quantidade);
        
        // Verificar se a missão foi cumprida (verificação silenciosa)
        if (verificarMissao(missaoJogador, mapa, quantidade)) {
            printf("\n🎉 PARABÉNS! MISSÃO CUMPRIDA! 🎉\n");
            printf("=================================================\n");
            printf("           VITÓRIA!\n");
            printf("=================================================\n");
            printf("Você completou sua missão: %s\n", missaoJogador);
            printf("=================================================\n");
            break;
        }
        
        // Selecionar território atacante
        printf("\n--- SELEÇÃO DO ATACANTE ---\n");
        indiceAtacante = selecionarTerritorio(mapa, quantidade, "atacar");
        if (indiceAtacante == -1) continue;
        
        // Selecionar território defensor
        printf("\n--- SELEÇÃO DO DEFENSOR ---\n");
        indiceDefensor = selecionarTerritorio(mapa, quantidade, "defender");
        if (indiceDefensor == -1) continue;
        
        // Validar ataque
        if (!validarAtaque(&mapa[indiceAtacante], &mapa[indiceDefensor])) {
            continue;
        }
        
        // Executar ataque
        atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
        
        // Verificar novamente se a missão foi cumprida após o ataque
        if (verificarMissao(missaoJogador, mapa, quantidade)) {
            printf("\n🎉 PARABÉNS! MISSÃO CUMPRIDA! 🎉\n");
            printf("=================================================\n");
            printf("           VITÓRIA!\n");
            printf("=================================================\n");
            printf("Você completou sua missão: %s\n", missaoJogador);
            printf("=================================================\n");
            break;
        }
        
        // Perguntar se deseja continuar
        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &opcao);
        
        if (opcao == 'n' || opcao == 'N') {
            continuar = 0;
        }
    }
    
    printf("\nModo de batalha encerrado.\n");
}

/*
 * Função para liberar a memória alocada dinamicamente
 * 
 * Parâmetros:
 * - mapa: ponteiro para o vetor de territórios a ser liberado
 */
void liberarMemoria(struct Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemória dos territórios liberada com sucesso.\n");
    }
    
    if (missaoJogador != NULL) {
        free(missaoJogador);
        printf("Memória da missão liberada com sucesso.\n");
    }
}

/*
 * Função principal do programa
 * 
 * Responsável por:
 * 1. Solicitar número de territórios
 * 2. Alocar memória dinamicamente
 * 3. Atribuir missão estratégica ao jogador
 * 4. Cadastrar territórios
 * 5. Gerenciar o loop de batalhas com verificação de missão
 * 6. Liberar memória ao final
 */
int main() {
    // Inicialização da semente para números aleatórios
    srand(time(NULL));
    
    // Declaração de variáveis
    struct Territorio* mapa = NULL;
    int quantidade;
    char opcao;
    
    // Mensagem de boas-vindas
    printf("=================================================\n");
    printf("     SISTEMA WAR ESTRUTURADO FINAL\n");
    printf("=================================================\n");
    printf("Sistema de guerra entre territórios com:\n");
    printf("- Alocação dinâmica de memória\n");
    printf("- Simulação de ataques com dados\n");
    printf("- Transferência de controle de territórios\n");
    printf("- Missões estratégicas individuais\n");
    printf("- Verificação automática de vitória\n");
    printf("=================================================\n");
    
    // Solicitar cor do jogador
    printf("\nDigite sua cor de exército: ");
    scanf("%9s", corJogador);
    
    // Alocação dinâmica para a missão do jogador
    missaoJogador = (char*)malloc(100 * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro: Não foi possível alocar memória para a missão!\n");
        return 1;
    }
    
    // Atribuir missão estratégica aleatória
    atribuirMissao(missaoJogador, missoesPredefinidas, TOTAL_MISSOES);
    
    // Exibir missão do jogador
    exibirMissao(missaoJogador);
    
    // Solicitar número de territórios
    printf("\nQuantos territórios deseja cadastrar? ");
    scanf("%d", &quantidade);
    
    // Validação da entrada
    if (quantidade <= 0) {
        printf("Erro: Número de territórios deve ser maior que zero!\n");
        liberarMemoria(NULL);
        return 1;
    }
    
    // Alocação dinâmica de memória
    mapa = alocarTerritorios(quantidade);
    if (mapa == NULL) {
        liberarMemoria(NULL);
        return 1; // Erro na alocação
    }
    
    // Cadastro dos territórios
    cadastrarTerritorios(mapa, quantidade);
    
    // Exibição inicial dos territórios
    exibirTerritorios(mapa, quantidade);
    
    // Perguntar se deseja iniciar batalhas
    printf("\nDeseja iniciar o modo de batalha? (s/n): ");
    scanf(" %c", &opcao);
    
    if (opcao == 's' || opcao == 'S') {
        gerenciarBatalhas(mapa, quantidade);
        
        // Exibir estado final dos territórios
        printf("\n=== ESTADO FINAL DOS TERRITÓRIOS ===\n");
        exibirTerritorios(mapa, quantidade);
    }
    
    // Liberação da memória
    liberarMemoria(mapa);
    
    printf("\nObrigado por usar o Sistema WAR Estruturado Final!\n");
    return 0;
}