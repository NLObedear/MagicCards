#pragma once
#include <iostream>
#include "InGameStates.cpp"
#include "Deck.cpp"
#include "Card.cpp"
#include "Hand.cpp"
#include "Field.cpp"
#include "GameStates.cpp"
#include "InputHandler.cpp"
#include "PlayerHealth.cpp"
#include "Renderer.cpp"

class PlayerTurn : public InGameStates {
public:
	GameStates update(Field* enemyfield, PlayerHealth* enemyhp) override {
		string command;
		int count = 1, coutput, x, y, buttonclick;
		bool play = false, attack = false, quit = false;
		map<int, int> positions = hand.CheckPlayableCards(manaCurrent);
		while (!endturn) {
			rend->PlayGame();
			rend->RenderHand(&hand);
			rend->RenderField(field);
			rend->setStats(manaCurrent, manaTotal, deck->GetSize(), health.getHealth());
			rend->StatBox();
			rend->rend();
			positions = hand.CheckPlayableCards(manaCurrent);
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
			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == quit) {
						quit = true;
					}
					else {
						switch (e.type) {
						case SDL_MOUSEBUTTONDOWN:
							SDL_GetMouseState(&x, &y);
							buttonclick = rend->endturncheck(x, y);
							if (buttonclick == 1) {
								command = "end";
								quit = true;
							}
							break;
						}
						switch (e.key.keysym.sym) {
						case SDLK_1:
							if (play) {
								command = "play";
								quit = true;
							}
							else {
								rend->PlayGame();
								rend->RenderHand(&hand);
								rend->RenderField(field);
								rend->StatBox();
								rend->NoMana();
								rend->rend();
								SDL_Delay(500);
								rend->PlayGame();
								rend->RenderField(field);
								rend->RenderHand(&hand);
								rend->StatBox();
								rend->rend();
							}
							break;
						case SDLK_2:
							if (attack) {
								command = "attack";
								quit = true;
							}
							else {
								rend->PlayGame();
								rend->RenderHand(&hand);
								rend->RenderField(field);
								rend->StatBox();
								rend->NoAttack();
								rend->rend();
								SDL_Delay(500);
								rend->PlayGame();
								rend->RenderField(field);
								rend->RenderHand(&hand);
								rend->StatBox();
								rend->rend();
							}
							break;
						}
					}
					SDL_Delay(150);
				}
			}
			if (command == "end" || command == "End") {
				return GameStates::COMPUTER_TURN;
			}
			else {
				coutput = input.handleInput(command, &hand, field, manaCurrent, enemyfield, enemyhp, rend);
				manaCurrent = manaCurrent - coutput;
				command = "";
				quit = false;
			}
			count = 1;
			if (health.getHealth() <= 0) {
				cout << "You are at 0 health you lose!! " << endl;
				return GameStates::QUIT;
			}
			else if (enemyhp->getHealth() <= 0) {
				cout << "The enemy is at 0 health you WIN!!!!" << endl;
				return GameStates::QUIT;
			}
		}
	}
	void render() override {
		cout << "----------------------------------------------------------------------------------" << endl;
		cout << ">> It is your turn!" << endl;
		hand.add(deck->addToHand());
		if (hand.GetSize() == 10) {
			deck->burn();
		}
		if (manaTotal == 9) {}
		else {
			manaTotal++;
		}
		manaCurrent = manaTotal;
		field->wakeAllMinions();
		rend->PlayGame();
		rend->RenderHand(&hand);
		rend->RenderField(field);
		rend->setStats(manaCurrent, manaTotal, deck->GetSize(), health.getHealth());
		rend->StatBox();
		rend->rend();
		cout << "Cards in hand" << " Health: " << health.getHealth() << " "<< " Mana: "<< manaCurrent << "/" << manaTotal << " Deck: "<< deck->GetSize() << endl;
		hand.printDesc();
		string none = "";
		if (field->GetSize() == 0) {
			none = " None";
		}
		cout << "Cards on field:" <<  none << endl;
		field->printDesc();
	}
	void startGame(Deck* deck1,Field* field1, int i) { // Draw starting Hand
		deck = deck1;
		field = field1;
		if (i == 0) {
			cout << "You go Second" << endl;
			for (int j = 0; j < 4;j++) {
				hand.add(deck->addToHand());
			}
		//	hand.printDesc();
		}
		else if (i == 1) {
			cout << "You go First" << endl;
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
	SDL_Event e;
	Renderer* rend;
	InputHandler input;
	Deck* deck;
	Field* field;
	Hand hand;
	bool endturn = false;
	PlayerHealth health;
	int manaTotal = 0, manaCurrent = 0;

};