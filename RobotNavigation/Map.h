#pragma once
#include <iostream>

#define ARRAY_MAX_SIZE 20

enum Status {
    Floor,
    Wall,
    Goal,
    Nil
};

struct Point {
    int x;
    int y;
};

class Map {
private:
    int fHeight;
    int fWidth;
    Status fMapArray[ARRAY_MAX_SIZE][ARRAY_MAX_SIZE];

public:
    Map();

    void setHeight(int aHeight) { fHeight = aHeight; }
    void setWidth(int aWidth) { fWidth = aWidth; }

    int getHeight() { return fHeight; }
    int getWidth() { return fWidth; }

    void setStatus(int x, int y, Status aStatus);
    void setStatus(Point aPoint, Status aStatus);
    Status getStatus(Point aPoint);

    // Create output stream of map for printing
    friend std::ostream& operator<<(std::ostream& aOstream, const Map& aMap);
};