#include "Map.h"

using namespace std;

#define CELL_SIZE 60
#define SPACER 3

Map::Map() {
    fWidth = 0;
    fHeight = 0;
    for (int i = 0; i < ARRAY_MAX_SIZE; i++) {
        for (int j = 0; j < ARRAY_MAX_SIZE; j++) {
            fMapArray[i][j] = Nil;
        }
    }
}

void Map::setStatus(int x, int y, Status aStatus) {
    fMapArray[x][y] = aStatus;
}

void Map::setStatus(Point aPoint, Status aStatus) {
    fMapArray[aPoint.x][aPoint.y] = aStatus;
}

Status Map::getStatus(Point aPoint) {
    if (aPoint.x <= fWidth && aPoint.y <= fHeight) {
        if (aPoint.x >= 0 && aPoint.y >= 0) {
            Status Result = fMapArray[aPoint.x][aPoint.y];
            return Result;
        }
    }
    return Nil;
}

void Map::draw(sf::RenderWindow& aWindow) {
    // flattened 2d vector of cells to be drawn
    // accessing flattened vector: lCells[3][5] --> lCells[(3 * fHeight) + 5]
    vector<sf::RectangleShape> lCells(fWidth * fHeight);

    // default cell for changing and adding to vector
    sf::RectangleShape lDefaultCell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::RectangleShape lCell;

    // loop through map array, setting position and colour of each cooresponding cell
    // and adding cell to vector
    for (int y = 0; y < fHeight; y++) {
        for (int x = 0; x < fWidth; x++) {
            lCell = lDefaultCell;
            lCell.setPosition(sf::Vector2f((SPACER + ((CELL_SIZE + SPACER) * x)), 
                (SPACER + ((CELL_SIZE + SPACER) * y)) ));

            if (fMapArray[x][y] == Wall) {
                lCell.setFillColor(sf::Color(128, 128, 128));
            }
            else if (fMapArray[x][y] == Goal) {
                lCell.setFillColor(sf::Color::Green);
            }
            else {
                lCell.setFillColor(sf::Color::White);
            }

            lCells[(x * fHeight) + y] = lCell;
        }
    }

    // determine size of windows to be create
    sf::Vector2u fSize;
    fSize.x = SPACER + fWidth * (CELL_SIZE + SPACER);
    fSize.y = SPACER + fHeight * (CELL_SIZE + SPACER);

    // set window to calculated size if not already that size
    if (aWindow.getSize() != fSize) {
        aWindow.create(sf::VideoMode(fSize.x, fSize.y), "Robot Navigation");
    }

    // draw each cell in cells vector
    for (auto& lCell : lCells) {
        aWindow.draw(lCell);
    }
}

std::ostream& operator<<(std::ostream& aOstream, const Map& aMap) {
    for (int y = 0; y < aMap.fHeight; y++) {
        for (int x = 0; x < aMap.fWidth; x++) {
            aOstream << aMap.fMapArray[x][y] << " ";
        }
        cout << endl;
    }
    return aOstream;
}
