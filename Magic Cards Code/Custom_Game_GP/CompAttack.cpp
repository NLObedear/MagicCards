#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Command.cpp"
#include "MessagePost.cpp"

using namespace std;

class CompAttack : public Command {
public:
	virtual int execute(Hand* hand, Field* field, int mana, Field* enemyfield, PlayerHealth* enemyhp, Renderer* render) {
		rend = render;
		rend->PlayGame();
		rend->RenderEnemyHand(hand);
		rend->StatBox();
		rend->RenderEnemyField(field);
		rend->rend();
		int fieldsize = field->GetSize();
		int enemyfieldsize = enemyfield->GetSize();
		computer = hand->ReturnComputer();
		string input1, input2;
		while (!end) {
		//	cout << "Your minions: " << endl;
			field->printAttackDesc();
		//	cout << "-------------------------------------------------------------------" << endl;
		//	cout << "Enemy minions: " << endl;
			enemyfield->printDesc();
		//	cout << "-------------------------------------------------------------------" << endl;
		//	cout << "Choose a minion to attack with: " << endl;
		//	cout << "Select 1-" << fieldsize << ">: ";
			input1 = computer->Attack1(field);
			int in1 = stoi(input1);
			cout << endl;
			if (in1 > 0 && in1 <= fieldsize && field->CanAttack(in1 - 1)) {
		//		cout << "Enemy minions: " << endl;
				enemyfield->printDesc();
		//		cout << "Choose a minion to attack: " << endl;
		//		cout << "Select 1-" << enemyfieldsize << " Or choose 8 to attack enemy player" << ">: ";
				input2 = computer->Attack2(enemyfield);
				int in2 = stoi(input2);
				cout << endl;
				if (in2 > 0 && in2 <= enemyfieldsize) {
					// Handles minions attacking minions
					messenger.add(field, enemyfield, in1 - 1, in2 - 1);
					messenger.send();
					cout << "The Enemies " << field->GetChildName(in1 - 1) << " Took " << enemyfield->GetChildAttack(in2 - 1) << " Damage " << endl;
					cout << "Your " << enemyfield->GetChildName(in2 - 1) << " Took " << field->GetChildAttack(in1 - 1) << " Damage " << endl;
					if (field->GetChildHealth(in1 - 1) <= 0) {
						cout << "The Enemies " << field->GetChildName(in1 - 1) << " Died " << endl;
						field->remove(in1 - 1);
					}
					if (enemyfield->GetChildHealth(in2 - 1) <= 0) {
						cout << "Your " << enemyfield->GetChildName(in1 - 1) << " Died " << endl;
						enemyfield->remove(in2 - 1);
					}
					rend->PlayGame();
					rend->RenderEnemyHand(hand);
					rend->StatBox();
					rend->RenderEnemyField(field);
					rend->rend();
				}
				// Handles minions attacking heroes
				else if (in2 == 8) {
					field->SleepAMinion(in1 - 1);
					enemyhp->DamageHealth(field->GetChildAttack(in1 - 1));
					cout << "Your " << field->GetChildName(in1 - 1) << " Did " << field->GetChildAttack(in1 - 1) << " Damage to Enemy Hero" << endl;
					cout << "Enemy Hero at " << enemyhp->getHealth() << endl;
					if (enemyhp->getHealth() <= 0) {
						end = true;
					}
					rend->PlayGame();
					rend->RenderEnemyHand(hand);
					rend->StatBox();
					rend->RenderEnemyField(field);
					rend->rend();
				}
				else {
					cout << "That minion cannot attack! or your selection was incorrect" << endl;
				}
				if (!field->checkAttacks() || input2 == "back") {
					end = true;
				}
			}
			else {
				cout << "That minion cannot attack! or your selection was incorrect" << endl;
			}
		}
		end = false;
		return 0;
	}
private:
	Renderer* rend;
	ComputerLevel1* computer;
	MessagePost messenger;
	bool end = false;
};