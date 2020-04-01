#include "Map.h"

using namespace std;

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

std::ostream& operator<<(std::ostream& aOstream, const Map& aMap) {
    for (int y = 0; y < aMap.fHeight; y++) {
        for (int x = 0; x < aMap.fWidth; x++) {
            aOstream << aMap.fMapArray[x][y] << " ";
        }
        cout << endl;
    }
    return aOstream;
}
