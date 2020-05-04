#include "SearchMethod.h"
#include <iostream>
#include <cmath>        // for std::abs()
#include <vector>

using namespace std;

list<pair<string, Point>> SearchMethod::getActions(Map aMap, Point aState)
{
    Point lPoint;
    list<pair<string, Point>> lActions;

    // check up
    lPoint.x = aState.x;
    lPoint.y = aState.y - 1;
    if (!(aMap.getStatus(lPoint) == Nil || aMap.getStatus(lPoint) == Wall))
    {
        lActions.push_back(make_pair("up", lPoint));
    }
    // check left
    lPoint.x = aState.x - 1;
    lPoint.y = aState.y;
    if (!(aMap.getStatus(lPoint) == Nil || aMap.getStatus(lPoint) == Wall))
    {
        lActions.push_back(make_pair("left", lPoint));
    }
    // check down
    lPoint.x = aState.x;
    lPoint.y = aState.y + 1;
    if (!(aMap.getStatus(lPoint) == Nil || aMap.getStatus(lPoint) == Wall))
    {
        lActions.push_back(make_pair("down", lPoint));
    }
    // check right
    lPoint.x = aState.x + 1;
    lPoint.y = aState.y;
    if (!(aMap.getStatus(lPoint) == Nil || aMap.getStatus(lPoint) == Wall))
    {
        lActions.push_back(make_pair("right", lPoint));
    }

    return lActions;
}

unsigned SearchMethod::heuristic(Point aState, Map aMap)
{
    vector<unsigned> lDistances;
    for (auto const& g : aMap.getGoals())
    {
        // calculate manhattan distance to a goal
        lDistances.push_back(abs((float)g.x - (float)aState.x) +
            abs((float)g.y - (float)aState.y));
    }
    sort(lDistances.begin(), lDistances.end());
    // return shortest distance to a goal
    return lDistances.front();
}

list<Node*> SearchMethod::expand(Node* aNode, Map aMap, bool aInformed)
{
    list<Node*> lSuccessors;
    list<pair<string, Point>> lActions = getActions(aMap, aNode->getState());

    if (aInformed)
    {
        for (auto const& p : lActions)
        {
            lSuccessors.push_back(new Node(p.second, aNode, p.first, 
                aNode->getCost()+1, heuristic(aNode->getState(), aMap)));
        }
    }
    else
    {
        for (auto const& p : lActions)
        {
            lSuccessors.push_back(new Node(p.second, aNode, p.first, aNode->getCost()+1));
        }
    }
    return lSuccessors;
}

SearchMethod::SearchMethod()
{
    fNumOfNodes = 0;
}

Node* SearchMethod::search(Map aMap, Node* aInitialNode)
{
    std::cout << "test1";
    return new Node();
}

void SearchMethod::printDetails(list<Node*> aFrontier, list<Point> aExplored)
{
    cout << "Explored: ";
    for (Point p : aExplored)
    {
        cout << p.x << "," << p.y << " ";
    }
    cout << endl << "Frontier: ";
    for (Node* n : aFrontier)
    {
        cout << n->getState().x << "," << n->getState().y << " ";
    }
    cout << endl;
}
