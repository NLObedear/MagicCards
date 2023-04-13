#pragma once
#include <iostream>
#include "GameStates.cpp"
#include "InGameStates.cpp"
#include "EndGame.cpp"
#include "PlayerTurn.cpp"
#include "ComputerTurn.cpp"


class InGameStateManager {
private:
	EndGame quitgame;
	PlayerTurn playert;
	ComputerTurn compt;
	Field* field;
	PlayerHealth* health;


	InGameStates* _current = nullptr;
	bool _running = true;
	GameStates _state = GameStates::MAIN_MENU;

public:
	bool running() const { return _state != GameStates::DONE; }
	void update() {
		if (_state == GameStates::PLAYER_TURN) { _current = &playert; field = compt.getField(); health = compt.getHealth(); }
		else if (_state == GameStates::COMPUTER_TURN) { _current = &compt; field = playert.getField(); health = playert.getHealth(); }
		else if (_state == GameStates::QUIT) {
			_current = &quitgame; 		
			PlayerTurn pt;
			playert = pt;
			ComputerTurn ct;
			compt = ct;
		}

		_state = _current->update(field, health);
	}
	void render() {
		if (_state == GameStates::PLAYER_TURN) { _current = &playert; }
		else if (_state == GameStates::COMPUTER_TURN) { _current = &compt; }
		else if (_state == GameStates::QUIT) { _current = &quitgame; }

		_current->render();
	}
	void SetSate(InGameStates* start) {
		_current = start;
		if (_current == &playert) {
			_state = GameStates::PLAYER_TURN;
		}
		else if (_current == &compt) {
			_state = GameStates::COMPUTER_TURN;
		}
	}
	PlayerTurn* setPlayer() {
		return &playert;
	}
	ComputerTurn* setComp() {
		return &compt;
	}
};