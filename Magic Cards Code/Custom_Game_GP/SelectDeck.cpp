#pragma once
#include <iostream>
#include "State.cpp"
#include "GameStates.cpp"

class SelectDeck : public State {
public:
	GameStates update() override {
		return GameStates::PLAY;
	}
	void render(Renderer* renderer) override {
		cout << ">> Currently cannot Select a Deck" << endl;
	}

};