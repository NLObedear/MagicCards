#pragma once
#include <iostream>
#include <vector>
#include <algorithm> 
#include <functional> 
#include "Itemsframework.cpp"
using namespace std;

class Field : public Itemsframework {
public:
	void printDesc() const {
		for (int i = 0; i < itemlist.size();i++) {
			cout << i + 1 << ". ";
			itemlist.at(i)->printDesc();
			cout << endl;
		}
	}
	void printAttackDesc() const {
		for (int i = 0; i < itemlist.size();i++) {
			cout << i + 1 << ". ";
			if (itemlist.at(i)->attackStatus()) {
				cout << " Can Attack | ";
			}
			else {
				cout << " Can't Attack | ";
			}
			itemlist.at(i)->printDesc();
			cout << endl;
		}
	}
	void add(Itemsframework* item) {
		if (itemlist.size() >= 7) {
			cout << "Hand is full!" << endl;
		}
		else {
			itemlist.push_back(item);
		}
	}
	void remove(int numb) {
		itemlist.erase(itemlist.begin() + numb);
	}
	int GetSize() {
		return itemlist.size();
	}
	void wakeAllMinions() const {
		for (int i = 0; i < itemlist.size();i++) {
			itemlist.at(i)->Awake();
		}
	}
	void SleepAMinion(int i) {
		itemlist.at(i)->Sleep();
	}
	bool checkAttacks() const {
		bool check;
		for (int i = 0; i < itemlist.size();i++) {
			check = itemlist.at(i)->attackStatus();
			if (check) {
				return true;
			}
		}
		return false;
	}
	bool CanAttack(int i) {
		return itemlist.at(i)->attackStatus();
	}
	void Recieve(int attack, int pos) {											
		itemlist.at(pos)->Recieve(attack, pos);
	}
	int GetChildAttack(int i) {
		return itemlist.at(i)->getAttack();
	}
	int GetChildHealth(int i) {
		return itemlist.at(i)->getHealth();
	}
	string GetChildName(int i) {
		return itemlist.at(i)->getName();
	}
	int getCost(int i) {
		return itemlist.at(i)->getCost();
	}
	int getAttack(int i) {
		return itemlist.at(i)->getAttack();
	}
	int getHealth(int i) {
		return itemlist.at(i)->getHealth();
	}
private:
	vector<Itemsframework*> itemlist;
};