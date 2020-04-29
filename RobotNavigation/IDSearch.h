#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <list>

class IDSearch : public SearchMethod
{
private:
    std::list<Node*> fFrontier;
    std::list<Point> fExplored;

public:
    IDSearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};