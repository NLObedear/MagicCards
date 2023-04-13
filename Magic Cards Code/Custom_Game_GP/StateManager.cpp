#pragma once
#include <iostream>
#include "GameStates.cpp"
#include "State.cpp"
#include "MainMenu.cpp"
#include "Quit.cpp"
#include "Play.cpp"
#include "SelectDeck.cpp"
#include "CreateDeck.cpp"
#include "ViewDecks.cpp"
#include "Renderer.cpp"


class StateManager {
private:
	MainMenu mainmenu;
	Quit quitgame;
	Play playgame;
	SelectDeck selectd;
	CreateDeck created;
	ViewDecks viewd;


	State* _current = &mainmenu;
	bool _running = true;
	GameStates _state = GameStates::MAIN_MENU;

	Renderer renderer;

public:
	bool running() const { return _state != GameStates::DONE; }
	void update() {
		if (_state == GameStates::MAIN_MENU) { _current = &mainmenu; }
		else if (_state == GameStates::PLAY) { _current = &playgame; }
		else if (_state == GameStates::SELECT_DECK) { _current = &selectd; }
		else if (_state == GameStates::VIEW_DECKS) { _current = &viewd; }
		else if (_state == GameStates::CREATE_DECK) { _current = &created; }
		else if (_state == GameStates::QUIT) { _current = &quitgame; }

		_state = _current->update();
	}
	void render() {
		if (_state == GameStates::MAIN_MENU) { _current = &mainmenu; }
		else if (_state == GameStates::PLAY) { _current = &playgame; }
		else if (_state == GameStates::SELECT_DECK) { _current = &selectd; }
		else if (_state == GameStates::VIEW_DECKS) { _current = &viewd; }
		else if (_state == GameStates::CREATE_DECK) { _current = &created; }
		else if (_state == GameStates::QUIT) { _current = &quitgame; }

		_current->render(&renderer);
	}

};