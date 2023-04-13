#pragma once
#include <iostream>
#include <vector>
#include <algorithm> 
#include <functional> 
#include "Itemsframework.cpp"


using namespace std;

class Card : public Itemsframework {
public: 
	Card(string name, string special, int cost, int attack, int health) : name(name), special(special), cost(cost), attack(attack), health(health){}
	Card(string name, int cost, int attack, int health) : name(name), cost(cost), attack(attack), health(health) {}

	void printDesc() const {
		cout << name << "| cost: " << cost << "| attack: " << attack << "| health: " << health << "| special: " << special << endl;
	}
	int getCost() {
		return cost;
	}
	int getHealth() {
		return health;
	}
	int getAttack() {
		return attack;
	}
	void Awake() {
		canAttack = true;
	}
	void Sleep() {
		canAttack = false;
	}
	void Attacked() {
		canAttack = false;
	}
	bool attackStatus() {
		return canAttack;
	}
	string getName() {
		return name;
	}
	void Recieve(int attack, int pos) {
		health = health - attack;
		canAttack = false;
	}
	string getSpecial() {
		return special;
	}
private:
	string name, special = "None";
	int cost, attack, health;
	bool canAttack = false;
};