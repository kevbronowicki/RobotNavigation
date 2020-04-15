#include "BFSearch.h"

using namespace std;

list<Node*> BFSearch::expand(Node* aNode, Map aMap)
{
    list<Node*> lSuccessors;
    unordered_map<string, Point> lActions = getActions(aMap, aNode->getState());

    for (auto const& p : lActions)
    {
        lSuccessors.push_back(new Node(p.second, aNode, p.first));
    }

    return lSuccessors;
}

unordered_map<string, Point> BFSearch::getActions(Map aMap, Point aPoint)
{
    Point lPoint;
    std::unordered_map<string, Point> lActions;

    // check up
    lPoint.x = aPoint.x;
    lPoint.y = aPoint.y - 1;
    if (!(aMap.getStatus(lPoint) == Nil || aMap.getStatus(lPoint) == Wall))
    {
        lActions.insert({"up", lPoint});
    }
    // check left
    lPoint.x = aPoint.x - 1;
    lPoint.y = aPoint.y;
    if (!(aMap.getStatus(lPoint) == Nil || aMap.getStatus(lPoint) == Wall))
    {
        lActions.insert({ "left", lPoint });
    }
    // check down
    lPoint.x = aPoint.x;
    lPoint.y = aPoint.y + 1;
    if (!(aMap.getStatus(lPoint) == Nil || aMap.getStatus(lPoint) == Wall))
    {
        lActions.insert({ "down", lPoint });
    }
    // check right
    lPoint.x = aPoint.x + 1;
    lPoint.y = aPoint.y;
    if (!(aMap.getStatus(lPoint) == Nil || aMap.getStatus(lPoint) == Wall))
    {
        lActions.insert({ "right", lPoint });
    }
    return lActions;
}

BFSearch::BFSearch()
{
    fNumOfNodes = 0;
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
        bool lCheck = false;
        for (Node* child : expand(lNode, aMap))
        {
            for (Point p : fExplored)
            {
                if (child->getState() == p)
                {
                    lCheck = true;
                    break;
                }
                    
            }
            for (Node* n : fFrontier)
            {
                if (child->getState() == n->getState())
                {
                    lCheck = true;
                    break;
                }
            }
            if (aMap.getStatus(child->getState()) == Goal)
            {
                return child;
            }
                
            if (lCheck)
            {
                lCheck = false;
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
