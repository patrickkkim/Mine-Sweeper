#pragma once
#include <QString>
#include "monstersdata.h"
#include "creature.h"
#include "monstersdata.h"

using namespace std;

class Monster : public Creature {
private:
	int difficulty;
	int freq;

public:
	Monster(MonsterData*);

	int getDifficulty();
	int getFrequency();
	void setDifficulty(int);
	void setFrequency(int);
};