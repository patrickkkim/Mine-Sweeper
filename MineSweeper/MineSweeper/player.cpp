#include "player.h"
#include "data.h"

const int START_HP = 20;
const int START_AC = 10;
const int START_MAX_WEIGHT = 100;
const QString DEF_ATTACK = "1d2";

Player::Player()
	: Creature(DEF_ATTACK, START_HP, START_AC, 0, "" , 0.0) {}
