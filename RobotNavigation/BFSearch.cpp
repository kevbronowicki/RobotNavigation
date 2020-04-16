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
        cout << "explored: ";
        for (Point p : fExplored)
        {
            cout << p.x << "," << p.y << " ";
        }
        cout << endl << "frontier: ";
        for (Node* n : fFrontier)
        {
            cout << n->getState().x << "," << n->getState().y << " ";
        }
        cout << endl;

        lNode = fFrontier.front();
        fFrontier.pop_front();
        fExplored.push_back(lNode->getState());
        bool lRepeated = false;
        for (Node* child : expand(lNode, aMap))
        {
            for (Point p : fExplored)
            {
                if (child->getState() == p)
                {
                    lRepeated = true;
                    break;
                }
                    
            }
            for (Node* n : fFrontier)
            {
                if (child->getState() == n->getState())
                {
                    lRepeated = true;
                    break;
                }
            }

            /*for (Node* n : child->getPredecessors())
            {
                if (child->getState() == n->getState())
                {
                    lCheck = true;
                    break;
                }
            }*/

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
