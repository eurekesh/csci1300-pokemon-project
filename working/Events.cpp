#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <fstream>
#include "Events.h"
#include "Pokemon.h"
#include "Trainer.h"
#include "Map.h"
using namespace std;


//events implementation - run all events at end of every turn
Events::Events()
{
  ;
}




/* Algorithm will present the pokemon center dialgoue and associated actions
  1. heal pokemon to full hp
  2. print pokedex and allow for switching
  3. then begin the turn
  Input: none
  Returns: none
  Output: event dialogue
*/
void Events::pokemonCenter(Trainer& player)
{
  for(int i = 0; i < player.pokedex.size(); i++) //restore health
  {
    player.pokedex[i].setCurrentHP(player.pokedex[i].getHP());
  }
  cout << "Welcome to the ​Pokémon Center. All Pokémon in your party have been healed. Do you want to change the members of your party (Y/N):" << endl;
  string response;
  cin >> response;
  if(response == "Y")
  {
    for(int j = 0; j < player.pokedex.size(); j++) //clear out current pokemon
    {
      player.pokedex[j].setPartyMember(false);
      player.pokedex[j].setActive(false);
    }
    bool valid = false;
    string selection;
    while(valid != true)
    {
      cout << "Here are all the Pokémon in your Pokédex. Choose at most 6 numbers:" << endl;
      player.displayPokedex();

      cin >> selection;
      if(selection.length() > 6) //edge case check
      {
        cout << "Your selection must be less than 6!" << endl;
      }
      else
      {
        valid = true;
      }
    }

    int selection_index = 0;
    for(int k = 0; k < player.pokedex.size(); k++)
    {
      char current_char = selection[selection_index];
      int pokemon_selector = (int)current_char - 49;
      if(pokemon_selector == k)
      {
        player.pokedex[k].setPartyMember(true);
        selection_index++;
      }
      else
      {
        ;
      }
    }
    cout << endl;
    cout << "Great! The following Pokémon are in your active party. Choose one of them to be your Active Pokémon:" << endl;
    player.displayParty();
    int input_change;
    cin >> input_change;
    input_change--;
    int matchID = 0;
    for(int j = 0; j < player.pokedex.size(); j++)
    {
      if(player.pokedex[j].isPartyMember() && (input_change == matchID)) //match index to matches
      {
        player.pokedex[j].setActive(true);
        matchID++;
      }
      else if(player.pokedex[j].isPartyMember())
      {
        matchID++;
      }
    }
  }
  else if(response == "N")
  {
    cout << "Best of luck on your adventure!" << endl;
  }
  else
  {
    cout << "Please select a valid option!" << endl;
  }
}
/* Algorithm will handle random catching chance for pokemon within 7x7 square of player
  1. generate a random number to calculate chance
  2. If successful, add pokemon to party and/or pokedex for free
  Input: none
  Returns: none
  Output: event dialogue
*/
void Events::tryYourLuck(Map& map, Trainer& player, vector<Pokemon> loadedPokemon)
{
  int low_cord = player.getRow() - 3;
  int up_cord = player.getRow() + 3;
  int right_cord = player.getColumn() + 3;
  int left_cord = player.getColumn() - 3;

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

  srand(time(NULL));
  bool ran = false; //this only runs once!
  bool found = false;
  for(int i = low_cord; i <= up_cord; i++)
  {
    for(int j = left_cord; j <= right_cord; j++)
    {
      if((map.map[i][j] == 'P') && (ran == false))
      {
        int rand_num = rand() % 2;
        found = true;
        if (rand_num == 1)
        {
          map.map[i][j] = 'p'; //delete the pokemon
          int rand_poke = rand() % 151;
          cout << "Today's your lucky day!" << endl;
          // player.displayParty();
          player.addPokemon(loadedPokemon[rand_poke], player);
          ran = true;
        }
        else
        {
          cout << "Too bad! Better luck next time!" << endl;
        }
      }
      else
      {
        // cout << map.map[i][j]; DEBUG ONLY
      }
    }
  }
  if(found == false)
  {
    cout << "No pokemon found!" << endl;
  }
}
/* Algorithm will handle random treasure chance for player
  1. generate a random number to calculate chance
  2. If successful, present treasure to player
  Input: vector, trainer
  Returns: none
  Output: event dialogue
*/
void Events::hiddenTreasureCheck(Trainer& player)
{
  srand(time(NULL));
  int rand_chance = rand() % 4;
  if(rand_chance == 0)
  {
    int treasure_choice = rand() % 2;
    if(treasure_choice == 0)
    {
      player.addPokeballs(2);
      cout << "Great news! You have stumbled upon a hidden stash of Pokéballs​. Your reserves increased to " << player.getPokeballs() << " Pokéballs​." << endl;
    }
    else
    {
      cout << "Great news! You have stumbled upon a hidden stash of Poffins​. Your ​Pokémon are delighted. Choose one of them to feast on the Poffins and Level Up:" << endl;
      player.displayParty();
      int choice;
      cin >> choice;
      choice--; //decrease it by one to accurately reflect the index
      int match = 0;
      for(int i = 0; i < player.pokedex.size(); i++)
      {
        if(player.pokedex[i].isPartyMember() && (match == choice))
        {
          player.pokedex[i].addLevel();
        }
        else
        {
          match++;
        }
      }
    }
  }
}

void Events::randomEncounterCheck(vector<Pokemon> loadedPokemon, Trainer& player)
{
  srand(time(NULL));
  int rand_chance = rand() % 3;
  if(rand_chance == 2)
  {
    bool choice_made = false;
    while(choice_made != true)
    {
    int rand_poke = rand() % 151; //get a random pokemon
    cout << "Suddenly, " << loadedPokemon[rand_poke].getName() << " appears in your path! Do you want to:" << endl;
    cout << "1. Catch it" << endl;
    cout << "2. Release it" << endl;
    string choice;
    cin >> choice;
    if(isdigit(choice[0]))
    {
      if((stoi(choice) == 1))
      {
        choice_made = true;
        player.subtractPokeball();
        player.addPokemon(loadedPokemon[rand_poke], player);
      }
      else if((stoi(choice) == 2))
      {
        cout << loadedPokemon[rand_poke].getName() << " fades into the surroundings..." << endl;
        choice_made = true;
      }
      else
      {
        cout << "Please select a valid option!" << endl;
      }
    }
    else
    {
      cout << "Please input a legal option!" << endl;
    }
  }
  }
}
/* Algorithm will handle death for player
  1. generate a random number to calculate chance
  2. If successful, delete a pokemon from party/pokedex and make player aware
  Input: none
  Returns: none
  Output: event dialogue
*/
void Events::randomDeathCheck(Trainer& player)
{
  srand(time(NULL));
  int rand_chance = rand() % 5;
  if(rand_chance == 0)
  {
    int pokedexSize = player.pokedex.size();
    if(pokedexSize > 3) //don't kill off pokemon if player hasn't gotten started!
    {
    bool selected = false;
    while(selected != true)
    {
    int poke_in_party = rand() % pokedexSize;
    if(player.pokedex[poke_in_party].isPartyMember())
    {
      selected = true;
      cout << "Oh no! After years of legendary battles, " << player.pokedex[poke_in_party].getName() << " died of old age. Thank you for your companionship, dear friend." << endl;
      player.pokedex.erase(player.pokedex.begin() + poke_in_party);

      int active_counter = 0;
      for(int i = 0; i < player.pokedex.size(); i++) //make sure that there is an active pokemon!
      {
        if(player.pokedex[i].isActive())
        {
          active_counter++;
        }
      }
      if(active_counter == 0) //if no active pokemon are found, we need to find them!
      {
        int j = 0;
        bool found = false;
        while((j < player.pokedex.size()) && (found != true)) //wait until we get the first party member to set active
        {
          if(player.pokedex[j].isPartyMember())
          {
            player.pokedex[j].setActive(true);
            found = true;
          }
          j++;
        }
      }
    }
  }
}

  }

  }
/* Algorithm will handle end of game checks
  1. check for win conditions (6 badges or 8 types caught)
  2. If successful, end game and print to text file the results
  Input: none
  Returns: none
  Output: event dialogue
*/
//0: KEEP GOING
//1: END OF GAME
int Events::endOfGameCheck(Trainer& player, bool voluntary)
{
  //calculate number of types
  vector<string> types;
  for(int i = 0; i < player.pokedex.size(); i++)
  {
    if(i == 0)
    {
      types.push_back(player.pokedex[i].getType());
      types.push_back(player.pokedex[i].getSecType());
    }
    else
    {
      bool match = false;
      for(int j = 0; j < types.size(); j++)
      {
        if(types[j] == player.pokedex[i].getType()) //if it matches don't put it in
        {
          match = true;
        }
      }
      if(match == false)
      {
        types.push_back(player.pokedex[i].getType());
      }
    }
  }
  if((types.size() == 8) || (player.badges == 6))
  {
    cout << "You win!" << endl;
    ofstream results;
    results.open("resultsPoke.txt", std::ios_base::app);
    results << player.getTrainerName() << " Win! " << player.getPoints() << endl;
    results.close();
    cout << "Do you wish to play again? Press Y to continue" << endl;
    string option;
    cin >> option;
    if(option == "Y")
    {
      return 0;
    }
    else
    {
      cout << "Thanks for playing!" << endl;
      return 1;
    }
  }
  else if(voluntary == true)
  {
    cout << "You lose!" << endl;
    ofstream results;
    results.open("resultsPoke.txt", std::ios_base::app);
    results << player.getTrainerName() << " Loss! " << player.getPoints() << endl;
    results.close();
    cout << "Do you wish to play again? Press Y to continue" << endl;
    string option;
    cin >> option;
    if(option == "Y")
    {
      return 0;
    }
    else
    {
      cout << "Thanks for playing!" << endl;
      return 1;
    }
  }
  else
  {
    return 2;
  }
}


/* Algorithm will handle rest action for player
  1. increase hp by 1, decrease pokeballs by 1
  Input: none
  Returns: none
  Output: event dialogue
*/
Trainer Events::Rest(Trainer& player)
{
  if(player.getPokeballs() < 1) //make sure can actually rest
  {
    cout << "You do not have enough Pokéballs to rest!" << endl;
    return player;
  }
  for(int i = 0; i < player.pokedex.size(); i++)
  {
    if(player.pokedex[i].isPartyMember() && (player.pokedex[i].getCurrentHP() < player.pokedex[i].getHP()))
    {
    int current_hp = player.pokedex[i].getCurrentHP(); //add hp
    player.pokedex[i].setHP(current_hp + 1);
  }
  }
  player.subtractPokeball();
  return player;
}
/*
  return 1: player wins battle
  return 2: pokemon won battle
  return 3: pokemon fled
  return 4: player fled
*/
/* Algorithm will generate the battle dialogue and fight characteristics
  1. calculate results of fights and run chances
  2. Present menu of choices and contain the battle
  Input: none
  Returns: none
  Output: event dialogue
*/
int Events::wildBattle(Trainer& player, Pokemon& enemyPokemon)
{
  int active_index;
  int flee_attempts = 0;
  for(int i = 0; i < player.pokedex.size(); i++)
  {
    if(player.pokedex[i].isActive())
    {
      active_index = i;
    }
  }
  srand(time(NULL));
  int attack_chance = rand() % 10;
  if(attack_chance < 4)
  {
    //calculate A
    int a = enemyPokemon.getSpeed();
    cout << enemyPokemon.getName() << " is attempting to flee!" << endl;
    cout << "A: " << a << endl;
    //calculate B
    int playerSpeed = player.pokedex[active_index].getSpeed();
    int b = (playerSpeed / 4) % 256;
    cout << "B: " << b << endl;
    cout << "C: 1" << endl;
    int f = ((a*32)/b) + 30; //f formula
    cout << "F: " << f << endl;
    if(f > 255)
    {
      return 3;
    }
    else
    {
      int rand_num = rand() % 256;
      if(rand_num < f)
      {
        return 3;
      }
    }
  }
  else
  {
    cout << "You ran into a wild Pokémon!" << endl;
    while((player.pokedex[active_index].getCurrentHP() > 0) && (enemyPokemon.getCurrentHP() > 0))
    {
      cout << "Name: " << enemyPokemon.getName() << " HP: " << enemyPokemon.getCurrentHP() << ", A: " << enemyPokemon.getAttack() << ", D: " << enemyPokemon.getDefense() << ", S: " << enemyPokemon.getSpeed() << ", M: " << enemyPokemon.getMax() << endl;
      cout << endl;
      cout << "Your ACTIVE Pokémon is:" << endl;
      cout << "Name: " << player.pokedex[active_index].getName() << " HP: " << player.pokedex[active_index].getCurrentHP() << ", A: " << player.pokedex[active_index].getAttack() << ", D: " << player.pokedex[active_index].getDefense() << ", S: " << player.pokedex[active_index].getSpeed() << ", M: " << player.pokedex[active_index].getMax() << endl;
      cout << endl;
      cout << "What do you want to do? (Pick 1, 2, or 3)" << endl;
      cout << "1. Fight" << endl;
      cout << "2. Switch Active ​Pokémon" << endl;
      cout << "3. Run" << endl;
      int choice;
      cin >> choice;
      if(choice == 1)
      {
        int enemySpeed = enemyPokemon.getSpeed();
        int playerSpeed = player.pokedex[active_index].getSpeed();
        if(playerSpeed >= enemySpeed)
        {
          //player attack phase
          int result = player.pokedex[active_index].getAttack() - enemyPokemon.getDefense();
          if(result < 0)
          {
            result = 0;
          }
          cout << player.pokedex[active_index].getName() << " dealt " << result << " damage!" << endl;
          enemyPokemon.setCurrentHP(enemyPokemon.getCurrentHP() - result); //calculate damage
          if(enemyPokemon.getCurrentHP() <= 0)
          {
            player.pokedex[active_index].addLevel();
            return 1;
          }
          //enemy attack phase
          cout << "Name: " << enemyPokemon.getName() << " HP: " << enemyPokemon.getCurrentHP() << ", A: " << enemyPokemon.getAttack() << ", D: " << enemyPokemon.getDefense() << ", S: " << enemyPokemon.getSpeed() << ", M: " << enemyPokemon.getMax() << endl;
          cout << endl;
          cout << "Name: " << player.pokedex[active_index].getName() << " HP: " << player.pokedex[active_index].getCurrentHP() << ", A: " << player.pokedex[active_index].getAttack() << ", D: " << player.pokedex[active_index].getDefense() << ", S: " << player.pokedex[active_index].getSpeed() << ", M: " << player.pokedex[active_index].getMax() << endl;

          int enemy_result = enemyPokemon.getAttack() - player.pokedex[active_index].getDefense();
          if(enemy_result < 0)
          {
            enemy_result = 0;
          }
          cout << enemyPokemon.getName() << " dealt " << enemy_result << " damage!" << endl;
          player.pokedex[active_index].setCurrentHP(player.pokedex[active_index].getCurrentHP() - enemy_result); //calculate damage

          if(player.pokedex[active_index].getCurrentHP() <= 0) //if pokemon faints, select new active pokemon
          {
            player.pokedex[active_index].setActive(false);
            enemyPokemon.addLevel();
            int alive = 0;
            for(int i = 0; i < player.pokedex.size(); i++)
            {
              if(player.pokedex[i].getCurrentHP() > 0)
              {
                alive++;
              }
            }
            if(alive == 0)
            {
              return 2;
            }
            cout << endl;
            cout << "Your pokemon has fainted! The following Pokémon are in your active party. Choose one of them to be your Active Pokémon:" << endl;
            player.displayParty();
            int input_change;
            cin >> input_change;
            input_change--;
            int matchID = 0;
            for(int j = 0; j < player.pokedex.size(); j++)
            {
              if(player.pokedex[j].isPartyMember() && (input_change == matchID) && player.pokedex[j].getCurrentHP() > 0) //match index to matches
              {
                player.pokedex[j].setActive(true);
                active_index = j;
                matchID++;
              }
              else if(player.pokedex[j].isPartyMember() && player.pokedex[j].getCurrentHP() > 0)
              {
                matchID++;
              }
            }

          }
        }
        else
        {
          //enemy attack phase
          int enemy_result = enemyPokemon.getAttack() - player.pokedex[active_index].getDefense();
          if(enemy_result < 0)
          {
            enemy_result = 0;
          }
          cout << enemyPokemon.getName() << " dealt " << enemy_result << " damage!" << endl;
          player.pokedex[active_index].setCurrentHP(player.pokedex[active_index].getCurrentHP() - enemy_result); //calculate damage
          if(player.pokedex[active_index].getCurrentHP() <= 0) //if pokemon faints, select new active pokemon
          {
            player.pokedex[active_index].setActive(false);
            enemyPokemon.addLevel();
            int alive = 0;
            for(int i = 0; i < player.pokedex.size(); i++)
            {
              if(player.pokedex[i].getCurrentHP() > 0)
              {
                alive++;
              }
            }
            if(alive == 0)
            {
              return 2;
            }
            cout << endl;
            cout << "Your pokemon has fainted! The following Pokémon are in your active party. Choose one of them to be your Active Pokémon:" << endl;
            player.displayParty();
            int input_change;
            cin >> input_change;
            input_change--;
            int matchID = 0;
            for(int j = 0; j < player.pokedex.size(); j++)
            {
              if(player.pokedex[j].isPartyMember() && (input_change == matchID) && player.pokedex[j].getCurrentHP() > 0) //match index to matches
              {
                player.pokedex[j].setActive(true);
                active_index = j;
                matchID++;
              }
              else if(player.pokedex[j].isPartyMember() && player.pokedex[j].getCurrentHP() > 0)
              {
                matchID++;
              }
            }
          }

          cout << "Name: " << enemyPokemon.getName() << " HP: " << enemyPokemon.getCurrentHP() << ", A: " << enemyPokemon.getAttack() << ", D: " << enemyPokemon.getDefense() << ", S: " << enemyPokemon.getSpeed() << ", M: " << enemyPokemon.getMax() << endl;
          cout << endl;
          cout << "Name: " << player.pokedex[active_index].getName() << " HP: " << player.pokedex[active_index].getCurrentHP() << ", A: " << player.pokedex[active_index].getAttack() << ", D: " << player.pokedex[active_index].getDefense() << ", S: " << player.pokedex[active_index].getSpeed() << ", M: " << player.pokedex[active_index].getMax() << endl;
          //player attack phase
          int result = player.pokedex[active_index].getAttack() - enemyPokemon.getDefense();
          if(result < 0)
          {
            result = 0;
          }
          cout << player.pokedex[active_index].getName() << " dealt " << result << " damage!" << endl;
          enemyPokemon.setCurrentHP(enemyPokemon.getCurrentHP() - result); //calculate damage
          if(enemyPokemon.getCurrentHP() <= 0)
          {
            player.pokedex[active_index].addLevel();
            return 1;
          }

        }
      }
      else if(choice == 2)
      {
        int alive = 0;
        for(int i = 0; i < player.pokedex.size(); i++)
        {
          if(player.pokedex[i].getCurrentHP() > 0)
          {
            alive++;
          }
        }
        if(alive == 0)
        {
          return 2;
        }
        cout << endl;
        cout << "The following Pokémon are in your active party. Choose one of them to be your Active Pokémon:" << endl;
        player.displayParty();
        int input_change;
        cin >> input_change;
        input_change--;
        int matchID = 0;
        for(int j = 0; j < player.pokedex.size(); j++) //reset all actives
        {
          player.pokedex[j].setActive(false);
          }
        for(int j = 0; j < player.pokedex.size(); j++)
        {
          if(player.pokedex[j].isPartyMember() && (input_change == matchID) && player.pokedex[j].getCurrentHP() > 0) //match index to matches
          {
            player.pokedex[j].setActive(true);
            active_index = j;
            matchID++;
          }
          else if(player.pokedex[j].isPartyMember() && player.pokedex[j].getCurrentHP() > 0)
          {
            matchID++;
          }
        }
      }
      else if(choice == 3)
      {
        flee_attempts++;
        int a = player.pokedex[active_index].getSpeed();
        cout << "A: " << a << endl;
        //calculate B
        int enemySpeed = enemyPokemon.getSpeed();
        int b = (enemySpeed / 4) % 256;
        cout << "B: " << b << endl;
        cout << "C: " << flee_attempts << endl;
        int f = ((a*32)/b) + 30 * flee_attempts; //f formula
        cout << "F: " << f << endl;
        if(f > 255)
        {
          return 4;
        }
        else
        {
          int rand_num = rand() % 256;
          if(rand_num < f)
          {
            return 4;
          }
        }
      }
    }
  }
}

void Events::wildPokemonBattleCheck(Trainer& player, Map& map, vector<Pokemon> loadedPokemon)
{
  int low_cord = player.getRow() - 2;
  int up_cord = player.getRow() + 2;
  int right_cord = player.getColumn() + 2;
  int left_cord = player.getColumn() - 2;

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

  srand(time(NULL));
  bool ran = false; //this only runs once!
  for(int i = low_cord; i <= up_cord; i++)
  {
    for(int j = left_cord; j <= right_cord; j++)
    {
      if((map.map[i][j] == 'P') && (ran == false)) //only run once
      {
        int wild_poke = rand() % 151;
        if(player.pokedex.size() > 2)
        {
          int result = wildBattle(player, loadedPokemon[wild_poke]);
          ran = true;
          if(result == 1)
          {
            map.map[i][j] = 'p';
            player.addPoints(10);
            player.subtractPokeball();
            loadedPokemon[wild_poke].setCurrentHP(loadedPokemon[wild_poke].getHP());
            player.addPokemon(loadedPokemon[wild_poke], player);
          }
          else if((result == 2) || result == 4)
          {
            //nearest pokemon center
            int low_cord = player.getRow() - 2;
            int up_cord = player.getRow() + 2;
            int right_cord = player.getColumn() + 2;
            int left_cord = player.getColumn() - 2;
            bool found = false;
            //make sure all inputs are valid on the boundaries
            while(found != true)
            {
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
                if(map.map[i][j] == 'C')
                {
                  player.setColumn(i);
                  player.setRow(j);
                  found = true;
                  pokemonCenter(player);
                }
              }
            }
            //redefine boundaries and search again
            low_cord--;
            up_cord++;
            right_cord++;
            left_cord--;
          }
          }
          else if(result == 3)
          {
            //make enemy flee
            map.map[i][j] = 'p';
            bool selected = false;
            while(selected != true)
            {
            int rand_row = rand() % 25;
            int rand_column = rand() % 16;
            if((map.map[rand_row][rand_column] != 'C') && (map.map[rand_row][rand_column] != 'w') && (map.map[rand_row][rand_column] != 'G') && (map.map[rand_row][rand_column] != 'P'))
            {
              map.map[rand_row][rand_column] = 'P';
              cout << "Pokemon fled to row: " << rand_row << " column: " << rand_column << endl;
              selected = true;
            }
          }
          }
        }
        else
        {
          map.map[i][j] = 'p';
          cout << loadedPokemon[wild_poke].getName() << " is among the first to join your party!" << endl;
          player.addPoints(10);
          player.subtractPokeball();
          player.addPokemon(loadedPokemon[wild_poke], player);
          ran = true;
        }
      }
      else
      {
        ;
      }
    }
  }
}
//GYM BATTLE
int Events::gymBattle(Trainer& player, Pokemon& enemyPokemon)
{
  int active_index;
  //int flee_attempts = 0;
  for(int i = 0; i < player.pokedex.size(); i++) //get active index
  {
    if(player.pokedex[i].isActive())
    {
      active_index = i;
    }
  }
    while((player.pokedex[active_index].getCurrentHP() > 0) && (enemyPokemon.getCurrentHP() > 0)) //main loop
    {
      cout << "Name: " << enemyPokemon.getName() << " HP: " << enemyPokemon.getCurrentHP() << ", A: " << enemyPokemon.getAttack() << ", D: " << enemyPokemon.getDefense() << ", S: " << enemyPokemon.getSpeed() << ", M: " << enemyPokemon.getMax() << endl;
      cout << endl;
      cout << "Your ACTIVE Pokémon is:" << endl;
      cout << "Name: " << player.pokedex[active_index].getName() << " HP: " << player.pokedex[active_index].getCurrentHP() << ", A: " << player.pokedex[active_index].getAttack() << ", D: " << player.pokedex[active_index].getDefense() << ", S: " << player.pokedex[active_index].getSpeed() << ", M: " << player.pokedex[active_index].getMax() << endl;
      cout << endl;
      cout << "What do you want to do? (Pick 1, 2, or 3)" << endl;
      cout << "1. Fight" << endl;
      cout << "2. Switch Active ​Pokémon" << endl;
      cout << "3. Run" << endl;
      int choice;
      cin >> choice;
      if(choice == 1)
      {
        int enemySpeed = enemyPokemon.getSpeed();
        int playerSpeed = player.pokedex[active_index].getSpeed();
        if(playerSpeed >= enemySpeed)
        {
          //player attack phase
          int result = player.pokedex[active_index].getAttack() - enemyPokemon.getDefense();
          if(result < 0)
          {
            result = 0;
          }
          cout << player.pokedex[active_index].getName() << " dealt " << result << " damage!" << endl;
          enemyPokemon.setCurrentHP(enemyPokemon.getCurrentHP() - result); //calculate damage
          if(enemyPokemon.getCurrentHP() <= 0)
          {
            player.pokedex[active_index].addLevel();
            return 1;
          }
          //enemy attack phase
          cout << "Name: " << enemyPokemon.getName() << " HP: " << enemyPokemon.getCurrentHP() << ", A: " << enemyPokemon.getAttack() << ", D: " << enemyPokemon.getDefense() << ", S: " << enemyPokemon.getSpeed() << ", M: " << enemyPokemon.getMax() << endl;
          cout << endl;
          cout << "Name: " << player.pokedex[active_index].getName() << " HP: " << player.pokedex[active_index].getCurrentHP() << ", A: " << player.pokedex[active_index].getAttack() << ", D: " << player.pokedex[active_index].getDefense() << ", S: " << player.pokedex[active_index].getSpeed() << ", M: " << player.pokedex[active_index].getMax() << endl;

          int enemy_result = enemyPokemon.getAttack() - player.pokedex[active_index].getDefense();
          if(enemy_result < 0)
          {
            enemy_result = 0;
          }
          cout << enemyPokemon.getName() << " dealt " << enemy_result << " damage!" << endl;
          player.pokedex[active_index].setCurrentHP(player.pokedex[active_index].getCurrentHP() - enemy_result); //calculate damage

          if(player.pokedex[active_index].getCurrentHP() <= 0) //if pokemon faints, select new active pokemon
          {
            player.pokedex[active_index].setActive(false);
            enemyPokemon.addLevel();
            int alive = 0;
            for(int i = 0; i < player.pokedex.size(); i++)
            {
              if(player.pokedex[i].getCurrentHP() > 0)
              {
                alive++;
              }
            }
            if(alive == 0)
            {
              return 2;
            }
            cout << endl;
            cout << "Your pokemon has fainted! The following Pokémon are in your active party. Choose one of them to be your Active Pokémon:" << endl;
            player.displayParty();
            int input_change;
            cin >> input_change;
            input_change--;
            int matchID = 0;
            for(int j = 0; j < player.pokedex.size(); j++)
            {
              if(player.pokedex[j].isPartyMember() && (input_change == matchID) && player.pokedex[j].getCurrentHP() > 0) //match index to matches
              {
                player.pokedex[j].setActive(true);
                active_index = j;
                matchID++;
              }
              else if(player.pokedex[j].isPartyMember() && player.pokedex[j].getCurrentHP() > 0)
              {
                matchID++;
              }
            }

          }
        }
        else
        {
          //enemy attack phase
          int enemy_result = enemyPokemon.getAttack() - player.pokedex[active_index].getDefense();
          if(enemy_result < 0)
          {
            enemy_result = 0;
          }
          cout << enemyPokemon.getName() << " dealt " << enemy_result << " damage!" << endl;
          player.pokedex[active_index].setCurrentHP(player.pokedex[active_index].getCurrentHP() - enemy_result); //calculate damage
          if(player.pokedex[active_index].getCurrentHP() <= 0) //if pokemon faints, select new active pokemon
          {
            player.pokedex[active_index].setActive(false);
            enemyPokemon.addLevel();
            int alive = 0;
            for(int i = 0; i < player.pokedex.size(); i++)
            {
              if(player.pokedex[i].getCurrentHP() > 0)
              {
                alive++;
              }
            }
            if(alive == 0)
            {
              return 2;
            }
            cout << endl;
            cout << "Your pokemon has fainted! The following Pokémon are in your active party. Choose one of them to be your Active Pokémon:" << endl;
            player.displayParty();
            int input_change;
            cin >> input_change;
            input_change--;
            int matchID = 0;
            for(int j = 0; j < player.pokedex.size(); j++)
            {
              if(player.pokedex[j].isPartyMember() && (input_change == matchID) && player.pokedex[j].getCurrentHP() > 0) //match index to matches
              {
                player.pokedex[j].setActive(true);
                active_index = j;
                matchID++;
              }
              else if(player.pokedex[j].isPartyMember() && player.pokedex[j].getCurrentHP() > 0)
              {
                matchID++;
              }
            }
          }

          cout << "Name: " << enemyPokemon.getName() << " HP: " << enemyPokemon.getCurrentHP() << ", A: " << enemyPokemon.getAttack() << ", D: " << enemyPokemon.getDefense() << ", S: " << enemyPokemon.getSpeed() << ", M: " << enemyPokemon.getMax() << endl;
          cout << endl;
          cout << "Name: " << player.pokedex[active_index].getName() << " HP: " << player.pokedex[active_index].getCurrentHP() << ", A: " << player.pokedex[active_index].getAttack() << ", D: " << player.pokedex[active_index].getDefense() << ", S: " << player.pokedex[active_index].getSpeed() << ", M: " << player.pokedex[active_index].getMax() << endl;
          //player attack phase
          int result = player.pokedex[active_index].getAttack() - enemyPokemon.getDefense();
          if(result < 0)
          {
            result = 0;
          }
          cout << player.pokedex[active_index].getName() << " dealt " << result << " damage!" << endl;
          enemyPokemon.setCurrentHP(enemyPokemon.getCurrentHP() - result); //calculate damage
          if(enemyPokemon.getCurrentHP() <= 0)
          {
            player.pokedex[active_index].addLevel();
            return 1;
          }

        }
      }
      else if(choice == 2)
      {
        int alive = 0;
        for(int i = 0; i < player.pokedex.size(); i++)
        {
          if(player.pokedex[i].getCurrentHP() > 0)
          {
            alive++;
          }
        }
        if(alive == 0)
        {
          return 2;
        }
        cout << endl;
        cout << "The following Pokémon are in your active party. Choose one of them to be your Active Pokémon:" << endl;
        player.displayParty();
        int input_change;
        cin >> input_change;
        input_change--;
        int matchID = 0;
        for(int j = 0; j < player.pokedex.size(); j++) //reset all actives
        {
          player.pokedex[j].setActive(false);
          }
        for(int j = 0; j < player.pokedex.size(); j++)
        {
          if(player.pokedex[j].isPartyMember() && (input_change == matchID) && player.pokedex[j].getCurrentHP() > 0) //match index to matches
          {
            player.pokedex[j].setActive(true);
            active_index = j;
            matchID++;
          }
          else if(player.pokedex[j].isPartyMember() && player.pokedex[j].getCurrentHP() > 0)
          {
            matchID++;
          }
        }
      }
      else if(choice == 3)
      {
        cout << "You cannot flee from a gym battle!" << endl;
      }
    }
  }



/* Algorithm will generate a "gym" trainer on a square for the player to battle
  1. generate a Player object with randomized amount of pokemon between 1-6
  2. Call the battle function
  3. If successful, call addBadges()
  Input: none
  Returns: none
  Output: event dialogue
*/

void Events::Gym(Trainer& player, Map& map, vector<Trainer> &enemies)
{
  int enemy_index;
  int playerRow = player.getRow();
  int playerColumn = player.getColumn();
  for(int i = 0; i < enemies.size(); i++) //find the right index
  {
    if((enemies[i].getRow() == playerRow) && (enemies[i].getColumn() == playerColumn))
    {
      enemy_index = i;
    }
  }
  if(enemies[enemy_index].pokedex.size() == 0) //make sure the gym has been battled
  {
    cout << "You have already beaten this gym!" << endl;
    return;
  }
  cout << "You arrived at the gym and the trainer is there. They want to fight!" << endl;
  int numFight = enemies[enemy_index].pokedex.size() - 1;
  for(int j = 0; j < enemies[enemy_index].pokedex.size(); j++)
  {
    if(j == numFight)
    {
      cout << "You win!" << endl;
      for(int k = 0; k < enemies[enemy_index].pokedex.size(); k++)
      {
        enemies[enemy_index].pokedex[k].setCurrentHP(enemies[enemy_index].pokedex[k].getHP());
        player.addPokemon(enemies[enemy_index].pokedex[k], player);
      }
      enemies[enemy_index].pokedex.clear();
      player.addBadge();
      player.addPoints(60);
      player.addPokeballs(5);
      return;
    }
    int battle_result = gymBattle(player, enemies[enemy_index].pokedex[j]);
    if(battle_result == 1)
    {
      ;
    }
    else if(battle_result == 2)
    {
        //nearest pokemon center
        int low_cord = player.getRow() - 2;
        int up_cord = player.getRow() + 2;
        int right_cord = player.getColumn() + 2;
        int left_cord = player.getColumn() - 2;
        bool found = false;
        //make sure all inputs are valid on the boundaries
        while(found != true)
        {
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
            if(map.map[i][j] == 'C')
            {
              player.setColumn(i);
              player.setRow(j);
              found = true;
              pokemonCenter(player);
              return;
            }
          }
        }
        //redefine boundaries and search again
        low_cord--;
        up_cord++;
        right_cord++;
        left_cord--;
      }
    }

  }
}
/* Algorithm will handle movement around map
  1. present movement options to player
  2. check if movement is valid, if it is then execute
  Input: none
  Returns: none
  Output: event dialogue
*/
void Events::Travel(Trainer& player, Map map, vector<Trainer> &enemies)
{
  bool traveled = false;
  //travel logic in any direction once per turn
  while(traveled != true)
  {
  cout << "Which direction would you like to travel? North (N), South(S), East(E), or West(W)" << endl;
  string response;
  cin >> response;
  if((response == "N") || (response == "North"))
  {
    int target_row = player.getRow() - 1;
    int target_column = player.getColumn();
    if((map.getCurrentTileType(target_row, target_column) != 'w') && (target_row > -1))
    {
      player.setRow(target_row);
      cout << "You traveled North!" << endl;
      if(map.getCurrentTileType(player.getRow(), player.getColumn()) == 'C')
      {
        pokemonCenter(player);
      }
      else if(map.getCurrentTileType(player.getRow(), player.getColumn()) == 'G')
      {
        Gym(player, map, enemies);
      }
      traveled = true;
    }
    else
    {
      cout << "You cannot travel onto water or out of bounds! Please try again." << endl;
    }
  }
  else if((response == "S") || (response == "South"))
  {
    int target_row = player.getRow() + 1;
    int target_column = player.getColumn();
    if((map.getCurrentTileType(target_row, target_column) != 'w') && (target_row < 25))
    {
      player.setRow(target_row);
      cout << "You traveled South!" << endl;
      if(map.getCurrentTileType(player.getRow(), player.getColumn()) == 'C')
      {
        pokemonCenter(player);
      }
      traveled = true;
    }
    else if(map.getCurrentTileType(player.getRow(), player.getColumn()) == 'G')
    {
      Gym(player, map, enemies);
    }
    else
    {
      cout << "You cannot travel onto water or out of bounds! Please try again." << endl;
    }
  }
  else if((response == "W") || (response == "West"))
  {
    int target_row = player.getRow();
    int target_column = player.getColumn() - 1;
    if((map.getCurrentTileType(target_row, target_column) != 'w') && (target_column > 0))
    {
      player.setColumn(target_column);
      cout << "You traveled West!" << endl;
      if(map.getCurrentTileType(player.getRow(), player.getColumn()) == 'C')
      {
        pokemonCenter(player);
      }
      else if(map.getCurrentTileType(player.getRow(), player.getColumn()) == 'G')
      {
        Gym(player, map, enemies);
      }
      traveled = true;
    }
    else
    {
      cout << "You cannot travel onto water or out of bounds! Please try again." << endl;
    }
  }
  else if((response == "E") || (response == "East"))
  {
    int target_row = player.getRow();
    int target_column = player.getColumn() + 1;
    if((map.getCurrentTileType(target_row, target_column) != 'w') && (target_column < 16))
    {
      player.setColumn(target_column);
      cout << "You traveled East!" << endl;
      if(map.getCurrentTileType(player.getRow(), player.getColumn()) == 'C')
      {
        pokemonCenter(player);
      }
      else if(map.getCurrentTileType(player.getRow(), player.getColumn()) == 'G')
      {
        Gym(player, map, enemies);
      }
      traveled = true;
    }
    else
    {
      cout << "You cannot travel onto water or out of bounds! Please try again." << endl;
    }
  }
  else
  {
    cout << "Please select a valid letter or word for movement!" << endl;
  }
}
}
