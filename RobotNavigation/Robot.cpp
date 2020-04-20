#include "Robot.h"
#include "Node.h"
using namespace std;

Robot::Robot(Point aInitialPoint, string aMethod)
{
    fInitialNode = new Node(aInitialPoint, NULL, "none");
    if (aMethod == "dfs")
    {
        fSearchMethod = new DFSearch();
    }
    else if (aMethod == "bfs")
    {
        fSearchMethod = new BFSearch();
    }
    else
    {
        throw std::runtime_error("Not a valid search method.\n");
    }
    
}

void Robot::search(Map aMap)
{
    fSolution = fSearchMethod->search(aMap, fInitialNode);
}

void Robot::draw()
{
}

string Robot::getPath()
{
    string lResult = "";
    if (!goalFound())
    {
        lResult = "No solution found";
    }
    else
    {
        cout << "Number of nodes: " << fSearchMethod->getNumOfNodes() << endl;
        lResult = fSolution->getAction() + "; ";
        for (Node* n : fSolution->getPredecessors())
        {
            if (n->getParent() != NULL)
            {
                lResult = n->getAction() + "; " + lResult;
            }
        }
        
    }
    return lResult;
}

string Robot::getMethod()
{
    return string();
}

unsigned Robot::getNumOfNodes()
{
    return fSearchMethod->getNumOfNodes();
}

bool Robot::goalFound()
{
    if (fSolution->getAction() != "No solution found")
    {
        return true;
    }
    return false;
}
