#include "Edge.h"

using namespace std;

Edge::Edge(){	
}
string Edge::describe(){
	if (!visible)
		return "";
	return shortDescription;
}

string Edge::examine(){
	if (!visible)
		return "";
	visited = true;
	return longDescription;
}