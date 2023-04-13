#pragma once
#include <iostream>
#include "State.cpp"
#include "GameStates.cpp"

class Quit : public State {
public:
	GameStates update() override {
		return GameStates::DONE;
	}
	void render(Renderer* renderer) override {
		cout << ">> Good Bye!" << endl;
	}

};