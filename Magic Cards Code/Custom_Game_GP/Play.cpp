#pragma once
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include "State.cpp"
#include "GameStates.cpp"
#include "LoadCards.cpp"
#include "Deck.cpp"
#include "Card.cpp"
#include "Field.cpp"
#include "PlayerTurn.cpp"
#include "ComputerTurn.cpp"
#include "InGameStateManager.cpp"
#include "Renderer.cpp"
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

class Play : public State {
public:
	GameStates update() override {
		while (manager.running()) {
			manager.render();
			manager.update();
		}
		Field f;
		fieldPlayer = f;
		fieldComp = f;
		return GameStates::MAIN_MENU;
	}
	void render(Renderer* renderer) override {
		rend = renderer;
		rend->PlayGame();
		rend->rend();
		cout << ">> Game Starting!" << endl;
		player = manager.setPlayer();
		computer = manager.setComp();
		player->SetRender(rend);
		computer->SetRender(rend);
		srand(int(time(0)));
		int random = rand() % 500 + 0;
		if (random % 2) {
			_current = player;
			playerstart = 1;
		//	cout << "Player" << endl;
		}
		else {
			_current = computer;
			computerstart = 1;
		//	cout << "Computer" << endl;
		}
		// Builds decks for both players
		manager.SetSate(_current);
		GetDeck(&deckPlayer, deckname);
		GetDeck(&deckComp, deckname);

		//Shuffles decks then does a start game setup;
		deckPlayer.shuffleDeck();
		deckComp.shuffleDeck();
		player->startGame(&deckPlayer,&fieldPlayer, playerstart);
		computer->startGame(&deckComp,&fieldComp, computerstart);
	}
private:
	InGameStates* _current = nullptr;
	InGameStateManager manager;
	PlayerTurn* player;
	ComputerTurn* computer;
	LoadCards load;
	Deck deckPlayer, deckComp;
	Field fieldPlayer, fieldComp;
	string deckname = "deck";
	Renderer* rend;
	int playerstart = 0, computerstart = 0;

	void GetDeck(Deck* deck, string deckname) {
		vector<string>* cardDetails = nullptr;
		load.ReadFile();
		load.LoadDeck(deckname);
		for (int i = 0; i < 30;i++) { // Builds the Deck
			cardDetails = load.buildDeck(i);
			if (cardDetails->size() == 4) { // Creates a card with no special
				Card* card = new Card(cardDetails->at(0), stoi(cardDetails->at(1)), stoi(cardDetails->at(2)), stoi(cardDetails->at(3)));
				deck->add(card);
			}
			else { // Creates a card with a special
				Card* card = new Card(cardDetails->at(0), cardDetails->at(4), stoi(cardDetails->at(1)), stoi(cardDetails->at(2)), stoi(cardDetails->at(3)));
				deck->add(card);
			}
			load.ClearCardDetails(); //Clears the card details so the indexes dont stack
		}
		//	deck.printDesc(); // Prints the deck
	}
};