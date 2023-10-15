/**
 * @file    map.cpp
 * @brief   Map functions
**/

#include <exception>
#include <sstream>
#include <iostream>
#include <fstream>
#include "map.h"

using namespace std;


void map::setArrayValue(int x, int y, char value) {
    mapArray[x * sizeX + y] = value;
}

char map::getArrayValue(int x, int y) const{
    return mapArray[x * sizeX + y];
}

void map::saveMap() const {
    std::ofstream mapFile("newmap.rmap");

    for (int i = 0; i < sizeX; ++i) {
        for (int j = 0; j < sizeY; ++j) {
            mapFile << mapArray[j * sizeX + i];
            mapFile << " ";
        }
        mapFile << "\n";
    }
    mapFile.close();
}


void map::setMap() {
    int x = 1;
    int y = 1;
    char item = '-';

    while (item != 'k') {
        cout << "What would you like to place? x = wall, - = walkable terrain, k = exit" << endl;
        cin >> item;
        while ((item != 'x' && item != '-' && item != 'k') || !cin) {
            cout << "Invalid input. x = wall, - = walkable terrain, k = exit" << endl;
            cin >> item;
        }

        if (item == 'k') {
            return;
        }

        cout << "Please enter the X coordinate. (1-10)" << endl;
        cin >> x;
        while ((x > sizeX || x < 1) || !cin) {
            cout << "The number is outside the allowed range. Please enter a new number." << endl;
            cin >> x;
        }

        cout << "Please enter the Y coordinate. (1-10)" << endl;
        cin >> y;
        while ((y > sizeY || y < 1) || !cin) {
            cout << "The number is outside the allowed range. Please enter a new number." << endl;
            cin >> y;
        }

        setArrayValue(x - 1, y - 1, item);

        renderMap();
    }
    return;
}

void map::loadMap() {
    std::string line;
    std::ifstream infile("newmap.rmap");
    int i = 0;
    int j = 0;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        char c;
        while (iss >> c) {
            setArrayValue(j, i, c);
            j++;
            if (j == sizeY) {
                j = 0;
                i++;
            }
        }
    }
    infile.close();
}

void map::renderMap() const{
    for (int i = 0; i < sizeX; ++i) {
        for (int j = 0; j < sizeY; ++j) {
            if (mapArray[j * sizeX + i] != '-') {
                cout << mapArray[j * sizeX + i];
            }
            else {
                cout << ' ';
            }
        }
        cout << "\n";
    }
}

