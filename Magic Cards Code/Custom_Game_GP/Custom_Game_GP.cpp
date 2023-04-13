#pragma once
#include <iostream>
#include "StateManager.cpp"
#include "MainMenu.cpp"

using namespace std;


int main(int argc, char* args[])
{

	StateManager manager;

	while (manager.running()) {
		manager.render();
		manager.update();
	}
	return 0;
}
