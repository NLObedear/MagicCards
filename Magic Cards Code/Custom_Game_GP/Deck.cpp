#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include <algorithm> 
#include <functional> 
#include "Itemsframework.cpp"

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

class Deck : public Itemsframework {
public:
	Deck() {
		srand(int(time(0)));
	}
	void printDesc() const {
		for (int i = 0; i < itemlist.size();i++) {
			cout << i + 1 << ". ";
			itemlist.at(i)->printDesc();
			cout << endl;
		}
	}
	void add(Itemsframework* item) {
		if (itemlist.size() >= 30) {
			cout << "Deck is full" << endl;
		}
		else {
			itemlist.push_back(item);
		}
	}
	void remove(int numb) {
		itemlist.erase(itemlist.begin() + numb - 1);
	}
	void shuffleDeck() { // Shuffles a deck into a random order
	//	printDesc();
		for (int h = 0; h < 90;h++) {
			i = rand() % 30 + 0;
			sleep_for(5ns);
			j = rand() % 30 + 0;
	//		cout << "i: " << i << " j: " << j << endl;
			swap(itemlist.at(i), itemlist.at(j));
		}
	//	printDesc();
	}
	Itemsframework* addToHand() { // Adds a card to a hand
		Itemsframework* topcard;
		topcard = itemlist.at(0);
		itemlist.erase(itemlist.begin());
		return topcard;
	}
	void burn() {
		itemlist.erase(itemlist.begin());
	}
	int GetSize() {
		return itemlist.size();
	}
private:
	int i = 0, j = 0, m = 0, n = 0;
	vector<Itemsframework*> itemlist;
};