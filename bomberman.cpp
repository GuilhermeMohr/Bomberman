#include <iostream> //Cout, Cin, etc...
#include <windows.h> //Biblioteca windows para o terminal.
#include <conio.h> //Teclado.
#include <time.h> //Usar o tempo.
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
    int x;
    int y;
    bool alive = true;
    char facing;
    char draw = char(1);
};
enemys E[5];

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

char check_map(char direction, int& x, int& y) { //Move os carinhas pelo mapa.
    switch (direction)
    {
    case 72: case 'w': ///cima
        if (map[y - 1][x] == 0) { //Checa se o espaço é livre
            y = y - 1;
            return 'w';
        } else if (map[y - 1][x] == 4) { //Checa se há uma bomba
            B.hidden = true; //Esconde a bomba
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

int create_bomb(int x, int y) { //Cria nova bomba
    map[y][x] = 4;
    B.x = x;
    B.y = y;
    B.exist = true;
    P.draw = char(1);
    return time(NULL);
}

//Checa se é possível colocar uma bomba no mapa conforme a orientação do jogador
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

void kill_enemy(int x, int y){ //Mata um inimigo
    for(int i=0; i < 5; i++){
        if(E[i].x == x && E[i].y == y){
            E[i].alive = false;
        }
    }
}

int explode_bomb(int x, int y) { //Explode a bomba, matando inimigos e o jogador
    kill_enemy(x, y); //Matar inimigo

    if (map[y][x] == 3) { //Matar jogador
        P.alive = false;
    }
    map[y][x] = 5; //Colocar chama

    if (map[y - 1][x] != 1) {
        kill_enemy(x, y-1);

        if (map[y - 1][x] == 3) {
            P.alive = false;
        }
        map[y - 1][x] = 5;
    }

    if (map[y + 1][x] != 1) {
        kill_enemy(x, y+1);

        if (map[y + 1][x] == 3) {
            P.alive = false;
        }
        map[y + 1][x] = 5;
    }

    if (map[y][x - 1] != 1) {
        kill_enemy(x-1, y);

        if (map[y][x - 1] == 3) {
            P.alive = false;
        }
        map[y][x - 1] = 5;
    }
    if (map[y][x + 1] != 1) {
        kill_enemy(x+1, y);

        if (map[y][x + 1] == 3) {
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

int enemy_move(int i){ //Move o inimigo.
    map[E[i].y][E[i].x] = 0;

    if(check_map(E[i].facing, E[i].x, E[i].y) == ' '){ //Se bateu em uma parede gira.
        switch(E[i].facing){
            case 'a':
                if (map[E[i].y][E[i].x-1] == 3) {
                    P.alive = false;
                }
                E[i].facing = 's';
            break;
            case 's':
                if (map[E[i].y + 1][E[i].x] == 3) {
                    P.alive = false;
                }
                E[i].facing = 'd';
            break;
            case 'd':
                if (map[E[i].y][E[i].x + 1] == 3) {
                    P.alive = false;
                }
                E[i].facing = 'w';
            break;
            case 'w':
                if (map[E[i].y + 1][E[i].x] == 3) {
                    P.alive = false;
                }
                E[i].facing = 'a';
            break;
        }
    }

    map[E[i].y][E[i].x] = 6;

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

    //Randomizar a seed das funções rand().
    srand(time(NULL));

    //Prepara o código para pegar o tempo atual em segundos.
    time_t seconds;

    //Recebe a entrada e saída padrão.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Coloca inimigos no mapa.
    for (int i = 0; i < sizeof(E) / sizeof(E[i]); i++)
    {
        switch(rand()%4){
            case 1:
                E[i].facing = 'a';
            break;
            case 2:
                E[i].facing = 's';
            break;
            case 3:
                E[i].facing = 'd';
            break;
            case 4:
                E[i].facing = 'w';
            break;
            default:
                E[i].facing = 'w';
        }

        do {
            E[i].x = (rand() % map_size) - 1;
            E[i].y = (rand() % map_size) - 1;
        } while (map[E[i].y][E[i].x] != 0);

        map[E[i].y][E[i].x] = 6;
    };


    //Variavel para a tecla precionada.
    char keyboard;

    //Variáveis para contagem do tempo.
    int timer = 0;
    int timer2 = 0;
    int timer3 = 0;

    //Posição inicial do jogador.
    map[P.y][P.x] = 3;

    while (P.alive) {
        ///Posiciona a escrita no início do console.
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for (int h = 0; h < map_size; h++) {
            for (int w = 0; w < map_size; w++) {
                switch (map[h][w]) {
                case 0: SetConsoleTextAttribute(hConsole, 0); cout << " "; break; //caminho.
                case 1: SetConsoleTextAttribute(hConsole, 8); cout << char(219); break; //parede.
                case 2: SetConsoleTextAttribute(hConsole, 8);  cout << char(178); break; //parede frágil.
                case 3: SetConsoleTextAttribute(hConsole, 15); cout << P.draw; break; //player.
                case 4: SetConsoleTextAttribute(hConsole, 8);  cout << B.draw; break; //bomba.
                case 5: SetConsoleTextAttribute(hConsole, 12); cout << F.draw; break; //chama.
                case 6: SetConsoleTextAttribute(hConsole, 12); cout << E[0].draw; break; //inimigos.
                //fim switch.
                }
            }
            cout << "\n";
        } //fim for mapa.

        ///executa os movimentos.
        if (_kbhit()) {
            keyboard = _getch();

            map[P.y][P.x] = 0; //Apaga o jogador para atualizar sua posição.

            //Coloca a bomba se requisitado.
            if (time(NULL) - timer >= 3.5) {
                if (keyboard == char(32)) {
                    timer = check_map_bomb(P.facing, P.x, P.y);
                }
            }

            P.facing = check_map(keyboard, P.x, P.y); //Checa o mapa para movimentar o jogador.
            map[P.y][P.x] = 3; //Coloca o jogador na sua posição atualizada.
        }

        //Mostra a bomba se escondida.
        if(!B.exist){
            B.hidden = false;
        }
        else if(B.hidden){
            if(map[B.y][B.x] == 0){
                map[B.y][B.x] = 4;
                B.hidden = false;
            }
        }

        //Inimigo anda.
        if (time(NULL) - timer3 > 0.5) {
            bool alive = false;
            for (int i = 0; i < sizeof(E) / sizeof(E[i]); i++) {
                if (E[i].alive) {
                    timer3 = enemy_move(i);
                    alive = true;
                }
            }
            if(!alive){
                break;
            }
        }

        //Explode a bomba se existir.
        if (time(NULL) - timer >= 3 && B.exist) {
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

    } //fim do laço do jogo.

    system("cls");


    if(P.alive){
        SetConsoleTextAttribute(hConsole, 10);
        cout << "_____.___.               __      __                    \n";
        cout << "\\__  |   | ____  __ __  /  \\    /  \\____   ____     \n";
        cout << " /   |   |/  _ \\|  |  \\ \\   \\/\\/   /  _ \\ /    \\    \n";
        cout << " \\____   (  <_> )  |  /  \\        (  <_> )   |  \\ \n";
        cout << " / ______|\\____/|____/    \\__/\\  / \\____/|___|  /  \n";
        cout << " \\/                            \\/             \\/    \n";
    }else{
        SetConsoleTextAttribute(hConsole, 12);
        cout << "       ________                        ________                         \n";
        cout << "      / _____ / _____    _____   ____   \\_____  \\___   __ ___________ \n";
        cout << "     /   \\  ___\\__   \\  /     \\_/ __ \\   /   |   \\  \\ / // __ \\_  __ \\     \n";
        cout << "     \\    \\_\\  \\/ __  \\|  Y Y  \\  ___/  /    |    \\    /\\  ___/|  | \\/\n";
        cout << "      \\______  (____  / __|_|  /\__  >    \______  / \\_ /  \\___  >__|    \n";
        cout << "             \\/     \\/       \\/    \\/          \\/           \\/        \n";
    }

    return 0;
} //fim main.