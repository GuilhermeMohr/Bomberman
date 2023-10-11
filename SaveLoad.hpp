#pragma once

#include <iostream> //Cout, Cin, etc...

using namespace std;

void save(int timer = 0, int timer2 = 0, int timer3 = 0);
template <typename I>
void assign_value(char value, I* receiver, string load);
void load_game();
void wall_break(int x, int y);

//Número de parede destruída.
int walls_destroyed = 0;
int** walls_destroyed_array = new int* [walls_destroyed];