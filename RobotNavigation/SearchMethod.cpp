#include "SearchMethod.h"
#include <iostream>

using namespace std;

list<pair<string, Point>> SearchMethod::getActions(Map aMap, Point aPoint)
{
    Point lPoint;
    list<pair<string, Point>> lActions;

    // check up
    lPoint.x = aPoint.x;
    lPoint.y = aPoint.y - 1;
    if (!(aMap.getStatus(lPoint) == Nil || aMap.getStatus(lPoint) == Wall))
    {
        lActions.push_back(make_pair("up", lPoint));
    }
    // check left
    lPoint.x = aPoint.x - 1;
    lPoint.y = aPoint.y;
    if (!(aMap.getStatus(lPoint) == Nil || aMap.getStatus(lPoint) == Wall))
    {
        lActions.push_back(make_pair("left", lPoint));
    }
    // check down
    lPoint.x = aPoint.x;
    lPoint.y = aPoint.y + 1;
    if (!(aMap.getStatus(lPoint) == Nil || aMap.getStatus(lPoint) == Wall))
    {
        lActions.push_back(make_pair("down", lPoint));
    }
    // check right
    lPoint.x = aPoint.x + 1;
    lPoint.y = aPoint.y;
    if (!(aMap.getStatus(lPoint) == Nil || aMap.getStatus(lPoint) == Wall))
    {
        lActions.push_back(make_pair("right", lPoint));
    }

    for (auto const& x : lActions)
    {
        cout << x.first << " ";
    }
    cout << endl;

    return lActions;
}

list<Node*> SearchMethod::expand(Node* aNode, Map aMap)
{
    list<Node*> lSuccessors;
    list<pair<string, Point>> lActions = getActions(aMap, aNode->getState());

    for (auto const& p : lActions)
    {
        lSuccessors.push_back(new Node(p.second, aNode, p.first));
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
