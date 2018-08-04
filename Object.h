#ifndef OBJECT_H
#define OBJECT_H

class Edge;
class Object;
class Feature;
class Node;
class Game;

#include "Edge.h"
#include "Feature.h"
#include "Node.h"
#include "Game.h"
#include <string>
#include <vector>

class Object{
public:
	Object();
	std::string name;
	std::string shortDescription;
	std::string longDescription;
	bool visited = false;
	bool visible = true;
	bool fixed = false;
	//Edge* edge = 0; // this is the edge that becomes visible or passable when the user activate() the object
	//std::string initialEdgeName;
	std::string target;
	std::string describe();
	std::string examine();
	virtual std::string verb(); // this is the word that can be entered into the user interface 
								// to activate the object (i.e, take or eat). Can be polymorphic.
	std::string activate(); // when you consume or take an object.
	void setVerb(std::string verb, std::string response, std::string _hintResponse);
	std::string _verb; 
	std::string _response; 
	std::string _hintResponse;

	static Game* g;


};
#endif
