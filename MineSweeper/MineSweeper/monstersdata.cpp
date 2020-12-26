#include "monstersdata.h"

using namespace std;

MonsterData::MonsterData(QString name, QString atk, int hp, int diff, int xp, int ac, int freq) {
	this->name = name;
	this->hp = hp;
	this->atk = atk;
	this->difficulty = diff;
	this->xp = xp;
	this->ac = ac;
	this->freq = freq;
}

QString MonsterData::getName() { return name; }
QString MonsterData::getAttack() { return atk; }
int MonsterData::getHp() { return hp; }
int MonsterData::getDifficulty() { return difficulty; }
int MonsterData::getXp() { return xp; }
int MonsterData::getAc() { return ac; }
int MonsterData::getFrequency() { return freq; }

void MonsterData::setName(QString name) { this->name = name; }
void MonsterData::setAttack(QString atk) { this->atk = atk; }
void MonsterData::setHp(int hp) { this->hp = hp; }
void MonsterData::setDifficulty(int diff) { this->difficulty = diff; }
void MonsterData::setXp(int xp) { this->xp = xp; }
void MonsterData::setAc(int ac) { this->ac = ac; }
void MonsterData::setFrequency(int freq) { this->freq = freq; }

MonstersData::MonstersData() {
	wolf = new MonsterData("wolf", "2d4", 25, 5, 45, 3, 3);
	kobold = new MonsterData("kobold", "1d4", 8, 1, 10, 10, 3);
	kitten = new MonsterData("kitten", "1d6", 15, 3, 20, 6, 2);
	hobbit = new MonsterData("hobbit", "1d6", 12, 2, 13, 10, 2);
	dwarf = new MonsterData("dwarf", "1d8", 20, 4, 22, 10, 3);
	imp = new MonsterData("imp", "1d4", 16, 4, 33, 2, 1);
	blueJelly = new MonsterData("blueJelly", "1d6", 30, 5, 45, 8, 2);
	mnstList = { wolf, kobold, kitten, hobbit, dwarf, imp, blueJelly };
}

vector<MonsterData*> MonstersData::getFullList() {
	return mnstList;
}

vector<MonsterData*> MonstersData::getMonstersByDifficulty(int minDiff, int maxDiff) {
	vector<MonsterData*> newList;

	for (int i = 0; i < mnstList.size(); ++i) {
		int diff = mnstList[i]->getDifficulty();
		if (diff >= minDiff || diff <= maxDiff) {
			newList.push_back(mnstList[i]);
		}
	}
	return newList;
}

MonsterData* MonstersData::findMonster(QString name) {
	for (int i = 0; i < mnstList.size(); ++i) {
		QString mnstName = mnstList[i]->getName();
		if (mnstName == name) {
			return mnstList[i];
		}
	}
	return NULL;
}