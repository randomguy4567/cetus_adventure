#include "Edge.h"

using namespace std;

Edge::Edge(){	
}
string Edge::describe(){
	if (!visible)
		return "";
	if (visited){
		visited = true;
		return shortDescription;
	}
	else{
		visited = true;
		return longDescription;
	}
}
string Edge::examine(){
	if (!visible)
		return "";
	return longDescription;
}