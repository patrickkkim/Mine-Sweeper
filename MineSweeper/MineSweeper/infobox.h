#pragma once
#include <QVBoxLayout>
#include "monster.h"
#include "player.h"

class InfoBox : public QVBoxLayout {
private:
	QHBoxLayout* mnstBox;
	QHBoxLayout* playerBox;
	QHBoxLayout* logBox;
	MonstersData* mnstData;
	QVBoxLayout* mnstTextBox;
	QLabel* mnstImg;
	QLabel* mnstName;
	QLabel* mnstHp;
	Player* player;
	QLabel* torchAnim;
	QVBoxLayout* playerTextBox;
	QLabel* playerName;
	QLabel* playerHp;
	QLabel* playerAc;
	QLabel* playerXp;
	QPushButton* atkBtn;

public:
	InfoBox(QWidget* parent = 0);
	QVBoxLayout* getInfoBox();
	void AttackBtnClicked(Monster*);
	void updateMonsterHp(Monster*);
	void updatePlayerHp();
	void clearLayout(QLayout* layout);
};