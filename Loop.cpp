#include <algorithm>
#include <sstream>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include "Game.h"
#include "Loop.h"
#include "Parser.hpp"
#include "Tag.hpp"
#include "Database.h"


using namespace std;

string stringToLower(string s){
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

void buildDictionary(Game* g, std::map<std::string, Tag>& dict, vector<string>& verbs){
	for (auto* e: g->current->edges)
		if (e->visible)
		{
			auto str = e->name;
			std::transform(str.begin(), str.end(), str.begin(), ::tolower);
			dict[str] = E;
		}
	for (auto* f: g->current->features)
		if (f->visible)
		{
			auto str = f->name;
			std::transform(str.begin(), str.end(), str.begin(), ::tolower);
			dict[str] = N;
		}
	for (auto* o: g->current->objects)
		if (o->visible)
		{
			auto str = o->name;
			std::transform(str.begin(), str.end(), str.begin(), ::tolower);
			dict[str] = N;
		}
	// Inventory
	for (auto* o: g->objects){
		auto str = o->name;
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		dict[str] = N;
		str = o->_verb;

		str = stringToLower(str);
		dict[str] = V;
	}
	
	
	// Verbs for "help"
	for (auto* o: g->allObjects){
		if(o->_verb.size())
			if(find(verbs.begin(), verbs.end(), o->_verb) == verbs.end())
				verbs.push_back(o->_verb);
	}

	dict["cheat"] = V;
	dict["use"] = V;
	dict["help"] = V;
	dict["save"] = V;
	dict["load"] = V;
}
// This allows us to "play" the game
void loop(Game* g){
	std::map<std::string, Tag> dict;
	g->interface.print(g->describe() + ".\n\n");
	while(g->current != g->end){
		g->interface.print("> ");
		string cmd = g->interface.getline();
		
		cmd = g->preParse(cmd);
		
		// This is to allow an Edge name as a command
		if (g->go(cmd, true)){
			g->interface.print(g->describe() + ".\n\n");
		}
		else{
			string verb, param;
			vector<string> verbs;
			//*****This is where the parser is integrated************************************
			bool useParser = true;
			if(useParser&&cmd.size()){
				Parser parser;
				ParsedCommand parsedCommand;
				dict.clear();

				buildDictionary(g, dict, verbs);
				
				parsedCommand = parser.getParsedCommand( cmd, dict );
				std::cout << "Verb: " << parsedCommand.getVerb() << std::endl;
				std::cout << "Param: " << parsedCommand.getParam() << std::endl;
				std::cout << "Status: " << parsedCommand.getStatus() << std::endl;
				
				verb = parsedCommand.getVerb();
				param = parsedCommand.getParam();
				
			}else{
				istringstream istr(cmd);

				istr >> verb >> param;				
			}

			
			
			
			
			
			
			
			
			
			string s;
			//Process output from parser
			if(!verb.size()){
				
			}
			else if(verb == "l"){
				s = g->describe(param);
				if(s.empty()){
					g->interface.print("You can't look at that.");
					s = g->whatToLook();
					if(s.size())
						g->interface.print(" You can look at " + s + ".");
					g->interface.print("\n\n");
				}
				else
					g->interface.print(s + ".\n\n");
						 	
			}else if(verb == "examine" || verb == "look"){
				if (param!="" || cmd=="look") s=g->examine(param);
				if(s.empty()){
					g->interface.print("You can't look at that.");
					s = g->whatToLook();
					if(s.size())
						g->interface.print(" You can look at " + s + ".\n\n");
				}else
					g->interface.print(s + ".\n\n");	
						
			}else if(verb == "go"){
			
				if(!g->go(param)){
					g->interface.print("You can't go that way.");	
					s = g->whereToGo();
					if (s.size())
						g->interface.print(" You can go " + s);
					g->interface.print("\n\n");				
				}
				else
					g->interface.print(g->describe() + ".\n\n");
				
			}else if(verb == "take"){
				s = g->take(param);
				if(s.empty())
					g->interface.print("You can't take that.\n\n");
				else
					g->interface.print(s + ".\n\n");	
							 	
			}else if(verb == "drop"){
				s = g->drop(param);
				if(s.empty())
					g->interface.print("You can't drop that.\n\n");				
				else
					g->interface.print(s + ".\n\n");			 	
			}else if(verb == "inventory"){
	
				g->interface.print(g->inventory() + ".\n\n");			 	
			}else if(verb == "cheat"){
		
				g->printDatabase();	
					//verifying dictionary conetents
				cout << "current dictionary: " << endl;
				for(auto p: dict){
					cout << p.first << " " << p.second << endl;
				}		 	
			}else if(verb == "help"){
				ifstream in ("help.txt");
				while (in){
					string s;
					getline(in, s);
					if (in){
						g->interface.print(s + "\n");
					}
				}
				g->interface.print("Additional verbs that can be used on objects: \n");
				for (auto s: verbs)
					g->interface.print(s + "\n");
				g->interface.print("\n");		 	
			}else if(verb == "save"){
				if(saveGame(g))
					g->interface.print("The game has been saved!\n");
				else
					g->interface.print("The game was not able to be saved.\n");							 	
			}else if(verb == "load"){
				if(loadGame(g, numberOfRooms)){
					g->interface.print("The game has been loaded from a saved state.\n");
					g->interface.print(g->describe() + ".\n\n");
				}
				else
					g->interface.print("The game was not able to be loaded.\n");							 	
			}else if(verb == "quit"){

				g->interface.print("Quitting the game.\n");	
				return;						 	
			}else{
				s = g->tryVerb(verb, param);
				if (s.empty())
					g->interface.print("I don't understand that. \n\n");
				else
					g->interface.print(s + ".\n\n");
			}
			
		}
	}
	g->interface.print(g->describe() + ".\n\n");
}
