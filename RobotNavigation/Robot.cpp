#include "Robot.h"
#include "Node.h"
using namespace std;

constexpr unsigned c_cellSize = 60;
constexpr unsigned c_spacer = 3;

Robot::Robot(Point aInitialPoint, string aMethod)
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
    else
    {
        throw std::runtime_error("Not a valid search method.\n");
    }
    
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
