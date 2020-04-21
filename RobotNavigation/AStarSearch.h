#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <list>

class AStarSearch : public SearchMethod
{
private:
    std::list<Node*> fFrontier;
    std::list<Point> fExplored;
public:
    AStarSearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};