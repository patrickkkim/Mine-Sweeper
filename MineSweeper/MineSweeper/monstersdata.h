#pragma once
#include <QString>
#include <vector>

using namespace std;

class MonsterData {
private:
	QString name;
	QString atk;
	int hp;
	int difficulty;
	int xp;
	int ac;
	int freq;

public:
	QString getName();
	QString getAttack();
	int getHp();
	int getDifficulty();
	int getXp();
	int getAc();
	int getFrequency();
	void setName(QString);
	void setAttack(QString);
	void setHp(int);
	void setDifficulty(int);
	void setXp(int);
	void setAc(int);
	void setFrequency(int);
	MonsterData(QString, QString, int, int, int, int, int);
};

class MonstersData {
private:
	MonsterData *wolf;
	MonsterData *kobold;
	MonsterData *kitten;
	MonsterData *hobbit;
	MonsterData *dwarf;
	MonsterData *imp;
	MonsterData *blueJelly;
	vector<MonsterData*> mnstList;

public:
	vector<MonsterData*> getFullList();
	vector<MonsterData*> getMonstersByDifficulty(int, int);
	MonsterData* findMonster(QString);
	MonstersData();
};