#pragma once
#include <iostream>
#include "InGameStates.cpp"
#include "GameStates.cpp"
#include "Deck.cpp"
#include "Card.cpp"
#include "Field.cpp"
#include "Hand.cpp"
#include "InputHandler.cpp"
#include "PlayerHealth.cpp"
#include "ComputerLevel1.cpp"
#include "Renderer.cpp"

class ComputerTurn : public InGameStates {
public:
	GameStates update(Field* enemyfield, PlayerHealth* enemyhp) override {
		string command;
		int count = 1, coutput;
		bool play = false, attack = false;
		while (!endturn) {
			rend->PlayGame();
			rend->RenderEnemyHand(&hand);
			rend->RenderEnemyField(field);
			rend->esetStats(manaCurrent, manaTotal, deck->GetSize(), health.getHealth());
			rend->EnemyStatBox();
			rend->rend();
			map<int, int> positions = hand.CheckPlayableCards(manaCurrent);
			if (positions.size() != 0 && hand.GetSize() != 0) {
				play = true;
			}
			else {
				play = false;
			}
			if (field->GetSize() != 0 && field->checkAttacks()) {
				attack = true;
			}
			else {
				attack = false;
			}
			// Computer deciding
			command = computer.DecideAction1(play, attack);
			if (command == "end" || command == "End") {
				return GameStates::PLAYER_TURN;
			}
			else {
				coutput = input.handleInput(command, &hand, field, manaCurrent, enemyfield, enemyhp, rend);
				manaCurrent = manaCurrent - coutput;
			}
			if (health.getHealth() <= 0) {
				cout << "The enemy is at 0 health you WIN!!!!" << endl;
				return GameStates::QUIT;
			}
			else if (enemyhp->getHealth() <= 0) {
				cout << "You are at 0 health you lose!! " << endl;
				return GameStates::QUIT;
			}
		}
	}
	void render() override {
		cout << "----------------------------------------------------------------------------------" << endl;
		cout << ">> It is the computers turn!" << endl;
		hand.add(deck->addToHand());
		hand.GetComputer(&computer);
		computer.start();
		field->wakeAllMinions();
		if (hand.GetSize() == 10) {
			deck->burn();
		}
		if (manaTotal == 9) {}
		else {
			manaTotal++;
		}
		manaCurrent = manaTotal;
		rend->PlayGame();
		rend->RenderEnemyHand(&hand);
		rend->RenderEnemyField(field);
		rend->esetStats(manaCurrent, manaTotal, deck->GetSize(), health.getHealth());
		rend->EnemyStatBox();
		rend->rend();
		cout << "Opponents mana: " << " Health: " << health.getHealth() << " " << manaCurrent << "/" << manaTotal << " Deck: " << deck->GetSize() << endl;
		hand.printDesc();
		string none = "";
		if (field->GetSize() == 0) {
			none = " None";
		}
		cout << "Cards on field:" << none << endl;
		field->printDesc();
	}
	void startGame(Deck* deck1,Field* field1, int i) { //Draw Starting hHnd
		deck = deck1;
		field = field1;
		if (i == 0) {
			cout << "Computer goes Second" << endl;
			for (int j = 0; j < 4;j++) {
				hand.add(deck->addToHand());
			}
		//	hand.printDesc();
		}
		else if (i == 1) {
			cout << "Computer goes First" << endl;
			for (int j = 0; j < 3;j++) {
				hand.add(deck->addToHand());
			}
		//	hand.printDesc();
		}
	}
	Field* getField() {
		return field;
	}
	PlayerHealth* getHealth() {
		return &health;
	}
	void SetRender(Renderer* render) {
		rend = render;
	}
private:
	Renderer* rend;
	ComputerLevel1 computer;
	InputHandler input;
	Deck* deck;
	Field* field;
	Hand hand;
	bool endturn = false;
	PlayerHealth health;
	int manaTotal = 0, manaCurrent = 0;
};