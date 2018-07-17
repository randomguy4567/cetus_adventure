#include "Game.h"
using namespace std;

#include <sstream>


// This is an example of how to use the engine to build the database.
 // The database will have to read the input files and parse them to make similar calls.
void initialize(Game* g){
	//Beginning Node/room instantiation
	Node* n1 = g->current = g->root = new Node();
		n1->name = "Beginning";
		n1->shortDescription = "Cold, bright room";
		n1->longDescription = "You wake up in a bright room. It's cold in here";

		
	//Middle Node/room instantiation
	Node* n2 = new Node();
		n2->name = "Middle";
		n2->shortDescription = "Cold, dark cave";
		n2->longDescription = "You are now in a cave. It's dark";

	//End Node/room instantiation
	Node* n3 = g->end = new Node();
		n3->name = "End";
		n3->shortDescription = "The light";
		n3->longDescription = "You are now out of the cave. You see light";


	// Note that the database has to be built in multiple passes. You must
	 // have the Nodes before you can build the Edges.
	Edge* e1 = new Edge(); //e1 = edge 1
		e1->name = "East";
		e1->shortDescription = "Door";
		e1->longDescription = "You see a door to the east. It appears to be locked";
		e1->passable = false;
		e1->node = n2; //link to middle Node/room
		n1->edges.push_back(e1);
		
	Edge* e2a = new Edge(); // e2a = west edge of room 2, heading back to node/room 1
		e2a->name = "West"; 
		e2a->shortDescription = "Door to west";
		e2a->longDescription = "There is an unlocked door to the west";	
		e2a->node = n1; //link from middle Node back to beginning Node
		n2->edges.push_back(e2a);
		
	Edge* e2b = new Edge(); // e2b = east edge of room 2, heading in to end node/room
		e2b->name = "East";
		e2b->shortDescription = "An opening to the east";
		e2b->longDescription = "There is an opening to the east. It leads to a good place";
		e2b->visible = false;
		e2b->passable = false;
		e2b->node = n3; //link from middle Node to end Node
		n2->edges.push_back(e2b);
		
	Feature* f2a = new Feature();
		f2a->name = "Hole";
		f2a->shortDescription="You see a hole";
		f2a->longDescription="You see a hole. There is something inside";
		f2a->visible = true;
	
	Feature* f2b = new Feature();
		f2b->name = "Mouse";
		f2b->shortDescription="Rotting dead mouse";
		f2b->longDescription="You've found a dead mouse. It's rotting";
		f2b->visible = false; //not visible until you examine f2a
	
	n2->features.push_back(f2a); //adding feature to room
	n2->features.push_back(f2b);
	f2a->feature = f2b; //linking examine, will cause f2b to become visible/accessible
	
	Object* o1 = new Object();
		o1->name = "Key";
		o1->shortDescription = "Shiny key";
		o1->longDescription = "A shiny key is on the ground. Maybe you can find a locked door";
		o1->visible = true;
		o1->edge = e1; //when you have the key, edge to middle node/room traversable
		o1->setVerb("Take", "You take the key");
	n1->objects.push_back(o1); 
	
	Object* o2 = new Object();
		o2->name = "Maggots";
		o2->shortDescription = "Maggots look live, fresh, tasty";
		o2->longDescription = "Maggots look live, fresh and tasty. You should eat them";
		o2->visible = false;
		o2->edge = e2b; //when you consume maggots, edge to end room now visible.
		
		o2->setVerb("Eat", "You eat the maggots. You can see clearly now");
		
	n2->objects.push_back(o2); //object now in inventory.
	f2b->object = o2; //connecting maggots to the second feature
	
	//This is to provide easy access to the Nodes for the database save and load feature
	g->allNodes.push_back(n1);
	g->allNodes.push_back(n2);
	g->allNodes.push_back(n3);	

	
}



void initializeSimplified(Game* g){
	//Beginning Node/room instantiation
	Node* n1 = g->current = g->root = new Node();
		n1->name = "Beginning";
		n1->shortDescription = "Cold, bright room";
		n1->longDescription = "You wake up in a bright room. It's cold in here";

		
	//Middle Node/room instantiation
	Node* n2 = new Node();
		n2->name = "Middle";
		n2->shortDescription = "Cold, dark cave";
		n2->longDescription = "You are now in a cave. It's dark";

	//End Node/room instantiation
	Node* n3 = g->end = new Node();
		n3->name = "End";
		n3->shortDescription = "The light";
		n3->longDescription = "You are now out of the cave. You see light";


	// Note that the database has to be built in multiple passes. You must
	 // have the Nodes before you can build the Edges.
	Edge* e1 = new Edge(); //e1 = edge 1
		e1->name = "East";
		e1->shortDescription = "Door";
		e1->longDescription = "You see a door to the east. It appears to be locked";
		e1->passable = false;
		//e1->node = n2; //link to middle Node/room
		e1->initialNodeName = "Middle";
		n1->edges.push_back(e1);
		
	Edge* e2a = new Edge(); // e2a = west edge of room 2, heading back to node/room 1
		e2a->name = "West"; 
		e2a->shortDescription = "Door to west";
		e2a->longDescription = "There is an unlocked door to the west";	
		//e2a->node = n1; //link from middle Node back to beginning Node
		e2a->initialNodeName = "Beginning";
		n2->edges.push_back(e2a);
		
	Edge* e2b = new Edge(); // e2b = east edge of room 2, heading in to end node/room
		e2b->name = "East";
		e2b->shortDescription = "An opening to the east";
		e2b->longDescription = "There is an opening to the east. It leads to a good place";
		e2b->visible = false;
		e2b->passable = false;
		//e2b->node = n3; //link from middle Node to end Nod
		e2b->initialNodeName = "End";
		n2->edges.push_back(e2b);
		
	Feature* f2a = new Feature();
		f2a->name = "Hole";
		f2a->shortDescription="You see a hole";
		f2a->longDescription="You see a hole. There is something inside";
		f2a->visible = true;
		f2a->initialFeatureName = "Mouse";
	
	Feature* f2b = new Feature();
		f2b->name = "Mouse";
		f2b->shortDescription="Rotting dead mouse";
		f2b->longDescription="You've found a dead mouse. It's rotting";
		f2b->visible = false; //not visible until you examine f2a
		f2b->initialObjectName = "Maggots";
	
	n2->features.push_back(f2a); //adding feature to room
	n2->features.push_back(f2b);
	//f2a->feature = f2b; //linking examine, will cause f2b to become visible/accessible
	
	Object* o1 = new Object();
		o1->name = "Key";
		o1->shortDescription = "Shiny key";
		o1->longDescription = "A shiny key is on the ground. Maybe you can find a locked door";
		o1->visible = true;
		//o1->edge = e1; //when you have the key, edge to middle node/room traversable
		o1->initialEdgeName = "East";
		o1->setVerb("Take", "You take the key");
	n1->objects.push_back(o1); 
	
	Object* o2 = new Object();
		o2->name = "Maggots";
		o2->shortDescription = "Maggots look live, fresh, tasty";
		o2->longDescription = "Maggots look live, fresh and tasty. You should eat them";
		o2->visible = false;
		//o2->edge = e2b; //when you consume maggots, edge to end room now visible.
		o2->initialEdgeName = "East";
		
		o2->setVerb("Eat", "You eat the maggots. You can see clearly now");
		
	n2->objects.push_back(o2); //object now in inventory.
	//f2b->object = o2; //connecting second feature to maggots
	
	//This is to provide easy access to the Nodes for the database save and load feature
	g->allNodes.push_back(n1);
	g->allNodes.push_back(n2);
	g->allNodes.push_back(n3);	

	g->buildGraph();
}




// Here is an example of some of the method calls that the main loop will use.	
 // It was my Original intention that the parser would be able to make these 
 // method calls, but some of these calls are also intended to be made by the main loop itself.
 // **See Figure 1 of PROJECT PLAN for a more clear visual walkthrough**
void walkthrough(Game* g){
	
	g->interface.print("\n\n");
	
	//Beginning Node/Room 
	g->interface.print(g->describe());
	g->interface.print(".\n\n");
	g->interface.print("> look\n");	
	g->interface.print(g->describe());
	g->interface.print(".\n\n");
	g->interface.print("> go east\n\n");	
	if (!g->go("east")) 
		g->interface.print("You can't go that way\n\n");	
	g->interface.print("> take key\n");	
	g->interface.print(g->take("key"));
	g->interface.print(".\n\n");
	g->interface.print("> go east\n\n");	
	if (!g->go("east")) 
		g->interface.print("You can't go that way");
	g->interface.print(g->describe());
	g->interface.print(".\n\n");	
	g->interface.print("> go west\n\n");	
	if (!g->go("west")) 
		g->interface.print("You can't go that way");
	g->interface.print(g->describe());
	g->interface.print(".\n\n");	
	g->interface.print("> go east\n\n");	
	if (!g->go("east")) 
		g->interface.print("You can't go that way");
	
	//Middle Node/Room
	g->interface.print(g->describe());
	g->interface.print(".\n\n");	
	g->interface.print("> examine hole\n");	
	g->interface.print(g->examine("hole"));	
	g->interface.print(".\n\n");
	g->interface.print("> examine mouse\n");	
	g->interface.print(g->examine("mouse"));	
	g->interface.print(".\n\n");
	g->interface.print("> consume maggots\n");	
	g->interface.print(g->consume("maggots"));	
	g->interface.print(".\n\n");
	g->interface.print("> look\n");	
	g->interface.print(g->describe());
	g->interface.print(".\n\n");
	g->interface.print("> go east\n\n");	
	if (!g->go("east")) 
		g->interface.print("You can't go that way\n\n");

	//End Node/Room
	g->interface.print(g->describe());
	g->interface.print(".\n\n");
	if(g->current == g->end)
		g->interface.print("We're at the end. This is where the main loop would quit");
}

//This allows us to "play" the demo
void loop(Game* g){
	g->interface.print(g->describe() + "\n\n");
	while(g->current != g->end){
		g->interface.print("> ");
		string s = g->interface.getline();
		istringstream istr(s);
		string verb, param;
		istr >> verb >> param;
		if(verb == "look"){
			g->interface.print(g->describe(param) + ".\n\n");			
		 	
		}else if(verb == "examine"){
			g->interface.print(g->examine(param) + ".\n\n");			
		}else if(verb == "go"){
			if(g->go(param)){
				g->interface.print(g->describe() + ".\n\n");
			}else{
				g->interface.print("You can't go that way.\n\n");
			}
		}else if(verb == "take"){
			g->interface.print(g->take(param) + ".\n\n");			 	
		}
	}
	g->interface.print(g->describe() + ".\n\n");
}

int main(){
	Game* g = new Game();
	initializeSimplified(g);
	g->interface.print("Welcome to Cetus. \n\n");
	loop(g);
	//walkthrough(g);	
}