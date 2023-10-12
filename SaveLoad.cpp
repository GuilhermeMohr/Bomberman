#include "SaveLoad.hpp"

using namespace std;

void save(int timer = 0, int timer2 = 0, int timer3 = 0) {
    ofstream save_file;
    save_file.open("save.txt");
    save_file << "P: x=" << P.x << ", y=" << P.y << ", facing=" << int(P.facing) << ", draw=" << int(P.draw) << ", \n";
    for (int i = 0; i < sizeof(E) / sizeof(E[i]); i++) {
        save_file << "E: x=" << E[i].x << ", y=" << E[i].y << ", facing=" << int(E[i].facing) << ", draw=" << int(E[i].draw) << ", Alive=" << E[i].alive << ", \n";
    }
    save_file << "B: x=" << B.x << ", y=" << B.y << ", exist=" << B.exist << ", hidden=" << B.hidden << ", \n";
    save_file << "F: x=" << F.x << ", y=" << F.y << ", exist=" << F.exist << ", hidden=" << F.hidden << ", \n";
    save_file << "TIMERS: a=" << timer << ", b=" << timer2 << ", c=" << timer3 << ", \n";
    save_file << "WALLS: DESTROID=" << walls_destroyed << ", ";
    int ii = 0;
    for (int i = 0; i < walls_destroyed; i++) {
        save_file << 'x' << char(97 + ii) << "=" << walls_destroyed_array[i][0] << ", ";
        save_file << 'y' << char(97 + ii + 1) << "=" << walls_destroyed_array[i][1] << ", ";
        ii += 2;
    }
    save_file << "\n";
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
            for (int ii = 1; load[i] >= char(48) and load[i] <= char(57); ii *= 10) {//É um número (0, 9).
                temp_value += (int(load[i]) - '0') * ii;
                i--;
            }
            *receiver = I(temp_value);
            return;
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
        case 'T':
            assign_value('a', &timer, load);
            assign_value('b', &timer2, load);
            assign_value('c', &timer3, load);
            break;
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