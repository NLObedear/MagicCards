#pragma once
#include <iostream>
#include <map>
#include "Command.cpp"
#include "Hand.cpp"
#include "Field.cpp"
#include "PlayerHealth.cpp"
#include "Attack.cpp"
#include "PlayACard.cpp"
#include "CompPlayACard.cpp"
#include "CompAttack.cpp"
#include "Renderer.cpp"

class InputHandler
{
public:
	void MapCommands() {
		play1 = &play;
		attack1 = &attack;
		compplay1 = &compplay;
		compattack1 = &compattack;
		_commands["cattack"] = { compattack1 };
		_commands["cplay"] = { compplay1 };
		_commands["play"] = { play1 };
		_commands["Play"] = { play1 };
		_commands["attack"] = { attack1 };
		_commands["Attack"] = { attack1 };
	}
	int handleInput(string input, Hand* hand, Field* field, int mana, Field* enemyfield, PlayerHealth* enemyhealth, Renderer* render) {
		MapCommands();
		int result;
		if (_commands.count(input)) {
			result = _commands[input]->execute(hand, field, mana, enemyfield, enemyhealth, render);
			return result;
		}
		else {
			cout << "Your command was not valid" << endl;
			return 0;
		}
	}
private:
	CompAttack compattack;
	CompPlayACard compplay;
	PlayACard play;
	Attack attack;
	Command* attack1;
	Command* play1;
	Command* compplay1;
	Command* compattack1;
	map<string, Command*> _commands;
};