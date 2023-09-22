#include <iostream> //Cout, Cin, etc...
#include <windows.h> //Biblioteca windows para o terminal.
#include <conio.h> //Teclado.
#include <time.h> //Usar o tempo.
#include <cstdlib>
#include <fstream>
#include <string>
#include "bomb_class.h"
#include "bomb_func.h"

using namespace std;

ifstream map_file;

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

    char c;
    int i=0;
    int ii=0;
    map_file.open("map_file.txt");
    do {
        c = map_file.get();
        if (c == '\n') {
            i++;
            ii = 0;
        }
        else {
            map[i][ii] = int(c) - '0';
            ii++;
        }
    } while(!map_file.eof());

    map_file.close();

    B.set_draw(char(208));

    F.set_coord(0,0);
    F.set_draw('#');

    P.set_coord(5,5);
    P.set_facing('d');
    P.set_draw(char(2));

    //Coloca inimigos no mapa.
    for (int i = 0; i < sizeof(E) / sizeof(E[i]); i++)
    {
        switch(rand()%4){
            case 1:
                E[i].set_facing('a');
            break;
            case 2:
                E[i].set_facing('s');
            break;
            case 3:
                E[i].set_facing('d');
            break;
            case 4:
                E[i].set_facing('w');
            break;
            default:
                E[i].set_facing('w');
        }

        do {
            E[i].set_coord(rand() % (map_size-1), rand() % (map_size-1));
        } while (map[E[i].get_y()][E[i].get_x()] != 0);

        map[E[i].get_y()][E[i].get_x()] = 6;
    };


    //Variavel para a tecla precionada.
    char keyboard;

    //Variáveis para contagem do tempo.
    int timer = 0;
    int timer2 = 0;
    int timer3 = 0;

    //Posição inicial do jogador.
    map[P.get_y()][P.get_x()] = 3;

    while (P.get_alive()) {
        ///Posiciona a escrita no início do console.
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        ///Imprime o jogo: mapa e personagem.
        for (int h = 0; h < map_size; h++) {
            for (int w = 0; w < map_size; w++) {
                switch (map[h][w]) {
                case 0: SetConsoleTextAttribute(hConsole, 0); cout << " "; break; //caminho.
                case 1: SetConsoleTextAttribute(hConsole, 8); cout << char(219); break; //parede.
                case 2: SetConsoleTextAttribute(hConsole, 8);  cout << char(178); break; //parede frágil.
                case 3: SetConsoleTextAttribute(hConsole, 15); cout << P.get_draw(); break; //player.
                case 4: SetConsoleTextAttribute(hConsole, 8);  cout << B.get_draw(); break; //bomba.
                case 5: SetConsoleTextAttribute(hConsole, 12); cout << F.get_draw(); break; //chama.
                case 6: SetConsoleTextAttribute(hConsole, 12); cout << E[0].get_draw(); break; //inimigos.
                //fim switch.
                }
            }
            cout << "\n";
        } //fim for mapa.

        ///executa os movimentos.
        if (_kbhit()) {
            keyboard = _getch();

            map[P.get_y()][P.get_x()] = 0; //Apaga o jogador para atualizar sua posição.

            //Coloca a bomba se requisitado.
            if (time(NULL) - timer >= 3.5) {
                if (keyboard == char(32)) {
                    timer = check_map_bomb(P.get_facing(), P.get_x(), P.get_y());
                }
            }

            P.set_facing(check_map(keyboard, P)); //Checa o mapa para movimentar o jogador.
            map[P.get_y()][P.get_x()] = 3; //Coloca o jogador na sua posição atualizada.
        }

        //Mostra a bomba se escondida.
        if(!B.get_exist()){
            B.set_hidden(false);
        }
        else if(B.get_hidden()){
            if(map[B.get_y()][B.get_x()] == 0){
                map[B.get_y()][B.get_x()] = 4;
                B.set_hidden(false);
            }
        }

        //Inimigo anda.
        if (time(NULL) - timer3 > 0.5) {
            bool alive = false;
            for (int i = 0; i < sizeof(E) / sizeof(E[i]); i++) {
                if (E[i].get_alive()) {
                    timer3 = enemy_move(i);
                    alive = true;
                }
            }
            if(!alive){
                break;
            }
        }

        //Explode a bomba se existir.
        if (time(NULL) - timer >= 3 && B.get_exist()) {
            timer2 = explode_bomb(B.get_x(), B.get_y());
            P.set_draw(char(2));
        }

        //Se existir chamas deixadas pela bomba as extingue depois de um tempo.
        if (time(NULL) - timer2 >= 0.5 && F.get_exist()) {
            if (map[F.get_y() - 1][F.get_x()] == 5) {
                map[F.get_y() - 1][F.get_x()] = 0;
            }
            if (map[F.get_y() + 1][F.get_x()] == 5) {
                map[F.get_y() + 1][F.get_x()] = 0;
            }
            if (map[F.get_y()][F.get_x() - 1] == 5) {
                map[F.get_y()][F.get_x() - 1] = 0;
            }
            if (map[F.get_y()][F.get_x() + 1] == 5) {
                map[F.get_y()][F.get_x() + 1] = 0;
            }
            if (time(NULL) - timer2 >= 1) {
                if (map[F.get_y()][F.get_x()] == 5) {
                    map[F.get_y()][F.get_x()] = 0;
                    F.set_exist(false);
                }
            }
        }

    } //fim do laço do jogo.

    system("cls");


    if(P.get_alive()){
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
        cout << "      \\______  (____  / __|_|  /\\__  >    \\______  / \\_ /  \\___  >__|    \n";
        cout << "             \\/     \\/       \\/    \\/          \\/           \\/        \n";
    }

    return 0;
} //fim main.
