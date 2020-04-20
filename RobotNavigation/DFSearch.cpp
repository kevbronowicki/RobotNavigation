#include "DFSearch.h"

using namespace std;

DFSearch::DFSearch()
{
}

Node* DFSearch::search(Map aMap, Node* aInitialNode)
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
        // override expand to reverse successor list, as successors
        // are pushed to front of frontier list
        list<Node*> lExpand = expand(lNode, aMap);
        lExpand.reverse();
        for (Node* child : lExpand)
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
                fFrontier.push_front(child);
                fNumOfNodes++;
            }
        }

    }
    // return empty node when fail to find solution
    return new Node();
}
