#include "Feature.h"

using namespace std;


Feature::Feature(){	
}
string Feature::describe(){
	if (!visible)
		return "";
	return shortDescription;
}

string Feature::examine(){
	if (!visible)
		return "";
	string s = longDescription;
	if (feature){
		feature->visible = true;
		if (s.size())
			s = s +". ";
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

	return s ;
}

