#include <iostream>
#include <vector>
#include "Trainer.h"
#include "Pokemon.h"
using namespace std;

Trainer::Trainer()
{
  name = "";
  points = 0;
  pokeballs = 10;
}
Trainer::Trainer(string input)
{
  name = input;
  points = 0;
  pokeballs = 10;
}
void Trainer::setTrainerName(string input)
{
  name = input;
}
string Trainer::getTrainerName()
{
  return name;
}
void Trainer::setRow(int input)
{
  row = input;
}
int Trainer::getRow()
{
  return row;
}
void Trainer::setColumn(int input)
{
  column = input;
}
int Trainer::getColumn()
{
  return column;
}
/* Algorithm iterates through all pokemon in pokedex vector, printing out their name
  No Input, or return - outputs pokemon
  */
void Trainer::displayPokedex()
{
//  display the pokedex
  for(int i = 0; i < pokedex.size(); i++)
  {
    cout << (i + 1) << ". " << pokedex[i].getName() << endl;
  }
}
void Trainer::displayParty()
{
  //display the party
  int num = 1;
  for(int i = 0; i < pokedex.size(); i++)
  {
    if(pokedex[i].isPartyMember() && (pokedex[i].getCurrentHP() > 0))
    {
        cout << num << ". " << pokedex[i].getName() << endl;
        num++;
    }
  }
}
void Trainer::calcPartySize()
{
  party_size = 0;
  for(int i = 0; i < pokedex.size(); i++)
  {
    if(pokedex[i].isPartyMember())
    {
      party_size++;
    }
  }
}
void Trainer::addPokemon(Pokemon& pokemon, Trainer& player)
{
  calcPartySize();
  if(party_size > 5)
  {
    cout << "Awesome! You acquired " << pokemon.getName() <<", who joins the ​Pokédex​. Your battle party is full. Do you want to add " << pokemon.getName() << " to your Active ​Party? (Y/N):" << endl;
    string input;
    cin >> input;
    if(input == "N")
    {
      cout << "Alright! We'll put it in the Pokédex." << endl;
      pokedex.push_back(pokemon);
    }
    else if(input == "Y")
    {
      cout << "Which Pokémon should not be a part of the Active Party anymore?" << endl;
      displayParty();
      int input;
      cin >> input;
      input--; //decrease to reflect index
      int match = 0;
      for(int i = 0; i < pokedex.size(); i++)
      {
        if(pokedex[i].isPartyMember() && (input == match)) //match index to matches
        {
          pokedex[i].setActive(false);
          pokedex[i].setPartyMember(false);
          match++; //make sure we don't set rest of party as inactive
        }
        else if(pokedex[i].isPartyMember()) //iterating through pokedex, make sure no one else is active
        {
          pokedex[i].setActive(false);
          match++;
        }
      }
      pokedex.push_back(pokemon);
      pokedex[pokedex.size() - 1].setPartyMember(true); //make it active!
      cout << "Great! The following Pokémon are in your active party. Choose one of them to be your Active Pokémon:" << endl;
      displayParty();
      int input_change;
      cin >> input_change;
      input_change--;
      int matchID = 0;
      for(int j = 0; j < pokedex.size(); j++)
      {
        if(pokedex[j].isPartyMember() && (input_change == matchID)) //match index to matches
        {
          pokedex[j].setActive(true);
          matchID++;
        }
        else if(pokedex[j].isPartyMember())
        {
          matchID++;
        }
      }
    }
    else
    {
      cout << "Please use valid input!" << endl;
    }
  }
  else
  {
    cout << pokemon.getName() << " has joined your party!" << endl;
    pokedex.push_back(pokemon);
    pokedex[pokedex.size() - 1].setPartyMember(true);
  }
}
void Trainer::printStats()
{
  int num = 0;
  for(int i = 0; i < pokedex.size(); i++)
  {
    if(pokedex[i].isPartyMember())
    {
      if(pokedex[i].isActive())
      {
        cout << "Name: " << pokedex[i].getName() << " (ACTIVE), HP: " << pokedex[i].getCurrentHP() << ", A: " << pokedex[i].getAttack() << ", D: " << pokedex[i].getDefense() << ", S: " << pokedex[i].getSpeed() << ", M: " << pokedex[i].getMax() << endl;
      }
      else
      {
        cout << "Name: " << pokedex[i].getName() << " HP: " << pokedex[i].getCurrentHP() << ", A: " << pokedex[i].getAttack() << ", D: " << pokedex[i].getDefense() << ", S: " << pokedex[i].getSpeed() << ", M: " << pokedex[i].getMax() << endl;
      }
    }
  }
}
void Trainer::addBadge()
{
  badges++;
}
void Trainer::addPoints(int value)
{
  points += value;
}
int Trainer::getPokeballs()
{
  return pokeballs;
}
void Trainer::addPokeballs(int value)
{
  pokeballs += value;
}
void Trainer::subtractPokeball()
{
  pokeballs--;
}
int Trainer::getPoints()
{
  return points;
}
