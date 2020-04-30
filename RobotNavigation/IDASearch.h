/* Iterative Deepening A* Search */
#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <list>

class IDASearch : public SearchMethod
{
private:
    std::list<Node*> fFrontier;
    std::list<Point> fExplored;
public:
    IDASearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};