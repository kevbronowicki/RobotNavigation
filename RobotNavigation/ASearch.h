/* A* Search */
#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <list>

class ASearch : public SearchMethod
{
public:
    ASearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};