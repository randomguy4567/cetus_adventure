#include "Node.h"

using namespace std;

Node::Node(){	
}

string joinString(const string& string1, const string& string2){
	if (!string1.size())
		return string2;
	if (!string2.size())
		return string1;
	return string1 + ". " + string2;
}
string Node::describe(){
	string s = name + "\n----------\n";
	if (visited){
		visited = true;
		s += shortDescription;
	}
	else{
		visited = true;
		s += longDescription;
	}
	for (auto& e: edges)
		s = joinString(s, e->describe());
	for (auto& o: objects)
		s = joinString(s, o->describe());
	for (auto& f: features)
		s = joinString(s, f->describe());
	return s;
}