#pragma once
#include <iostream>
#include <map>
#include <ctime>
#include <chrono>
#include <thread>
#include <string> 
#include "InGameStates.cpp"
#include "GameStates.cpp"
#include "Deck.cpp"
#include "Card.cpp"
#include "Field.cpp"
#include "PlayerHealth.cpp"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

class ComputerLevel1 {

public:
	void start() {
		srand(int(time(0)));
	}
	string DecideAction1(bool playacard, bool attackpossible) {
		if (!playacard && !attackpossible) {
			string end = "end";
			sleep_for(1s);
			return end;
		}
		if (playacard) {
			string play = "cplay";
			sleep_for(1s);
			return play;
		}
		if (attackpossible) {
			string attack = "cattack";
			sleep_for(1s);
			return attack;
		}
	}
	string PlayACard(map<int, int>* positions) {
		int playable = positions->size();
		int i = 0;
		if (playable != 0) {
			i = rand() % playable + 1;
		}
		return to_string(i);
	}
	string Attack1(Field* field) {
		bool attack = false;
		int i = 0;
		while (!attack) {
			int playable = field->GetSize();
			if (playable != 0) {
				i = rand() % playable + 1;
			}
			attack = field->CanAttack(i - 1);
		}
		sleep_for(1s);
		return to_string(i);
	}
	string Attack2(Field* field) {
		int i = 0;
		int playable = field->GetSize();
		//int random = playable + 1;
		if (playable != 0) {
			i = rand() % playable + 1;
		}
		else {
			return to_string(8);
		}
		sleep_for(1s);
		//return to_string(8);
		 return to_string(i);
	}
};