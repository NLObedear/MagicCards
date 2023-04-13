#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Command.cpp"
#include "MessagePost.cpp"

using namespace std;

class Attack : public Command {
public:
	virtual int execute(Hand* hand, Field* field, int mana, Field* enemyfield, PlayerHealth* enemyhp, Renderer* render) {
		bool end = false;
		int fieldsize = field->GetSize();
		int enemyfieldsize = enemyfield->GetSize();
		rend = render;
		bool quit = false;
		while (!end) {
		rend->PlayGame();
		rend->RenderHand(hand);
		rend->RenderField(field);
		rend->StatBox();
		rend->Attack1();
		rend->rend();
		int input1 = 9, input2 = 9;
			while (!quit) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == quit) {
						quit = true;
					}
					else {
						switch (e.key.keysym.sym) {
						case SDLK_1:
							if (field->GetSize() >= 1) {
								if (field->CanAttack(0)) {
									input1 = 1;
									quit = true;
								}
							}
							break;
						case SDLK_2:
							if (field->GetSize() >= 2) {
								if (field->CanAttack(1)) {
									input1 = 2;
									quit = true;
								}
							}
							break;
						case SDLK_3:
							if (field->GetSize() >= 3) {
								if (field->CanAttack(2)) {
									input1 = 3;
									quit = true;
								}
							}
							break;
						case SDLK_4:
							if (field->GetSize() >= 4) {
								if (field->CanAttack(3)) {
									input1 = 4;
									quit = true;
								}
							}
							break;
						case SDLK_5:
							if (field->GetSize() >= 5) {
								if (field->CanAttack(4)) {
									input1 = 5;
									quit = true;
								}
							}
							break;
						case SDLK_6:
							if (field->GetSize() >= 6) {
								if (field->CanAttack(5)) {
									input1 = 6;
									quit = true;
								}
							}
							break;
						case SDLK_7:
							if (field->GetSize() >= 7) {
								if (field->CanAttack(6)) {
									input1 = 7;
									quit = true;
								}
							}
							break;
						case SDLK_9:
							quit = true;
							end = true;
						}
					}
				}
			}
			SDL_Delay(1500);
			int in1 = input1;
			if (in1 >= 0 ) {
				rend->PlayGame();
				rend->RenderHand(hand);
				rend->RenderField(field);
				rend->StatBox();
				rend->Attack2();
				rend->rend();
				quit = false;
				while (!quit) {
					while (SDL_PollEvent(&f) != 0) {
						if (f.type == quit) {
							quit = true;
						}
						else {
							switch (f.key.keysym.sym) {
							case SDLK_1:
								if (enemyfield->GetSize() >= 1) {
										input2 = 1;
										quit = true;
								}
								break;
							case SDLK_2:
								if (enemyfield->GetSize() >= 2) {
										input2 = 2;
										quit = true;
								}
								break;
							case SDLK_3:
								if (enemyfield->GetSize() >= 3) {
										input2 = 3;
										quit = true;
								}
								break;
							case SDLK_4:
								if (enemyfield->GetSize() >= 4) {
										input2 = 4;
										quit = true;
								}
								break;
							case SDLK_5:
								if (enemyfield->GetSize() >= 5) {
										input2 = 5;
										quit = true;
								}
								break;
							case SDLK_6:
								if (enemyfield->GetSize() >= 6) {
										input2 = 6;
										quit = true;
								}
								break;
							case SDLK_7:
								if (enemyfield->GetSize() >= 7) {
										input2 = 7;
										quit = true;
								}
								break;
							case SDLK_8:
								input2 = 8;
								quit = true;
								break;
							case SDLK_9:
								quit = true;
								input2 = 9;
								break;
							}

						}
					}
				}
				int in2 = input2;
				cout << in2;
				if (in2 >= 0 && in2 <= enemyfieldsize) {
					// Handles minions attacking minions
					messenger.add(field, enemyfield, in1 - 1, in2 - 1);
					messenger.send();
					cout << "Your " << field->GetChildName(in1 - 1) << " Took " << enemyfield->GetChildAttack(in2 - 1) << " Damage " << endl;
					cout << "The Enemies " << enemyfield->GetChildName(in2 - 1) << " Took " << field->GetChildAttack(in1 - 1) << " Damage " << endl;
					if (field->GetChildHealth(in1 - 1) <= 0) {
						cout << "Your " << field->GetChildName(in1 - 1) << " Died " << endl;
						field->remove(in1 - 1);
					}
					if (enemyfield->GetChildHealth(in2 - 1) <= 0) {
						cout << "The Enemies " << enemyfield->GetChildName(in1 - 1) << " Died " << endl;
						enemyfield->remove(in2 - 1);
					}
					rend->PlayGame();
					rend->RenderHand(hand);
					rend->RenderField(field);
					rend->StatBox();
					rend->rend();
					quit = false;
				}
				// Handles minions attacking heroes
				else if (in2 == 8) {
					field->SleepAMinion(in1 - 1);
					enemyhp->DamageHealth(field->GetChildAttack(in1 - 1));
					cout << "Your " << field->GetChildName(in1 - 1) << " Did " << field->GetChildAttack(in1 - 1) << " Damage to Enemy Hero"<< endl;
					cout << "Enemy Hero at " << enemyhp->getHealth() << endl;
					if (enemyhp->getHealth() <= 0) {
						end = true;
					}
					rend->PlayGame();
					rend->RenderHand(hand);
					rend->RenderField(field);
					rend->StatBox();
					rend->rend();
					quit = false;
				}
				else if (in2 == 9) {
					end = true;
				}
				else {
					cout << "That minion cannot attack! or your selection was incorrect" << endl;
				}
			}
			else {
				cout << "That minion cannot attack! or your selection was incorrect" << endl;
			}
		}
		end = false;
		SDL_Delay(50);
		return 0;
	}
private:
	SDL_Event e;
	SDL_Event f;
	Renderer* rend;
	MessagePost messenger;
};