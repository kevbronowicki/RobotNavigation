#pragma once
#include "Map.h"
#include "SearchMethod.h"
#include "Node.h"
#include "BFSearch.h"
#include "DFSearch.h"
#include <list>

class Robot
{
private:
    Node* fInitialNode;
    SearchMethod* fSearchMethod;
    std::string fMethod;
    Node* fSolution;
public:
    Robot(Point aInitialPoint, std::string aMethod);
    
    void search(Map aMap);
    void draw();
    std::string getPath();
    std::string getMethod();
    unsigned getNumOfNodes();
    bool goalFound();
};