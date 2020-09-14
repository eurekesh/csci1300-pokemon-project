//THIS IS THE DRIVER FILE
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cctype>
#include "Map.h"
#include "Pokemon.h"
#include "Trainer.h"
#include "Events.h"
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
/*Algorithm will load pokemon from a file using fstream and assign attributes
  1. read each line of file
  2. use setters to set the base characteristics of the pokemon and push it to the array
  Returns: nothing
  Outputs: nothing
  Inputs: file
*/

vector<Pokemon> loadPokemon(string fileName, vector<Pokemon> &pokemon)
{
  ifstream pokeFile;
  pokeFile.open(fileName);

  if(pokeFile.fail())
  {
    cout << "Failed to intialize pokemon from file." << endl;
    vector<Pokemon> empty_vector;
    return empty_vector;
  }

  string current_line = "";
  while(getline(pokeFile, current_line))
  {
    string holding_array[10];
    split(current_line, ',', holding_array, 10);
    Pokemon current_pokemon;
    //load it up!
    current_pokemon.setNum(stoi(holding_array[0]));
    current_pokemon.setName(holding_array[1]);
    current_pokemon.setHP(stoi(holding_array[2]));
    current_pokemon.setCurrentHP(stoi(holding_array[2]));
    current_pokemon.setAttack(stoi(holding_array[3]));
    current_pokemon.setDefense(stoi(holding_array[4]));
    current_pokemon.setSpeed(stoi(holding_array[5]));
    current_pokemon.setMax(stoi(holding_array[6]));
    current_pokemon.setType(holding_array[7]);
    current_pokemon.setSecType(holding_array[8]);
    pokemon.push_back(current_pokemon);

  }
  //cout << "Pokemon loaded successfully" << endl;
  return pokemon;
}

Map scatterPokemon(Map &input_map, Trainer player)
{
  int i = 0;
  int random_row;
  int random_column;
  int num = 1; //debugging only
  srand(time(NULL));
  while(i < 21) //25 rows, 16 columns
  {
    random_row = rand() % 25;
    random_column = rand() % 16;
    if((input_map.map[random_row][random_column] != 'C') && (input_map.map[random_row][random_column] != 'w') && (input_map.map[random_row][random_column] != 'G') && (input_map.map[random_row][random_column] != 'x'))
    { //randomly generate pokemon locations
      if((random_row != player.getRow()) && (random_column != player.getColumn()))
      {
        input_map.map[random_row][random_column] = 'P';
        i++;
       // cout << num << endl;
        num++;
      }
    }
  }
  return input_map;
}

Map endTurnScatterPokemon(Map &input_map, Trainer player) //moves pokemon at the end of turn
{
  srand(time(NULL));
  for(int j = 0; j < 25; j++) //iterate through entire map
    {
      for(int k = 0; k < 16; k++)
      {
        if(input_map.map[j][k] == 'P') //we got a match!
        {
          bool moved = false; //keep running until we move
          int tried = 0; //prevents infinite loop if a pokemon gets cornered, try to move a lot
          while((moved == false) && (tried < 100))
          {
          int rand_result = rand() % 5;
          if(rand_result == 1) //we are moving north! j - 1
          {
            int new_row = (j - 1);
            if((input_map.map[new_row][k] != 'C') && (input_map.map[new_row][k] != 'w') && (input_map.map[new_row][k] != 'G') && (input_map.map[new_row][k] != 'P') && (new_row > -1))
            { //randomly generate pokemon locations
              if((new_row != player.getRow()) && (k != player.getColumn()))
              {
                input_map.map[j][k] = 'p';
                input_map.map[new_row][k] = 'P';
                moved = true; //moved successfully!
              }
              else
              {
                ;
              }
            }
            else
            {
              moved = false;
              //cout << "Failed" << endl;
              tried++;
            }
          }
          else if(rand_result == 2) //we are moving south! j + 1
          {
            int new_row = (j + 1);
            if((input_map.map[new_row][k] != 'C') && (input_map.map[new_row][k] != 'w') && (input_map.map[new_row][k] != 'G') && (input_map.map[new_row][k] != 'P') && (new_row < 25))
            { //randomly generate pokemon locations
              if((new_row != player.getRow()) && (k != player.getColumn()))
              {
                input_map.map[j][k] = 'p';
                input_map.map[new_row][k] = 'P';
                moved = true; //moved successfully!
              }
              else
              {
                ;
              }
            }
            else
            {
              moved = false;
              //cout << "Failed" << endl;
              tried++;
            }
          }
          else if(rand_result == 3) //we are moving west! k - 1
          {
            int new_column = (k - 1);
            if((input_map.map[j][new_column] != 'C') && (input_map.map[j][new_column] != 'w') && (input_map.map[j][new_column] != 'G') && (input_map.map[j][new_column] != 'P') && (new_column > -1))
            { //randomly generate ponew_columnemon locations
              if((j != player.getRow()) && (new_column != player.getColumn()))
              {
                input_map.map[j][k] = 'p';
                input_map.map[j][new_column] = 'P';
                moved = true; //moved successfully!
              }
              else
              {
                ;
              }
            }
            else
            {
              moved = false;
              //cout << "Failed" << endl;
              tried++;
            }
          }
          else if(rand_result == 4) //we are moving west! k + 1
          {
            int new_column = (k + 1);
            if((input_map.map[j][new_column] != 'C') && (input_map.map[j][new_column] != 'w') && (input_map.map[j][new_column] != 'G') && (input_map.map[j][new_column] != 'P') && (new_column < 16))
            { //randomly generate ponew_columnemon locations
              if((j != player.getRow()) && (new_column != player.getColumn()))
              {
                input_map.map[j][k] = 'p';
                input_map.map[j][new_column] = 'P';
                moved = true; //moved successfully!
              }
              else
              {
                ;
              }
            }
            else
            {
              moved = false;
              //cout << "Failed" << endl;
              tried++;
            }
          }
          else
          {
            moved = false;
            tried++;
          }
        }
      }
      else
      {

      }
    }
  }
  return input_map;
}


void run()
{
  //initialization

  Map map;
  map.loadMap("mapPoke.txt");

  vector<Pokemon> loadedPokemon;
  loadPokemon("pokemon.txt", loadedPokemon);

  Trainer player;

  cout << "Welcome to Pokémon!" << endl;
  cout << "What is your name?" << endl;
  string input;
  cin >> input;
  player.setTrainerName(input);

  bool pokemonChosen = false;
  int chosenPokemon;
  while(pokemonChosen != true)
  {
  string select;
  cout << "Welcome, " << player.getTrainerName() << "! Before you can begin your Pokémon adventure, you must choose a starting Pokémon, courtesy of the Professor. ​Please choose from the following ​Pokémon​:" << endl;
  cout << endl;
  cout << "1. Bulbasaur" << endl;
  cout << "2. Charmander" << endl;
  cout << "3. Squirtle" << endl;
  cout << "4. Pikachu" << endl;
  cin >> select;
  if(isdigit(select[0])) //don't break things!
  {
    if((stoi(select) > 0) && (stoi(select) < 5))
    {
      chosenPokemon = stoi(select);
      pokemonChosen = true;
    }
    else
    {
      cout << "Please input a valid option!" << endl;
    }
  }
  else
  {
    cout << "Please input a number between 1-4!" << endl;
  }
} //set things up
  if(chosenPokemon == 1)
  {
    player.setRow(12);
    player.setColumn(6);
    player.pokedex.push_back(loadedPokemon[0]);
    player.pokedex[0].setPartyMember(true);
    player.pokedex[0].setActive(true);
  }
  else if(chosenPokemon == 2)
  {
    player.setRow(12);
    player.setColumn(7);
    player.pokedex.push_back(loadedPokemon[3]);
    player.pokedex[0].setPartyMember(true);
    player.pokedex[0].setActive(true);
  }
  else if(chosenPokemon == 3)
  {
    player.setRow(12);
    player.setColumn(8);
    player.pokedex.push_back(loadedPokemon[6]);
    player.pokedex[0].setPartyMember(true);
    player.pokedex[0].setActive(true);
  }
  else if(chosenPokemon == 4)
  {
    player.setRow(12);
    player.setColumn(9);
    player.pokedex.push_back(loadedPokemon[24]);
    player.pokedex[0].setPartyMember(true);
    player.pokedex[0].setActive(true);
  }
  scatterPokemon(map, player);
//************************************
  //LOAD GYMS
  vector<Trainer> enemies;
  for(int j = 0; j < 25; j++)
    {
      for(int k = 0; k < 16; k++)
      {
        if(map.map[j][k] == 'G')
        {
          Trainer enemy; //create an object
          enemy.setRow(j); //set it equal to gym position
          enemy.setColumn(k);

          int num_pokemon = rand() % 6; //num of pokemon to generate
          vector<int> used; //used to test matches
          for(int i = 0; i < num_pokemon; i++)
          {
            int pokemonAdded = rand() % 151;
            bool match = false;
            for(int l = 0; l < used.size(); l++)
            {
              if(used[l] == pokemonAdded) //makes sure that pokemon currently added don't match
              {
                match = true;
              }
            }
            if(match == false)
            {
              enemy.pokedex.push_back(loadedPokemon[pokemonAdded]);
            }
          }
          enemies.push_back(enemy); //plan is to use enemies.size() - 1 in battle
          //cout << "Loaded!" << endl;
        }
      }
    }
  /*  for(int m = 0; m < enemies.size(); m++)
    {
        enemies[m].displayPokedex();
    } */
    //*************************************
//GAME TIME
  bool playing = true;
  Events game;
  bool luckTried = false;
  while(playing)
  {
    cout << endl; //to make things look neat
    map.displayMap(player.getColumn(), player.getRow());
    cout << endl;
    player.printStats();

    cout << "It's a great day outside " << player.getTrainerName() << "! We have " << player.getPokeballs() << " Pokéballs left and your Pokémon are doing great!" << endl;
    //PRINT POKEMON STATS HERE
    cout << "Please choose from the following options:" << endl;
    cout << "1. Travel" << endl;
    cout << "2. Rest" << endl;
    cout << "3. Try your luck" << endl;
    cout << "4. Quit the game" << endl;
    string option;
    cin >> option;

    if(isdigit(option[0]))
    {
      if((stoi(option) == 1))
      {
        game.Travel(player,map,enemies);
        game.hiddenTreasureCheck(player);
        game.randomEncounterCheck(loadedPokemon, player);
        game.randomDeathCheck(player);
        game.wildPokemonBattleCheck(player, map, loadedPokemon);
        endTurnScatterPokemon(map, player);
        int result = game.endOfGameCheck(player, false);
        if(result == 0)
        {
          run();
        }
        else if(result == 1)
        {
          return;
        }
        luckTried = false;
      }
      else if((stoi(option) == 2))
      {
        game.Rest(player);
        game.hiddenTreasureCheck(player);
        game.randomEncounterCheck(loadedPokemon, player);
        game.randomDeathCheck(player);
        game.wildPokemonBattleCheck(player, map, loadedPokemon);
        endTurnScatterPokemon(map, player);
        int result = game.endOfGameCheck(player, false);
        if(result == 0)
        {
          run();
        }
        else if(result == 1)
        {
          return;
        }
      }
      else if((stoi(option) == 3))
      {
        if(luckTried == false)
        {
          game.tryYourLuck(map, player, loadedPokemon);
          game.hiddenTreasureCheck(player);
          game.randomEncounterCheck(loadedPokemon, player);
          game.randomDeathCheck(player);
          game.wildPokemonBattleCheck(player, map, loadedPokemon);
          endTurnScatterPokemon(map, player);
          int result = game.endOfGameCheck(player, false);
          if(result == 0)
          {
            run();
          }
          else if(result == 1)
          {
            return;
          }
          luckTried = true;
        }
        else
        {
          cout << "You've already tried your luck!" << endl;
        }
      }
      else if((stoi(option) == 4))
      {
        int result = game.endOfGameCheck(player, true);
        if(result == 0)
        {
          run();
        }
        else if(result == 1)
        {
          return;
        }
        playing = false;
      }
      else if((stoi(option) == 5))
      {
        player.displayParty();
        map.printFullMap();
        endTurnScatterPokemon(map, player);
      }
      else
      {
        cout << "Please input a valid option!" << endl;
      }
    }
    else
    {
      cout << "Please input a number between 1-4!" << endl;
    }
  }
}




int main()
{
  run();
}
