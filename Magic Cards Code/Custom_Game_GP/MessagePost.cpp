#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "Itemsframework.cpp"

using namespace std;

class MessagePost {
public:
	void add(Itemsframework* attack, Itemsframework* defend, int pos1, int pos2) {
		Attacker.push_back(attack);
		Defender.push_back(defend);
		Pos1.push_back(pos1);
		Pos2.push_back(pos2);
	}
	void send() {
		Defender.at(0)->Recieve(Attacker.at(0)->GetChildAttack(Pos1.at(0)), Pos2.at(0));
		Attacker.at(0)->Recieve(Defender.at(0)->GetChildAttack(Pos2.at(0)), Pos1.at(0));
		Attacker.erase(Attacker.begin());
		Defender.erase(Defender.begin());
		Pos1.erase(Pos1.begin());
		Pos2.erase(Pos2.begin());
	}
private:
	vector<Itemsframework*> Attacker;
	vector<Itemsframework*> Defender;
	vector<int> Pos1;
	vector<int> Pos2;
};