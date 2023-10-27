#include <time.h>
#include "bomb_class.hpp"
#include "bomb_func.hpp"

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
        } else {
            y = y - 1;
            if(!pick_powerup(y, x)){
                y = y + 1;
            } else {
                return 'w';
            }
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
        } else {
            y = y + 1;
            if(!pick_powerup(y, x)){
                y = y - 1;
            } else {
                return 's';
            }
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
        } else {
            x = x - 1;
            if(!pick_powerup(y, x)){
                x = x + 1;
            } else {
                return 'a';
            }
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
        } else {
            x = x + 1;
            if(!pick_powerup(y, x)){
                x = x - 1;
            } else {
                return 'd';
            }
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

bool pick_powerup(int y, int x){
    if (P.y == bomb3x3.get_y() && P.x == bomb3x3.get_x()){
        P.powerup = 'B';
        bomb3x3.set_active(true);
        bomb3x3.set_exist(false);
        bomb3x3.set_coord(0, 0);
        return true;
    } else if (P.y == bombRand.get_y() && P.x == bombRand.get_x()){
        P.powerup = 'R';
        bombRand.set_active(true);
        bombRand.set_exist(false);
        bombRand.set_coord(0, 0);
        return true;
    }

    if(y == bomb3x3.get_y() && x == bomb3x3.get_x()) {
        bomb3x3.set_exist(false);
        bomb3x3.set_coord(0, 0);
        return true;
    }
    if(y == bombRand.get_y() && x == bombRand.get_x()) {
        bombRand.set_exist(false);
        bombRand.set_coord(0, 0);
        return true;
    }
    return false;
}

void create_powerup(){
    if(rand() % 2 == 1){
        if(bomb3x3.get_exist() == false){
            bomb3x3.create(rand() % (map_size_x - 1), rand() % (map_size_y - 1), 3);
            bomb3x3.set_size(3);
            while(map[bomb3x3.get_y()][bomb3x3.get_x()] != ' '){
                bomb3x3.set_coord(rand() % (map_size_x - 1), rand() % (map_size_y - 1));
            }
            map[bomb3x3.get_y()][bomb3x3.get_x()] = bomb3x3.get_draw();
        }
    }
    if(rand() % 2 == 1){
        if (bombRand.get_exist() == false){
            bombRand.create(rand() % (map_size_x - 1), rand() % (map_size_y - 1), (rand()%3)+2, 0, 4);
            bombRand.set_size((rand()%3)+2);
            while(map[bombRand.get_y()][bombRand.get_x()] != ' '){
                bombRand.set_coord(rand() % (map_size_x - 1), rand() % (map_size_y - 1));
            }
            map[bombRand.get_y()][bombRand.get_x()] = bombRand.get_draw();
        }
    }
}


void kill_enemy(int x, int y) { //Mata um inimigo
    for (int i = 0; i < 5; i++) {
        if (E[i].x == x && E[i].y == y && E[i].alive != false) {
            E[i].alive = false;
            create_powerup();
        }
    }
}

int explode_bomb(int x, int y, int size, int diagonal) { //Explode a bomba, matando inimigos e o jogador
    for (int i=0; i < size+1; i++){
        if (!(x-i < 0)){
            if (map[y][x-i] != char(219)) {
                kill_enemy(x-i, y);

                if (map[y][x-i] == char(2)) {
                    P.alive = false;
                }
                if (map[y][x-i] == char(178)) {
                    wall_break(x-i, y);
                }

                map[y][x-i] = F.draw;
            }
        }

        if (!(x+i > map_size_x)){
            if (map[y][x+i] != char(219)) {
                kill_enemy(x+i, y);

                if (map[y][x+i] == char(2)) {
                    P.alive = false;
                }
                if (map[y][x+i] == char(178)) {
                    wall_break(x+i, y);
                }

                map[y][x+i] = F.draw;
            }
        }

        if (!(y-i < 0)){
            if (map[y-i][x] != char(219)) {
                kill_enemy(x, y-i);

                if (map[y-i][x] == char(2)) {
                    P.alive = false;
                }
                if (map[y-i][x] == char(178)) {
                    wall_break(x, y-i);
                }

                map[y-i][x] = F.draw;
            }
        }

        if (!(y+i > map_size_y)){
            if (map[y+i][x] != char(219)) {
                kill_enemy(x, y+1);

                if (map[y+i][x] == char(2)) {
                    P.alive = false;
                }
                if (map[y+i][x] == char(178)) {
                    wall_break(x, y+i);
                }

                map[y+i][x] = F.draw;
            }
        }
    }

    F.x = x;
    F.y = y;
    B.exist = false;
    F.exist = true;
    return time(NULL);
}

void extingue_fire(int size){
    if (time(NULL) - timer_flame >= 0.5 && F.exist) {
        if (time(NULL) - timer_flame >= 1) {
                map[F.y][F.x] = ' ';
                F.exist = false;
        }
        for (int i=0; i < size+1; i++){
            if (map[F.y-i][F.x] == F.draw) {
                map[F.y-i][F.x] = ' ';
            }
            if (map[F.y+i][F.x] == F.draw) {
                map[F.y+i][F.x] = ' ';
            }
            if (map[F.y][F.x-i] == F.draw) {
                map[F.y][F.x-i] = ' ';
            }
            if (map[F.y][F.x+i] == F.draw) {
                map[F.y][F.x+i] = ' ';
            }
        }
    }
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