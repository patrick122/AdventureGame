// chpt 8 q3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <vector>

class Character {

private:
	std::string m_characterType;
	std::string m_name;
	int m_hit_points;
	int m_level;
	int m_min_attack;
	int m_max_attack;
	

public:
	Character(std::string characterType, std::string name, int hit_points, int level, int min_attack, int max_attack) :
		m_characterType(characterType), m_name(name), m_hit_points(hit_points), m_level(level),m_min_attack(min_attack), m_max_attack(max_attack)
	{
	}


	void print()
	{
		std::cout << m_name << " the " << m_characterType <<" is level "<< m_level<< " and has " << m_hit_points << " hit points \n";
	}

	std::string GetCharacterType() {
		
		return m_characterType;

	}

	int Characterhealth() {
		return m_hit_points;
	}

	int CurrentLevel(){
		return m_level;
	}

	void WinBonus() {
		
		m_level += 1;
	}

	void AttackBonus() {
		m_hit_points += 5;
		m_min_attack += 1;
		m_max_attack += 1;
	}

	std::vector<int> GetCharAttackRange() {
		return { m_min_attack, m_max_attack };
	}
};


class CharacterChoice 
{
public:

	static Character ChooseCharacter() {

		std::cout << "Please name your character (no spaces) \n";

		std::string characterName;

		std::cin >> characterName;
		std::cin.ignore(32767, '\n');

		while (true) {

			std::cout << "Please Choose a class: \nKnight (hit points: 20, attack range: 0-6 \nWizard (hit points: 10, attack range: 2-4 \nRanger (hit points: 15, attack range: 1-5 \n";

			std::string charactertype;

			std::cin >> charactertype;
			std::cin.ignore(32767, '\n');

			if (charactertype == "Knight" || charactertype == "knight") {

				return Character("Knight", characterName, 20,1,0,6);
			}

			else if (charactertype == "Wizard" || charactertype == "wizard") {

				return Character("Wizard", characterName, 10,1,2,4);
			}
			else if (charactertype == "Ranger" || charactertype=="ranger") {

				return Character("Ranger", characterName, 15,1,1,5);
			}
			else {
				std::cin.clear();
				std::cout << "Oops, that input is invalid.  Please try again.\n";
			}
		}
	}
};

class Monster
{
public:
	enum MonsterType
	{
		Dragon,
		Goblin,
		Ogre,
		Orc,
		Skeleton,
		Troll,
		Vampire,
		Zombie,
		MAX_MONSTER_TYPES
	};

private:
	MonsterType m_monsterType;
	std::string m_name;
	std::string m_roar;
	int			m_hit_points;
	int m_min_attack;
	int m_max_attack;

public:
	Monster(MonsterType monsterType, std::string name, std::string roar, int hit_points, int min_attack, int max_attack) :
		m_monsterType(monsterType), m_name(name), m_roar(roar), m_hit_points(hit_points),m_min_attack(min_attack),m_max_attack(max_attack)
	{
	}

	std::string FindMonsterType(const MonsterType &monstertype)
	{
		switch (monstertype)
		{
		case Dragon:	return "Dragon";
		case Goblin:	return "Goblin";
		case Ogre:		return "Ogre";
		case Orc:		return "Orc";
		case Skeleton:  return "Skeleton";
		case Troll:		return "Troll";
		case Vampire:	return "Vampire";
		case Zombie:	return "Zombie";
		}
		return "???";
	}

	void print()
	{
		std::cout << m_name << " the " << FindMonsterType(m_monsterType) << " with " << m_hit_points << " hit points and says " << m_roar << "\n";
	}

	int MonsterHealth() {
		return m_hit_points;
	}

	std::vector<int> GetMonAttackRange() {
		return{ m_min_attack, m_max_attack };
	}

};

class MonsterGenerator
{
public:

	static int getRandomNumber(int min, int max)
	{
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  // static used for efficiency, so we only calculate this value once
																					 // evenly distribute the random number across our range
		return static_cast<int>(rand() * fraction * (max - min + 1) + min);
	}

	static Monster generateMonster(int win_counter, bool win_checker)
	{
		Monster::MonsterType monstertype = static_cast<Monster::MonsterType>(getRandomNumber(0, Monster::MAX_MONSTER_TYPES - 1));

		static int min=1; //min hit points 
		static int max=20; // max hit points 
		int hit_points;
		static int MonsterLvel = 1;
		static int min_attack = 0; //min attack
		static int max_attack = 3; //max attack


		//Check what level the character is, if divisible by 3 monsters hit points increase
		if (win_counter%3 == 0 && win_checker==true) {
			MonsterLvel += 1;
			std::cout << "\n";
			std::cout << "You are fighting monsters at level " << MonsterLvel << " ";
			min += 10;
			max += 5;
			min_attack += 1;
			max_attack += 1;
			std::cout << "with attack range " << min_attack << " - " << max_attack << "\n \n";
			hit_points = getRandomNumber(min, max);
		}
		else {
			std::cout << "\n";
			std::cout << "You are fighting monsters at level " << MonsterLvel <<" ";
			std::cout << "with attack range " << min_attack << " - " << max_attack << "\n \n";
			hit_points = getRandomNumber(min, max);
		}

		static std::string s_names[6]{ "Blarg", "Moog", "Pksh", "Tyrn", "Mort", "Hans" };
		static std::string s_sounds[6]{ "*ROAR*", "*peep*", "*squeal*", "*whine*", "*hum*", "*burp*" };

		return Monster(monstertype, s_names[getRandomNumber(0,5)], s_sounds[getRandomNumber(0,5)], hit_points, min_attack,max_attack);
	}	
};

std::string GetPlayerChoice() {

	while (true) // Loop until user enters a valid input
	{

		std::string choice;
		std::cin >> choice;
		std::cin.ignore(32767, '\n');


		if (choice=="fight" || choice=="run")
		{
			return choice;
		}
		else {
			std::cin.clear();
			std::cout << "Oops, that input is invalid.  Please type exactly how the command is spelled.\n";
		}
	}

}

bool fight(Character &p, Monster &m) {

	std::cout << "Get Ready to fight ";
	m.print();


	std::cout<< "Would like to fight or run?";

	std::string choice = GetPlayerChoice();

	std::cout << "\n";

	if (choice == "fight") {
		int MonsterHealth = m.MonsterHealth();
		int CharacterHealth = p.Characterhealth();
		

		while (true) {
			
			int CharacterAttack = MonsterGenerator::getRandomNumber(p.GetCharAttackRange()[0], p.GetCharAttackRange()[1]);
			int MonsterAttack = MonsterGenerator::getRandomNumber(m.GetMonAttackRange()[0], m.GetMonAttackRange()[1]);	

			CharacterHealth -= MonsterAttack;
			MonsterHealth -= CharacterAttack;

			std::cout << "You did " << CharacterAttack << " damage. " ;

			if (MonsterHealth <= 0) {
				std::cout << "The monster's health is now 0! You are victorious! \n";
				p.WinBonus();
				std::cout << "\n";
				return true;
			}			

			std::cout << "The monster's health is now " << MonsterHealth << "\n";
			std::cout << "\n";
			Sleep(2500);
			std::cout << "The monster did " << MonsterAttack<<" damage. ";

			if (CharacterHealth <= 0) {
				std::cout << "Your health is now 0! Sorry, you lose! \n";
				std::cout << "\n";
				return false;
			}
			std::cout << "Your health is now " << CharacterHealth << "\n";
			std::cout << "\n";
			Sleep(2500);						
		}		 
		
	}
	else if (choice == "run") {
		std::cout << "You ran away! \n";
		return false;
	}

	return false;
}

std::string getPlayerChoice()
{
	std::cout << "(y) to play another round, or (n) to end the game. ";
	
	while (true) {
		std::string choice;
		std::cin >> choice;
		std::cin.ignore(32767, '\n');
		if (choice == "yes" || choice == "y") {
			return "yes";
		}
		else if (choice == "no" || choice == "n") {
			return "no";
		}
		else {
			std::cin.clear();
			std::cout << "Oops, that input is invalid.  Please type either yes/y or no/n.\n";
		}
	}

}


int main()
{
	srand(static_cast<unsigned int>(time(0))); // set initial seed value to system clock
	rand(); // If using Visual Studio, discard first random value

	int win_counter = 1;
	bool win_checker = true;

	Character p = CharacterChoice::ChooseCharacter();
	p.print();

	double CharLevel = p.CurrentLevel();

	Monster m = MonsterGenerator::generateMonster(win_counter, win_checker);

	bool winStatus = fight(p, m);

	if (winStatus) {
		win_checker = true;
		++win_counter;
	}
	else {
		win_checker = false;
	}

	while (getPlayerChoice() != "no") {
		
		m = MonsterGenerator::generateMonster(win_counter, win_checker);
		
		winStatus = fight(p, m);
		if (winStatus) {
			win_checker = true;
			++win_counter;
			if (win_counter % 3 == 0) {
				p.AttackBonus();
				std::cout << "You leveled up! Your attack range is now " << p.GetCharAttackRange()[0] << " - " << p.GetCharAttackRange()[1] << " and you now have "<<p.Characterhealth()<<" hit points \n \n";
			}
		}
		else {
			win_checker = false;
		}
	}

	system("PAUSE");
	
    return 0;
}

