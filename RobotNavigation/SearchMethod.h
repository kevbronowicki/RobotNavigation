/* SearchMethod */
// Abstract class for code reuse between tree search methods
#pragma once
#include <string>
#include "Map.h"
#include "Node.h"
#include <list>

class SearchMethod
{
protected:
    unsigned fNumOfNodes; // total number of nodes expanded
    std::list<Node*> fFrontier;
    std::list<Point> fExplored;

    // returns a list of possible actions paired with states for passed state
    std::list<std::pair<std::string, Point>> getActions(Map aMap, Point aState);
    // calculates heuristic of passed state using manhattan distance
    unsigned heuristic(Point aState, Map aMap);
    // returns a list of successors for passed node, bool toggle
    // for adding heuristic to nodes if informed search
    std::list<Node*> expand(Node* aNode, Map aMap, bool aInformed = false);
    
    SearchMethod();
    virtual ~SearchMethod() {}
public:
    // implementation of search algorithm, to be overwritten by child classes
    virtual Node* search(Map aMap, Node* aInitialNode);

    unsigned getNumOfNodes() { return fNumOfNodes; }
    // prints frontier and explored lists
    // for debugging
    void printDetails(std::list<Node*> aFrontier, std::list<Point> aExplored);
};