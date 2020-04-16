#include "SearchMethod.h"
#include <iostream>

using namespace std;

std::unordered_map<std::string, Point> SearchMethod::getActions(Map aMap, Point aPoint)
{
    Point lPoint;
    std::unordered_map<string, Point> lActions;

    // check up
    lPoint.x = aPoint.x;
    lPoint.y = aPoint.y - 1;
    if (!(aMap.getStatus(lPoint) == Nil || aMap.getStatus(lPoint) == Wall))
    {
        lActions.insert({ "up", lPoint });
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

std::list<Node*> SearchMethod::expand(Node* aNode, Map aMap)
{
    list<Node*> lSuccessors;
    unordered_map<string, Point> lActions = getActions(aMap, aNode->getState());

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
