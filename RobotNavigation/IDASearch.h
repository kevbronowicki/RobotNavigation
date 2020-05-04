/* Iterative-deepening A* Search */
#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <list>

class IDASearch : public SearchMethod
{
public:
    IDASearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};