/* Depth-first Search */
#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <list>

class DFSearch : public SearchMethod
{
public:
    DFSearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};