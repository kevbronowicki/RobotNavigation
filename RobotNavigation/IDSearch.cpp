/* Iterative Deepening Depth First Search */

#include "IDSearch.h"

using namespace std;

IDSearch::IDSearch()
{
}

Node* IDSearch::search(Map aMap, Node* aInitialNode)
{
    Node* lNode;
    if (aMap.getStatus(aInitialNode->getState()) == Goal)
        return aInitialNode;
    fNumOfNodes++;

    list<Point> lLastExplored;
    list<Point> lNewExplored;
    
    // increment max depth, repeating depth first search till each level of 
    // depth until a solution is found.
    for(int lMaxDepth = 0;;lMaxDepth++)
    {
        fFrontier.push_back(aInitialNode);
        while (!fFrontier.empty())
        {
            //printDetails(fFrontier, fExplored);
            lNode = fFrontier.front();
            fFrontier.pop_front();
            fExplored.push_back(lNode->getState());
            lNewExplored.push_back(lNode->getState());
            bool lRepeated = false;
            // reverse successor list, as successors
            // are pushed to front of frontier list
            list<Node*> lSuccessors = expand(lNode, aMap);
            lSuccessors.reverse();
            for (Node* child : lSuccessors)
            {
                int lDepth = 0;
                for (Node* n : child->getPredecessors())
                {
                    lDepth++;
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
                    // only add to frontier if within max depth
                    if (lDepth <= lMaxDepth)
                    {
                        fFrontier.push_front(child);
                        fNumOfNodes++;
                    }
                    else
                    {
                        delete child;
                    }
                }
            }
        }

        // if the next depth explores the exact same nodes as the previous depth,
        // then the whole map has been explored and there is no solution
        if (lLastExplored == lNewExplored)
        {
            break;
        }
        else
        {
            lLastExplored = lNewExplored;
            lNewExplored.clear();
        }
    }
    // return empty node when fail to find solution
    return new Node();
}
