#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <list>

class ASearch : public SearchMethod
{
private:
    std::list<Node*> fFrontier;
    std::list<Point> fExplored;
public:
    ASearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};