#ifndef BOMB_FUNC
#define BOMB_FUNC

#include "bomb_class.h"

char check_map(char direction, creature &caracter);
int create_bomb(int x, int y);
int check_map_bomb(char facing, int  x, int  y);
void kill_enemy(int x, int y);
int explode_bomb(int x, int y);
int enemy_move(int i);

#endif
