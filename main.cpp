#include "Game.h"
#include "Loop.h"
#include "Database.h"

using namespace std;


int main(){
	Game* g = new Game();
	g->interface.init();
	initialize(g, numberOfRooms);
	g->interface.print("Welcome to Cetus. \n\n");
	loop(g);
	g->interface.shutdown();
}