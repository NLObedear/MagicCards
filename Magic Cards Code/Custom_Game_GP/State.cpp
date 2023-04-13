#pragma once
#include <iostream>
#include "GameStates.cpp"
#include "Renderer.cpp"

using namespace std;

// class GameManager;

class State {
protected:
	// 	GameManager* _manager = nullptr;
public:
	virtual GameStates update() = 0;
	virtual void render(Renderer*) = 0;
};