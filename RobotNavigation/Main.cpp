#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Robot.h"

using namespace std;

// Loads map data from text file of passed name
// Sets passed initial point as found in file and returns map data
Map readMapData(string aFileName, Point& aPoint);

// arv[1] = file name, arv[2] = search method
int main(int argc, char* argv[]) 
{
    if (argc < 3) 
    {
        cerr << "Argumens missing" << endl;
        cerr << "Call program using the following format: search <filename> <method> [gui]" 
             << endl;
        return 1;               // program failed
    }
    bool lDrawGUI = false;
    // check to draw gui
    if (argc == 4)
    {
        string temp = argv[3];
        if (temp == "gui")
        {
            lDrawGUI = true;
        }
    }
    
    Point lInitialState;
    Map lMap = readMapData(argv[1], lInitialState);

    try
    {
        Robot lRobot(lInitialState, argv[1], argv[2]);
        lRobot.search(lMap);
        // print solution
        cout << lRobot << endl;

        // draw gui if requested and goal found
        if (lRobot.goalFound() && lDrawGUI)
        {
            sf::RenderWindow window(sf::VideoMode(100, 100), "Robot Navigation");
            while (window.isOpen())
            {
                // check for "close request" of window and close if requested
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                // clear the window with black color
                window.clear(sf::Color::Black);

                // draw objects
                lMap.draw(window);
                lRobot.draw(window);
                // end the current frame
                window.display();
            }
        }
    }
    catch (exception e)
    {
        cerr << e.what() << endl;
    }
    
    return 0;
}

Map readMapData(string aFileName, Point& aPoint) 
{
    ifstream lInput(aFileName);
    Map lMap;
    char lChar; // dummy characters (seperators)
    unsigned lHeight, lWidth;
    Point lPoint;

    if (!lInput.good()) 
    {
        cerr << "Cannot open input file: " << aFileName << endl;
        exit(2); // program failed (input)
    }
    else 
    {
        lInput >> lChar >> lHeight >> lChar >> lWidth >> lChar;
        lMap.setSize(lWidth, lHeight);
        lInput >> lChar >> aPoint.x >> lChar >> aPoint.y >> lChar;
        for (lPoint.x = 0; lPoint.x < lWidth; lPoint.x++) 
        {
            for (lPoint.y = 0; lPoint.y < lHeight; lPoint.y++) 
            {
                lMap.setStatus(lPoint, Floor);
            }
        }

        string lReadLine;
        lInput.ignore(); // prevents getline reading newline and skipping line
        getline(lInput, lReadLine);
        istringstream lStringStream(lReadLine); // create string stream from read line for formatting
        string lPart; // store current part of stream
        // loop though groupings "(7,0)", "|" and "(10,3)"
        while (lStringStream >> lPart) 
        {
            if (lPart != "|")
            {
                istringstream lStringPart(lPart); // convert string to stream for further formatting
                lStringPart >> lChar >> lPoint.x >> lChar >> lPoint.y >> lChar; // seperate char from ints
                lMap.setStatus(lPoint, Goal);
            }
        }

        while (lInput >> lChar >> lPoint.x >> lChar >> lPoint.y >> lChar >> lWidth >> lChar >> lHeight >> lChar) 
        {
            for (unsigned x = lPoint.x; x < (lPoint.x + lWidth); x++) 
            {
                for (unsigned y = lPoint.y; y < (lPoint.y + lHeight); y++) 
                {
                    lMap.setStatus({ x, y }, Wall);
                }
            }
        }

        lInput.close();
    }

    return lMap;
}
