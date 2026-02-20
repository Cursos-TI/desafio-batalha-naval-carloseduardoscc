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
    int navioC[3] = {3,3,3};
    int navioD[3] = {3,3,3};

    // Declarando arrays representando as habilidades
    int habilidadeCone[3][5] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {1,1,1,1,1}
    };

    int habilidadeCruz[3][5] = {
        {0,0,1,0,0},
        {1,1,1,1,1},
        {0,0,1,0,0}
    };

    int habilidadeOctaedro[3][5] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {0,0,1,0,0}
    };
    
    // Declarando matrix para o tabuleiro e inicializando com zeros
    int tabuleiro[11][11] = {0};

    // Posicionando navios por meio de pontos cardeais
    alocarNavio(tabuleiro, navioA, 1, 1, "N", isDebugging);
    alocarNavio(tabuleiro, navioB, 1, 5, "E", isDebugging);
    alocarNavio(tabuleiro, navioB, 5, 5, "NW", isDebugging);
    alocarNavio(tabuleiro, navioB, 9, 9, "SW", isDebugging);

    // Aplicando habilidades
    lancarHabilidade(tabuleiro, habilidadeOctaedro, 5, 7);
    lancarHabilidade(tabuleiro, habilidadeCone, 8, 1);
    lancarHabilidade(tabuleiro, habilidadeCruz, 1, 5);

    // Exibindo tabuleiro no terminal
    exibirTabuleiro(tabuleiro);

    return 0;
}

// Esta função copia os elementos do navio no tabuleiro, de acordo com a posição e orientação informados
void alocarNavio(int tabuleiro[10][10], int navio[], int x, int y, char orientacao[], bool isDebugging){
    int navioLength = sizeof(navio)/sizeof(navio[0]);
    for (int i = 0; i <= navioLength; i++){
        trocarElementoTabuleiro(tabuleiro, x, y, 3);

        // Caso esteja no modo debug, detalha a alocação de cada um dos elementos do navio no tabuleiro
        if (isDebugging){
            ("setando valor %d na posicao x %d y %d no tabuleiro\n",navio[i], x, y);
        }

        // Implementa movimentação do ponteiro que aloca as partes do navio usando pontos cardeais
        // Ex.:
        // "N" navio sendo alocado em direção ao norte
        // "W" navio sendo alocado em direção ao oeste
        // "SE" ativa dois if's e executa y-- e x++, fazendo a movimentação do ponteiro no sudeste
        if (strchr(orientacao, 'N') == 0) x--;
        if (strchr(orientacao, 'E') == 0) y--;
        if (strchr(orientacao, 'S') == 0) x++;
        if (strchr(orientacao, 'W') == 0) y++;
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
void lancarAviso(char mensagem[]){
    printf("\033[31m\n\nAviso!!!\n\nMensagem: %s\n\n\033[0m\n", mensagem);
}

// Implementa um funcao que aplica uma habilidade no tabuleiro com base no ponto de ataque
void lancarHabilidade(int tabuleiro[10][10], int habilidade[3][5], int posicaoXHabilidade, int posicaoYHabilidade){
    int ponteiroXTabuleiro = posicaoXHabilidade - 2;
    int ponteiroYTabuleiro = posicaoYHabilidade + 1;

    int larguraHabilidade = 5;
    int comprimentoHabilidade = 3;

    for (int ponteiroYHabilidade = 0; ponteiroYHabilidade < comprimentoHabilidade; ponteiroYHabilidade++, ponteiroYTabuleiro--){
        for (int ponteiroXHabilidade = 0; ponteiroXHabilidade < larguraHabilidade; ponteiroXHabilidade++, ponteiroXTabuleiro++){
            int elementoCorrespondenteDaHabilidade = habilidade[ponteiroYHabilidade][ponteiroXHabilidade];
            if (elementoCorrespondenteDaHabilidade != 0){
                trocarElementoTabuleiro(tabuleiro, ponteiroYTabuleiro, ponteiroXTabuleiro, 5);
            }
        }
        ponteiroXTabuleiro = posicaoXHabilidade - 2;
    }
}

// Abstrai posicionamento de elementos no tabuleiro com verificacao de erros
void trocarElementoTabuleiro(int tabuleiro[10][10], int posicaoX, int posicaoY, int elemento){
    // Lanca um erro ao tentar sobrepor um navio sobre outro já no tabuleiro
    if (tabuleiro[posicaoX][posicaoY] != 0 && elemento == 3){
        lancarAviso("Foi tentado alocar elemento dum navio numa posição já ocupada por outro!\nRevise as alocações para garantir que não haja sobreposições");
        return;
    }
    // Verifica se houve posicionamento fora do tabuleiro, permite que habilidades sobresaiam do tabuleiro
    if ((posicaoX > 10 || posicaoX < 0 || posicaoY > 10 || posicaoY < 0) && elemento != 5 && elemento != 0){
        lancarAviso("Foi tentado alocar elemento numa posição fora do tabuleiro!\nRevise as alocações para garantir que estejam dentro do tabuleiro");
        return;
    }

    tabuleiro[posicaoX][posicaoY] = elemento;
}