#include "Node.h"
using namespace std;

Node::Node()
{
    fState = { 0, 0 };
    fParent = NULL;
    fAction = "No solution found";
    fCost = 0;
    fDistance = 0;
}

Node::Node(Point aState, Node* aParent, string aAction, int aCost, unsigned aDistance)
{
    fState = aState;
    fParent = aParent;
    fAction = aAction;
    fCost = aCost;
    fDistance = aDistance;
}
