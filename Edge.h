#ifndef EDGE_H
#define EDGE_H

class Edge;
class Object;
class Feature;
class Node;

#include "Object.h"
#include "Feature.h"
#include "Node.h"
#include <string>
#include <vector>

class Edge{
public:
	Edge();
	std::string name;
	std::string nameAlt;
	std::string shortDescription;
	std::string longDescription;
	bool visited = false;
	bool visible = true;
	bool passable = true;
	Node* node = 0;
	//Just set this to the name of the node you want and forget about the Node*
	std::string initialNodeName; 
	std::string describe();
	std::string examine();
};
#endif

