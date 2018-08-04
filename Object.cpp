#include "Object.h"
#include "Game.h"


using namespace std;


Game* Object::g = 0;

Object::Object(){
}
string Object::describe(){
	if (!visible)
		return "";

	return shortDescription;
}
string Object::examine(){
	if (!visible)
		return "";
	return longDescription;
}
string Object::verb(){
	return _verb;
}

//Didnt end up using this
string Object::activate(){
	return _response;
}

//This was not demonstrated in the prototype. It's intended to allow the object to have
 // a verb that can be called. It calls the Objects activate. This can be built out if
 // we choose to use it.
void Object::setVerb(std::string verb, std::string response, std::string _hintResponse){
	_verb = verb;
	_response = response;
}