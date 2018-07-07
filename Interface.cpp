#include <string>
#include <iostream>
#include "Interface.h"

using namespace std;

void Interface::print(std::string text){ //whatever text will go on the screen
	cout << text;
} 
std::string Interface::getline() {
	string s;
	std::getline(cin, s);
	return s;
}
