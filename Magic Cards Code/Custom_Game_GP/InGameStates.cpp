#pragma once
#include <iostream>
#include "GameStates.cpp"
#include "Field.cpp"
#include "PlayerHealth.cpp"

using namespace std;

// class GameManager;

class InGameStates {
protected:
	// 	GameManager* _manager = nullptr;
public:
	virtual GameStates update(Field*, PlayerHealth*) = 0;
	virtual void render() = 0;
};