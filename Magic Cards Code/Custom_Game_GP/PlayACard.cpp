#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Command.cpp"

using namespace std;

class PlayACard : public Command {
public:
	virtual int execute(Hand* hand, Field* field, int mana, Field* enemyfield, PlayerHealth* enemyhp, Renderer* render) {
		int command = 0;
		rend = render;
		rend->PlayGame();
		rend->RenderHand(hand);
		rend->RenderField(field);
		rend->StatBox();
		rend->PlayMode();
		rend->rend();
		bool quit = false;
		while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == quit) {
					quit = true;
				}
				else {
					switch (e.key.keysym.sym) {
					case SDLK_1:
						if (hand->GetSize() >= 1) {
							if (hand->getCost(0) <= mana) {
								command = 0;
								quit = true;
							}
						}
						break;
					case SDLK_2:
						if (hand->GetSize() >= 2) {
							if (hand->getCost(1) <= mana) {
								command = 1;
								quit = true;
							}
						}
						break;
					case SDLK_3:
						if (hand->GetSize() >= 3) {
							if (hand->getCost(2) <= mana) {
								command = 2;
								quit = true;
							}
						}
						break;
					case SDLK_4:
						if (hand->GetSize() >= 4) {
							if (hand->getCost(3) <= mana) {
								command = 3;
								quit = true;
							}
						}
						break;
					case SDLK_5:
						if (hand->GetSize() >= 5) {
							if (hand->getCost(4) <= mana) {
								quit = true;
								command = 4;
							}
						}
						break;
					case SDLK_6:
						if (hand->GetSize() >= 6) {
							if (hand->getCost(5) <= mana) {
								command = 5;
								quit = true;
							}
						}
						break;
					case SDLK_7:
						if (hand->GetSize() >= 7) {
							if (hand->getCost(6) <= mana) {
								command = 6;
								quit = true;
							}
						}
						break;
					case SDLK_8:
						if (hand->GetSize() >= 8) {
							if (hand->getCost(7) <= mana) {
								command = 7;
								quit = true;
							}
						}
						break;
					case SDLK_9:
						if (hand->GetSize() >= 9) {
							if (hand->getCost(8) <= mana) {
								quit = true;
								command = 8;
							}
						}
						break;
					case SDLK_0:
						if (hand->GetSize() >= 10) {
							if (hand->getCost(9) <= mana) {
								command = 9;
								quit = true;
							}
						}
						break;
					}
				}
			}
		}
		if (command >= 0 ) {
			int cost = hand->getCost(command);
			field->add(hand->addToField(command));
			cout << "Field now contains: " << endl;
			rend->PlayGame();
			rend->RenderHand(hand);
			rend->StatBox();
			rend->RenderField(field);
			rend->rend();
			SDL_Delay(50);
			return cost;
		}
		else {
			cout << "Enter a valid number" << endl;
			return 0;
		}
	}
private:
	SDL_Event e;
	Renderer* rend;
};