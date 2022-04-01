//
//  main.cpp
//
//  Project: UALR - Programming 2 - Spring 22 - Power Play 10
//  Created by: Mark McCorkle on 20220401
//  Based on: Code Provided by Sean Orme
//  IDE: CLion 2021.2.3     - UNVERIFIED
//  IDE: XCode              - UNVERIFIED
//  IDE: Visual Studio 2022 - VERIFIED
//  IDE: Linux via g++      - UNVERIFIED
//
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <map>

#include "Item.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"


void createMonsters(std::vector<Object*>& objects);

void displayBattle(const std::vector<Object*>& objects);
void bringOutYourDead(std::vector<Object*>& objects);


int main()
{
	std::vector<Object*> objects{ new Player() };
	while (objects.front()->getName() == Object::Type::player)
	{
		createMonsters(objects);

		std::cout << objects.size() - 1 << " monster(s) approaches!!" << std::endl;
		/*system("pause");
		system("cls");*/

		while (objects.size() > 1
			&& objects.front()->getName() == Object::Type::player)
		{
			bringOutYourDead(objects);
			if (objects.front()->getName() == Object::Type::player)
			{
				displayBattle(objects);
				std::cout << std::endl;
				std::for_each(objects.begin(), objects.end(), [&](Object* object)
					{
						object->update(objects);
					});

				system("PAUSE");
				system("CLS");
			}
		}
	}

	if (objects.size() == 0
		|| objects.front()->getName() != Object::Type::player)
	{
		std::cout << "You Have Died" << std::endl;
	}
	if (objects.size() == 0)
	{
		std::cout << "BUT" << std::endl;
	}
	if (objects.size() == 0
		|| objects.front()->getName() == Object::Type::player)
	{
		std::cout << "You have killed the monsters!!!" << std::endl;
	}
	system("PAUSE");

}

void displayBattle(const std::vector<Object*>& objects)
{
	Object::nameOnly = false;

	std::cout << *(objects.front()) << std::endl;
	std::cout << std::endl << "  Monsters: " << std::endl;
	{
		int i{ 1 };
		std::for_each(objects.begin() + 1, objects.end(), [&](const Object* monster)
			{
				std::cout << "   " << i << ". " << *monster << std::endl;

				i++;
			});
	}
}

void createMonsters(std::vector<Object*>& objects)
{
	std::normal_distribution<double> randomNumMonsters((double)objects.front()->getLevel(), objects.front()->getLevel() / 2.0);
	objects.resize(std::max(2, (int)randomNumMonsters(Object::engine)));
	std::generate(objects.begin() + 1, objects.end(), [&]()
		{
			return new Monster(objects.front());
		});
}

void bringOutYourDead(std::vector<Object*>& objects)
{
	Object::nameOnly = true;
	objects.erase(
		std::remove_if(objects.begin(), objects.end(),
			[](Object* object)
			{
				if (object->isDead())
				{

					std::cout << *object << " has died!!!" << std::endl << std::endl;
					return true;
				}
				return false;
			}),
		objects.end());

}