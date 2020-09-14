//contains details about events
#include <iostream>
#include "Pokemon.h"
#include "Trainer.h"
#include "Map.h"
using namespace std;

#ifndef EVENTS_H
#define EVENTS_H
class Events
{
public:
  Events();
  void Gym(Trainer& player, Map& map, vector<Trainer> &enemies);
  void pokemonCenter(Trainer&);
  void tryYourLuck(Map&, Trainer&, vector<Pokemon> loadedPokemon);
  void hiddenTreasureCheck(Trainer&);
  void randomDeathCheck(Trainer&);
  void randomEncounterCheck(vector<Pokemon>, Trainer&);
  int endOfGameCheck(Trainer&, bool);
  void wildPokemonBattleCheck(Trainer&, Map&, vector<Pokemon>);
  int wildBattle(Trainer&, Pokemon&);
  int gymBattle(Trainer&, Pokemon&);
  void Travel(Trainer& player, Map map, vector<Trainer> &enemies);
  Trainer Rest(Trainer&);
};
#endif
