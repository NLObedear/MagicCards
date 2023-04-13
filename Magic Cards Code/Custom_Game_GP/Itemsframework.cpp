#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Itemsframework {
public:
	virtual void printDesc() const = 0;
	virtual void remove(int numb) {}
	virtual void shuffleDeck() {}
	virtual void add(Itemsframework* c) {}
	virtual void getChild(int, int) {}
	virtual void Awake() {}
	virtual void Sleep() {}
	virtual void Attacked() {}
	virtual bool attackStatus() { return NULL; }
	virtual int getCost() { return NULL; }
	virtual int getAttack() { return NULL; }
	virtual int getHealth() { return NULL; }
	virtual int GetChildAttack(int) { return NULL; }
	virtual void Recieve(int, int) {}
	virtual string getName() { return ""; }
	virtual ~Itemsframework() {}
};