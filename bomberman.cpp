#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <cstdlib>

using namespace std;

struct bomb {
    int x;
    int y;
    bool exist = false;
    bool hidden = false;
    char draw = char(208);
};
bomb B;

struct flame {
    int x = 0;
    int y = 0;
    bool exist = false;
    char draw = '#';
};
flame F;

struct player {
    int x = 5;
    int y = 5;
    bool alive = true;
    char facing = 'd';
    char draw = char(2);
};
player P;

struct enemys {
    int x[5];
    int y[5];
    bool alive[5] = {true,true,true,true,true};
    char facing[5];
    char draw = char(1);
};
enemys E;

int map_size = 15;
int map[15][15] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
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
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };

char check_map(char direction, int& x, int& y) {
    switch (direction)
    {
    case 72: case 'w': ///cima
        if (map[y - 1][x] == 0) {
            y = y - 1;
            return 'w';
        } else if (map[y - 1][x] == 4) {
            B.hidden = true;
            y = y - 1;
            return 'w';
        }
        break;
    case 80: case 's': ///baixo
        if (map[y + 1][x] == 0) {
            y = y + 1;
            return 's';
        } else if (map[y + 1][x] == 4) {
            B.hidden = true;
            y = y + 1;
            return 's';
        }
        break;
    case 75: case 'a': ///esquerda
        if (map[y][x - 1] == 0) {
            x = x - 1;
            return 'a';
        } else if (map[y][x - 1] == 4) {
            B.hidden = true;
            x = x - 1;
            return 'a';
        }
        break;
    case 77: case 'd': ///direita
        if (map[y][x + 1] == 0) {
            x = x + 1;
            return 'd';
        } else if (map[y][x + 1] == 4) {
            B.hidden = true;
            x = x + 1;
            return 'd';
        }
        break;
    }
    return ' ';
}

int create_bomb(int x, int y) {
    map[y][x] = 4;
    B.x = x;
    B.y = y;
    B.exist = true;
    P.draw = char(1);
    return time(NULL);
}

int check_map_bomb(char facing, int  x, int  y) {
    switch (facing)
    {
    case 'w': ///cima
        if (map[y - 1][x] == 0) {
            return create_bomb(x, y - 1);
        }
        break;
    case 's': ///baixo
        if (map[y + 1][x] == 0) {
            return create_bomb(x, y + 1);
        }
        break;
    case 'a': ///esquerda
        if (map[y][x - 1] == 0) {
            return create_bomb(x - 1, y);
        }
        break;
    case 'd': ///direita
        if (map[y][x + 1] == 0) {
            return create_bomb(x + 1, y);
        }
        break;
    }
}

void kill_enemy(int x, int y){
    for(int i=0; i < 5; i++){
        if(E.x[i] == x && E.y[i] == y){
            E.alive[i] = false;
        }
    }
}

int explode_bomb(int x, int y) {
    if(map[y][x] == 6){
        kill_enemy(x, y);
    } else if (map[y][x] == 3) {
        P.alive = false;
    }
    map[y][x] = 5;

    if (map[y - 1][x] != 1) {
        if(map[y - 1][x] == 6){
            kill_enemy(x, y);
        } else if (map[y - 1][x] == 3) {
            P.alive = false;
        }

        map[y - 1][x] = 5;
    }
    if (map[y + 1][x] != 1) {
        if(map[y + 1][x] == 6){
            kill_enemy(x, y);
        } else if (map[y + 1][x] == 3) {
            P.alive = false;
        }

        map[y + 1][x] = 5;
    }
    if (map[y][x - 1] != 1) {
        if(map[y][x - 1] == 6){
            kill_enemy(x, y);
        } else if (map[y][x - 1] == 3) {
            P.alive = false;
        }

        map[y][x - 1] = 5;
    }
    if (map[y][x + 1] != 1) {
        if(map[y][x + 1] == 6){
            kill_enemy(x, y);
        } else if (map[y][x + 1] == 3) {
            P.alive = false;
        }

        map[y][x + 1] = 5;
    }
    F.x = x;
    F.y = y;
    B.exist = false;
    F.exist = true;
    return time(NULL);
}

int enemy_move(int i){
    map[E.y[i]][E.x[i]] = 0;

    if(check_map(E.facing[i], E.x[i], E.y[i]) == ' '){
        switch(E.facing[i]){
            case 'a':
                if (map[E.y[i]][E.x[i]-1] == 3) {
                    P.alive = false;
                }
                E.facing[i] = 's';
            break;
            case 's':
                if (map[E.y[i] + 1][E.x[i]] == 3) {
                    P.alive = false;
                }
                E.facing[i] = 'd';
            break;
            case 'd':
                if (map[E.y[i]][E.x[i] + 1] == 3) {
                    P.alive = false;
                }
                E.facing[i] = 'w';
            break;
            case 'w':
                if (map[E.y[i] + 1][E.x[i]] == 3) {
                    P.alive = false;
                }
                E.facing[i] = 'a';
            break;
        }
    }

    map[E.y[i]][E.x[i]] = 6;

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
    short int CX = 0, CY = 0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;
    //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, ACIMA.

    srand(time(NULL));

    //Prepara o código para pegar o tempo atual em segundos.
    time_t seconds;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Coloca inimigos no mapa.
    for (int i = 0; i < sizeof(E.x) / sizeof(*E.x); i++)
    {
        switch(rand()%4){
            case 1:
                E.facing[i] = 'a';
            break;
            case 2:
                E.facing[i] = 's';
            break;
            case 3:
                E.facing[i] = 'd';
            break;
            case 4:
                E.facing[i] = 'w';
            break;
            default:
                E.facing[i] = 'w';
        }

        do {
            E.x[i] = (rand() % map_size) - 1;
            E.y[i] = (rand() % map_size) - 1;
        } while (map[E.y[i]][E.x[i]] != 0);

        map[E.y[i]][E.x[i]] = 6;
    };


    //Variavel para a tecla precionada
    char keyboard;

    //Variáveis para contagem do tempo.
    int timer = 0;
    int timer2 = 0;
    int timer3 = 0;

    //Posição inicial do jogador.
    map[P.y][P.x] = 3;

    while (P.alive) {
        ///Posiciona a escrita no início do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for (int h = 0; h < map_size; h++) {
            for (int w = 0; w < map_size; w++) {
                switch (map[h][w]) {
                case 0: SetConsoleTextAttribute(hConsole, 0); cout << " "; break; //caminho
                case 1: SetConsoleTextAttribute(hConsole, 8); cout << char(219); break; //parede
                case 2: SetConsoleTextAttribute(hConsole, 8);  cout << char(178); break; //parede frágil
                case 3: SetConsoleTextAttribute(hConsole, 15); cout << P.draw; break; //player
                case 4: SetConsoleTextAttribute(hConsole, 8);  cout << B.draw; break; //bomba
                case 5: SetConsoleTextAttribute(hConsole, 12); cout << F.draw; break; //chama
                case 6: SetConsoleTextAttribute(hConsole, 12); cout << E.draw; break; //inimigos
                    //default: cout<<"-"; //erro
                 //fim switch
                }
            }
            cout << "\n";
        } //fim for mapa

        ///executa os movimentos
        if (_kbhit()) {
            keyboard = _getch();

            map[P.y][P.x] = 0; //Apaga o jogador para atualizar sua posição.

            //Coloca a bomba se requisitado.
            if (time(NULL) - timer >= 5.5) {
                if (keyboard == char(32)) {
                    timer = check_map_bomb(P.facing, P.x, P.y);
                }
            }

            P.facing = check_map(keyboard, P.x, P.y); //Checa o mapa para movimentar o jogador.
            map[P.y][P.x] = 3; //Coloca o jogador na sua posição atualizada.
        }

        if(B.hidden){
            if(map[B.y][B.x] == 0){
                map[B.y][B.x] = 4;
                B.hidden = false;
            }
        }

        if (time(NULL) - timer3 > 0.5) {
            for (int i = 0; i < 5; i++) {
                if (E.alive[i]) {
                    timer3 = enemy_move(i);
                }
            }
        }

        //Explode a bomba se existir.
        if (time(NULL) - timer >= 5 && B.exist) {
            timer2 = explode_bomb(B.x, B.y);
            P.draw = char(2);
        }

        //Se existir chamas deixadas pela bomba as extingue depois de um tempo.
        if (time(NULL) - timer2 >= 0.5 && F.exist) {
            if (map[F.y - 1][F.x] == 5) {
                map[F.y - 1][F.x] = 0;
            }
            if (map[F.y + 1][F.x] == 5) {
                map[F.y + 1][F.x] = 0;
            }
            if (map[F.y][F.x - 1] == 5) {
                map[F.y][F.x - 1] = 0;
            }
            if (map[F.y][F.x + 1] == 5) {
                map[F.y][F.x + 1] = 0;
            }
            if (time(NULL) - timer2 >= 1) {
                if (map[F.y][F.x] == 5) {
                    map[F.y][F.x] = 0;
                    F.exist = false;
                }
            }
        }

    } //fim do laço do jogo

    system("cls");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    SetConsoleTextAttribute(hConsole, 15);

    cout << "       ________                        ________                         \n";
    cout << "      / _____ / _____    _____   ____   \\_____  \\___   __ ___________ \n";
    cout << "     /   \\  ___\\__   \\  /     \\_/ __ \\   /   |   \\  \\ / // __ \\_  __ \\     \n";
    cout << "     \\    \\_\\  \\/ __  \\|  Y Y  \\  ___/  /    |    \\    /\\  ___/|  | \\/\n";
    cout << "      \\______  (____  / __|_|  /\__  >    \______  / \\_ /  \\___  >__|    \n";
    cout << "             \\/     \\/       \\/    \\/          \\/           \\/        \n";

    return 0;
} //fim main
