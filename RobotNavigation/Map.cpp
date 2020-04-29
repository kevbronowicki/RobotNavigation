#include "Map.h"

using namespace std;

constexpr unsigned c_cellSize = 40;
constexpr unsigned c_spacer = 2;

Map::Map() 
{
    fWidth = 0;
    fHeight = 0;
}

void Map::setSize(unsigned aWidth, unsigned aHeight) 
{
    fWidth = aWidth;
    fHeight = aHeight;
    fMapArray.resize(fWidth * fHeight, Floor);
}

void Map::setStatus(unsigned aX, unsigned aY, Status aStatus) 
{
    if (aX < fWidth && aY < fHeight) 
    {
        fMapArray[aX * fHeight + aY] = aStatus;
    }
    if (aStatus == Goal)
    {
        fGoals.push_back({ aX, aY });
    }
}

void Map::setStatus(Point aPoint, Status aStatus) 
{
    setStatus(aPoint.x, aPoint.y, aStatus);
}

Status Map::getStatus(unsigned aX, unsigned aY) 
{
    if (aX < fWidth && aY < fHeight) 
    {
        return fMapArray[aX * fHeight + aY];
    }
    else
    {
        return Nil;
    }
}

Status Map::getStatus(Point aPoint)
{
    return getStatus(aPoint.x, aPoint.y);
}

void Map::draw(sf::RenderWindow& aWindow) 
{
    // flattened 2d vector of cells to be drawn
    vector<sf::RectangleShape> lCells(fWidth * fHeight);

    // default cell for changing and adding to vector
    sf::RectangleShape lDefaultCell(sf::Vector2f(c_cellSize, c_cellSize));
    sf::RectangleShape lCell;

    // loop through map array, setting position and colour of each cooresponding cell
    // and adding cell to vector
    for (unsigned y = 0; y < fHeight; y++) 
    {
        for (unsigned x = 0; x < fWidth; x++) 
        {
            lCell = lDefaultCell;
            lCell.setPosition(sf::Vector2f((c_spacer + ((c_cellSize + c_spacer) * x)), 
                (c_spacer + ((c_cellSize + c_spacer) * y)) ));

            if (getStatus(x, y) == Wall) 
            {
                lCell.setFillColor(sf::Color(128, 128, 128));
            }
            else if (getStatus(x, y) == Goal) 
            {
                lCell.setFillColor(sf::Color::Green);
            }
            else 
            {
                lCell.setFillColor(sf::Color::White);
            }
            lCells[(x * fHeight) + y] = lCell;
        }
    }

    // determine size of windows to be create
    sf::Vector2u fSize;
    fSize.x = c_spacer + fWidth * (c_cellSize + c_spacer);
    fSize.y = c_spacer + fHeight * (c_cellSize + c_spacer);

    // set window to calculated size if not already that size
    if (aWindow.getSize() != fSize) 
    {
        aWindow.create(sf::VideoMode(fSize.x, fSize.y), "Robot Navigation");
    }

    // draw each cell in cells vector
    for (auto& lCell : lCells) 
    {
        aWindow.draw(lCell);
    }
}

std::ostream& operator<<(std::ostream& aOstream, const Map& aMap) 
{
    for (unsigned y = 0; y < aMap.fHeight; y++) 
    {
        for (unsigned x = 0; x < aMap.fWidth; x++) 
        {
            aOstream << aMap.fMapArray[x * aMap.fHeight + y] << " ";
        }
        cout << endl;
    }
    return aOstream;
}
