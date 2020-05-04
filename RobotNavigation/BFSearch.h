/* Breadth-first Search */
#pragma once
#include "SearchMethod.h"
#include "Node.h"
#include <list>
#include <map>
#include <unordered_map>

class BFSearch: public SearchMethod
{
public:
    BFSearch();

    Node* search(Map aMap, Node* aInitialNode) override;
};