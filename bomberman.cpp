/**
    Estrutura inicial para um jogo de labirinto
    versão: 0.1 (Felski)
*/
#include <iostream>
#include<windows.h>
#include<conio.h>

using namespace std;

int map_size = 15;
int map[15][15]={ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                  1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                  1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,
                  1,0,0,0,1,0,1,1,1,1,1,1,1,1,1,
                  1,1,0,0,1,0,0,0,0,0,1,1,1,1,1,
                  1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,
                  1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,
                  1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,
                  1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,
                  1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,
                  1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,
                  1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,
                  1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,
                  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

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


    //Posi��o inicial do personagem no console
    int x=5, y=5;
    //Vari�vel para tecla precionada
    char tecla;

    while(true){
        ///Posiciona a escrita no início do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<map_size;i++){
            for(int j=0;j<map_size;j++){
                if(i==x && j==y){
                    cout<<char(2); //personagem
                } else {
                    switch (map[i][j]){
                        case 0: cout<<" "; break; //caminho
                        case 1: cout<<char(219); break; //parede
                        //default: cout<<"-"; //erro
                    } //fim switch
                }
            }
            cout<<"\n";
        } //fim for mapa

        ///executa os movimentos
         if ( _kbhit() ){
            tecla = getch();
            check_map(tecla, x, y);
         }


    } //fim do laço do jogo

    return 0;
} //fim main

void check_map(char direcao, int x, int y){
    switch(direcao)
    {
        case 72: case 'w': ///cima
            if (map[x][y-1] == 0){
                y--;
            }
        break;
        case 80: case 's': ///baixo
            if (map[x][y+1] == 0){
                y++;
            }
        break;
        case 75:case 'a': ///esquerda
            if (map[x--][y] == 0){
                x--;
            }
        break;
        case 77: case 'd': ///direita
            if (map[x++][y] == 0){
                x++;
            }
        break;
    }
}