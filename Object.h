#ifndef OBJECT_H
#define OBJECT_H

class Edge;
class Object;
class Feature;
class Node;

#include "Edge.h"
#include "Feature.h"
#include "Node.h"
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
	Edge* edge = 0; // this is the edge that becomes visible or passable when the user activate() the object
	std::string initialEdgeName;
	std::string describe();
	std::string examine();
	virtual std::string verb(); // this is the word that can be entered into the user interface 
								// to activate the object (i.e, take or eat). Can be polymorphic.
	std::string activate(); // when you consume or take an object.
	void setVerb(std::string verb, std::string response);
	
private:
	std::string _verb; //this is internal
	std::string _response; 
};
#endif
