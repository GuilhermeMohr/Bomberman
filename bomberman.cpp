/**
    Estrutura inicial para um jogo de labirinto
    versão: 0.1 (Felski)
*/
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

struct bomb{
    int x;
    int y;
    bool existe = false;
    char desenho = char(208);
};
bomb B;

struct chama{
    int x = 0;
    int y = 0;
    bool existe = false;
    char desenho = '#';
};
chama C;

struct player{
    int x = 5;
    int y = 5;
    char facing = 'd';
    char desenho = char(2);
};
player P;

struct inimigos {

    int x[5];
    int y[5];
    char desenho = char(1);
};
inimigos I;

int map_size = 15;
int map[15][15]={ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                  1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,
                  1,1,1,1,0,0,0,1,1,0,1,1,1,0,1,
                  1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                  1,0,1,1,1,1,2,1,1,0,0,1,1,2,1,
                  1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                  1,0,1,1,1,0,0,1,1,0,0,1,1,0,1,
                  1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,
                  1,0,1,1,2,2,2,1,1,1,1,1,1,0,1,
                  1,0,0,0,2,0,0,0,0,0,0,0,0,0,1,
                  1,2,1,1,2,0,0,1,1,1,2,1,1,0,1,
                  1,0,0,0,0,0,0,2,0,0,0,0,0,1,1,
                  1,0,1,1,0,0,0,2,0,0,0,1,1,0,1,
                  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

int create_bomb(int x, int y){
    map[y][x] = 4;
    B.x = x;
    B.y = y;
    B.existe = true;
    P.desenho = char(1);
    return time(NULL);
}

void check_map(char direcao, int &x, int &y){
    switch(direcao)
    {
        case 72: case 'w': ///cima
            if (map[y-1][x] == 0){
                y = y-1;
                P.facing = 'w';
            }
        break;
        case 80: case 's': ///baixo
            if (map[y+1][x] == 0){
                y = y+1;
                P.facing = 's';
            }
        break;
        case 75: case 'a': ///esquerda
            if (map[y][x-1] == 0){
                x = x-1;
                P.facing = 'a';
            }
        break;
        case 77: case 'd': ///direita
            if (map[y][x+1] == 0){
                x = x+1;
                P.facing = 'd';
            }
        break;
    }
}

int check_map_bomb(char facing, int  x, int  y){
    switch(facing)
    {
        case 'w': ///cima
            if (map[y-1][x] == 0){
                return create_bomb(x, y-1);
            }
        break;
        case 's': ///baixo
            if (map[y+1][x] == 0){
                return create_bomb(x, y+1);
            }
        break;
        case 'a': ///esquerda
            if (map[y][x-1] == 0){
                return create_bomb(x-1, y);
            }
        break;
        case 'd': ///direita
            if (map[y][x+1] == 0){
                return create_bomb(x+1, y);
            }
        break;
    }
}

int explode_bomb(int x, int y){
    map[y][x] = 5;
    if (map[y-1][x] != 1){
        map[y-1][x] = 5;
    }
    if (map[y+1][x] != 1){
        map[y+1][x] = 5;
    }
    if (map[y][x-1] != 1){
        map[y][x-1] = 5;
    }
    if (map[y][x+1] != 1){
        map[y][x+1] = 5;
    }
    C.x = x;
    C.y = y;
    B.existe = false;
    C.existe = true;
    return time(NULL);
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

    time_t seconds;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Vari�vel para tecla precionada
    char tecla;
    int timer=0;
    int timer2=0;

    map[P.y][P.x] = 3;

    while(true){
        ///Posiciona a escrita no início do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for(int h=0;h<map_size;h++){
            for(int w=0;w<map_size;w++){
                switch (map[h][w]){
                    case 0: SetConsoleTextAttribute(hConsole, 0); cout << " "; break; //caminho
                    case 1: SetConsoleTextAttribute(hConsole, 8); cout << char(219); break; //parede
                    case 2: SetConsoleTextAttribute(hConsole, 8);  cout << char(178); break; //parede_frágil
                    case 3: SetConsoleTextAttribute(hConsole, 15); cout << P.desenho; break; //player
                    case 4: SetConsoleTextAttribute(hConsole, 8);  cout << B.desenho; break; //bomba
                    case 5: SetConsoleTextAttribute(hConsole, 12); cout << C.desenho; break; //chama
                    //default: cout<<"-"; //erro
                 //fim switch
                }
            }
            cout<<"\n";
        } //fim for mapa

        ///executa os movimentos
        if ( _kbhit() ){
            map[P.y][P.x] = 0;
            tecla = _getch();
            if (time(NULL) - timer >= 5){
                if (tecla == char(32)){
                    timer = check_map_bomb(P.facing, P.x, P.y);
                }
            }
            
            check_map(tecla, P.x, P.y);
            map[P.y][P.x] = 3;
        }

        if (time(NULL) - timer >= 3 && B.existe) {
            timer2 = explode_bomb(B.x, B.y);
            P.desenho = char(2);
        }

        if (time(NULL) - timer2 >= 0.5 && C.existe) {
            if (map[C.y - 1][C.x] == 5) {
                map[C.y - 1][C.x] = 0;
            }
            if (map[C.y + 1][C.x] == 5) {
                map[C.y + 1][C.x] = 0;
            }
            if (map[C.y][C.x - 1] == 5) {
                map[C.y][C.x - 1] = 0;
            }
            if (map[C.y][C.x + 1] == 5) {
                map[C.y][C.x + 1] = 0;
            }
            if (time(NULL) - timer2 >= 1) {
                if (map[C.y][C.x] == 5) {
                    map[C.y][C.x] = 0;
                    C.existe = false;
                }
            }
        }

    } //fim do laço do jogo

    return 0;
} //fim main
