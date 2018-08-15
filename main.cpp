#include "Game.h"
#include "Loop.h"
#include "Database.h"

using namespace std;


int main(){
	Game* g = new Game();
	
	initialize(g, numberOfRooms);
	g->interface.print("Welcome to Cetus. \n\n");
	loop(g);
	delete g;
}