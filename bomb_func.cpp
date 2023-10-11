#include <time.h>
#include "bomb_func.hpp"
#include "bomb_class.hpp"

/*char check_map(char direction, creature& caracter) { //Move os carinhas pelo mapa.
    switch (direction)
    {
    case 72: case 'w': ///cima
        if (map[caracter.get_y() - 1][caracter.get_x()] == 0) { //Checa se o espaço é livre
            caracter.set_coord(caracter.get_x(), caracter.get_y() - 1);
            return 'w';
        } else if (map[caracter.get_y() - 1][caracter.get_x()] == 4) { //Checa se há uma bomba
            B.set_hidden(true); //Esconde a bomba
            caracter.set_coord(caracter.get_x(), caracter.get_y() - 1);
            return 'w';
        }
        break;
    case 80: case 's': ///baixo
        if (map[caracter.get_y() + 1][caracter.get_x()] == 0) {
            caracter.set_coord(caracter.get_x(), caracter.get_y() + 1);
            return 's';
        } else if (map[caracter.get_y() + 1][caracter.get_x()] == 4) {
            B.set_hidden(true);
            caracter.set_coord(caracter.get_x(), caracter.get_y() + 1);
            return 's';
        }
        break;
    case 75: case 'a': ///esquerda
        if (map[caracter.get_y()][caracter.get_x() - 1] == 0) {
            caracter.set_coord(caracter.get_x() - 1, caracter.get_y());
            return 'a';
        } else if (map[caracter.get_y()][caracter.get_x() - 1] == 4) {
            B.set_hidden(true);
            caracter.set_coord(caracter.get_x() - 1, caracter.get_y());
            return 'a';
        }
        break;
    case 77: case 'd': ///direita
        if (map[caracter.get_y()][caracter.get_x() + 1] == 0) {
            caracter.set_coord(caracter.get_x() + 1, caracter.get_y());
            return 'd';
        } else if (map[caracter.get_y()][caracter.get_x() + 1] == 4) {
            B.set_hidden(true);
            caracter.set_coord(caracter.get_x() + 1, caracter.get_y());
            return 'd';
        }
        break;
    }
    return ' ';
}*/

char check_map(char direction, int& x, int& y) { //Move os carinhas pelo mapa.
    switch (direction)
    {
    case 72: case 'w': ///cima
        if (map[y - 1][x] == ' ') { //Checa se o espaço é livre
            y = y - 1;
            return 'w';
        }
        else if (map[y - 1][x] == B.draw) { //Checa se há uma bomba
            B.hidden = true; //Esconde a bomba
            y = y - 1;
            return 'w';
        }
        break;
    case 80: case 's': ///baixo
        if (map[y + 1][x] == ' ') {
            y = y + 1;
            return 's';
        }
        else if (map[y + 1][x] == B.draw) {
            B.hidden = true;
            y = y + 1;
            return 's';
        }
        break;
    case 75: case 'a': ///esquerda
        if (map[y][x - 1] == ' ') {
            x = x - 1;
            return 'a';
        }
        else if (map[y][x - 1] == B.draw) {
            B.hidden = true;
            x = x - 1;
            return 'a';
        }
        break;
    case 77: case 'd': ///direita
        if (map[y][x + 1] == ' ') {
            x = x + 1;
            return 'd';
        }
        else if (map[y][x + 1] == B.draw) {
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

void kill_enemy(int x, int y) { //Mata um inimigo
    for (int i = 0; i < 5; i++) {
        if (E[i].x == x && E[i].y == y) {
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
        kill_enemy(x, y - 1);

        if (map[y - 1][x] == char(2)) {
            P.alive = false;
        }
        if (map[y - 1][x] == char(178)) {
            wall_break(x, y - 1);
        }

        map[y - 1][x] = F.draw;
    }

    if (map[y + 1][x] != char(219)) {
        kill_enemy(x, y + 1);

        if (map[y + 1][x] == char(2)) {
            P.alive = false;
        }
        if (map[y + 1][x] == char(178)) {
            wall_break(x, y + 1);
        }

        map[y + 1][x] = F.draw;
    }

    if (map[y][x - 1] != char(219)) {
        kill_enemy(x - 1, y);

        if (map[y][x - 1] == char(2)) {
            P.alive = false;
        }
        if (map[y][x - 1] == char(178)) {
            wall_break(x - 1, y);
        }

        map[y][x - 1] = F.draw;
    }
    if (map[y][x + 1] != char(219)) {
        kill_enemy(x + 1, y);

        if (map[y][x + 1] == char(2)) {
            P.alive = false;
        }
        if (map[y][x + 1] == char(178)) {
            wall_break(x + 1, y);
        }

        map[y][x + 1] = F.draw;
    }
    F.x = x;
    F.y = y;
    B.exist = false;
    F.exist = true;
    return time(NULL);
}

int enemy_move(int i) { //Move o inimigo.
    map[E[i].y][E[i].x] = ' ';

    if (check_map(E[i].facing, E[i].x, E[i].y) == ' ') { //Se bateu em uma parede gira.
        switch (E[i].facing) {
        case 'a':
            if (map[E[i].y][E[i].x - 1] == char(2)) {
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