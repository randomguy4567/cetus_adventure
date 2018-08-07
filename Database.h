#ifndef DATABASE_H
#define DATABASE_H
#include "Game.h"


int initialize(Game *g, int numRooms);
bool saveGame(Game *g);
bool loadGame(Game *g, int numRooms);

#endif
