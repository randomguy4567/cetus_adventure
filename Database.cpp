#include <algorithm>
#include <assert.h>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "Database.h"
using namespace std;


string fileParser(int nextLevel, string currLevelStr, string targetAttrName, int *minPos) {
    
    string theStr = currLevelStr;
    string finalStr = "";
    string attName = "[[" + targetAttrName + "]]";
    string start = "[START" + to_string(nextLevel) + "]";
    string end = "[END" + to_string(nextLevel) + "]";
    
    size_t startPos = (*minPos);
    
    startPos = theStr.find(attName, *minPos);
    if(startPos == string::npos) {
        return "";
    }
    
    startPos = theStr.find(start, startPos) + 8;
    size_t endPos = theStr.find(end, startPos);
    
    if(startPos == string::npos || endPos == string::npos) {
        return "";
    }
    
    finalStr = theStr.substr(startPos, endPos - startPos);
    *minPos = (int) endPos + 6;
    
    return finalStr;
}
// Params: Game *g
int initialize(Game *g, int numRooms) {
    // CODE TO CYCLE THROUGH ALL ROOMS IN TARGET DIRECTORY NEEDED HERE
    string baseFileName = "./RoomFiles/Room";
    string rFileName;
    
    // TEMPORARY CODE: GET TEST ROOM AS FILE
    for(int i = 1; i < numRooms + 1; i++) {
        rFileName = baseFileName + to_string(i);
        
        ifstream inFile;
        inFile.open(rFileName);
        assert(inFile.good());
        Node* n = new Node();
        
        string roomContents = "";
        char c;
        while(inFile.get(c))
            roomContents = roomContents + c;
        
        // Print room name
        string target = "RoomName";
        int minpos = 0;
        string roomName = fileParser(0, roomContents, target, &minpos);
        // cout << "Room Name: " << roomName << endl;
        n->name = roomName;
        
        // Print room type
        target = "RoomType";
        minpos = 0;
        string roomType = fileParser(0, roomContents, target, &minpos);
        // cout << "Room Type: " << roomType << endl;
        
        if(roomType == "Start")
            g->current = g->root = n;
        else if(roomType == "End")
            g->end = n;
        
        // Print short description
        target = "ShortDescription";
        minpos = 0;
        string roomShortDesc = fileParser(0, roomContents, target, &minpos);
        // cout << "Short Description: " << roomShortDesc << endl;
        n->shortDescription = roomShortDesc;
        
        // Print long descriptions
        target = "LongDescription";
        minpos = 0;
        string roomLongDesc = fileParser(0, roomContents, target, &minpos);
        // cout << "Long Description: " << roomLongDesc << endl;
        n->longDescription = roomLongDesc;
        
        // cout << endl;
        
        // Get raw edges string
        target = "Edges";
        minpos = 0;
        string edgeList = fileParser(0, roomContents, target, &minpos);
        
        // Print all edges
        int counter = 0;
        target = "Edge";
        string edgeI;
        minpos = 0;
        do{
            edgeI = fileParser(1, edgeList, target, &minpos);
            
            if(edgeI != "") {
                Edge* e = new Edge();
                
                // cout << "Edge " << (counter + 1) << endl;
                
                // Print edge name
                int temp2 = 0;
                string edgeQuery = fileParser(2, edgeI, "EdgeName", &temp2);
                // cout << "Edge Name: " << edgeQuery << endl;
                e->name = edgeQuery;
                
                // Print edge short description
                temp2 = 0;
                edgeQuery = fileParser(2, edgeI, "EdgeShortDescription", &temp2);
                // cout << "Edge Short Description: " << edgeQuery << endl;
                e->shortDescription = edgeQuery;
                
                // Print edge long description
                temp2 = 0;
                edgeQuery = fileParser(2, edgeI, "EdgeLongDescription", &temp2);
                // cout << "Edge Long Description: " << edgeQuery << endl;
                e->longDescription = edgeQuery;
                
                // Print edge visibility
                temp2 = 0;
                edgeQuery = fileParser(2, edgeI, "EdgeVisible", &temp2);
                // cout << "Edge Visible?: " << edgeQuery << endl;
                e->visible = atoi(edgeQuery.c_str());
                
                // Print edge passability
                temp2 = 0;
                edgeQuery = fileParser(2, edgeI, "EdgePassable", &temp2);
                // cout << "Edge Passable?: " << edgeQuery << endl;
                e->passable = atoi(edgeQuery.c_str());
                
                // Print edge's ending node
                temp2 = 0;
                edgeQuery = fileParser(2, edgeI, "EdgeNode", &temp2);
                // cout << "Edge Node: " << edgeQuery << endl;
                e->initialNodeName = edgeQuery;
                
                
                n->edges.push_back(e);
            }
            counter++;
            // cout << endl;
            
        } while(edgeI != "");
        
        // Get raw features string
        target = "Features";
        minpos = 0;
        string featList = fileParser(0, roomContents, target, &minpos);
        
        // TEST
        // cout << featList << endl;
        
        // Print all features
        counter = 0;
        target = "Feature";
        string featI;
        minpos = 0;
        do{
            featI = fileParser(1, featList, target, &minpos);
            
            // TEST
            // cout << featI << endl;
            
            if(featI != "") {
                Feature* f = new Feature();
                
                // cout << "Feature " << (counter + 1) << endl;
                
                // Print feature name
                int temp2 = 0;
                string featQuery = fileParser(2, featI, "FeatureName", &temp2);
                // cout << "Feature Name: " << featQuery << endl;
                f->name = featQuery;
                
                // Print feature short description
                temp2 = 0;
                featQuery = fileParser(2, featI, "FeatureShortDescription", &temp2);
                // cout << "Feature Short Description: " << featQuery << endl;
                f->shortDescription = featQuery;
                
                // Print feature long description
                temp2 = 0;
                featQuery = fileParser(2, featI, "FeatureLongDescription", &temp2);
                // cout << "Feature Long Description: " << featQuery << endl;
                f->longDescription = featQuery;
                
                // Print feature visibility
                temp2 = 0;
                featQuery = fileParser(2, featI, "FeatureVisible", &temp2);
                // cout << "Feature Visible?: " << featQuery << endl;
                f->visible = atoi(featQuery.c_str());
                
                // Print feature target (UNUSED)
                temp2 = 0;
                featQuery = fileParser(2, featI, "FeatureTargetType", &temp2);
                
                if (featQuery == "Feature") {
                    temp2 = 0;
                    string featQuery2 = fileParser(2, featI, "FeatureTargetFeature", &temp2);
                    // cout << "Feature Target: " << featQuery2 << endl;
                    f->initialFeatureName = featQuery2;
                } else if (featQuery == "Object") {
                    temp2 = 0;
                    string featQuery2 = fileParser(2, featI, "FeatureTargetObject", &temp2);
                    // cout << "Feature Target: " << featQuery2 << endl;
                    f->initialObjectName = featQuery2;
                }
                
                n->features.push_back(f);
            }
            // cout << endl;
            counter++;
        } while(featI != "");
        
        // Get raw objects string
        target = "Objects";
        minpos = 0;
        string objList = fileParser(0, roomContents, target, &minpos);
        
        // Print all objects
        counter = 0;
        target = "Object";
        string objI;
        minpos = 0;
        do{
            Object* a = new Object();
            
            objI = fileParser(1, objList, target, &minpos);
            
            if(objI != "") {
                // cout << "Object " << (counter + 1) << endl;
                
                // Print object name
                int temp2 = 0;
                string objQuery = fileParser(2, objI, "ObjectName", &temp2);
                // cout << "Object Name: " << objQuery << endl;
                a->name = objQuery;
                
                // Print object short description
                temp2 = 0;
                objQuery = fileParser(2, objI, "ObjectShortDescription", &temp2);
                // cout << "Object Short Description: " << objQuery << endl;
                a->shortDescription = objQuery;
                
                // Print object long description
                temp2 = 0;
                objQuery = fileParser(2, objI, "ObjectLongDescription", &temp2);
                // cout << "Object Long Description: " << objQuery << endl;
                a->longDescription = objQuery;
                
                // Print object visibility
                temp2 = 0;
                objQuery = fileParser(2, objI, "ObjectVisible", &temp2);
                // cout << "Object Visible?: " << objQuery << endl;
                a->visible = atoi(objQuery.c_str());
                
                // Print object fixed nature
                temp2 = 0;
                objQuery = fileParser(2, objI, "ObjectFixed", &temp2);
                // cout << "Object Fixed?: " << objQuery << endl;
                a->fixed = atoi(objQuery.c_str());
                
                // Print object target
                temp2 = 0;
                objQuery = fileParser(2, objI, "ObjectTargetType", &temp2);
                // cout << "Object target type: " << objQuery << endl;
                // a->targetType = objQuery;
                if(objQuery == "Edge") {
                    temp2 = 0;
                    objQuery = fileParser(2, objI, "ObjectTargetRoom", &temp2);
                    temp2 = 0;
                    string objQuery2 = fileParser(2, objI, "ObjectTargetEdge", &temp2);
                    // cout << "Object target: Room = " << objQuery << ", Edge = " << objQuery2 << endl;
                    a->target = objQuery + "." + objQuery2;
                } else if(objQuery == "Feature") {
                    temp2 = 0;
                    objQuery = fileParser(2, objI, "ObjectTargetRoom", &temp2);
                    temp2 = 0;
                    string objQuery2 = fileParser(2, objI, "ObjectTargetFeature", &temp2);
                    // cout << "Object target: Room = " << objQuery << ", Feature = " << objQuery2 << endl;
                    a->target = objQuery + "." + objQuery2;
                } else if(objQuery == "Object") {
                    temp2 = 0;
                    objQuery = fileParser(2, objI, "ObjectTargetRoom", &temp2);
                    temp2 = 0;
                    string objQuery2 = fileParser(2, objI, "ObjectTargetObject", &temp2);
                    // cout << "Object target: Room = " << objQuery << ", Object = " << objQuery2 << endl;
                    a->target = objQuery + "." + objQuery2;
                }
                
                // Get object verbs
                temp2 = 0;
                objQuery = fileParser(2, objI, "ObjectVerbs", &temp2);
                
                int counter2 = 0;
                int minp2 = 0;
                string objVerb;
                string verbName, verbResponse, verbHint;
                do {
                    
                    objVerb = fileParser(3, objQuery, "Verb", &minp2);
                    if(objVerb != "") {
                        // cout << "Object Verb " << (counter2 + 1) << endl;
                        
                        int temp22 = 0;
                        string verbQuery = fileParser(4, objVerb, "VerbName", &temp22);
                        // cout << "Verb Name: " << verbQuery << endl;
                        verbName = verbQuery;
                        
                        temp22 = 0;
                        verbQuery = fileParser(4, objVerb, "VerbResponse", &temp22);
                        // cout << "Verb Response: " << verbQuery << endl;
                        verbResponse = verbQuery;
                        
                        temp22 = 0;
                        verbQuery = fileParser(4, objVerb, "VerbHint", &temp22);
                        // cout << "Verb Response: " << verbQuery << endl;
                        verbHint = verbQuery;
                        a->setVerb(verbName,verbResponse,verbHint);
                    }
                    counter2++;
                    
                } while(objVerb != "");
                n->objects.push_back(a);
            }
            // cout << endl;
            counter++;
            
        } while(objI != "");
        
        g->allNodes.push_back(n);
        
        inFile.close();
    }
    g->buildGraph();
    
    return 0;
}


bool saveGame(Game *g) {
    remove("savefile");
    ofstream outFile;
    outFile.open("savegame");
    
    string storageString0 = "[[Current]] : [START0]";
    storageString0 += g->current->name;
    storageString0 += "[END0]\n";
    
    outFile << storageString0;
    
    
    storageString0 = "[[Nodes]] : [START0]\n";
    
    outFile << storageString0;
    
    string storageString1 = "";
    for(auto* n: g->allNodes) {
        // cout << "NAME OF NODE: " << n->name << endl;
        
        storageString1 = "[[Node]] : [START1]\n";
        storageString1 += "[[NodeName]] : [START2]" + n->name + "[END2]\n";
        storageString1 += "[[NodeVisited]] : [START2]";
        storageString1.append(to_string((int) n->visited));
        storageString1 += "[END2]\n";
        
        for(auto* e: n->edges) {
            storageString1 += "[[Edge]] : [START2]\n";
            
            storageString1 += "[[EdgeName]] : [START3]" + e->name + "[END3]\n";
            
            storageString1 += "[[EdgeVisible]] : [START3]";
            storageString1.append(to_string((int) e->visible));
            storageString1 += "[END3]\n";
            
            storageString1 += "[[EdgePassable]] : [START3]";
            storageString1.append(to_string((int) e->passable));
            storageString1 += "[END3]\n";
            
            storageString1 += "[[EdgeVisited]] : [START3]";
            storageString1.append(to_string((int) e->visited));
            storageString1 += "[END3]\n";
            
            storageString1 += "[END2]\n";
        }
        for(auto* f: n->features) {
            storageString1 += "[[Feature]] : [START2]\n";
            
            storageString1 += "[[FeatureName]] : [START3]" + f->name + "[END3]\n";
            
            storageString1 += "[[FeatureVisible]] : [START3]";
            storageString1.append(to_string((int) f->visible));
            storageString1 += "[END3]\n";
            
            storageString1 += "[[FeatureVisited]] : [START3]";
            storageString1.append(to_string((int) f->visited));
            storageString1 += "[END3]\n";
            
            storageString1 += "[END2]\n";
        }
        storageString1 += "[END1]\n";
        
        // store storageString
        
        // TEST
        // cout << storageString1;
        // Game
        outFile << storageString1;
    }
    storageString0 = "[END0]\n";
    
    // TEST
    // cout << storageString0;
    
    // Game
    outFile << storageString0;
    
    storageString0 = "[[Objects]] : [START0]\n";
    
    // TEST
    // cout << storageString0;
    
    // Game
    outFile << storageString0;
    
    for(auto* o: g->allObjects) {
        // cout << "Object Name: " << o->name << endl;
        storageString1 = "[[Object]] : [START1]\n";
        storageString1 += "[[ObjectName]] : [START2]" + o->name + "[END2]\n";
        
        storageString1 += "[[ObjectVisible]] : [START2]";
        storageString1.append(to_string((int) o->visible));
        storageString1 += "[END2]\n";
        
        storageString1 += "[[ObjectVisited]] : [START2]";
        storageString1.append(to_string((int) o->visited));
        storageString1 += "[END2]\n";
        
        storageString1 += "[[ObjectLocation]] : [START2]" + g->getObjectLocation(o->name) + "[END2]\n";
        storageString1 += "[END1]\n";
        
        // TEST
        // cout << storageString1;
        
        // Game
        outFile << storageString1;
    }
    
    storageString0 = "[END0]\n";
    // TEST
    // cout << storageString0;
    
    // Game
    outFile << storageString0;
    
    outFile.close();
    
    return true;
}

bool loadGame(Game *g, int numRooms) {
    
    ifstream inFile;
    inFile.open("savegame");
    
    string saveContents = "";
    char c;
    while(inFile.get(c))
        saveContents = saveContents + c;
    
    int minpos = 0;
    string currentString = fileParser(0, saveContents, "Current", &minpos);
    
    for(auto* n: g->allNodes) {
        if(n->name == currentString)
            g->current = n;
    }
    
    minpos = 0;
    string roomsString = fileParser(0, saveContents, "Nodes", &minpos);
    
    // TEST
    // cout << roomsString << endl;
    
    string roomContents = "";
    Node *n;
    minpos = 0;
    
    // TEST
    // cout << "Good so far" << endl;
    int temp = 0;
    for(int i = 1; i < numRooms + 1; i++) {
        roomContents = fileParser(1, roomsString, "Node", &minpos);
        
        // TEST
        // cout << roomContents << endl;
        
        temp = 0;
        string roomName = fileParser(2, roomContents, "NodeName", &temp);
        
        // TEST
        // cout << "Room Name: " << roomName << endl;
        
        // TEST
        // cout << "Still Good" << endl;
        
        for(auto* i: g->allNodes){
            if(i->name == roomName) {
                n = i;
            }
            // TEST
            // cout << "Scanning nodes" << endl;
        }
        assert(n != 0);
        
        temp = 0;
        bool roomVisited = atoi(fileParser(2, roomContents, "NodeVisited", &temp).c_str());
        n->visited = roomVisited;
        
        // TEST
        // cout  << "Room: " << roomName << ", Visited: " << roomVisited << endl;
        
        string edgeContents = "";
        int minpos2 = 0;
        do {
            edgeContents = fileParser(2, roomContents, "Edge", &minpos2);
            if(edgeContents != "") {
                temp = 0;
                string edgeName = fileParser(3, edgeContents, "EdgeName", &temp);
                Edge *e;
                for(auto* i: n->edges) {
                    if(i->name == edgeName)
                        e = i;
                }
                assert(e != 0);
                
                temp = 0;
                bool edgeVisible = atoi(fileParser(3, edgeContents, "EdgeVisible", &temp).c_str());
                temp = 0;
                bool edgePassable = atoi(fileParser(3, edgeContents, "EdgePassable", &temp).c_str());
                temp = 0;
                bool edgeVisited = atoi(fileParser(3, edgeContents, "EdgeVisited", &temp).c_str());
                
                // TEST
                // cout  << "Edge: " << edgeName << ", Visible: " << edgeVisible << ", Visited: " << edgeVisited << ", Passable: " << edgePassable << endl;
                
                e->visible = edgeVisible;
                e->passable = edgePassable;
                e->visited = edgeVisited;
            }
        }while(edgeContents != "");
        
        string featContents = "";
        minpos2 = 0;
        do {
            featContents = fileParser(2, roomContents, "Feature", &minpos2);
            if(featContents != "") {
                temp = 0;
                string featName = fileParser(3, featContents, "FeatureName", &temp);
                Feature *f;
                for(auto* i: n->features) {
                    if(i->name == featName)
                        f = i;
                }
                assert(f != 0);
                
                temp = 0;
                bool featVisible = atoi(fileParser(3, featContents, "FeatureVisible", &temp).c_str());
                temp = 0;
                bool featVisited = atoi(fileParser(3, featContents, "FeatureVisited", &temp).c_str());
                
                // TEST
                // cout  << "Feature: " << featName << ", Visible: " << featVisible << ", Visited: " << featVisited << endl;
                
                f->visible = featVisible;
                f->visited = featVisited;
            }
        }while(featContents != "");
    }
    
    minpos = 0;
    string objectsString = fileParser(0, saveContents, "Objects", &minpos);
    
    // TEST
    // cout << objectsString << endl;
    
    string objContents = "";
    minpos = 0;
    do {
        // TEST
        // cout << "Starting Object Read" << endl;
        objContents = fileParser(1, objectsString, "Object", &minpos);
        
        // TEST
        // cout << "Min Pos: " << minpos << endl;
        
        if(objContents != "") {
            temp = 0;
            string objName = fileParser(2, objContents,"ObjectName", &temp);
            
            Object *o;
            for(auto* i: g->allObjects){
                if(i->name == objName)
                    o = i;
            }
            assert(o != 0);
            
            temp = 0;
            bool objVisible = atoi(fileParser(2, objContents, "ObjectVisible", &temp).c_str());
            temp = 0;
            bool objVisited = atoi(fileParser(2, objContents, "ObjectVisited", &temp).c_str());
            temp = 0;
            string objLoc = fileParser(2, objContents,"ObjectLocation", &temp);
            
            // TEST
            // cout  << "Object: " << objName << ", Visible: " << objVisible << ", Visited: " << objVisited << ", Location: " << objLoc << endl;
            
            o->visible = objVisible;
            o->visited = objVisited;
            
            // TEST
            // cout << "Assigning Location" << endl;
            
            g->setObjectLocation(objName, objLoc);
        }
    }while(objContents != "");
    return true;
}
