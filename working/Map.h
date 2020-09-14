//deals with all things map related
#include <iostream>
using namespace std;

#ifndef MAP_H
#define MAP_H

class Map{
public:
  void loadMap(string fileName);
  void displayMap(int, int);
  char getCurrentTileType(int, int);
  void printFullMap();
  char map[25][16];

};
#endif

//put Ps on the map that aren't water or gym or center and then generate on the tile
