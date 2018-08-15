#include <string>
#include <iostream>
#include "Interface.h"
#include <ncurses.h>
#include <sstream>

using namespace std;

enum COLORS {
	GREEN = 2, BLUE, MAGENTA, WHITE, CYAN
};

//ncurses initial
void Interface::init(){
	logFile.open("cetus.log");
	initscr();
	start_color();
	nonl();
	scrollok(stdscr, true);
	//init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);	
	init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
  string s = "\
\n\
       __        __   _                            _        \n\
       \\ \\      / /__| | ___ ___  _ __ ___   ___  | |_ ___  \n\
        \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\ \n\
         \\ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) |\n\
          \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/ \n\
\n\
\n\
#######################################/,*#######################################\n\
#####################################(   *#######################################\n\
#####################################(   *#######################################\n\
##*              ###.              ##(         ##   *#######   .###.            #\n\
#.   .///////////#(    ************##(   .*****##   *#######   .#(    **********#\n\
#    (############(   .##############(   *#######   *#######   .#(   ,###########\n\
#    (#########(**,    ************##(   *#######   *#######   .#(            .,#\n\
#    (#########/                   ##(   *#######   *#######   .##(             #\n\
#    (############(   .##############(   *#######   *#######   .##############  #\n\
#    /############(   .##############(   *#######   *#######   .##############  #\n\
#*               #(                ###         ##              .##.             #\n\
##(,             ###*              ####*       ###*            .##.            .#\n\
#################################################################################\n\
#############################################################/ (#################\n\
############################################################  *##################\n\
###########################################################    /#################\n\
###(,                    ...,,,**(########################/      ,*(#############\n\
##,                                .######################           ,###########\n\
##.                                  .(################*                    ..,.#\n\
##.                                         .....         *#########*.     .*(###\n\
##/                     ,                              *#########################\n\
###(                                                ,############################\n\
#######,,,*********,,.      ,                    ,###############################\n\
#########################    .                ,##################################\n\
##############################/.#################################################\n\
\n";
	attron(COLOR_PAIR(BLUE));
	printw(s.c_str());
	attron(COLOR_PAIR(WHITE));		
}

void Interface::shutdown(){
	endwin();
	cout << "All output written to cetus.log\n";
}

//custom tolower function
extern string tolower(const string& s);

//ncurses
void Interface::printString(std::string text){
	istringstream iLine(text);	
	string word;
	while(iLine >> word){
		bool switchColor = false;
		string cleanWord = tolower(word);
		if (!cleanWord.empty()){
			if (cleanWord[cleanWord.size() - 1] == '.')
				cleanWord.resize(cleanWord.size() - 1);
			if (cleanWord[cleanWord.size() - 1] == ',')
				cleanWord.resize(cleanWord.size() - 1);
			
		}
		auto it = dict.find(cleanWord);
		if(it != dict.end()){
			if(it->second == V){
				attron(COLOR_PAIR(GREEN));
				switchColor = true;				
			}
			if(it->second == N){
				attron(COLOR_PAIR(BLUE));
				switchColor = true;				
			}	
			if(it->second == E){
				attron(COLOR_PAIR(CYAN));
				switchColor = true;				
			}
		}
		printw((word + " ").c_str());
		if(switchColor){
			attron(COLOR_PAIR(WHITE));
		}
	}	
			
}

//whatever text will go on the screen
void Interface::print(std::string text){ 
	logFile << text;
	string s;
	for (auto ch: text){
		if(ch == '\n'){
			if(!s.empty()){
				printString(s);
				s = "";
			}
			printw("\n");
		}else{
			s += ch;
		}
	}
	if(!s.empty()){
		printString(s);
		s = "";
	}	
	refresh();	
}
 
std::string Interface::getline() {
	string s;
	char buf[4096];
	getnstr(buf, 4095);
	s = buf;
	return s;
/*	string s;
	std::getline(cin, s);
	if(cin.fail()){
		print("Quitting because input is exhausted.\n");
		exit(1);
	}
	return s;*/
}
