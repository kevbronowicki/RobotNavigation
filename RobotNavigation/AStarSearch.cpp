#include "AStarSearch.h"

using namespace std;

AStarSearch::AStarSearch()
{
}

Node* AStarSearch::search(Map aMap, Node* aInitialNode)
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
            //cout << "(" << n->getCost() << " " << n->getDistance() << " " << n->getAction() << ")";
        }
        cout << endl;

        lNode = fFrontier.front();
        fFrontier.pop_front();
        fExplored.push_back(lNode->getState());
        bool lRepeated = false;
        for (Node* child : expand(lNode, aMap, true))
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
        fFrontier.sort([](Node* a, Node* b) { return a->getDistance() + a->getCost() < b->getDistance() + b->getCost(); });
    }
    // return empty node when fail to find solution
    return new Node();
}
