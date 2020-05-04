#pragma once
#include "Map.h"
#include "SearchMethod.h"
#include <SFML/Graphics.hpp>
#include "Node.h"
#include "BFSearch.h"
#include "DFSearch.h"
#include "GBFSearch.h"
#include "ASearch.h"
#include "IDSearch.h"
#include "IDASearch.h"
#include <list>

class Robot
{
private:
    Node* fInitialNode;
    Node* fSolution;
    SearchMethod* fSearchMethod;
    std::string fMethod;
    std::string fFileName;

public:
    Robot(Point aInitialPoint, std::string aFileName, std::string aMethod);
    
    void search(Map aMap);
    void draw(sf::RenderWindow& aWindow);
    std::string getPath();
    int getCost();
    unsigned getNumOfNodes();
    bool goalFound();

    // used to send output solution of robot to cout
    friend std::ostream& operator<<(std::ostream& aOstream, Robot& aRobot);
};