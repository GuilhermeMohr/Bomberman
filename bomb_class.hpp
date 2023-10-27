#ifndef BOMB_CLASS
#define BOMB_CLASS

#include <iostream> //Cout, Cin, etc...
#include <windows.h> //Biblioteca windows para o terminal.
#include <conio.h> //Teclado.
#include <time.h> //Usar o tempo.
#include <cstdlib>
#include <fstream>
#include <string>

/*
struct obj {
    private:
        int x, y;
        bool exist = false, hidden = false;
        char draw = ' ';
    public:
        void set_coord(int _x, int _y){x = _x; y = _y;}
        void set_exist(bool _exist){exist = _exist;}
        void set_hidden(bool _hidden){hidden = _hidden;}
        void set_draw(char _draw){draw = _draw;}

        int get_x(){return x;}
        int get_y(){return x;}
        bool get_exist(){return exist;}
        bool get_hidden(){return hidden;}
        char get_draw(){return draw;}
};

struct creature {
    private:
        int x, y;
        bool alive = true;
        char facing, draw = char(1);
    public:
        void set_coord(int _x, int _y){x = _x; y = _y;}
        void set_alive(bool _alive){alive = _alive;}
        void set_facing(char _facing){facing = _facing;}
        void set_draw(char _draw){draw = _draw;}

        int get_x(){return x;}
        int get_y(){return x;}
        bool get_alive(){return alive;}
        char get_facing(){return facing;}
        char get_draw(){return draw;}
};
*/

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
    char powerup = ' ';
};

extern obj B; //Bomba

extern obj F; //Chama

extern creature P; //Player

class Powerup {
    private: 
        int x;
        int y;
        bool exist;
        bool active;
        int size;
        int diagonal;
        char draw;
        int quantity;
    public:
        void create(int _x, int _y, int _size = 1, int _diagonal = 0, char _draw = char(111), bool _exist = true){
            x = _x;
            y = _y;
            exist = _exist;
            draw = _draw;
            size = _size;
            diagonal = _diagonal;
        }

        void set_coord(int _x, int _y){x = _x; y = _y;}
        void set_exist(bool _exist){exist = _exist;}
        void set_active(bool _active){active = _active;}
        void set_draw(char _draw){draw = _draw;}
        void set_size(int _size){size = _size;}
        void set_diagonal(int _diagonal){diagonal = _diagonal;}
        void set_quantity(int _quantity){quantity = _quantity;}

        int get_x(){return x;}
        int get_y(){return x;}
        bool get_exist(){return exist;}
        bool get_active(){return active;}
        char get_draw(){return draw;}
        int get_size(){return size;}
        int get_diagonal(){return diagonal;}
        int get_quantity(){return quantity;}
};

extern creature E[5]; //Inimigo

extern Powerup bomb3x3;
extern Powerup bombRand;

extern int map_size_x;
extern int map_size_y;
extern char** map;
extern int current_map;

extern int timer_bomb;
extern int timer_flame;
extern int timer_enemy;
extern int timer_game;

extern int kill_count;

#endif