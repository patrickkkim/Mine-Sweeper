#pragma once
#include <QString>

class Creature {
protected:
	QString name;
	QString atk;
	int maxHp;
	int hp;
	int xp;
	int ac;
	double weight;

public:
	Creature(QString atk, int maxHp, int ac, int xp = 0, QString name = "", double weight = 0.0);
	int rollAttack();
	void attack(Creature*);
	bool isDead();

	QString getName();
	QString getAttack();
	int getMaxHp();
	int getHp();
	int getXp();
	int getAc();
	double getWeight();
	void setName(QString);
	void setAttack(QString);
	void setMaxHp(int);
	void setHp(int);
	void setXp(int);
	void setAc(int);
	void setWeight(double);
};