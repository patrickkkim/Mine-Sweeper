#include "creature.h"
#include "data.h"

Creature::Creature(QString atk, int maxHp, int ac, int xp, QString name, double weight) {
	this->atk = atk;
	this->maxHp = maxHp;
	this->hp = maxHp;
	this->ac = ac;
	this->weight = weight;
	this->xp = xp;
}

int Creature::rollAttack() {
	int count = atk.split("d")[0].toInt();
	int value = atk.split("d")[1].toInt();
	int total = 0;

	for (int i = 0; i < count; ++i) {
		total += Data::getRandomNum(value + 1, 1);
	}
	return total;
}

void Creature::attack(Creature* opponent) {
	int opponentHp = opponent->getHp();
	int atkValue = rollAttack();
	opponent->setHp(opponentHp - atkValue);
}

bool Creature::isDead() {
	if (hp <= 0) return true;
	else return false;
}

QString Creature::getName() { return name; }
QString Creature::getAttack() { return atk; }
int Creature::getMaxHp() { return maxHp; }
int Creature::getHp() { return hp; }
int Creature::getXp() { return xp; }
int Creature::getAc() { return ac; }
double Creature::getWeight() { return weight; }
void Creature::setName(QString name) { this->name = name; }
void Creature::setAttack(QString atk) { this->atk = atk; }
void Creature::setMaxHp(int maxHp) { this->maxHp = maxHp; }
void Creature::setHp(int hp) { this->hp = hp; }
void Creature::setXp(int xp) { this->xp = xp; }
void Creature::setAc(int ac) { this->ac = ac; }
void Creature::setWeight(double weight) { this->weight = weight; }