#ifndef NODE_H
#define NODE_H

class Edge;
class Object;
class Feature;
class Node;

#include "Edge.h"
#include "Object.h"
#include "Feature.h"
#include <string>
#include <vector>

class Node{
public:
	Node();
	std::string name;
	std::string shortDescription;
	std::string longDescription;
	bool visited = false;
	std::vector<Edge*> edges;
	std::vector<Object*> objects;
	std::vector<Feature*> features;
	std::string describe();
};
#endif
