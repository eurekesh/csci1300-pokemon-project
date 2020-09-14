#include <iostream>
#include <string>
#include "Pokemon.h"
using namespace std;

Pokemon::Pokemon()
{
  name = "";
  type = "";
  secType = "";
  hp = 0;
  attack = 0;
  defense = 0;
  max = 0;
  speed = 0;
}
Pokemon::Pokemon(int input_num, string input_name, string input_type, string input_type2, int input_hp, int input_attack, int input_defense, int input_max, int input_speed)
{
  num = input_num;
  name = input_name;
  type = input_type;
  secType = input_type2;
  hp = input_hp;
  attack = input_attack;
  defense = input_defense;
  max = input_max;
  speed = input_speed;
}
void Pokemon::setNum(int input)
{
  num = input;
}
int Pokemon::getNum()
{
  return num;
}
void Pokemon::setCurrentHP(int input)
{
  currentHP = input;
}
int Pokemon::getCurrentHP()
{
  return currentHP;
}
void Pokemon::setName(string input)
{
  name = input;
}
string Pokemon::getName()
{
  return name;
}
void Pokemon::setType(string input)
{
  type = input;
}
string Pokemon::getType()
{
  return type;
}
void Pokemon::setSecType(string input)
{
  secType = input;
}
string Pokemon::getSecType()
{
  return secType;
}
void Pokemon::setHP(int input)
{
  hp = input;
}
int Pokemon::getHP()
{
  return hp;
}
void Pokemon::setAttack(int input)
{
  attack = input;
}
int Pokemon::getAttack()
{
  return attack;
}
void Pokemon::setDefense(int input)
{
  defense = input;
}
int Pokemon::getDefense()
{
  return defense;
}
void Pokemon::setMax(int input)
{
  max = input;
}
int Pokemon::getMax()
{
  return max;
}
void Pokemon::setSpeed(int input)
{
  speed = input;
}
int Pokemon::getSpeed()
{
  return speed;
}
//Algorithm will increment all stats for a given pokemon by 2%
void Pokemon::addLevel()
{
  cout << endl;
  cout << name << " leveled up!" << endl;
  hp += 0.02 * hp;
  currentHP += 0.02 * currentHP;
  if(attack < max)
  {
    attack += 0.02 * attack;
  }
  if(defense < max)
  {
    defense += 0.02 * defense;
  }
  if(speed < max)
  {
    speed += 0.02 * speed;
  }
}
void Pokemon::setActive(bool input)
{
  active = input;
}
bool Pokemon::isActive()
{
  return active;
}
void Pokemon::setPartyMember(bool input)
{
  partyMember = input;
}
bool Pokemon::isPartyMember()
{
  return partyMember;
}
