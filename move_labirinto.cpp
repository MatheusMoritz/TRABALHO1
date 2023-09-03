/**
    Bomberman
    versão: 0.2
    Lucas Carvalho de Borba
    Miguel
    Matheus
*/

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h> ///contar o tempo

#define M_LINHAS 15
#define M_COLUNAS 15

using namespace std;
const int M = 3;

bool verificaColisao(int m[M_LINHAS][M_COLUNAS], int x, int y) {
    if (m[x][y] == 0 || m[x][y] == 4) {
        return true;
    } else {
        return false;
    }
}

void bomba(int m[M_LINHAS][M_COLUNAS], int x, int y, bool *flagBomba){
    if (!*flagBomba){ //verifica se a bomba já existe, se não existe, coloca uma bomba
        *flagBomba = true; //altera a flag informando que agora existe uma bomba
        m[x][y] = 3; // coloca a bomba no mapa
    }
}

void movimentoInimigo(int m[M_LINHAS][M_COLUNAS], int &ex, int &ey) {
    int direcao = rand() % 4; // escolhe uma direção aleatória
    int passo = rand() % 3 + 1; // escolhe um número aleatório de passos
    for (int i = 0; i < passo; i++) {
        if (direcao == 0 && verificaColisao(m, ex - 1, ey)) {
            ex--;
        } else if (direcao == 1 && verificaColisao(m, ex + 1, ey)) {
            ex++;
        } else if (direcao == 2 && verificaColisao(m, ex, ey - 1)) {
            ey--;
        } else if (direcao == 3 && verificaColisao(m, ex, ey + 1)) {
            ey++;
        } else {
            break;
        }
    }
}

int fimDeJogo() {
    cout<<"\nFIM DE JOGO!";
    return 0;
}


int main()
{
    ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, A SEGUIR.
        //INICIO: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
        //IN�CIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
        short int CX=0, CY=0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
        //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
    ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, ACIMA.

    int m[M_LINHAS][M_COLUNAS]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                1,0,0,0,0,0,2,2,2,0,0,0,0,0,1,
                                1,0,1,0,1,0,1,2,1,2,1,0,1,0,1,
                                1,0,0,0,0,0,2,2,2,2,2,0,0,0,1,
                                1,0,1,0,1,0,1,2,1,2,1,0,1,0,1,
                                1,0,0,2,0,2,2,2,2,2,2,2,0,0,1,
                                1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
                                1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
                                1,2,1,0,1,2,1,2,1,0,1,2,1,2,1,
                                1,0,0,0,2,2,2,2,2,2,2,2,0,0,1,
                                1,0,1,0,1,2,1,2,1,2,1,2,1,0,1,
                                1,0,0,0,0,2,2,2,2,2,2,2,0,0,1,
                                1,0,1,0,1,0,1,2,1,2,1,0,1,0,1,
                                1,0,0,0,0,0,2,2,2,2,0,0,0,0,1,
                                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                                };


    //Posi��o inicial do personagem no console
    int x=13, y=1;
    //Vari�vel para tecla precionada
    char tecla;
    int ex1 = 1, ey1 = 1; // posição do primeiro inimigo
    int ex2 = 13, ey2 = 13; // posição do segundo inimigo
    int contadorMovimentoInimigo = 0; // contador para controlar o movimento dos inimigos

    //Variável para verificar se já existe bomba
    bool flagBomba = false;

    int bx, by; //localização da bomba

    clock_t inicio, fim; //declaração das entidades de contagem de tempo para armazenar inicio e fim do período da bomba

    while(true){
        ///Posiciona a escrita no início do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<M_LINHAS;i++){
            for(int j=0;j<M_COLUNAS;j++){
                if(i==x && j==y){
                    cout<<char(2); //personagem
                } else if (i==ex1 && j==ey1) {
                    cout<<char(5); // primeiro inimigo
                } else if (i==ex2 && j==ey2) {
                    cout<<char(6); // segundo inimigo
                } else {
                    switch (m[i][j]){
                        case 0: cout<<" "; break; //caminho
                        case 1: cout<<char(219); break; //parede
                        case 2: cout<<"#"; break; //parede quebrável
                        case 3: cout<<char(207); break; //bomba
                        case 4: cout<<"*"; break; //explosão da bomba
                        //default: cout<<"-"; //erro
                    } //fim switch
                }
            }
            cout<<"\n";
        } //fim for mapa
        
        contadorMovimentoInimigo++;
        if (contadorMovimentoInimigo == 30) { // move os inimigos a cada 10 iterações do loop
        movimentoInimigo(m, ex1, ey1);
        movimentoInimigo(m, ex2, ey2);
        contadorMovimentoInimigo = 0;
        }

        if (m[x][y] == 4) { // condição de fim : explodiu com a bomba
            return fimDeJogo();
        }
        if ((x == ex1 && y == ey1) || (x == ex2 && y == ey2)) {
            return fimDeJogo(); // o jogador colidiu com um inimigo
        }
        if (m[ex1][ey1] == 4) {
            ex1 = -1; // o primeiro inimigo foi atingido pela explosão da bomba
        }
        if (m[ex2][ey2] == 4) {
            ex2 = -1; // o segundo inimigo foi atingido pela explosão da bomba
        }
        if (ex1 == -1 && ex2 == -1) {
        cout << "\nVOCÊ VENCEU!"; 
        return 0; // verifica se o jogador matou todos os inimigos  
        }
        
        ///executa os movimentos
         if ( _kbhit() ){
            tecla = getch();
            switch(tecla)
            {
                case 72: case 'w': ///cima
                    if (verificaColisao(m, x-1, y)){
                        x--;

                    }
                break;
                case 80: case 's': ///baixo
                    if (verificaColisao(m, x+1, y)){
                       x++;

                    }

                break;
                case 75:case 'a': ///esquerda
                    if (verificaColisao(m, x, y-1)){
                        y--;

                    }
                break;
                case 77: case 'd': ///direita
                    if (verificaColisao(m, x, y+1)) {
                      y++;

                    }
                break;

                case 32:
                    if (!flagBomba){
                        inicio = clock();
                        bx = x;
                        by = y;
                    }
                    bomba(m,x,y,&flagBomba);
                break;
            }
         }

         if (flagBomba) {
            fim = clock();
            if ((fim-inicio)/CLOCKS_PER_SEC == 3) {
                m[bx][by]=4;
                if (m[bx+1][by]==0 || m[bx+1][by]==2) m[bx+1][by] = 4;
                if (m[bx-1][by]==0 || m[bx-1][by]==2) m[bx-1][by] = 4;
                if (m[bx][by+1]==0 || m[bx][by+1]==2) m[bx][by+1] = 4;
                if (m[bx][by-1]==0 || m[bx][by-1]==2) m[bx][by-1] = 4;
            }

            if ((fim-inicio)/CLOCKS_PER_SEC == 4) {
                m[bx][by]=0;
                if (m[bx+1][by]!=1) m[bx+1][by] = 0;
                if (m[bx-1][by]!=1) m[bx-1][by] = 0;
                if (m[bx][by+1]!=1) m[bx][by+1] = 0;
                if (m[bx][by-1]!=1) m[bx][by-1] = 0;
                flagBomba=false;
            }

        }


    } //fim do laço do jogo

    return 0;
} //fim main
