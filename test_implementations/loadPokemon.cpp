#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//*******************************************
//Split function
int split(string split_string, char delimiter, string pieces[], int length)
{
  string holding = ""; //temp string
  int string_length = split_string.length();
  int holding_counter = 0;

  if (split_string == "") //make sure string isn't empty
  {
    return 0;
  }

  if (split_string[0] == delimiter) //if first character is delimiter, start 1 after
  {
    split_string = split_string.substr(1, split_string.length());
  }

  split_string += delimiter; //append delimiter to end of string for stopping point

  for(int slider = 0; slider <= string_length; slider++) //iterate through string
  {
    if(split_string[slider] != delimiter) //if current character != delimiter, then append to temp string
    {
      holding += split_string[slider];
    }

    else if (split_string[slider + 1] == delimiter) //if next character in sequence is delimiter, skip it
    {
      ;
    }
    else if (split_string[slider] == delimiter) //if character is delimiter, time to do some things
    {
      pieces[holding_counter] = holding; //push temp string to array
      holding_counter++; //increment element number in result array
      holding = ""; //reset temp string
    }
    else //if any condition isn't met above, keep going
    {
      ;
    }
  }
  return holding_counter; //return number of elements in result array
}


void loadPokemon(string fileName, vector<Pokemon> pokemon)
{
  ifstream pokeFile;
  pokeFile.open(fileName);

  if(pokeFile.fail())
  {
    cout << "Failed to intialize pokemon from file." << endl;
    return;
  }

  string current_line = "";
  while(getline(pokeFile, current_line))
  {
    string holding_array[9];
    split(current_line, ',', holding_array, 9);
    pokemon.push_back()
  }
}
