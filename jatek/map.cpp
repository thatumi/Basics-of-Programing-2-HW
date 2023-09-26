/**
    @file    map.cpp
    @brief   Terkep funkciok
**/


#include <exception>

#include <sstream>
#include <iostream>
#include <fstream>


#include "map.h"




using namespace std;

	/**
		@brief Setter a terkephez hasznalt 2d-s dinamikus tombhoz
		@param x - Az x pozicio ahova uj erteket akarunk allitani
		@param y - Az y pozicio ahova uj erteket akarunk allitani
		@param value - Az ertek amit akarunk allitani
	**/
	void terkep::setArrayValue(int x, int y, char value) {
		mapArray[x * sizeX + y] = value;
	}

	/**
		@brief Getter a terkephez hasznalt 2d-s dinamikus tombhoz
		@param int x - Az x pozicio ahonnan olvasni akarunk
		@param int y -  Az y pozicio ahonnan olvasni akarunk
	**/
	char terkep::getArrayValue(int x, int y) {
		return mapArray[x * sizeX + y];
	}

	/**
		@brief Ez a funkcio menti el a terkepet
		@details A 2d-s dinamikus tombon atiteralva irja ki a 'newmap.rmap'
		fajlba a terkep ertekeit
	**/
	void terkep::saveMap() {
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

	/**
		@brief Ezzel a funkcioval tudunk terkepet szerkeszteni
		@details Jarhato teruletet es falat tudunk lerakni (alapbol mindenhol
		jarhato terulet van). A funkcio inputot var, eloszor, hogy mit akarunk
		letenni (x = fal, - jarhato terulet), majd az x es y koordinatat. Ha
		rossz inputot adunk meg, a funkcio addig iteral, ameddig nem kap egy
		valid inputot. A funkciobol a 'k' karakterrel lehet kilepni az iteracio
		elejen.
	**/
	void terkep::setMap() {
		int x = 1;
		int y = 1;
		char item = '-';

		while (item != 'k') {
			cout << "Mit szeretnel letenni? x = fal, - = jarhato terulet, k = kilepes" << endl;
			cin >> item;
			while ((item != 'x' &&  item != '-' && item != 'k') || !cin) {
				cout << "Hibas input. x = fal, - = jarhato terulet, k = kilepes" << endl;
				cin >> item;
			}

			if (item == 'k') {
				return;
			}

			cout << "Kerem az X koordinatat. (1-10)" << endl;
			cin >> x;
			while ((x > sizeX || x < 1) || !cin) {
				cout << "A szam nem megengedett tartomanyban van. Kerek egy uj szamot." << endl;
				cin >> x;
			}

			cout << "Kerem az Y koordinatat. (1-10)" << endl;
			cin >> y;
			while ((y > sizeY || y < 1) || !cin) {
				cout << "A szam nem megengedett tartomanyban van. Kerek egy uj szamot." << endl;
				cin >> y;
			}

			setArrayValue(x - 1 , y - 1, item);

			renderMap();
		}

		return;

	}



	/**
		@brief Ez a funkcio tolti be a terkepet
		@details A funkcio atiteral a "newmap.rmap" fajl sorain es karakterein
		es ezeket tolti be sorba a dinamikus tombbe.
	**/
	void terkep::loadMap() {
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

	/**
		@brief A map kirajzolasaert felelos funkcio
		@details A programresz atiteral a tombon, es egyesevel kiirja annak
		tartalmat. Mivel a '-' jarhato helyet jelol, ezert ahelyett egy szokozt
		ir ki.
	**/
	void terkep::renderMap() {
		for (int i = 0; i < sizeX; ++i) {
			for (int j = 0; j < sizeY; ++j) {
			if (mapArray[j * sizeX + i] != '-') {
					cout << mapArray[j * sizeX + i];
				}else {
					cout << ' ';
				}
			}
			cout << "\n";
		}
	}
	/**
		@brief  Getter ami a dinamikus tomb x meretet adja vissza
	**/
	int terkep::getSizeX() {
		return sizeX;
	}

	/**
		@brief  Getter ami a dinamikus tomb y meretet adja vissza
	**/
	int terkep::getSizeY() {
		return sizeY;
	}

