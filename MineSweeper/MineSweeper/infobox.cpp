#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include "infobox.h"
#include "event.h"

const QString projectDir = "C:/Users/Artium/source/repos/MineSweeper/MineSweeper";

InfoBox::InfoBox(QWidget* parent) {
	mnstBox = new QHBoxLayout();
	playerBox = new QHBoxLayout();
	logBox = new QHBoxLayout();
	mnstData = new MonstersData();
	Monster* monster = new Monster(mnstData->findMonster("kobold"));
	player = new Player();

	mnstTextBox = new QVBoxLayout();
	mnstImg = new QLabel();
	QPixmap mnstPxmp(projectDir + "/icons/monsters/" + monster->getName() + ".png");
	mnstImg->setPixmap(mnstPxmp.scaled(100, 130, Qt::KeepAspectRatio));
	mnstBox->addWidget(mnstImg);
	mnstName = new QLabel(monster->getName());
	mnstHp = new QLabel();
	updateMonsterHp(monster);
	mnstTextBox->addStretch();
	mnstTextBox->addWidget(mnstName);
	mnstTextBox->addWidget(mnstHp);
	mnstTextBox->addStretch();
	mnstBox->addLayout(mnstTextBox);

	torchAnim = new QLabel();
	QMovie* movie = new QMovie(projectDir + "/icons/Torch.gif");
	movie->setScaledSize(QSize(125, 150));
	torchAnim->setMovie(movie);
	movie->start();
	playerBox->addWidget(torchAnim);
	playerTextBox = new QVBoxLayout();
	playerName = new QLabel("Player");
	playerHp = new QLabel();
	updatePlayerHp();
	playerAc = new QLabel("AC: " + QString::number(player->getAc()));
	playerXp = new QLabel("XP: " + QString::number(player->getXp()));
	playerTextBox->addStretch();
	playerTextBox->addWidget(playerName);
	playerTextBox->addWidget(playerHp);
	playerTextBox->addWidget(playerAc);
	playerTextBox->addWidget(playerXp);
	playerTextBox->addStretch();
	playerBox->addLayout(playerTextBox);

	atkBtn = new QPushButton("Attack");
	connect(atkBtn, &QPushButton::clicked, this, [this, monster] { AttackBtnClicked(monster); });
	logBox->addWidget(atkBtn);

	addLayout(mnstBox);
	addLayout(playerBox);
	addLayout(logBox);
}

QVBoxLayout* InfoBox::getInfoBox() {
	return this;
}

void InfoBox::AttackBtnClicked(Monster* monster) {
	player->attack(monster);
	if (monster->isDead()) {
		delete monster;
		atkBtn->setEnabled(false);
		clearLayout(mnstBox);
		return;
	}
	updateMonsterHp(monster);

	monster->attack(player);
	updatePlayerHp();
	if (player->isDead()) {
		// game over
	}
}

void InfoBox::updateMonsterHp(Monster* monster) {
	mnstHp->setText("HP: " + QString::number(monster->getHp()) + " / " + QString::number(monster->getMaxHp()));
	mnstHp->update();
}

void InfoBox::updatePlayerHp() {
	playerHp->setText("HP: " + QString::number(player->getHp()) + " / " + QString::number(player->getMaxHp()));
	playerHp->update();
}

void InfoBox::clearLayout(QLayout* layout) {
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			item->layout()->setParent(NULL);
		}
		if (item->widget()) {
			item->widget()->setParent(NULL);
		}
	}
}