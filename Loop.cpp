#include <sstream>
#include "Game.h"
#include "Loop.h"


using namespace std;


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
			//*****This is where the parser will be integrated************************************
			istringstream istr(s);
			string verb, param;
			istr >> verb >> param;
			
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
