#include <algorithm>
#include <assert.h>
#include <iostream>
#include "Game.h"

using namespace std;


//custom tolower function
string tolower(const string& s){ 
	string r;
	for (auto c: s)
		r += tolower(c);
	return r;
}

bool replace(string& s, string oldS, string newS){
	oldS = tolower(oldS);
	newS = tolower(newS);
	auto index = s.find(oldS);
	if(index == string::npos)
		return false;
	s.replace(index, oldS.size(), newS);
	return true;
}

//cleans string of invalids
void strip(string& s){
	s = tolower(s);
	string allowed = "abcdefghijklmnopqrstuvwxyz0123456789-";
	string out = "";
	bool allowSpace = false;
	
	for(auto c: s){
		if(find(allowed.begin(), allowed.end(), c) != allowed.end()){
			out.push_back(c);
			allowSpace = true;
		}else if(c == ' ' && allowSpace){
			out.push_back(c);
			allowSpace = false;
		}
	}
	if(s.size())
		if(s[s.size() - 1] == ' ')
			s.resize(s.size() - 1);
	s = out;
}

//smart append
string combineWords(const vector<string> words){ 
	if (words.size() == 0)
		return "";
	if (words.size() == 1)
		return words[0];
	if (words.size() == 2)
		return words[0] + " and " + words[1]; 
	
	string s = words[0];
	for (int i = 1; i < words.size() - 1; i++){
		s += ", " + words[i];
	}
	s += " and " + words[(words.size() - 1)];
	return s;
}


//Determines if user input is "close enough" to the name of object to get examined.
bool closeEnough(std::string toFind, std::string toSearch){
	if (toFind.empty())
		return false;
	toFind = tolower(toFind);
	toSearch = tolower(toSearch);
	return toSearch.find(toFind) != string::npos;
}



Game::Game(){}

bool Game::go(std::string name, bool exact) {
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
	if (exact)
		return false;
	
	for (auto& e: current->edges)
		if(closeEnough(n,e->shortDescription)){
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
std::string Game::drop(std::string name){
	assert(current != 0);
	string n = tolower(name);
	for (int i = 0; i < objects.size(); i++){
		if(n == tolower(objects[i]->name)){
			current->objects.push_back(objects[i]);
			string s = objects[i]->name;
			objects.erase(objects.begin() + i);
			
			return "You drop the " + s;
		}
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
	if (!name.size())
		return current->examine();
	string n = tolower(name);
	for (auto& e: current->edges)
		if(closeEnough(n, e->name) || closeEnough(n, e->shortDescription))  
			return e->examine();
	for (auto& o: current->objects)
		if(closeEnough(n, o->name) || closeEnough(n, o->shortDescription))
			return o->examine();
	for (auto& f: current->features)
		if(closeEnough(n, f->name) || closeEnough(n, f->shortDescription))
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
			if(find(allObjects.begin(), allObjects.end(), o) == allObjects.end())
				allObjects.push_back(o);
		}
	}
	
	//Pat, this is  a demo of how to use setObjectLocation and getObjectLocation
	Object* o = new Object;
	o->name = "ChristmasPoo";
	o->shortDescription = "Hanky is the Poo";
	o->longDescription = "You see what appears to have been Mr. Hanky the X-mas Poo";
	allObjects.push_back(o);
	setObjectLocation("ChristmasPoo", "Spaceship");
	setObjectLocation("ChristmasPoo", "Inventory");
	setObjectLocation("ChristmasPoo", "Beach");
	cout << "current location: " << getObjectLocation("ChristmasPoo") << endl;
	
}

// FIX Incomplete
std::string Game::inventory(){
	if (objects.empty())
		return "Your inventory is empty";
	string s = "You have ";
	
	for (auto* o: objects){
		s += o->name + " ";
	}
	return s;
	
}

std::string Game::whatToLook(){
	vector <string> itemsToLookFor;
	for (auto* e: current->edges)
		if(e->visible)
			itemsToLookFor.push_back(e->name);
	for (auto* f: current->features)
		if(f->visible)
			itemsToLookFor.push_back(f->name);
	for	(auto* o: current->objects)
		if(o->visible)
			itemsToLookFor.push_back(o->name);
	return combineWords(itemsToLookFor);
}

std::string Game::whereToGo(){
	vector <string> itemsToLookFor;
	for (auto* e: current->edges)
		if(e->visible && e->passable)
			itemsToLookFor.push_back(e->name);
	return combineWords(itemsToLookFor);	
}







std::string Game::preParse(std::string rawInput){
	string s = rawInput;
	strip(s);
	for (auto* e: current->edges)
		if(replace(s, e->shortDescription, e->name))
			break;
// FIX  Add Feature and Object and correct the functionality currently present
	//cout << "Game::preParse: " << s << endl;
	return s;
}

std::string Game::getObjectLocation(std::string name){
	name = tolower(name);
	for (auto* n: allNodes){
		for (auto* o: n->objects)
			if(name == tolower(o->name))
				return n->name;
	}
	for (auto* o: objects){
		if (name == tolower(o->name))
			return "inventory";
	}
	return "void";
}
	
bool Game::setObjectLocation(std::string name, std::string location){
	name = tolower(name);
	location = tolower(location);
	
	Object* objectToPlace = 0;
	for (auto* o: allObjects)
		if(name == tolower(o->name)){
			objectToPlace = o;
			break;
		}
	if(!objectToPlace)
		return false;
	
	for (auto* n: allNodes){
		for (int i = 0; i < n->objects.size(); i++)
			if(name == tolower(n->objects[i]->name)){
				n->objects.erase(current->objects.begin() + i); // erasing object from a node
				break;	
			}
	}
	for (int i = 0; i < objects.size(); i++)
		if(name == tolower(objects[i]->name)){
			objects.erase(objects.begin() + i); // erasing object from inventory
			break;	
		}
	if(location == "void")
		return true;
	if(location == "inventory"){
		objects.push_back(objectToPlace);
		return true;
	}
	for(auto* n: allNodes){
		if(location == tolower(n->name)){
			n->objects.push_back(objectToPlace);
			return true;
		}
	}
	return false;
}