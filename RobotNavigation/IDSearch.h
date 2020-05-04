/* Iterative-deepening Depth-first Search */
#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <list>

class IDSearch : public SearchMethod
{
public:
    IDSearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};