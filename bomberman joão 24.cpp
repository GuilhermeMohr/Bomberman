/**
    Estrutura inicial para um jogo de labirinto
    versão: 0.1 (Felski)
*/
#include <iostream>
#include<windows.h>
#include<conio.h>

using namespace std;

struct inimigos{

    int x [5];
    int y [5];
    char desenho = char (1);
};
inimigos inimigos;

struct player{
    int x = 5;
    int y = 5;
    char desenho = char(2);
};
player p1;

int map_size = 15;
int map[15][15]={ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                  1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
                  1,1,1,1,2,1,1,1,1,0,1,2,1,0,1,
                  1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
                  1,2,1,1,1,1,2,1,1,0,2,1,1,2,1,
                  1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                  1,0,1,1,1,2,1,1,1,2,2,1,1,1,1,
                  1,0,0,0,0,0,0,2,0,0,0,0,0,0,1,
                  1,1,1,1,2,1,2,1,2,1,2,1,1,0,1,
                  1,0,0,0,2,0,1,0,0,2,0,1,0,0,1,
                  1,2,1,1,1,1,1,1,1,1,2,1,0,0,1,
                  1,0,0,0,0,1,0,2,0,0,1,0,2,0,1,
                  1,0,1,1,0,2,0,1,0,0,2,0,1,0,1,
                  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

void check_map(char direcao, int &x, int &y){
    cout<<direcao;
    switch(direcao)
    {
        case 'w': ///cima
            if (map[y-1][x] == 0 || map[y-1][x] == 4 ){
                y = y-1;
            }
        break;
        case 's': ///baixo
            if (map[y+1][x] == 0 || map[y+1][x] == 4){
                y = y+1;
            }
        break;
        case 'a': ///esquerda
            if (map[y][x-1] == 0 || map[y][x-1] == 0){
                x = x-1;
            }
        break;
        case 'd': ///direita
            if (map[y][x+1] == 0 || map[y][x+1] == 0){
                x = x+1;
            }
        break;
    }
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

    //Vari�vel para tecla precionada
    char tecla;

    map[p1.y][p1.x] = 3;

    for(int i=0; i<5;i++)
    {
       do{
        inimigos.x[i] = (rand()%15)-1;
        inimigos.y[i] = (rand()%15)-1;
        }while(map[inimigos.y[i]][inimigos.x[i]] != 0);
         map[inimigos.y[i]][inimigos.x[i]]  = 6;
    };

    while(true){
        ///Posiciona a escrita no início do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for(int h=0;h<map_size;h++){
            for(int w=0;w<map_size;w++){
                switch (map[h][w]){
                    case 0: cout<<" "; break; //caminho
                    case 1: cout<<char(219); break; //parede
                    case 2: cout<<char(177); break; //parede_frágil
                    case 3: cout<<p1.desenho; break; //player
                    case 4: cout<<char(208); break; //bomba
                    case 6: cout<<inimigos.desenho; break; //inimigos
                    //default: cout<<"-"; //erro
                 //fim switch
                }
            }
            cout<<"\n";
        } //fim for mapa

        ///executa os movimentos
         if ( _kbhit() ){
            map[p1.y][p1.x] = 0;
            tecla = getch();
            check_map(tecla, p1.x, p1.y);
            map[p1.y][p1.x] = 3;
         }


    } //fim do laço do jogo

    return 0;
} //fim main
