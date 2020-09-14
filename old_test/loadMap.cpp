#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void loadMap(string fileName, char map[25][16])
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

void displayMap(char map[25][16], int row, int column)
{
  int left_cord = column - 3;
  int right_cord = column + 3;
  int up_cord = row - 3;
  int low_cord = row + 3;

  //make sure all inputs are valid on the boundaries
  if(left_cord < 0)
  {
    left_cord = 0;
  }
  if(right_cord > 15)
  {
    right_cord = 15;
  }
  if(up_cord < 0)
  {
    up_cord = 0;
  }
  if(low_cord > 24)
  {
    low_cord = 24;
  }

  for(int i = up_cord; i <= low_cord; i++)
  {
    for(int j = left_cord; j <= right_cord; j++)
    {
      if((i == row) && (j == column))
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


char getCurrentTileType(int xPosition, int yPosition, char map[25][16])
{
  return map[xPosition][yPosition];
}

int main()
{
  char map[25][16];
  loadMap("mapPoke.txt", map);
  displayMap(map, 0, 0);
  cout << endl;
  cout << getCurrentTileType(8, 15, map);

}
