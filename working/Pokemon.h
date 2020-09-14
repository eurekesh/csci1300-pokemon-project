//all things pokemon
#include <iostream>
using namespace std;

#ifndef POKEMON_H
#define POKEMON_H

class Pokemon{
public:
  Pokemon();
  Pokemon(int, string, string, string, int, int, int, int, int);
  void setNum(int);
  int getNum();
  void setCurrentHP(int);
  int getCurrentHP();
  void setName(string);
  string getName();
  void loadPokemon(string);
  void setType(string);
  string getType();
  void setSecType(string);
  string getSecType();
  void setHP(int);
  int getHP();
  void setAttack(int);
  int getAttack();
  void setDefense(int);
  int getDefense();
  void setMax(int);
  int getMax();
  void setSpeed(int);
  int getSpeed();
  void addLevel();
  void setActive(bool);
  bool isActive();
  bool isPartyMember();
  void setPartyMember(bool);

private:
  bool partyMember;
  bool active;
  int num;
  string name;
  string type;
  string secType;
  int hp; //max hp value to be affected by level up
  int currentHP;
  int attack;
  int defense;
  int max;
  int speed;
};
#endif
