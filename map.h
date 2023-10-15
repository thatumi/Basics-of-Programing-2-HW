/**
 * @file    map.h
 * @brief   The description of the map is provided here
 **/
#pragma once

class map {
    int sizeX;
    int sizeY;
    char* mapArray;

public:
    /**
     * @brief Constructor that creates a 2D dynamic array and fills it with '-' characters, representing walkable terrain
     * @param gSizeX - The X size of the map
     * @param gSizeY - The Y size of the map
     **/
    map(int gSizeX, int gSizeY) : sizeX(gSizeX), sizeY(gSizeY), mapArray(new char[gSizeX * gSizeY]) {
        for (int i = 0; i < gSizeX; i++) {
            for (int j = 0; j < gSizeY; j++) {
                setArrayValue(i, j, '-');
            }
        }
    }

    /**
     * @brief Default constructor that creates a 2D dynamic array with default size and fills it with '-' characters, representing walkable terrain
     **/
    map() : sizeX(20), sizeY(40), mapArray(new char[20 * 40]) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 40; j++) {
                setArrayValue(i, j, '-');
            }
        }
    }

    /**
     * @brief Setter for the 2D dynamic array used for the map
     * @param x - The x position where we want to set a new value
     * @param y - The y position where we want to set a new value
     * @param value - The value we want to set
     **/
    void setArrayValue(int x, int y, char value);

    /**
     * @brief Getter for the 2D dynamic array used for the map
     * @param x - The x position we want to read from
     * @param y - The y position we want to read from
     **/
    char getArrayValue(int x, int y) const;

    /**
     * @brief This function saves the map
     * @details By iterating through the 2D dynamic array, it writes the map's values to a 'newmap.rmap' file.
     **/
    void saveMap() const;

    /**
     * @brief This function allows us to edit the map
     * @details It enables us to place walkable terrain and walls (by default, all areas are walkable). The function expects input for what to place (x = wall, - = walkable terrain) and the x and y coordinates. If incorrect input is provided, the function will iterate until it receives valid input. You can exit the iteration with the 'k' character.
     **/
    void setMap();

    /**
     * @brief This function loads the map
     * @details The function iterates through the lines and characters of the "newmap.rmap" file, loading them into the dynamic array.
     **/
    void loadMap();

    /**
     * @brief Function responsible for rendering the map
     * @details The function iterates through the array and prints its contents one by one. As '-' represents walkable terrain, it prints a space instead.
     **/
    void renderMap() const;

    /**
     * @brief Getter that returns the X size of the dynamic array
     **/
    int map::getSizeX() const{ return sizeX; }

    /**
     * @brief Getter that returns the Y size of the dynamic array
     **/
    int map::getSizeY() const { return sizeY; }


    /**
     * @brief Destructor that frees the 2D dynamic array
     **/
    ~map() {
        delete[] mapArray;
    }
};
