#include <iostream> //Cout, Cin, etc...
#include <windows.h> //Biblioteca windows para o terminal.
#include <conio.h> //Teclado.
#include <time.h> //Usar o tempo.
#include <cstdlib>
#include <fstream>
#include <string>

#include "bomb_class.hpp"
#include "SaveLoad.hpp"
#include "bomb_func.hpp"

using namespace std;

obj B; //Bomba

obj F; //Chama

creature P; //Player

creature E[5]; //Inimigo

Powerup bomb3x3;
Powerup bombRand;

int powerups_quantity = 0;
Powerup** powerup = new Powerup*[powerups_quantity]; //Powerups

//Mapa
int map_size_x;
int map_size_y;
char** map;
const int maps_quantity = 2;
const char* map_names[maps_quantity] = {"map_file.txt", "map2_file.txt"};
int current_map;

string GameState = "Open";

//Variáveis para contagem do tempo.
int timer_bomb = 0;
int timer_flame = 0;
int timer_enemy = 0;
int timer_game = 0;

//Número de parede destruída.
int walls_destroyed = 0;
int** walls_destroyed_array = new int*[walls_destroyed];

//g++.exe C:\Users\Usuario\Downloads\bomberman-main\*.cpp C:\Users\Usuario\Downloads\bomberman-main\*.hpp -o C:\Users\Usuario\Downloads\bomberman-main\bomberman.exe

void load_map(const char* map_file_name) {
    ifstream map_file;
    map_file.open(map_file_name);
    string c;
    int temp_value = 0;
    int y = 0;

    getline(map_file, c); //Pega o x e y do mapa.
    for (int i = 0; i < c.size(); i++) {
        if (c[i] == 'y') {
            while (c[i] != ',') {
                i++;
            }
            i--;

            for (int ii = 1; c[i] >= char(48) && c[i] <= char(57); ii *= 10) {//É um número (0, 9).
                temp_value += (int(c[i]) - '0') * ii;
                i--;
            }

            map = new char* [temp_value];
            map_size_y = temp_value;

            temp_value = 0;

            while (c[i] != 'x') {
                i--;
            }
            while (c[i] != ',') {
                i++;
            }
            i--;

            for (int ii = 1; c[i] >= char(48) && c[i] <= char(57); ii *= 10) {//É um número (0, 9).
                temp_value += (int(c[i]) - '0') * ii;
                i--;
            }

            for (int i = 0; i < map_size_y; i++) {
                map[i] = new char[temp_value];
            }

            map_size_x = temp_value;
            break;
        }
    }
    do {
        getline(map_file, c);
        for (int i = 0; i < c.size() + 1; i++) {
            if (c[i] == '@') {
                map[y][i] = char(219);
            }
            else if (c[i] == '#') {
                map[y][i] = char(178);
            }
            else if (c[i] == ' ') {
                map[y][i] = ' ';
            }
        }
        y++;
    } while (!map_file.eof());

    map_file.close();
}

///////////////////////////////////////////////\    /\//////////////////////////////////////////////
//////////////////////////////////////////////  \  /  \/////////////////////////////////////////////
/////////////////////////////////////////////    \/    \////////////////////////////////////////////
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

    //Variavel para a tecla precionada.
    char keyboard;

    B.draw = char(208);
    F.draw = '#';

    while (true) {
        ///Posiciona a escrita no início do console.
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        if (GameState == "Open"){
            SetConsoleTextAttribute(hConsole, 12);
            cout << " ______   _______  _______  ______   _______  _______  _______  _______  _        \n";
            cout << "(  ___ \\ (  ___  )(       )(  ___ \\ (  ____ \\(  ____ )(       )(  ___  )( (    /| \n";
            cout << "| (   ) )| (   ) || () () || (   ) )| (    \\/| (    )|| () () || (   ) ||  \\  ( | \n";
            cout << "| (__/ / | |   | || || || || (__/ / | (__    | (____)|| || || || (___) ||   \\ | | \n";
            cout << "|  __ (  | |   | || |(_)| ||  __ (  |  __)   |     __)| |(_)| ||  ___  || (\\ \\) | \n";
            cout << "| (  \\ \\ | |   | || |   | || (  \\ \\ | (      | (\\ (   | |   | || (   ) || | \\   | \n";
            cout << "| )___) )| (___) || )   ( || )___) )| (____/\\| ) \\ \\__| )   ( || )   ( || )  \\  | \n";
            cout << "|/ \\___/ (_______)|/     \\||/ \\___/ (_______/|/   \\__/|/     \\||/     \\||/    )_) \n";

            cout << " /\\  _  _  __|_ _    _  _ _  _  _  _    _  _  _ _    . _  _  _  _| \n";
            cout << "/~~\\|_)(/_|  | (/_  (/__\\|_)(_|(_ (_)  |_)(_|| (_|   |(_)(_|(_|| . \n";
            cout << "    |                    |             |            L|    _|       \n";

            cout << "\n\n\n Desenvolvido por Guilherme Mohr, Lucas Alexandre e Joao Victor Ferreira. ";


            if (_kbhit()) {
                keyboard = _getch();
                if(keyboard == 32){
                    GameState = "menu";
                    system("cls");
                }
            }
        }
        else if (GameState == "menu") {
            cout << "     __                   __                            _ __  \n";
            cout << "  /\\ \\ \\_____   _____     \\ \\  ___   __ _  ___         | '_ \\ \n";
            cout << " /  \\/ / _ \\ \\ / / _ \\     \\ \\/ _ \\ / _` |/ _ \\        | | | |\n";
            cout << "/ /\\  / (_) \\ V / (_) | /\\_/ / (_) | (_| | (_) |       |_| |_|\n";
            cout << "\\_\\ \\/ \\___/ \\_/ \\___/  \\___/ \\___/ \\__, |\\___/      \n";
            cout << "                                    |___/                      \n";
            cout << "\n";
            cout << "   __                      __       _                    ___     \n";
            cout << "   \\ \\  ___   __ _  ___   / _\\ __ _| |_   _____         / __|    \n";
            cout << "    \\ \\/ _ \\ / _` |/ _ \\  \\ \\ / _` | \\ \\ / / _ \\        \\__ \\    \n";
            cout << " /\\_/ / (_) | (_| | (_) | _\\ \\ (_| | |\\ V / (_) |       |___/    \n";
            cout << " \\___/ \\___/ \\__, |\\___/  \\__/\\__,_|_| \\_/ \\___/           \n";
            cout << "             |___/                                                 \n";
            cout << "\n\n\n Desenvolvido por Guilherme Mohr, Lucas Alexandre e Joao Victor Ferreira.";
            cout << "\n\n !!! Pressione as setas do teclado, ou as teclas A, W, S, D, para movimentar o personagem, e espaco para soltar a bomba !!!";

            if (_kbhit()) {
                keyboard = _getch();
                if (keyboard == 'n') { //Novo Jogo.
                    F.x = 0; F.y = 0;
                    P.x = 5; P.y = 5;
                    P.facing = 'd';
                    P.draw = char(2);

                    system("cls");

                    for (int i = 0; i < maps_quantity; i++) {
                        load_map(map_names[i]);
                        SetConsoleTextAttribute(hConsole, 8);
                        cout << map_names[i] << " - " << i << '\n';
                        for (int h = 0; h < map_size_y; h++) {
                            for (int w = 0; w < map_size_x; w++) {
                                switch (map[h][w]) {
                                    case ' ': SetConsoleTextAttribute(hConsole, 0); cout << ' '; break; //caminho.
                                    case char(219) : SetConsoleTextAttribute(hConsole, 8); cout << char(219); break; //parede.
                                    case char(178) : SetConsoleTextAttribute(hConsole, 8);  cout << char(178); break; //parede frágil.
                                }
                            }
                            cout << "\n";
                        } //fim for mapa.
                        cout << "\n";

                        for (int i = 0; i < map_size_x; i++) {
                            delete map[i];
                        }
                        delete map;
                    }

                    GameState = "new";
                }
                else if (keyboard == 's') { //Jogo Salvo.
                    load_game();
                    GameState = "running";
                    system("cls");

                    load_map(map_names[current_map]);
                    map[P.y][P.x] = P.draw;
                    for (int i = 0; i < sizeof(E) / sizeof(E[i]); i++) {
                        if (E[i].alive) {
                            map[E[i].y][E[i].x] = E[i].draw;
                        }
                    }
                    if (B.exist) {
                        map[B.y][B.x] = B.draw;
                    }
                    if (F.exist) {
                        map[F.y][F.x] = F.draw;
                    }
                }
            }
        } else if (GameState == "new") {
            if (_kbhit()) {
                keyboard = _getch();
                for (int i = 0; i < maps_quantity; i++) {
                    if (keyboard == '0' + i) {
                        load_map(map_names[i]);
                        current_map = i;

                        timer_game = time(NULL);

                        //Coloca inimigos no mapa.
                        for (int i = 0; i < sizeof(E) / sizeof(E[i]); i++)
                        {
                            switch (rand() % 4) {
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
                                E[i].x = rand() % (map_size_x - 1);
                                E[i].y = rand() % (map_size_y - 1);
                            } while (map[E[i].y][E[i].x] != ' ');

                            map[E[i].y][E[i].x] = E[0].draw;
                        };

                        //Posição inicial do jogador.
                        do {
                            P.x = rand() % (map_size_x - 1);
                            P.y = rand() % (map_size_y - 1);
                        } while (map[P.y][P.x] != ' ');

                        map[P.y][P.x] = char(2);

                        GameState = "running";
                        system("cls");
                    }
                }
            }
        } else if (GameState == "paused"){
            cout<<"Voltar (aperte espaco)\n";
            cout<<"Salvar (aperte S)\n";
            cout<<"Sair (aperte esc)\n";
            if (_kbhit()) {
                keyboard = _getch();
                if(keyboard == 27){
                    return 0;
                } else if (keyboard == 's'){
                    timer_game = time(NULL) - timer_game;
                    save();
                    timer_game = time(NULL) - timer_game;
                } else if (keyboard == 32){
                    timer_bomb = time(NULL) - timer_bomb;
                    timer_flame = time(NULL) - timer_flame;
                    timer_enemy = time(NULL) - timer_enemy;
                    timer_game = time(NULL) - timer_game;
                    GameState = "running";
                    system("cls");
                }
            }

        } else if (GameState == "running"){
            SetConsoleTextAttribute(hConsole, 8);
            cout << time(NULL) - timer_game << "\n";
            ///Imprime o jogo: mapa e personagem.
            for (int h = 0; h < map_size_y; h++) {
                for (int w = 0; w < map_size_x; w++) {
                    if (P.x == w && P.y == h) { SetConsoleTextAttribute(hConsole, 15); cout << P.draw; }
                    else {
                        switch (map[h][w]) {
                            case ' ': SetConsoleTextAttribute(hConsole, 0); cout << ' '; break; //caminho.
                            case char(219) : SetConsoleTextAttribute(hConsole, 8); cout << char(219); break; //parede.
                            case char(178) : SetConsoleTextAttribute(hConsole, 8);  cout << char(178); break; //parede frágil.
                            case char(2) : SetConsoleTextAttribute(hConsole, 15); cout << P.draw; break; //player.
                            case char(208) : SetConsoleTextAttribute(hConsole, 8);  cout << B.draw; break; //bomba.
                            case '#': SetConsoleTextAttribute(hConsole, 12); cout << F.draw; break; //chama.
                            case char(1) : SetConsoleTextAttribute(hConsole, 12); cout << E[0].draw; break; //inimigos.
                            case char(111) : SetConsoleTextAttribute(hConsole, 11); cout <<char(111); break;
                            case char(4) : SetConsoleTextAttribute(hConsole, 14); cout <<char(4); break;
                        }
                    }
                }
                cout << "\n";
            } //fim for mapa.

            if (P.alive != true){
                GameState = "gameover";
            }

            //Mostra a bomba se escondida.
            if(!B.exist){
                B.hidden = false;
            }
            else if(B.hidden){
                if(map[B.y][B.x] == ' '){
                    map[B.y][B.x] = B.draw;
                    B.hidden = false;
                }
            }

            //Inimigo anda.
            if (time(NULL) - timer_enemy > 0.5) {
                bool alive = false;
                for (int i = 0; i < sizeof(E) / sizeof(E[i]); i++) {
                    if (E[i].alive) {
                        timer_enemy = enemy_move(i);
                        alive = true;
                    }
                }
                if(!alive){
                    GameState = "gameover";
                }
            }

            //Explode a bomba se existir.
            if (time(NULL) - timer_bomb >= 3 && B.exist) {
                switch(P.powerup){
                    case 'B':
                        timer_flame = explode_bomb(B.x, B.y, bomb3x3.get_size());
                        bomb3x3.set_quantity(bomb3x3.get_quantity()-1);
                        if(bomb3x3.get_quantity() == 0){
                            bomb3x3.set_active(false);
                            P.powerup = ' ';
                        }
                    break;

                    case 'R':
                        timer_flame = explode_bomb(B.x, B.y, bombRand.get_size());
                        bombRand.set_quantity(bombRand.get_quantity()-1);
                        if(bomb3x3.get_quantity() == 0){
                            bomb3x3.set_active(false);
                            P.powerup = ' ';
                        }
                    break;

                    default:
                        timer_flame = explode_bomb(B.x, B.y);
                }
                P.draw = char(2);
            }
                

            //Se existir chamas deixadas pela bomba as extingue depois de um tempo.
            switch(P.powerup){
                    case 'B':
                        extingue_fire(bomb3x3.get_size());
                    break;

                    case 'R':
                        extingue_fire(bombRand.get_size());
                    break;

                    default:
                        extingue_fire();
            }

            ///executa os movimentos.
            if (_kbhit()) {
                keyboard = _getch();

                map[P.y][P.x] = ' '; //Apaga o jogador para atualizar sua posição.

                //Coloca a bomba se requisitado.
                if (time(NULL) - timer_bomb >= 3.5) {
                    if (keyboard == char(32)) {
                        timer_bomb = check_map_bomb(P.facing, P.x, P.y);
                    }
                }

                P.facing = check_map(keyboard, P.x, P.y); //Checa o mapa para movimentar o jogador.
                map[P.y][P.x] = char(2); //Coloca o jogador na sua posição atualizada.

                if(keyboard == 27){
                    timer_bomb = time(NULL) - timer_bomb;
                    timer_flame = time(NULL) - timer_flame;
                    timer_enemy = time(NULL) - timer_enemy;
                    timer_game = time(NULL) - timer_game;
                    GameState = "paused";
                    system("cls");
                }
            }
        } else if (GameState == "gameover"){
            system("cls");

            for (int i = 0; i < walls_destroyed; i++) {
                delete walls_destroyed_array[i];
            }
            delete walls_destroyed_array;

            for (int i = 0; i < map_size_x; i++) {
                delete map[i];
            }
            delete map;

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
                    cout << "  ________                        ________                         \n";
                    cout << " / _____ / _____    _____   ____   \\_____  \\___   __ ___________ \n";
                    cout << "/   \\  ___\\__   \\  /     \\_/ __ \\   /   |   \\  \\ / // __ \\_  __ \\     \n";
                    cout << "\\    \\_\\  \\/ __  \\|  Y Y  \\  ___/  /    |    \\    /\\  ___/|  | \\/\n";
                    cout << " \\______  (____  / __|_|  /\\__  >  \\______  / \\_ /  \\___  >__|    \n";
                    cout << "        \\/     \\/       \\/    \\/          \\/           \\/        \n";
                }
            do{
                if (_kbhit()){
                    return 0;
                }
            }while(true);
        }
    } //fim do laço do jogo.
    return 0;
} //fim main.
