#pragma once
#include <string>
#include "Map.h"
#include "Node.h"
#include <list>

class SearchMethod
{
protected:
    unsigned fNumOfNodes;
    std::list<std::pair<std::string, Point>> getActions(Map aMap, Point aPoint);
    unsigned heuristic(Point aState, Map aMap);
    std::list<Node*> expand(Node* aNode, Map aMap, bool aInformed = false);
public:
    SearchMethod();
    
    virtual ~SearchMethod() {}
    
    virtual Node* search(Map aMap, Node* aInitialNode);

    unsigned getNumOfNodes() { return fNumOfNodes; }
    // prints frontier and explored lists
    // for debugging
    void printDetails(std::list<Node*> aFrontier, std::list<Point> aExplored);
};