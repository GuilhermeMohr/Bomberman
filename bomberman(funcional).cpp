#include <iostream> //Cout, Cin, etc...
#include <windows.h> //Biblioteca windows para o terminal.
#include <conio.h> //Teclado.
#include <time.h> //Usar o tempo.
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

struct obj {
    int x;
    int y;
    bool exist = false;
    bool hidden = false;
    char draw = ' ';
};

struct creature {
    int x;
    int y;
    bool alive = true;
    char facing;
    char draw = char(1);
};

obj B; //Bomba

obj F; //Chama

creature P; //Player

creature E[5]; //Inimigo

ifstream map_file;

const char map_size = 15;
char map[map_size][map_size];

string GameState = "Open";

void save(int timer = 0, int timer2 = 0, int timer3 = 0){
    ofstream save_file;
    save_file.open("save.txt");
    save_file << "P: x=" << P.x << ", y=" << P.y << ", facing=" << P.facing << ", draw=" << P.draw << "\n";
    for(int i=0; i < sizeof(E) / sizeof(E[i]); i++){
        save_file << "E: x=" << E[i].x << ", y=" << E[i].y << ", facing=" << E[i].facing << ", draw=" << E[i].draw << ", alive=" << E[i].alive << "\n";
    }
    save_file << "B: x=" <<B.x << ", y=" << B.y << ", exist=" << B.exist << ", hidden=" << B.hidden << ", draw=" << B.draw << "\n";
    save_file << "F: x=" << F.x << ", y=" << F.y << ", exist=" << F.exist << ", hidden=" << F.hidden << ", draw=" << F.draw << "\n";
    save_file << "Timers: 1=" << timer << ", 2=" << timer2 << ", 3=" << timer3 << "\n";
    save_file.close();
    cout<<"Salvo\n";
}

char check_map(char direction, int& x, int& y) { //Move os carinhas pelo mapa.
    switch (direction)
    {
    case 72: case 'w': ///cima
        if (map[y - 1][x] == ' ') { //Checa se o espaço é livre
            y = y - 1;
            return 'w';
        } else if (map[y - 1][x] == B.draw) { //Checa se há uma bomba
            B.hidden = true; //Esconde a bomba
            y = y - 1;
            return 'w';
        }
        break;
    case 80: case 's': ///baixo
        if (map[y + 1][x] == ' ') {
            y = y + 1;
            return 's';
        } else if (map[y + 1][x] == B.draw) {
            B.hidden = true;
            y = y + 1;
            return 's';
        }
        break;
    case 75: case 'a': ///esquerda
        if (map[y][x - 1] == ' ') {
            x = x - 1;
            return 'a';
        } else if (map[y][x - 1] == B.draw) {
            B.hidden = true;
            x = x - 1;
            return 'a';
        }
        break;
    case 77: case 'd': ///direita
        if (map[y][x + 1] == ' ') {
            x = x + 1;
            return 'd';
        } else if (map[y][x + 1] == B.draw) {
            B.hidden = true;
            x = x + 1;
            return 'd';
        }
        break;
    }
    return ' ';
}

int create_bomb(int x, int y) { //Cria nova bomba
    map[y][x] = B.draw;
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
        if (map[y - 1][x] == ' ') {
            return create_bomb(x, y - 1);
        }
        break;
    case 's': ///baixo
        if (map[y + 1][x] == ' ') {
            return create_bomb(x, y + 1);
        }
        break;
    case 'a': ///esquerda
        if (map[y][x - 1] == ' ') {
            return create_bomb(x - 1, y);
        }
        break;
    case 'd': ///direita
        if (map[y][x + 1] == ' ') {
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

    if (map[y][x] == char(2)) { //Matar jogador
        P.alive = false;
    }
    map[y][x] = F.draw; //Colocar chama

    if (map[y - 1][x] != char(219)) {
        kill_enemy(x, y-1);

        if (map[y - 1][x] == char(2)) {
            P.alive = false;
        }
        map[y - 1][x] = F.draw;
    }

    if (map[y + 1][x] != char(219)) {
        kill_enemy(x, y+1);

        if (map[y + 1][x] == char(2)) {
            P.alive = false;
        }
        map[y + 1][x] = F.draw;
    }

    if (map[y][x - 1] != char(219)) {
        kill_enemy(x-1, y);

        if (map[y][x - 1] == char(2)) {
            P.alive = false;
        }
        map[y][x - 1] = F.draw;
    }
    if (map[y][x + 1] != char(219)) {
        kill_enemy(x+1, y);

        if (map[y][x + 1] == char(2)) {
            P.alive = false;
        }
        map[y][x + 1] = F.draw;
    }
    F.x = x;
    F.y = y;
    B.exist = false;
    F.exist = true;
    return time(NULL);
}

int enemy_move(int i){ //Move o inimigo.
    map[E[i].y][E[i].x] = ' ';

    if(check_map(E[i].facing, E[i].x, E[i].y) == ' '){ //Se bateu em uma parede gira.
        switch(E[i].facing){
            case 'a':
                if (map[E[i].y][E[i].x-1] == char(2)) {
                    P.alive = false;
                }
                E[i].facing = 's';
            break;
            case 's':
                if (map[E[i].y + 1][E[i].x] == char(2)) {
                    P.alive = false;
                }
                E[i].facing = 'd';
            break;
            case 'd':
                if (map[E[i].y][E[i].x + 1] == char(2)) {
                    P.alive = false;
                }
                E[i].facing = 'w';
            break;
            case 'w':
                if (map[E[i].y + 1][E[i].x] == char(2)) {
                    P.alive = false;
                }
                E[i].facing = 'a';
            break;
        }
    }

    map[E[i].y][E[i].x] = E[0].draw;

    return time(NULL);
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

    char c;
    int i=0;
    int ii=0;
    map_file.open("map_file.txt");
    do {
        c = map_file.get();

        if (c == '\n') {
            i++;
            ii = 0;
        } else if (c == '@') {
            map[i][ii] = char(219);
            ii++;
        } else if (c == '#') {
            map[i][ii] = char(178);
            ii++;
        } else{
            map[i][ii] = ' ';
            ii++;
        }
    } while(!map_file.eof());

    map_file.close();

    B.draw = char(208);

    F.x = 0; F.y = 0;
    F.draw = '#';

    P.x = 5; P.y = 5;
    P.facing = 'd';
    P.draw = char(2);

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
            E[i].x = rand() % (map_size-1);
            E[i].y = rand() % (map_size-1);
        } while (map[E[i].y][E[i].x] != ' ');

        map[E[i].y][E[i].x] = E[0].draw;
    };

    //Posição inicial do jogador.
    do {
        P.x = rand() % (map_size-1);
        P.y = rand() % (map_size-1);
    } while (map[P.y][P.x] != ' ');
        
    map[P.y][P.x] = char(2);

    //Variavel para a tecla precionada.
    char keyboard;

    //Variáveis para contagem do tempo.
    int timer = 0;
    int timer2 = 0;
    int timer3 = 0;

    while (P.alive) {
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
            cout << "\n\n";

            cout << " /\\  _  _  __|_ _    _  _ _  _  _  _    _  _  _ _    . _  _  _  _| \n";
            cout << "/~~\\|_)(/_|  | (/_  (/__\\|_)(_|(_ (_)  |_)(_|| (_|   |(_)(_|(_|| . \n";
            cout << "    |                    |             |            L|    _|       \n";


            if (_kbhit()) {
                keyboard = _getch();
                if(keyboard == 32){
                    GameState = "menu";
                    system("cls");
                }
            }
        } else if (GameState == "menu"){
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

            if (_kbhit()) {
                keyboard = _getch();
                if(keyboard == 'n'){
                    GameState = "running";
                    system("cls");
                } else if (keyboard == 's'){
                    //Função carrega jogo.
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
                    save(timer, timer2, timer3);
                } else if (keyboard == 32){
                    GameState = "running";
                    system("cls");
                }
            }

        } else if (GameState == "running"){
            ///Imprime o jogo: mapa e personagem.
            for (int h = 0; h < map_size; h++) {
                for (int w = 0; w < map_size; w++) {
                    switch (map[h][w]) {
                    case ' ': SetConsoleTextAttribute(hConsole, 0); cout << ' '; break; //caminho.
                    case char(219): SetConsoleTextAttribute(hConsole, 8); cout << char(219); break; //parede.
                    case char(178): SetConsoleTextAttribute(hConsole, 8);  cout << char(178); break; //parede frágil.
                    case char(2): SetConsoleTextAttribute(hConsole, 15); cout << P.draw; break; //player.
                    case char(208): SetConsoleTextAttribute(hConsole, 8);  cout << B.draw; break; //bomba.
                    case '#': SetConsoleTextAttribute(hConsole, 12); cout << F.draw; break; //chama.
                    case char(1): SetConsoleTextAttribute(hConsole, 12); cout << E[0].draw; break; //inimigos.
                    //fim switch.
                    }
                }
                cout << "\n";
            } //fim for mapa.

            ///executa os movimentos.
            if (_kbhit()) {
                keyboard = _getch();

                if(keyboard == 27){
                    GameState = "paused";
                    system("cls");
                }

                map[P.y][P.x] = ' '; //Apaga o jogador para atualizar sua posição.

                //Coloca a bomba se requisitado.
                if (time(NULL) - timer >= 3.5) {
                    if (keyboard == char(32)) {
                        timer = check_map_bomb(P.facing, P.x, P.y);
                    }
                }

                P.facing = check_map(keyboard, P.x, P.y); //Checa o mapa para movimentar o jogador.
                map[P.y][P.x] = char(2); //Coloca o jogador na sua posição atualizada.
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
                if (map[F.y - 1][F.x] == F.draw) {
                    map[F.y - 1][F.x] = ' ';
                }
                if (map[F.y + 1][F.x] == F.draw) {
                    map[F.y + 1][F.x] = ' ';
                }
                if (map[F.y][F.x - 1] == F.draw) {
                    map[F.y][F.x - 1] = ' ';
                }
                if (map[F.y][F.x + 1] == F.draw) {
                    map[F.y][F.x + 1] = ' ';
                }
                if (time(NULL) - timer2 >= 1) {
                    map[F.y][F.x] = ' ';
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
        cout << "      \\______  (____  / __|_|  /\\__  >    \\______  / \\_ /  \\___  >__|    \n";
        cout << "             \\/     \\/       \\/    \\/          \\/           \\/        \n";
    }

    return 0;
} //fim main.
