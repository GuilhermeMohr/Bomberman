#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "bomb_class.hpp"

using namespace std;

void save(int timer, int timer2, int timer3);
template <typename I>
void assign_value(char value, I* receiver, string load);
void load_game();
void wall_break(int x, int y);

//Número de parede destruída.
extern int walls_destroyed;
extern int** walls_destroyed_array;