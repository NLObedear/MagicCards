#pragma once
#include <iostream>
#include <vector>
#include <algorithm> 
#include <functional> 
#include "Itemsframework.cpp"


using namespace std;

class PlayerHealth : public Itemsframework {
public:
	int getHealth() {
		return health;
	}
	void DamageHealth(int i) {
		health = health - i;
	}
	void printDesc() const {
		
	}
private:
	int health = 30;
};