#include "monster.h"

Monster::Monster(MonsterData* mnstData)
	: Creature("", 0, 0, 0, "") {
	setName(mnstData->getName());
	setAttack(mnstData->getAttack());
	setAc(mnstData->getAc());
	setMaxHp(mnstData->getHp());
	setHp(maxHp);
	setXp(mnstData->getXp());
	setDifficulty(mnstData->getDifficulty());
	setFrequency(mnstData->getFrequency());
}

int Monster::getDifficulty() { return difficulty; }
int Monster::getFrequency() { return freq; }
void Monster::setDifficulty(int diff) { this->difficulty = diff; };
void Monster::setFrequency(int freq) { this->freq = freq; }
