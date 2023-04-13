#pragma once
#include <iostream>
#include "Hand.cpp"
#include "Field.cpp"
#include "PlayerHealth.cpp"
#include "Renderer.cpp"
using namespace std;
class Command
{
public:
	virtual ~Command() {}
	virtual int execute(Hand*, Field*, int, Field*, PlayerHealth*, Renderer*) = 0;
};