#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Map.h"

using namespace std;

Map readMapData(string aFileName, Point& aPoint) {
    ifstream lInput(aFileName);
    Map lMap;
    char lChar; // dummy characters (seperators)
    int lHeight, lWidth;
    Point lPoint;

    if (!lInput.good()) {
        cerr << "Cannot open input file: " << aFileName << endl;
    }
    else {
        lInput >> lChar >> lHeight >> lChar >> lWidth >> lChar;
        lMap.setHeight(lHeight);
        lMap.setWidth(lWidth);
        lInput >> lChar >> aPoint.x >> lChar >> aPoint.y >> lChar;
        for (lPoint.x = 0; lPoint.x < lWidth; lPoint.x++) {
            for (lPoint.y = 0; lPoint.y < lHeight; lPoint.y++) {
                lMap.setStatus(lPoint, Floor);
            }
        }
        
        string lReadLine;
        lInput.ignore(); // prevents getline reading newline and skipping line
        getline(lInput, lReadLine);
        istringstream lStringStream(lReadLine); // create string stream from read line for formatting
        string lPart; // store current part of stream
        while(lStringStream >> lPart) {
            if (lPart != "|") {
                istringstream lStringPart(lPart); // convert string to stream for further formatting
                lStringPart >> lChar >> lPoint.x >> lChar >> lPoint.y >> lChar; // seperate char from ints
                lMap.setStatus(lPoint, Goal);
            }
        }
        
        while (lInput >> lChar >> lPoint.x >> lChar >> lPoint.y >> lChar >> lWidth >> lChar >> lHeight >> lChar) {
            for (int x = lPoint.x; x < (lPoint.x + lWidth); x++) {
                for (int y = lPoint.y; y < (lPoint.y + lHeight); y++) {
                    lMap.setStatus({ x, y }, Wall);
                    //cout << x << " " << y << endl;
                }
            }
        }

        lInput.close();
    }

    return lMap;
}


int main(int argc, char* argv[]) {
    string a;
    Point lInitialState;
    Map lMapData;

    lMapData = readMapData("RobotNav-test.txt", lInitialState);

    cout << lMapData;

    return 0;
}
