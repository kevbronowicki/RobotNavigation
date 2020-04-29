#pragma once
#include "Map.h"
#include "SearchMethod.h"
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "BFSearch.h"
#include "DFSearch.h"
#include "GBFSearch.h"
#include "AStarSearch.h"
#include <list>

class Robot
{
private:
    Node* fInitialNode;
    SearchMethod* fSearchMethod;
    std::string fMethod;
    std::string fFileName;
    Node* fSolution;
public:
    Robot(Point aInitialPoint, std::string aFileName, std::string aMethod);
    
    void search(Map aMap);
    void draw(sf::RenderWindow& aWindow);
    std::string getPath();
    unsigned getNumOfNodes();
    bool goalFound();

    friend std::ostream& operator<<(std::ostream& aOstream, Robot& aRobot);
};