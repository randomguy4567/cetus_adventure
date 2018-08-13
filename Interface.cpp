#include <string>
#include <iostream>
#include "Interface.h"

using namespace std;

//whatever text will go on the screen
void Interface::print(std::string text){ 
	cout << text;
}
 
std::string Interface::getline() {
	string s;
	std::getline(cin, s);
	if(cin.fail()){
		print("Quitting because input is exhausted.\n");
		exit(1);
	}
	return s;
}
