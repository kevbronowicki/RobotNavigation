#pragma once
#include <string>
#include "Map.h"
#include "Node.h"
#include <unordered_map>

class SearchMethod
{
protected:
    unsigned fNumOfNodes;
    std::unordered_map<std::string, Point> getActions(Map aMap, Point aPoint);
    std::list<Node*> expand(Node* aNode, Map aMap);
public:
    SearchMethod();
    
    virtual ~SearchMethod() {}
    
    virtual Node* search(Map aMap, Node* aInitialNode);

    unsigned getNumOfNodes() { return fNumOfNodes; }
};