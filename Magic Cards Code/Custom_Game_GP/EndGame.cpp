#pragma once
#include <iostream>
#include "InGameStates.cpp"
#include "GameStates.cpp"

class EndGame : public InGameStates {
public:
	GameStates update(Field* enemyfield, PlayerHealth* enemyhp) override {
		return GameStates::DONE;
	}
	void render() override {
	//	cout << ">> Good Bye!" << endl;
	}

};