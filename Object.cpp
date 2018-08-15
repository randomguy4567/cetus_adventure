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


void Object::setVerb(std::string verb, std::string response, std::string hintResponse){
	_verb = verb;
	_response = response;
	_hintResponse = hintResponse;
}