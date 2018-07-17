#include "Game.h"
#include <cctype>
#include <assert.h>

using namespace std;


string tolower(const string& s){ //custom tolower function
	string r;
	for (auto c: s)
		r += tolower(c);
	return r;
}
Game::Game(){	
}
bool Game::go(std::string name) {
	assert(current != 0);
	string n = tolower(name);
	for (auto& e: current->edges)
		if(n == tolower(e->name)){
			if (!e->passable)
				return false;
			assert(e->node != 0);
			current = e->node;
			return true;
		}
	return false;
}
string Game::take(std::string name) {
	assert(current != 0);
	string n = tolower(name);
	for (int i = 0; i < current->objects.size(); i++)
		if(n == tolower(current->objects[i]->name)){
			objects.push_back(current->objects[i]); // item stored in vector
			string s = current->objects[i]->name;
			current->objects[i]->activate();
			current->objects.erase(current->objects.begin() + i); // erasing object from current node
																	// because it is now in your inventory
			return "The " + s + " is in your inventory"; //hardcoded for demo.	
		}
	return "";
} 	
string Game::consume(std::string name) {
	assert(current != 0);
	string n = tolower(name);
	for (int i = 0; i < current->objects.size(); i++)
		if(n == tolower(current->objects[i]->name)){
			string s = current->objects[i]->name;
			current->objects[i]->activate();
			current->objects.erase(current->objects.begin() + i); // erasing object from current node
																	//NOTE: consume() deletes the object permanently
			
			return "You consume the " + s ; //hardcoded for demo.	
		}
	return "";
} 
string Game::describe(std::string name) {
	assert(current != 0);
	if (!name.size())
		return current->describe();
	string n = tolower(name);
	for (auto& e: current->edges)
		if(n == tolower(e->name))
			return e->describe();
	for (auto& o: current->objects)
		if(n == tolower(o->name))
			return o->describe();
	for (auto& f: current->features)
		if(n == tolower(f->name))
			return f->describe();
	return "";
} 
string Game::examine(std::string name) {
	assert(current != 0);
	string n = tolower(name);
	for (auto& e: current->edges)
		if(n == tolower(e->name))
			return e->examine();
	for (auto& o: current->objects)
		if(n == tolower(o->name))
			return o->examine();
	for (auto& f: current->features)
		if(n == tolower(f->name))
			return f->examine();
	return "";	
}
Node* Game::findNode(std::string name){
	for (auto* n: allNodes)
		if(tolower(n->name) == tolower(name))
			return n;
	return 0;
}
Feature* Game::findFeature(std::string name, Node* n){
	for (auto* f: n->features)
		if(tolower(f->name) == tolower(name))
			return f;
	return 0;
}
Object* Game::findObject(std::string name, Node* n){
	for (auto* o: n->objects)
		if(tolower(o->name) == tolower(name))
			return o;
	return 0;	
}
Edge* Game::findEdge(std::string name, Node* n){
	for (auto* e: n->edges)
		if(tolower(e->name) == tolower(name))
			return e;
	for (auto* aN: allNodes)
		for (auto* e: aN->edges)
			if(tolower(e->name) == tolower(name))
				return e;
	return 0;	
}	
bool Game::buildGraph(){
	for (auto* n: allNodes){
		for (auto* e: n->edges)
			e->node = findNode(e->initialNodeName);
		for (auto* f: n->features){
			f->feature = findFeature(f->initialFeatureName, n);
			f->object = findObject(f->initialObjectName, n);
		}
		for (auto* o: n->objects){
			o->edge = findEdge(o->initialEdgeName, n);
		}
	}
	
	
}