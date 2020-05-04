/* Greedy Best-first Search*/
#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <list>

class GBFSearch : public SearchMethod
{
public:
    GBFSearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};