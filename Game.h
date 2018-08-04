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
	
	/* Constructor */
	Game();	
	
	/* After you have created all the Nodes, including Edges, Features and Objects, call this 
	function to build all of the pointers. Therefore, you do not have to set Edge::node, Feature::feature,
	Feature::object, or Object::edge. Instead, just set the "string initial*" parameters to the matching 
	names (NO SPACES in names, node names must be unique.) You still need to put every Node* into allNodes. */
	bool buildGraph(); 
	
	/* Root node needs to be set during initialization because the main loop needs to know where to start.*/
	Node* root = 0; 
	
	/* End node also needs to be set during initialization, arrival at the end node is used as a 
	trigger to signify end of game.*/
	Node* end = 0; 
	
	/* Current node changes as the user moves. Parser can use the current node to learn the names of things
    the user can act on, as well as verbs that are available to act on objects in the current room.*/
	Node* current = 0; 
	
	/* This should be filled as the graph is being built by the data structures. This will 
	be convenient for game saves and loads. */
	std::vector<Node*> allNodes; 
	
	/* This is created by buildGraph(), for convenience during game save/load.*/
	std::vector<Object*> allObjects; 
	
	/* When you call take(), an Object is added to your character's inventory. */
	std::vector<Object*> objects; 
	
	/* This is where the Ncurses implementation will go. Initially it is just going to be a set of stubs. */
	Interface interface; 
	
	/* You call this to traverse an Edge. */
	bool go(std::string name , bool exact = false); 
	
	/* You call this to put an object from the current room into your inventory (objects). */
	std::string take(std::string name); 
	
	/* Call this to drop an object from your inventory */
	std::string drop(std::string name); 
	
	/* This activates an object and then destroys it (examples are to eat something or 
	set something off, ('a button or hand grenade') */
	std::string consume(std::string name); 
	
	/* This is called upon entering a room. It sets the visited flag and so the second call to 
	describe would get the short description. */ 
	std::string describe(std::string name = ""); 
	
	/* Examine() is intended for Features. It follows the link in the feature to potentially 
	reveal additional Features.	*/
	std::string examine(std::string name = "");
	
	/* If the verb is correct one, activate() it */
	std::string tryVerb(std::string verb, std::string param);
	
	/* Added to account from the drop() functionality */
	std::string inventory(); 
	
	std::string whatToLook();
	
	std::string whereToGo();
	
	std::string preParse(std::string rawInput);
	
	/* Get the current location of any object. The return value is the name of a node, inventory, or void.  */
	std::string getObjectLocation(std::string name);
	
	/* This is the opposite of getObjectLocation. */
	bool setObjectLocation(std::string name, std::string location);
	
	/*Database dump used for debugging and general information. */
	void printDatabase();

	/* If you want, you could add pointers to your classes here to integrate the parser and the database, 
    or you could just write the code so that you act on this interface. */
	
private:
	
	Node* findNode(std::string name);
	Feature* findFeature(std::string name, Node* n);
	Object* findObject(std::string name, Node* n);
	Edge* findEdge(std::string name, Node* n);
	
};
#endif