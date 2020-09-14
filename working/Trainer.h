//all things Trainer related

#include <iostream>
#include <vector>
#include "Pokemon.h"
using namespace std;

#ifndef TRAINER_H
#define TRAINER_H

class Trainer
{
public:
  Trainer();
  Trainer(string);
  void setTrainerName(string);
  void setRow(int);
  void setColumn(int);
  int getRow();
  int getColumn();
  void addPokemon(Pokemon&, Trainer&);
  void printStats();
  void calcPartySize();
  string getTrainerName();
  void subtractPokeball();
  void addBadge();
  void addPoints(int);
  int getPokeballs();
  int getPoints();
  void addPokeballs(int);
  void displayPokedex();
  void displayParty();
  vector<Pokemon> pokedex;
  int badges;

private:
  int party_size = 0;
  string name;
  int row;
  int column;
  int points;
  int pokeballs;

};
#endif
