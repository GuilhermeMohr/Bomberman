#include "SaveLoad.hpp"

using namespace std;

void save() {
    ofstream save_file;
    save_file.open("save.txt");
    save_file << "P: x=" << P.x << ", y=" << P.y << ", facing=" << int(P.facing) << ", draw=" << int(P.draw) << ", poWerup=" << int(P.powerup) << ", \n";
    for (int i = 0; i < sizeof(E) / sizeof(E[i]); i++) {
        save_file << "E: x=" << E[i].x << ", y=" << E[i].y << ", facing=" << int(E[i].facing) << ", draw=" << int(E[i].draw) << ", Alive=" << E[i].alive << ", \n";
    }
    save_file << "B: x=" << B.x << ", y=" << B.y << ", exist=" << B.exist << ", hidden=" << B.hidden << ", \n";
    save_file << "F: x=" << F.x << ", y=" << F.y << ", exist=" << F.exist << ", hidden=" << F.hidden << ", \n";
    save_file << "3x3: X=" << bomb3x3.get_x() << ", Y=" << bomb3x3.get_y() << ", Exist=" << bomb3x3.get_exist() << ", Active=" << bomb3x3.get_active() << ", Size=" << bomb3x3.get_size() << ", Diagonal=" << bomb3x3.get_diagonal() << ", draW=" << int(bomb3x3.get_draw()) << ", Quantity=" << bomb3x3.get_quantity() << ", \n";
    save_file << "Rand: X=" << bombRand.get_x() << ", Y=" << bombRand.get_y() << ", Exist=" << bombRand.get_exist() << ", Active=" << bombRand.get_active() << ", Size=" << bombRand.get_size() << ", Diagonal=" << bombRand.get_diagonal() << ", draW=" << int(bombRand.get_draw()) << ", Quantity=" << bombRand.get_quantity() << ", \n";
    save_file << "TIMERS: a=" << timer_bomb << ", b=" << timer_flame << ", c=" << timer_enemy << ", d=" << timer_game << ", \n";
    save_file << "Kill_Count: k=" << kill_count << ", \n";
    save_file << "WALLS: DESTROID=" << walls_destroyed;
    int ii = 0;
    for (int i = 0; i < walls_destroyed; i++) {
        save_file << ", ";
        save_file << 'x' << char(97 + ii) << "=" << walls_destroyed_array[i][0] << ", ";
        save_file << 'y' << char(97 + ii + 1) << "=" << walls_destroyed_array[i][1];
        ii += 2;
    }
    save_file << ", \n" << "Map: map_name=" << current_map << ", \n";
    save_file.close();
    cout << "Salvo\n";
}

template <typename I>
void assign_value(char value, I* receiver, string load) {
    for (int i = 0; i < load.size(); i++) {
        if (load[i] == value) {
            while (load[i] != ',') {
                i++;
            }
            i--;
            int temp_value = 0;
            for (int ii = 1; load[i] >= char(48) and load[i] <= char(57); ii *= 10) {//� um n�mero (0, 9).
                temp_value += (int(load[i]) - '0') * ii;
                i--;
            }
            *receiver = I(temp_value);
            return;
        }
    }
}

template <typename II>
II assign_value_class(char value, II receiver, string load) {
    for (int i = 0; i < load.size(); i++) {
        if (load[i] == value) {
            while (load[i] != ',') {
                i++;
            }
            i--;
            int temp_value = 0;
            for (int ii = 1; load[i] >= char(48) and load[i] <= char(57); ii *= 10) {//Um numero (0, 9).
                temp_value += (int(load[i]) - '0') * ii;
                i--;
            }
            return II(temp_value);
        }
    }
}

void load_game() {
    int enemy_count = 0;
    ifstream save_file;
    save_file.open("save.txt");
    string load;
    do {
        getline(save_file, load);
        switch (load[0]) {
        case 'P':
            assign_value('x', &P.x, load);
            assign_value('y', &P.y, load);
            assign_value('f', &P.facing, load);
            assign_value('d', &P.draw, load);
            assign_value('W', &P.powerup, load);
            break;
        case 'E':
            assign_value('x', &E[enemy_count].x, load);
            assign_value('y', &E[enemy_count].y, load);
            assign_value('f', &E[enemy_count].facing, load);
            assign_value('d', &E[enemy_count].draw, load);
            assign_value('A', &E[enemy_count].alive, load);
            enemy_count++;
            break;
        case 'B':
            assign_value('x', &B.x, load);
            assign_value('y', &B.y, load);
            assign_value('e', &B.exist, load);
            assign_value('h', &B.hidden, load);
            break;
        case 'F':
            assign_value('x', &F.x, load);
            assign_value('y', &F.y, load);
            assign_value('e', &F.exist, load);
            assign_value('h', &F.hidden, load);
            break;
        case '3':
            bomb3x3.set_coord(assign_value_class('X', bomb3x3.get_x(), load), assign_value_class('Y', bomb3x3.get_y(), load));
            bomb3x3.set_exist(assign_value_class('E', bomb3x3.get_exist(), load));
            bomb3x3.set_active(assign_value_class('A', bomb3x3.get_active(), load));
            bomb3x3.set_size(assign_value_class('S', bomb3x3.get_size(), load));
            bomb3x3.set_diagonal(assign_value_class('D', bomb3x3.get_diagonal(), load));
            bomb3x3.set_draw(assign_value_class('W', bomb3x3.get_draw(), load));
            bomb3x3.set_quantity(assign_value_class('Q', bomb3x3.get_quantity(), load));
            break;
        case 'R':
            bombRand.set_coord(assign_value_class('X', bombRand.get_x(), load), assign_value_class('Y', bombRand.get_y(), load));
            bombRand.set_exist(assign_value_class('E', bombRand.get_exist(), load));
            bombRand.set_active(assign_value_class('A', bombRand.get_active(), load));
            bombRand.set_size(assign_value_class('S', bombRand.get_size(), load));
            bombRand.set_diagonal(assign_value_class('D', bombRand.get_diagonal(), load));
            bombRand.set_draw(assign_value_class('W', bombRand.get_draw(), load));
            bombRand.set_quantity(assign_value_class('Q', bombRand.get_quantity(), load));
            break;
        case 'T':
            assign_value('a', &timer_bomb, load);
            assign_value('b', &timer_flame, load);
            assign_value('c', &timer_enemy, load);
            assign_value('d', &timer_game, load);
            break;
        case 'K':
            assign_value('k', &kill_count, load);
        /*case 'M':
            assign_value('m', &current_map, load);
            break;
        */
        case 'W':
            assign_value('D', &walls_destroyed, load);
            int ii = 0;
            delete walls_destroyed_array;
            walls_destroyed_array = new int* [walls_destroyed];
            for (int i = 0; i < walls_destroyed; i++) {
                walls_destroyed_array[i] = new int[2];
                assign_value(char(97 + ii), &walls_destroyed_array[i][0], load);
                assign_value(char(97 + ii + 1), &walls_destroyed_array[i][1], load);
                ii += 2;
            }
            for (int i = 0; i < walls_destroyed; i++) {
                map[walls_destroyed_array[i][1]][walls_destroyed_array[i][0]] = ' ';
            }
            break;
        }
    } while (!save_file.eof());
}

void wall_break(int x, int y) {
    walls_destroyed += 1;
    int** temp_array = new int* [walls_destroyed];
    for (int i = 0; i < walls_destroyed - 1; i++) {
        temp_array[i] = walls_destroyed_array[i];
    }
    delete walls_destroyed_array;
    temp_array[walls_destroyed - 1] = new int[2];
    temp_array[walls_destroyed - 1][0] = x;
    temp_array[walls_destroyed - 1][1] = y;
    walls_destroyed_array = new int* [walls_destroyed];

    for (int i = 0; i < walls_destroyed; i++) {
        walls_destroyed_array[i] = temp_array[i];
    }
    delete temp_array;
}

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