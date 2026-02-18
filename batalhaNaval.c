#include <stdio.h>
#include <stdbool.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

int main() {

    // Ativa ou desativa modo debug
    bool isDebugging = true;

    // Declarando arrays representando os navios
    int navioA[3] = {3,3,3};
    int navioB[3] = {3,3,3};
    
    // Declarando matrix para o tabuleiro e inicializando com zeros
    int tabuleiro[11][11] = {0};

    // Posicionando navio A na vertical
    alocarNavio(tabuleiro, navioA, 1, 1, true, isDebugging);

    // Posicionando navio B na horizontal
    alocarNavio(tabuleiro, navioB, 1, 5, false, isDebugging);

    // Exibindo tabuleiro no terminal
    exibirTabuleiro(tabuleiro);

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

    return 0;
}

// Esta função copia os elementos do navio no tabuleiro, de acordo com a posição e orientação informados
void alocarNavio(int tabuleiro[10][10], int navio[], int x, int y, bool isVertical, bool isDebugging){
    int navioLength = sizeof(navio)/sizeof(navio[0]);
    for (int i = 0; i <= navioLength; i++){
        // Verifica se o lugar do tabuleiro já está ocupado por outro navio e lanca um erro
        if (tabuleiro[x][y] != 0){
            lancarExcecao("Foi tentado alocar elemento dum navio, porém já está ocupada por outro!\nRevise as alocações para garantir que não haja sobreposições");
        }

        tabuleiro[x][y] = navio [i];

        // Caso esteja no modo debug, detalha a alocação de cada um dos elementos do navio no tabuleiro
        if (isDebugging){
            ("setando valor %d na posicao x %d y %d no tabuleiro\n",navio[i], x, y);
        }
        if (isVertical){
            x++;
        }else{
            y++;
        }
    }
}

// Imprime na tela o tabuleiro atual
void exibirTabuleiro(int tabuleiro[10][10]){
    printf("----- TABULEIRO BATALHA NAVAL -----\n\n");
        for (int x = 9; x >= 0; x--){
        for (int y = 0; y <= 10; y++){
            printf(" %d",tabuleiro[x][y]);
        }
        printf("\n");
    }
}

// Implementa uma funcao para mandar um aviso pelo console que algo saiu do esperado
void lancarExcecao(char mensagem[]){
    printf("\033[31m\n\nAviso!!!\n\nMensagem: %s\n\n\033[0m\n", mensagem);
}