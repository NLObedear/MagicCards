#pragma once
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Hand.cpp"
#include "field.cpp"
#include <map>

using namespace std;

class Renderer {
public:
	Renderer() {
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow(
			"Magic Cards",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_OPENGL
		);
		renderer = SDL_CreateRenderer(window, -1, 0);
		menu = SDL_LoadBMP("menu.bmp");
		play = SDL_LoadBMP("play.bmp");
		view = SDL_LoadBMP("view.bmp");
		create = SDL_LoadBMP("create.bmp");
		playb = SDL_LoadBMP("playbackground.bmp");
		minionbox = SDL_LoadBMP("minionbox.bmp");
		fieldbox = SDL_LoadBMP("fieldbox.bmp");
		statbox = SDL_LoadBMP("statbox.bmp");
		endturn = SDL_LoadBMP("endturn.bmp");
		playercard = SDL_LoadBMP("cards.bmp");
		enemycard = SDL_LoadBMP("cardback.bmp");
		numbers = SDL_LoadBMP("numbers.bmp");
		cardsleft = SDL_LoadBMP("cardsleft.bmp");
		nomana = SDL_LoadBMP("nomana.bmp");
		noattack = SDL_LoadBMP("noattack.bmp");
		playmode = SDL_LoadBMP("playmode.bmp");
		attack1mode = SDL_LoadBMP("attack1.bmp");
		attack2mode = SDL_LoadBMP("attack2.bmp");

		tmenu = SDL_CreateTextureFromSurface(renderer, menu);
		tplay = SDL_CreateTextureFromSurface(renderer, play);
		tview = SDL_CreateTextureFromSurface(renderer, view);
		tcreate = SDL_CreateTextureFromSurface(renderer, create);

		tplayb = SDL_CreateTextureFromSurface(renderer, playb);
		tminionbox = SDL_CreateTextureFromSurface(renderer, minionbox);
		tfieldbox = SDL_CreateTextureFromSurface(renderer, fieldbox);
		tstatbox = SDL_CreateTextureFromSurface(renderer, statbox);
		tendturn = SDL_CreateTextureFromSurface(renderer, endturn);
		tcardsleft = SDL_CreateTextureFromSurface(renderer, cardsleft);

		tplayercard = SDL_CreateTextureFromSurface(renderer, playercard);
		tnumbers = SDL_CreateTextureFromSurface(renderer, numbers);
		tenemycard = SDL_CreateTextureFromSurface(renderer, enemycard);

		tnomana = SDL_CreateTextureFromSurface(renderer, nomana);
		tnoattack = SDL_CreateTextureFromSurface(renderer, noattack);
		tplaymode = SDL_CreateTextureFromSurface(renderer, playmode);
		tattack1mode = SDL_CreateTextureFromSurface(renderer, attack1mode);
		tattack2mode = SDL_CreateTextureFromSurface(renderer, attack2mode);
	}
	void MainMenu() {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, tmenu, NULL, &rmenu);
		SDL_RenderCopy(renderer, tplay, NULL, &rplay);
		SDL_RenderCopy(renderer, tview, NULL, &rview);
		SDL_RenderCopy(renderer, tcreate, NULL, &rcreate);
		SDL_RenderPresent(renderer);
	}
	int MenuCheck(int x, int y) {
	//	cout << x << " "<< y << endl;
		if (x > 500 && x < 780 && y > 150 && y < 250) {
			return 1;
		}
		else if (x > 500 && x < 780 && y > 300 && y < 400) {
			return 2;
		}
		else if (x > 500 && x < 780 && y > 450 && y < 550) {
			return 3;
		}
	}
	int endturncheck(int x, int y) {
		if (x > rendturn.x && x < rendturn.x + rendturn.w && y > rendturn.y && y < rendturn.y + rendturn.h) {
			return 1;
		}
	}
	void PlayGame() {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, tplayb, NULL, &rplayb);
		SDL_RenderCopy(renderer, tcardsleft, NULL, &rcardsleft);
		SDL_RenderCopy(renderer, tcardsleft, NULL, &rcardslefte);
		SDL_RenderCopy(renderer, tfieldbox, NULL, &rfieldbox);
		SDL_RenderCopy(renderer, tstatbox, NULL, &rstatbox);
		SDL_RenderCopy(renderer, tstatbox, NULL, &renemy_statbox);
		SDL_RenderCopy(renderer, tendturn, NULL, &rendturn);
	}
	void RenderHand(Hand* hand1) {
		hand = hand1;
		for (int i = 0; i < hand->GetSize();i++) {
			SDL_RenderCopy(renderer, tplayercard, NULL, &Handslot);
			PlaceNumbersOnCard(&Handslot, hand->getCost(i), hand->getAttack(i), hand->getHealth(i));
			Handslot.x += 110;
		}
		if (enemyhand != NULL) {
			tenemycard = SDL_CreateTextureFromSurface(renderer, enemycard);
			for (int i = 0; i < enemyhand->GetSize();i++) {
				SDL_RenderCopy(renderer, tenemycard, NULL, &enemyHandslot);
				enemyHandslot.x += 110;
			}
			enemyHandslot.x = 25;
		}
		Handslot.x = 25;
	}
	void RenderField(Field* hand1) {
		field1 = true;
		field = hand1;
		Handslot.y = 375;
		for (int i = 0; i < field->GetSize();i++) {
			SDL_RenderCopy(renderer, tplayercard, NULL, &Handslot);
			PlaceNumbersOnCard(&Handslot, field->getCost(i), field->getAttack(i), field->getHealth(i));
			Handslot.x += 110;
		}
		if (enemyfield1) {
			field1 = false;
			RenderEnemyField(enemyfield);
			field1 = true;
		}
		Handslot.x = 25;
		Handslot.y = 585;
	}
	void RenderEnemyField(Field* hand1) {
		enemyfield1 = true;
		enemyfield = hand1;
		enemyHandslot.y = 150;
		for (int i = 0; i < enemyfield->GetSize();i++) {
			SDL_RenderCopy(renderer, tplayercard, NULL, &enemyHandslot);
			PlaceNumbersOnCard(&enemyHandslot, enemyfield->getCost(i), enemyfield->getAttack(i), enemyfield->getHealth(i));
			enemyHandslot.x += 110;
		}
		if (field1) {
			enemyfield1 = false;
			RenderField(field);
			enemyfield1 = true;
		}
		enemyHandslot.x = 25;
		enemyHandslot.y = 15;
	}
	void RenderEnemyHand(Hand* hand1) {
		enemyhand = hand1;
		for (int i = 0; i < enemyhand->GetSize();i++) {
			SDL_RenderCopy(renderer, tenemycard, NULL, &enemyHandslot);
			enemyHandslot.x += 110;
		}
		if (hand != NULL) {
			tplayercard = SDL_CreateTextureFromSurface(renderer, playercard);
			tnumbers = SDL_CreateTextureFromSurface(renderer, numbers);
			for (int i = 0; i < hand->GetSize();i++) {
				SDL_RenderCopy(renderer, tplayercard, NULL, &Handslot);
				PlaceNumbersOnCard(&Handslot, hand->getCost(i), hand->getAttack(i), hand->getHealth(i));
				Handslot.x += 110;
			}
			Handslot.x = 25;
		}
		enemyHandslot.x = 25;
	}
	void PlaceNumbersOnCard(SDL_Rect* rect, int cost, int atk, int hp) {
		SDL_Rect* numlocation = numbermap[cost];
	//	cout << cost << " " << atk << " " << hp << " " << endl;
		nplacement.x = rect->x + 7;
		nplacement.y = rect->y + 7;
		SDL_RenderCopy(renderer, tnumbers, numlocation, &nplacement);

		numlocation = numbermap[atk];
		nplacement.x = rect->x + 7;
		nplacement.y = rect->y + 88;
		SDL_RenderCopy(renderer, tnumbers, numlocation, &nplacement);

		numlocation = numbermap[hp];
		nplacement.x = rect->x + 85;
		nplacement.y = rect->y + 88;
		SDL_RenderCopy(renderer, tnumbers, numlocation, &nplacement);
	}
	void setStats(int mana1, int maxmana, int decksize, int health) {
		mana = mana1;
		mmax = maxmana;
		deck = decksize;
		hp = health;
	}
	void esetStats(int mana1, int maxmana, int decksize, int health) {
		emana = mana1;
		emmax = maxmana;
		edeck = decksize;
		ehp = health;
	}
	void StatBox() {
		astats = true;
		int decknum1, decknum2;
		bool digit2 = false;
		SDL_Rect* numlocation1;
		SDL_Rect* numlocation2;
		if (deck >= 10) {
			decknum2 = deck % 10;
			decknum1 = deck;
			decknum1 /= 10;

			numlocation1 = numbermap[decknum1];
			numlocation2 = numbermap[decknum2];
			SDL_RenderCopy(renderer, tnumbers, numlocation1, &deckplacement1);
			SDL_RenderCopy(renderer, tnumbers, numlocation2, &deckplacement2);
		}
		else {
			decknum1 = deck;
			numlocation1 = numbermap[decknum1];
			SDL_RenderCopy(renderer, tnumbers, numlocation1, &deckplacement1);
		}
		numlocation1 = numbermap[mana];
		numlocation2 = numbermap[mmax];
		SDL_RenderCopy(renderer, tnumbers, numlocation1, &manap1);
		SDL_RenderCopy(renderer, tnumbers, numlocation2, &manap2);
		if (hp >= 10) {
			decknum2 = hp % 10;
			decknum1 = hp;
			decknum1 /= 10;
			numlocation1 = numbermap[decknum1];
			numlocation2 = numbermap[decknum2];
			SDL_RenderCopy(renderer, tnumbers, numlocation1, &hp1);
			SDL_RenderCopy(renderer, tnumbers, numlocation2, &hp2);
		}
		else {
			decknum1 = hp;
			numlocation1 = numbermap[decknum1];
			SDL_RenderCopy(renderer, tnumbers, numlocation1, &hp1);
		}
		if (enemystats) {
			astats = false;
			EnemyStatBox();
			astats = true;
		}
	}
	void EnemyStatBox() {
		enemystats = true;
		int decknum1, decknum2;
		bool digit2 = false;
		SDL_Rect* numlocation1;
		SDL_Rect* numlocation2;
		if (edeck >= 10) {
			decknum2 = edeck % 10;
			decknum1 = edeck;
			decknum1 /= 10;

			numlocation1 = numbermap[decknum1];
			numlocation2 = numbermap[decknum2];
			SDL_RenderCopy(renderer, tnumbers, numlocation1, &edeckplacement1);
			SDL_RenderCopy(renderer, tnumbers, numlocation2, &edeckplacement2);
		}
		else {
			decknum1 = edeck;
			numlocation1 = numbermap[decknum1];
			SDL_RenderCopy(renderer, tnumbers, numlocation1, &edeckplacement1);
		}
		numlocation1 = numbermap[emana];
		numlocation2 = numbermap[emmax];
		SDL_RenderCopy(renderer, tnumbers, numlocation1, &emanap1);
		SDL_RenderCopy(renderer, tnumbers, numlocation2, &emanap2);
		if (ehp >= 10) {
			decknum2 = ehp % 10;
			decknum1 = ehp;
			decknum1 /= 10;
			numlocation1 = numbermap[decknum1];
			numlocation2 = numbermap[decknum2];
			SDL_RenderCopy(renderer, tnumbers, numlocation1, &ehp1);
			SDL_RenderCopy(renderer, tnumbers, numlocation2, &ehp2);
		}
		else {
			decknum1 = ehp;
			numlocation1 = numbermap[decknum1];
			SDL_RenderCopy(renderer, tnumbers, numlocation1, &ehp1);
		}
		if (astats) {
			enemystats = false;
			StatBox();
			enemystats = true;
		}
	}
	void NoMana() {
		SDL_RenderCopy(renderer, tnomana, NULL, &rno);
	}
	void NoAttack() {
		SDL_RenderCopy(renderer, tnoattack, NULL, &rno);
	}
	void PlayMode(){
		SDL_RenderCopy(renderer, tplaymode, NULL, &rno);
	}
	void Attack1() {
		SDL_RenderCopy(renderer, tattack1mode, NULL, &rno);
	}
	void Attack2() {
		SDL_RenderCopy(renderer, tattack2mode, NULL, &rno);
	}
	void rend() {
		SDL_RenderPresent(renderer);
	}
private:
	int emana, emmax, edeck, ehp, mana, mmax, deck, hp;
	bool astats = false, enemystats = false, enemyfield1 = false, field1 = false;
	Hand* hand = nullptr;
	Hand* enemyhand = nullptr;
	Field* field = nullptr;
	Field* enemyfield = nullptr;
	const int width = 1280;
	const int height = 720;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* tmenu;
	SDL_Texture* tplay;
	SDL_Texture* tview;
	SDL_Texture* tcreate;
	SDL_Texture* tplayb;
	SDL_Texture* tminionbox;
	SDL_Texture* tfieldbox;
	SDL_Texture* tstatbox;
	SDL_Texture* tendturn;
	SDL_Texture* tplayercard;
	SDL_Texture* tenemycard;
	SDL_Texture* tnumbers;
	SDL_Texture* tcardsleft;
	SDL_Texture* tnomana;
	SDL_Texture* tnoattack;
	SDL_Texture* tplaymode;
	SDL_Texture* tattack1mode;
	SDL_Texture* tattack2mode;

	SDL_Surface* menu = NULL;
	SDL_Surface* play = NULL;
	SDL_Surface* view = NULL;
	SDL_Surface* create = NULL;
	SDL_Surface* playb = NULL;
	SDL_Surface* minionbox = NULL;
	SDL_Surface* fieldbox = NULL;
	SDL_Surface* statbox = NULL;
	SDL_Surface* endturn;
	SDL_Surface* playercard;
	SDL_Surface* enemycard;
	SDL_Surface* numbers;
	SDL_Surface* cardsleft;
	SDL_Surface* nomana;
	SDL_Surface* noattack;
	SDL_Surface* playmode;
	SDL_Surface* attack1mode;
	SDL_Surface* attack2mode;

	SDL_Rect rno = { 25, 500, 200, 60 };

	SDL_Rect rmenu = { 0, 0, 1280, 720 };
	SDL_Rect rplay = { 500, 150, 280, 100 };
	SDL_Rect rview = { 500, 300, 280, 100 };
	SDL_Rect rcreate = { 500, 450, 280, 100 };
	SDL_Rect rplayb = { 0, 0, 1280, 720 };

	SDL_Rect rminionbox = {20, 590, 1085, 120};
	SDL_Rect renemy_minionbox = {20, 10, 1085, 120};
	SDL_Rect rfieldbox = {20, 140, 1035, 440};
	SDL_Rect rstatbox = { 1120, 460, 150, 250 };
	SDL_Rect renemy_statbox = {1120, 10, 150, 250};
	SDL_Rect rendturn = {1120, 330, 150, 60};
	SDL_Rect rcardslefte = { 1120, 260, 155, 60 };
	SDL_Rect rcardsleft = { 1120, 400, 155, 60 };

	SDL_Rect Handslot = {25, 585, 110, 120};
	SDL_Rect enemyHandslot = { 25, 15, 110, 120 };

	SDL_Rect r1 = { 0, 0, 33, 43 };
	SDL_Rect r2 = { 33, 0, 33, 43 };
	SDL_Rect r3 = { 66, 0, 33, 43};
	SDL_Rect r4 = { 99, 0, 33, 43 };
	SDL_Rect r5 = { 132, 0, 33, 43 };
	SDL_Rect r6 = { 165, 0, 33, 43 };
	SDL_Rect r7 = { 198, 0, 33, 43 };
	SDL_Rect r8 = { 231, 0, 33, 43 };
	SDL_Rect r9 = { 264, 0, 33, 43 };
	SDL_Rect r0 = { 297, 0, 33, 43 };

	SDL_Rect nplacement = { 0, 0, 16, 23 };

	SDL_Rect deckplacement2 = { 1100, 418, 16, 23 };
	SDL_Rect deckplacement1 = { 1080, 418, 16, 23 };

	SDL_Rect manap1 = { 1155, 493, 16, 23 };
	SDL_Rect manap2 = { 1185, 515, 16, 23 };

	SDL_Rect hp1 = { 1200, 640, 16, 23 };
	SDL_Rect hp2 = { 1220, 640, 16, 23 };

	SDL_Rect edeckplacement2 = { 1100, 278, 16, 23 };
	SDL_Rect edeckplacement1 = { 1080, 278, 16, 23 };

	SDL_Rect emanap1 = { 1155, 43, 16, 23 };
	SDL_Rect emanap2 = { 1185, 65, 16, 23 };

	SDL_Rect ehp1 = { 1200, 200, 16, 23 };
	SDL_Rect ehp2 = { 1220, 200, 16, 23 };

	map<int, SDL_Rect*> numbermap = {
		{0, &r0},
		{1, &r1},
		{2, &r2},
		{3, &r3},
		{4, &r4},
		{5, &r5},
		{6, &r6},
		{7, &r7},
		{8, &r8},
		{9, &r9},
	};
};