/**

    @file    map.h
    @brief   A terkep leirasa itt tortenik

**/
#pragma once


class terkep {
	int sizeX;
	int sizeY;
	char* mapArray;
public:
	/**
		@brief Konstruktor, ami 2d-s dinamikus tombot hoz letre es feltolti azt
		'-' karakterrel, ami jarhato helyet jelol.
	**/
	terkep(int gSizeX, int gSizeY) :
		sizeX(gSizeX), sizeY(gSizeY), mapArray(new char[gSizeX * gSizeY]) {
		for (int i = 0; i < gSizeX; i++) {
			for (int j = 0; j < gSizeY; j++) {
				setArrayValue(i, j, '-');
			}
		}
	}
	terkep() :
		sizeX(20), sizeY(40), mapArray(new char[20 * 40]) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 40; j++) {
				setArrayValue(i, j, '-');
			}
		}
	}

	void setArrayValue(int x, int y, char value);
	char getArrayValue(int x, int y);
	void saveMap();
	void setMap();

	void loadMap();
	void renderMap();
	int getSizeX();
	int getSizeY();

	/**
		@brief  Destruktor, ami vegul a 2d-s dinamikus tombot is felszabaditja
	**/
	~terkep() {
		delete[] mapArray;
	}

};

