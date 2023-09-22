#ifndef BOMB_CLASS
#define BOMB_CLASS

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

extern obj B; //Bomba

extern obj F; //Chama

extern creature P; //Player

extern creature E[5]; //Inimigo

const int map_size = 15;
int map[map_size][map_size];

#endif