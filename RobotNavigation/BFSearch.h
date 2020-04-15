#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <queue>
#include <list>
#include <map>
#include <unordered_map>

class BFSearch: public SearchMethod
{
private:
    std::deque<Node*> fFrontier;
    std::list<Point> fExplored;
    std::list<Node*> expand(Node* aNode, Map aMap);
    std::unordered_map<std::string, Point> getActions(Map aMap, Point aPoint);
public:
    BFSearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};