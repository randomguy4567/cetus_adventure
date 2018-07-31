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


using namespace std;

void buildDictionary(Game* g, std::map<std::string, Tag>& dict){
	for (auto* e: g->current->edges){
		auto str = e->name;
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		dict[str] = E;
	}
	for (auto* f: g->current->features){
		auto str = f->name;
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		dict[str] = N;
	}
	for (auto* o: g->current->objects){
		auto str = o->name;
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		dict[str] = N;
	}
	for (auto* o: g->objects){
		auto str = o->name;
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		dict[str] = N;
	}
	//verifying dictionary conetents
	cout << "current dictinary: " << endl;
	for(auto p: dict){
		cout << p.first << " " << p.second << endl;
	}
}
//This allows us to "play" the demo
void loop(Game* g){
	g->interface.print(g->describe() + "\n\n");
	while(g->current != g->end){
		g->interface.print("> ");
		string s = g->interface.getline();
		
		s = g->preParse(s);
		
		// This is to allow an Edge name as a command
		if (g->go(s, true)){
			g->interface.print(g->describe() + "\n\n");
		}
		else{
			string verb, param;
			//*****This is where the parser is integrated************************************
			bool useParser = true;
			if(useParser){
				Parser parser;
				ParsedCommand parsedCommand;
				std::map<std::string, Tag> dict;
				buildDictionary(g, dict);
				
				parsedCommand = parser.getParsedCommand( s, dict );
				std::cout << "Verb: " << parsedCommand.getVerb() << std::endl;
				std::cout << "Param: " << parsedCommand.getParam() << std::endl;
				std::cout << "Status: " << parsedCommand.getStatus() << std::endl;
				
				verb = parsedCommand.getVerb();
				param = parsedCommand.getParam();
				
			}else{
				istringstream istr(s);

				istr >> verb >> param;				
			}

			
			
			
			
			
			
			
			
			
			
			//Process output from parser
			if(verb == "l"){
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
				s = g->examine(param);
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
					g->interface.print(g->describe() + "\n\n");
				
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
			}else{
				g->interface.print("You don't understand that. \n\n");
			}
			
		}
	}
	g->interface.print(g->describe() + ".\n\n");
}
