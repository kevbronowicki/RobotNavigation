#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <list>

class GBFSearch : public SearchMethod
{
private:
    std::list<Node*> fFrontier;
    std::list<Point> fExplored;
public:
    GBFSearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};