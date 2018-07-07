#ifndef GAME_H
#define GAME_H

class Edge;
class Object;
class Feature;
class Node;

#include "Edge.h"
#include "Object.h"
#include "Feature.h"
#include "Node.h"
#include "Interface.h"
#include <string>
#include <vector>

class Game{
public:
	Game();	// Constructor
	
	Node* root = 0; // root node needs to be set during initialization because the main loop needs to know where to start.
	
	Node* end = 0; // end node also needs to be set during initialization, arrival at the end node is used as a trigger to signify end of game.
	
	Node* current = 0; // current node changes as the user moves. Parser can use the current node to learn the names of things the user can act on, as 
						//  well as verbs that are available to act on objects in the current room.
	
	std::vector<Node*> allNodes; // This should be filled as the graph is being built by the data structures. This will 
								  // be convenient for game saves and loads.
	
	std::vector<Object*> objects; // When you call take(), an Object is added to your character's inventory.
	
	Interface interface; // This is where the Ncurses implementation will go. Initially it is just going to be a set of stubs.
	
	bool go(std::string name); // You call this to traverse an Edge.
	
	std::string take(std::string name); // You call this to put an object from the current room into your inventory (objects).
	
	std::string consume(std::string name); // This activates an object and then destroys it (examples are to eat something or set something 
									 // off, ' a button or hand grenade')
	
	std::string describe(std::string name = ""); // This is called upon entering a room. It sets the visited flag and so the second call to describe would get
											 // the short description.
	
	std::string examine(std::string name = "");	// Examine() is intended for Features. It follows the link in the feature to potentially 
											 // reveal additional Features.	

	// If you want, you could add pointers to your classes here to integrate the parser and the database, 
	 // or you could just write the code so that you act on this interface.
};
#endif