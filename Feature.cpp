#include "Feature.h"

using namespace std;


Feature::Feature(){	
}
string Feature::describe(){
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
string Feature::examine(){
	if (!visible)
		return "";
	string s;
	if (feature){
		feature->visible = true;
		s = feature->describe();
		return s; //added, not sure if correct
	}
	if (object){
		object->visible = true;
		if (s.size())
			s = s +". ";
		s += object->describe();
		return s; //added not sure if correct	
	}
	if (s.size())
		s = s +". ";
	return s + longDescription;
}

