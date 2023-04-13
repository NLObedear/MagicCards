#pragma once
#include <iostream>
#include <vector>
#include <algorithm> 
#include <functional> 
#include <map>
#include "Itemsframework.cpp"
#include "ComputerLevel1.cpp"
using namespace std;

class Hand : public Itemsframework {
public:
	void printDesc() const {
		for (int i = 0; i < itemlist.size();i++) {
			cout << i + 1 << ". ";
			itemlist.at(i)->printDesc();
			cout << endl;
		}
	}
	map<int,int> PrintPlayableCards(int mana) {
		int h = 1;
		map<int, int> positions;
		for (int i = 0; i < itemlist.size();i++) {
			if (itemlist.at(i)->getCost() <= mana) {
				cout << h << ". ";
				itemlist.at(i)->printDesc();
				cout << endl;
				positions[h] = { i };
				h++;
			}
		}
		return positions;
	}
	map<int, int> CheckPlayableCards(int mana) {
		int h = 1;
		map<int, int> positions;
		for (int i = 0; i < itemlist.size();i++) {
			if (itemlist.at(i)->getCost() <= mana) {
				positions[h] = { i };
				h++;
			}
		}
		return positions;
	}
	void add(Itemsframework* item) {
		if (itemlist.size() >= 10) {
			cout << "Hand is full!" << endl;
		}
		else {
			itemlist.push_back(item);
		}
	}
	void remove(int numb) {
		itemlist.erase(itemlist.begin() + numb - 1);
	}
	Itemsframework* addToField(int i) { // Adds a card to the Field
		Itemsframework* topcard;
		topcard = itemlist.at(i);
		itemlist.erase(itemlist.begin() + i);
		return topcard;
	}
	int GetSize() {
		return itemlist.size();
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
	void GetComputer(ComputerLevel1* computer1) {
		computer = computer1;
	}
	ComputerLevel1* ReturnComputer() {
		return computer;
	}
private:
	vector<Itemsframework*> itemlist;
	ComputerLevel1* computer;
};