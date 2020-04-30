/* Iterative Deepening A* Search */
#include "IDASearch.h"

using namespace std;

IDASearch::IDASearch()
{
}

Node* IDASearch::search(Map aMap, Node* aInitialNode)
{
    Node* lNode;
    if (aMap.getStatus(aInitialNode->getState()) == Goal)
        return aInitialNode;
    
    fFrontier.push_back(aInitialNode);
    fNumOfNodes++;
    int lLastThreshold = 0;
    int lNextThreshold = 0;
    // increase threshold, repeating a * search on each level of 
    // threshold until a solution is found.
    for (int lThreshold = 0; ; lThreshold = lNextThreshold)
    {
        fFrontier.push_back(aInitialNode);
        while (!fFrontier.empty())
        {
            lNode = fFrontier.front();
            fFrontier.pop_front();
            fExplored.push_back(lNode->getState());
            bool lRepeated = false;
            for (Node* child : expand(lNode, aMap, true))
            {
                // f(n) = g(n) + h(n)
                int lTotalCost = child->getCost() + child->getDistance();
 
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
                    // only add to frontier if within threshold
                    if (lTotalCost <= lThreshold)
                    {
                        fFrontier.push_front(child);
                        fNumOfNodes++;
                    }
                    else
                    {
                        delete child;
                    }
                }
                // set the next thresold of the f(n) of the current child
                // is the lowest so far but still greater than the current threshold
                if (lNextThreshold < lTotalCost && lTotalCost > lThreshold)
                {
                    lNextThreshold = lTotalCost;
                    //cout << "new threshold:" << lNextThreshold << endl;
                }
            }
            fFrontier.sort([](Node* a, Node* b) { return a->getDistance() + a->getCost() < b->getDistance() + b->getCost(); });
        }
        // increase threshold
        //cout << "Last threshold: " << lLastThreshold << endl;
        //cout << "Next threshold: " << lNextThreshold << endl;

        // if the threshold does not increase
        // then the whole map has been explored and there is no solution
        if (lLastThreshold != lNextThreshold)
        {
            lLastThreshold = lNextThreshold;
        }
        else
        {
            break;
        }
    }
    // return empty node when fail to find solution
    return new Node();
}
