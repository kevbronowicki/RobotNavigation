#include "Robot.h"
#include "Node.h"
using namespace std;

constexpr unsigned c_cellSize = 40;
constexpr unsigned c_spacer = 2;

Robot::Robot(Point aInitialPoint, string aFileName, string aMethod)
{
    fInitialNode = new Node(aInitialPoint, NULL, "Initial");
    if (aMethod == "dfs")
    {
        fSearchMethod = new DFSearch();
    }
    else if (aMethod == "bfs")
    {
        fSearchMethod = new BFSearch();
    }
    else if (aMethod == "gbfs")
    {
        fSearchMethod = new GBFSearch();
    }
    else if (aMethod == "as")
    {
        fSearchMethod = new ASearch();
    }
    else if (aMethod == "ids")
    {
        fSearchMethod = new IDSearch();
    }
    else if (aMethod == "idas")
    {
        fSearchMethod = new IDASearch();
    }
    else
    {
        throw std::runtime_error("Not a valid search method.\n");
    }
    fMethod = aMethod;
    fFileName = aFileName;
    fSolution = nullptr;
}

void Robot::search(Map aMap)
{
    fSolution = fSearchMethod->search(aMap, fInitialNode);
}

void Robot::draw(sf::RenderWindow& aWindow)
{
    // flattened 2d vector of path to be drawn
    list<sf::RectangleShape> lPath;
    // default cell for changing and adding to vector
    sf::RectangleShape lDefaultCell(sf::Vector2f(c_cellSize, c_cellSize));
    sf::RectangleShape lCell;
    // get predessors of solution node and add them to path to draw
    for (Node* n : fSolution->getPredecessors())
    {
        unsigned x = n->getState().x;
        unsigned y = n->getState().y;
        lCell = lDefaultCell;
        lCell.setPosition(sf::Vector2f((c_spacer + ((c_cellSize + c_spacer) * x)),
            (c_spacer + ((c_cellSize + c_spacer) * y))));
        if (n->getParent() != NULL)
        {
            // colour path blue
            lCell.setFillColor(sf::Color::Blue);
        }
        else
        {
            // colour intial cell red
            lCell.setFillColor(sf::Color::Red);
        }
        lPath.push_back(lCell);
    }

    // draw each cell in cells vector
    for (auto& lCell : lPath)
    {
        aWindow.draw(lCell);
    }
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

unsigned Robot::getNumOfNodes()
{
    return fSearchMethod->getNumOfNodes();
}

bool Robot::goalFound()
{
    if (fSolution->getAction() != "No solution found.")
    {
        return true;
    }
    return false;
}

ostream& operator<<(ostream& aOstream, Robot& aRobot)
{
    aOstream << aRobot.fFileName << " " << aRobot.fMethod << " " << aRobot.getNumOfNodes() << endl;
    if (!aRobot.goalFound())
    {
        aOstream << aRobot.fSolution->getAction();
    }
    else
    {
        string lPath = aRobot.fSolution->getAction() + "; ";
        for (Node* n : aRobot.fSolution->getPredecessors())
        {
            if (n->getParent() != NULL)
            {
                lPath = n->getAction() + "; " + lPath;
            }
        }
        aOstream << lPath;
    }
    return aOstream;
}
