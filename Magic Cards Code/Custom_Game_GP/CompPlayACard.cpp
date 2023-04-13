#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Command.cpp"
#include "ComputerLevel1.cpp"

using namespace std;

class CompPlayACard : public Command {
public:
	virtual int execute(Hand* hand, Field* field, int mana, Field* enemyfield, PlayerHealth* enemyhp, Renderer* render) {
		string command;
		rend = render;
		computer = hand->ReturnComputer();
		//cout << "Which card do you wish to play?" << endl;
		map<int, int> positions = hand->PrintPlayableCards(mana);
		//cout << "Select 1-" << positions.size() << ":> ";
		command = computer->PlayACard(&positions);
		cout << endl;
		if (stoi(command) > 0 && stoi(command) <= positions.size()) {
			int cost = hand->getCost(positions[stoi(command)]);
			field->add(hand->addToField(positions[stoi(command)]));
			cout << "Field now contains: " << endl;
			field->printDesc();
			rend->PlayGame();
			rend->RenderEnemyHand(hand);
			rend->StatBox();
			rend->RenderEnemyField(field);
			rend->rend();
			return cost;
		}
		else {
			cout << "Computer didn't Enter a valid number" << endl;
			return 0;
		}
	}
private:
	Renderer* rend;
	ComputerLevel1* computer;

};