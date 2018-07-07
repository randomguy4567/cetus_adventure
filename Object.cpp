#include "Object.h"

using namespace std;


Object::Object(){
}
string Object::describe(){
	if (!visible)
		return "";
	if (visited){
		return shortDescription;
	}
	else{
		visited = true;
		return longDescription;
	}
}
string Object::examine(){
	if (!visible)
		return "";
	return longDescription;
}
string Object::verb(){
	return _verb;
}
string Object::activate(){
	if (!edge)
		return "";
	edge->visible = true;
	edge->passable = true;
	string s;
	return _response;
}

//This was not demonstrated in the prototype. It's intended to allow the object to have
 // a verb that can be called. It calls the Objects activate. This can be built out if
 // we choose to use it.
void Object::setVerb(std::string verb, std::string response){
	_verb = verb;
	_response = response;
}