#include <QLabel>
#include <QDebug>
#include "windowbox.h"
#include "event.h"
#include "infobox.h"

const int BTNWIDTH = 55;
const int BTNHEIGHT = 27;

WindowBox::WindowBox(int r, int c, int max, QWidget *parent) {
	minegrid = new MineGrid(r, c, max);
	infoBox = new InfoBox();

	textChanged = minegrid->changedSig;
	gameOverSig = minegrid->gameOverSig;
	connect(textChanged, &TextChanged::valueChanged, this, &WindowBox::setText);
	connect(minegrid->gameOverSig, &GameOver::gameOver, this, &WindowBox::gameOver);
	connect(minegrid->gameOverSig, &GameOver::victory, this, &WindowBox::victory);
	retryBtn = new QPushButton("Retry", this);
	connect(retryBtn, &QPushButton::clicked, this, [this, r, c, max] { retryClicked(r, c, max); });
	time = 0;
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &WindowBox::timerSlot);
	timer->start(1000);

	initUI();
}

void WindowBox::initUI() {
	vBox = new QVBoxLayout(this);
	topBox = new QHBoxLayout();
	qBox = new QBoxLayout(QBoxLayout::LeftToRight);
	mineCountLbl = new QLabel(QString::number(minegrid->getRemainingMine()));
	mineCountLbl->setFixedWidth(BTNWIDTH);
	mineCountLbl->setFixedHeight(BTNHEIGHT);
	mineCountLbl->setFrameShape(QFrame::Panel);
	mineCountLbl->setFrameShadow(QFrame::Sunken);
	mineCountLbl->setLineWidth(2);
	mineCountLbl->setAlignment(Qt::AlignCenter);
	timeLabel = new QLabel("T: " + QString::number(time));
	timeLabel->setFixedWidth(BTNWIDTH);
	timeLabel->setFixedHeight(BTNHEIGHT);
	timeLabel->setFrameShape(QFrame::Panel);
	timeLabel->setFrameShadow(QFrame::Sunken);
	timeLabel->setLineWidth(2);
	timeLabel->setAlignment(Qt::AlignCenter);
	retryBtn->setFixedWidth(BTNWIDTH);
	retryBtn->setFixedHeight(BTNHEIGHT);
	topBox->addWidget(mineCountLbl);
	topBox->addWidget(timeLabel);
	topBox->addWidget(retryBtn);
	vBox->addLayout(topBox);

	qBox->addLayout(minegrid->getGrid());
	qBox->addLayout(infoBox->getInfoBox());
	qBox->setSpacing(20);
	vBox->addLayout(qBox);
	setLayout(vBox);
	setMinimumWidth(700);
}

QLabel* WindowBox::createBorder() {
	QLabel* lbl = new QLabel();
	lbl->setFrameStyle(QFrame::Box | QFrame::Raised);
	return lbl;
}

void WindowBox::setText(QString text) {
	mineCountLbl->setText(text);
	mineCountLbl->update();
}

void WindowBox::timerSlot() {
	timeLabel->setText("T: " + QString::number(time));
	timeLabel->update();
	time++;
}

void WindowBox::retryClicked(int r, int c, int max) {
	QLayoutItem *item;
	while ((item = minegrid->getGrid()->layout()->takeAt(0)) != NULL) {
		delete item->widget();
		delete item;
	}
	minegrid = new MineGrid(r, c, max);
	vBox->addLayout(minegrid->getGrid());
	time = 0;
	timeLabel->setText("T: " + QString::number(time));
	timer->start();
	timeLabel->update();
	textChanged = minegrid->changedSig;
	gameOverSig = minegrid->gameOverSig;
	connect(textChanged, &TextChanged::valueChanged, this, &WindowBox::setText);
	connect(minegrid->gameOverSig, &GameOver::gameOver, this, &WindowBox::gameOver);
	mineCountLbl->setText(QString::number(max));
	mineCountLbl->update();

	vBox->update();
}

void WindowBox::gameOver() {
	// stop time
	timer->stop();
	// make text "game over"
	mineCountLbl->setText("(X..X)");
}

void WindowBox::victory() {
	timer->stop();
	mineCountLbl->setText("Wazam");
}