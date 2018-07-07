#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

class Interface {
public:
	//This is just a stub so that I can add an Ncurses layer toward the end to make things look nice.
	void print(std::string text); //whatever text will go on the screen
	std::string getline(); // get a line of input. 
};
#endif