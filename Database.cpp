#include <fstream>
#include <assert.h>
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
                
                // Print feature target
                temp2 = 0;
                featQuery = fileParser(2, featI, "FeatureTargetType", &temp2);
                // f->targetType = featQuery;
                if (featQuery == "Feature") {
                    temp2 = 0;
                    featQuery = fileParser(2, featI, "FeatureTargetFeature", &temp2);
                    // cout << "Feature Target: " << featQuery << endl;
                    f->initialFeatureName = featQuery;
                } else if (featQuery == "Object") {
                    temp2 = 0;
                    featQuery = fileParser(2, featI, "FeatureTargetObject", &temp2);
                    // cout << "Feature Target: " << featQuery << endl;
                    f->initialObjectName = featQuery;
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
                
                // Print object target
                temp2 = 0;
                objQuery = fileParser(2, objI, "ObjectTargetType", &temp2);
                // a->targetType = objQuery;
                if(objQuery == "Edge") {
                    temp2 = 0;
                    objQuery = fileParser(2, objI, "ObjectTargetRoom", &temp2);
                    temp2 = 0;
                    string objQuery2 = fileParser(2, objI, "ObjectTargetEdge", &temp2);
                    // cout << "Object target: Room = " << objQuery << ", Edge = " << objQuery2 << endl;
                    a->initialEdgeName = objQuery2;
                    
                }
                
                // Get object verbs
                temp2 = 0;
                objQuery = fileParser(2, objI, "ObjectVerbs", &temp2);
                
                int counter2 = 0;
                int minp2 = 0;
                string objVerb;
                string verbName, verbResponse;
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
                        a->setVerb(verbName,verbResponse);
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