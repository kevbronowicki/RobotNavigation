#pragma once
#include <string>
#include "Map.h"
#include "Node.h"

class SearchMethod
{
protected:
    unsigned fNumOfNodes;
public:
    SearchMethod();
    
    virtual ~SearchMethod() {}
    
    virtual Node* search(Map aMap, Node* aInitialNode);

    unsigned getNumOfNodes() { return fNumOfNodes; }
};