#include <iostream>
#include <fstream>
#include <string>
#include "Map.h"
using namespace std;

/* Algorithm will load the complete map into the character array
  1. copy characters into the array
  Input: file
  Returns: none
  Output: none
*/
void Map::loadMap(string fileName)
{
  ifstream mapFile;
  mapFile.open(fileName);

  if(mapFile.fail())
  {
    cout << "Failed to initialize map file" << endl;
  }
  string current_line;
  int row = 0;
  int column = 0;

  while(getline(mapFile, current_line))
  {
    for(int i = 0; i < current_line.length(); i++)
    {
      if(current_line[i] == ',')
      {
        ;
      }
      else if (column < 16)
      {
        map[row][column] = current_line[i];
        column++;
      }
      else
      {
        column = 0;
        row++;
      }
    }
  }
/*  for(int j = 0; j < 25; j++)
  {
    for(int k = 0; k < 16; k++)
    {
      cout << map[j][k];
    }
    cout << endl;
  } */
  mapFile.close();
}
/* Algorithm will display a 7x7 map around the player's position
  1. get target indices that it will output around the player
  2. cout a map that does not go beyond the borders
  Input: none
  Returns: none
  Output: 7x7 map of characters
*/
void Map::displayMap(int xPos, int yPos)
{
  int left_cord = xPos - 3;
  int right_cord = xPos + 3;
  int up_cord = yPos + 3;
  int low_cord = yPos - 3;

  //make sure all inputs are valid on the boundaries
  if(left_cord < 0)
  {
    left_cord = 0;
  }
  if(right_cord > 15)
  {
    right_cord = 15;
  }
  if(low_cord < 0)
  {
    low_cord = 0;
  }
  if(up_cord > 24)
  {
    up_cord = 24;
  }

  for(int i = low_cord; i <= up_cord; i++)
  {
    for(int j = left_cord; j <= right_cord; j++)
    {
      if((i == yPos) && (j == xPos))
      {
        cout << '@';
      }
      else if(map[i][j] == 'p')
      {
        cout << '*';
      }
      else if(map[i][j] == 'w')
      {
        cout << '~';
      }
      else
      {
        cout << map[i][j];
      }
    }
    cout << endl;
  }
}

void Map::printFullMap() //debugging only
{
  for(int j = 0; j < 25; j++)
    {
      for(int k = 0; k < 16; k++)
      {
        cout << map[j][k];
      }
      cout << endl;
    }
}

char Map::getCurrentTileType(int row, int column)
{
  //algorithm returns the current char at the player x and y position
  return map[row][column];
}
