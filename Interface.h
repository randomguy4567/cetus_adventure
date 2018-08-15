#ifndef INTERFACE_H
#define INTERFACE_H
#include <map>
#include <string>
#include <fstream>
#include "Tag.hpp"



class Interface {
public:
	Interface(){
		init();
	}
	~Interface(){
		shutdown();
	}
		//This is just a stub so that I can add an Ncurses layer toward the end to make things look nice.
	void print(std::string text); //whatever text will go on the screen
	std::string getline(); // get a line of input. 
	void setDict(const std::map<std::string, Tag> &dict){
		Interface::dict = dict;
	}
	
	
private:
	void init();
	void shutdown();
	std::map<std::string, Tag> dict;
	void printString(std::string text);
	std::ofstream logFile;
};
#endif