#include <time.h>
#include "bomb_func.h"
#include "bomb_class.h"

char check_map(char direction, creature &caracter) { //Move os carinhas pelo mapa.
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
}

int create_bomb(int x, int y) { //Cria nova bomba
    map[y][x] = 4;
    B.set_coord(x, y);
    B.set_exist(true);
    P.set_draw(char(1));
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
        if(E[i].get_x() == x && E[i].get_y() == y){
            E[i].set_alive(false);
        }
    }
}

int explode_bomb(int x, int y) { //Explode a bomba, matando inimigos e o jogador
    kill_enemy(x, y); //Matar inimigo

    if (map[y][x] == 3) { //Matar jogador
        P.set_alive(false);
    }
    map[y][x] = 5; //Colocar chama

    if (map[y - 1][x] != 1) {
        kill_enemy(x, y-1);

        if (map[y - 1][x] == 3) {
            P.set_alive(false);
        }
        map[y - 1][x] = 5;
    }

    if (map[y + 1][x] != 1) {
        kill_enemy(x, y+1);

        if (map[y + 1][x] == 3) {
            P.set_alive(false);
        }
        map[y + 1][x] = 5;
    }

    if (map[y][x - 1] != 1) {
        kill_enemy(x-1, y);

        if (map[y][x - 1] == 3) {
            P.set_alive(false);
        }
        map[y][x - 1] = 5;
    }
    if (map[y][x + 1] != 1) {
        kill_enemy(x+1, y);

        if (map[y][x + 1] == 3) {
            P.set_alive(false);
        }
        map[y][x + 1] = 5;
    }
    B.set_exist(false);
    F.set_coord(x, y);
    F.set_exist(true);
    return time(NULL);
}

int enemy_move(int i){ //Move o inimigo.
    map[E[i].get_y()][E[i].get_x()] = 0;

    if(check_map(E[i].get_facing(), E[i]) == ' '){ //Se bateu em uma parede gira.
        switch(E[i].get_facing()){
            case 'a':
                if (map[E[i].get_y()][E[i].get_x()-1] == 3) {
                    P.set_alive(false);
                }
                E[i].set_facing('s');
            break;
            case 's':
                if (map[E[i].get_y() + 1][E[i].get_x()] == 3) {
                    P.set_alive(false);
                }
                E[i].set_facing('d');
            break;
            case 'd':
                if (map[E[i].get_y()][E[i].get_x() + 1] == 3) {
                    P.set_alive(false);
                }
                E[i].set_facing('w');
            break;
            case 'w':
                if (map[E[i].get_y() + 1][E[i].get_x()] == 3) {
                    P.set_alive(false);
                }
                E[i].set_facing('a');
            break;
        }
    }

    map[E[i].get_y()][E[i].get_x()] = 6;

    return time(NULL);
}