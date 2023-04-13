#pragma once
#include <iostream>
#include <vector>
#include <cstdio>
#include<fstream>
#include <sstream>
#include <iterator>
#include <cassert>
#include <string>
#include <map>
#include "Card.cpp"

using namespace std;

class LoadCards {
private: 
	map<string, string> Cards;
	vector<string> Deck;
	vector<string> cardDetails;
public:
	void ReadFile() { //LOADS ALL CARDS
		vector<string> names;
		vector<string> stats;
		ifstream ifs("cards.txt");
		string token, text;
		bool name = true;
		while (!ifs.eof()) {
			getline(ifs, text);
			istringstream iss(text);
			while (getline(iss, token, ',')) {
				if (name) {
					names.push_back(token);
					name = false;
				}
				else if (!name) {
					stats.push_back(token);
					name = true;
				}
				
			}
		}
		for (int i = 0; i < names.size();i++) {
			Cards.emplace(names.at(i), stats.at(i));
		}
	}
	void LoadDeck(string deck) { // LOADS THE DECK NAMES
		string file = deck + ".txt", text;
		ifstream ifs(file);
		while (!ifs.eof()) {
			getline(ifs, text);
			Deck.push_back(text);
		}
		//for (int i = 0; i < cards.size();i++) { // PRINTS THE DECK
		//	cout << i << cards.at(i) << endl;
		//}
	}
	void printCards() { // PRINTS ALL AVALIABLE CARDS
		map<string, string>::iterator it;
		for (it = Cards.begin(); it != Cards.end();it++) {
			cout << "Names: " << it->first << " Stats: " << it->second << endl;
		}
	}
	vector<string>* buildDeck(int i) { // Builds the Deck of cards by splitting all of the stats
		string stats, token;
		stats = Cards.at(Deck.at(i));
		cardDetails.push_back(Deck.at(i));
		istringstream iss(stats);
		while (getline(iss, token, ' ')) {
			cardDetails.push_back(token);
		}

		return &cardDetails;
	}
	//Clears variable for deck building
	void ClearCardDetails() {
		cardDetails.clear();
	}
};