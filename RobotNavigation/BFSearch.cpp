#include "BFSearch.h"

using namespace std;

BFSearch::BFSearch()
{
}

Node* BFSearch::search(Map aMap, Node* aInitialNode)
{
    Node* lNode;
    if (aMap.getStatus(aInitialNode->getState()) == Goal)
        return aInitialNode;

    fFrontier.push_back(aInitialNode);
    fNumOfNodes++;
    while (!fFrontier.empty())
    {
        lNode = fFrontier.front();
        fFrontier.pop_front();
        fExplored.push_back(lNode->getState());
        bool lRepeated = false;
        for (Node* child : expand(lNode, aMap))
        {
            for (Node* n : child->getPredecessors())
            {
                if (child->getState() == n->getState())
                {
                    lRepeated = true;
                    break;
                }
            }

            // if child node has goal state return child
            if (aMap.getStatus(child->getState()) == Goal)
            {
                return child;
            }
                
            if (lRepeated)
            {
                lRepeated = false;
                delete child;
            }
            else
            {
                fFrontier.push_back(child);
                fNumOfNodes++;
            }      
        }

    }
    // return empty node when fail to find solution
    return new Node();
}
