#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <queue>
#include <list>

class DFSearch : public SearchMethod
{
private:
    std::deque<Node*> fFrontier; // implement stack
    std::list<Point> fExplored;

public:
    DFSearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};