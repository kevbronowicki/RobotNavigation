#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <list>

class DFSearch : public SearchMethod
{
private:
    std::list<Node*> fFrontier; // implement stack
    std::list<Point> fExplored;

public:
    DFSearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};