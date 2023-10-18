#ifndef SAVE_LOAD
#define SAVE_LOAD

#include <iostream>
#include <fstream>
#include <string>
#include "bomb_class.hpp"

using namespace std;

void save();
template <typename I>
void assign_value(char value, I* receiver, string load);
void load_game();
void wall_break(int x, int y);

//N�mero de parede destru�da.
extern int walls_destroyed;
extern int** walls_destroyed_array;

#endif