#ifndef FEATURE_H
#define FEATURE_H

class Edge;
class Object;
class Feature;
class Node;

#include "Edge.h"
#include "Object.h"
#include "Node.h"
#include <string>
#include <vector>

class Feature{
public:
	Feature();
	std::string name;
	std::string shortDescription;
	std::string longDescription;
	bool visited= false;
	bool visible= true;
	Feature* feature = 0;// this is the feature that becomes visible when the user examine() the object
	Object* object = 0; // this is the object that becomes visible when the user examine() the feature
	std::string describe();
	std::string examine();
	
private:
	//std::string _verb; //this is internal to Feature!
};
#endif
