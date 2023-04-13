#pragma once
#include <iostream>
#include "State.cpp"
#include "GameStates.cpp"
#include "Renderer.cpp"
using namespace std;

class MainMenu : public State {
public:
	GameStates update() override {
	/*	string command;
		cin >> command;
		cout << endl;
		if (command == "1")
		{
			return GameStates::SELECT_DECK;
		}
		else if (command == "2")
		{
			return GameStates::VIEW_DECKS;
		}
		else if (command == "3")
		{
			return GameStates::CREATE_DECK;
		}
		else if (command == "4")
		{
			return GameStates::QUIT;
		}
		else
		{
			return GameStates::MAIN_MENU;
		} */
		while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == quit) {
					quit = true;
				}
				else  {
					switch (e.type) {
					case SDL_MOUSEBUTTONDOWN:
						SDL_GetMouseState(&x, &y);
						buttonclick = rend->MenuCheck(x, y);
						if (buttonclick == 1) {
							return GameStates::SELECT_DECK;
						}
						else if (buttonclick == 2) {
							return GameStates::VIEW_DECKS;
						}
						else if (buttonclick == 3) {
							return GameStates::CREATE_DECK;
						}
						break;
					}
				}
			}
		}
	}
	void render(Renderer* renderer) override {
		cout << "Magic Cards :: Main Menu" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << endl << "Welcome to Magic Cards" << endl;
		cout << "	" << "1. Select to Play" << endl;
		cout << "	" << "2. View Decks" << endl;
		cout << "	" << "3. Create Deck" << endl;
		cout << "	" << "4. Quit" << endl;
		cout << endl << "Select 1-4:> ";   
		renderer->MainMenu();
	}
private:
	SDL_Event e;
	Renderer* rend;
	int x, y;
	int buttonclick;
	bool quit = false;
};