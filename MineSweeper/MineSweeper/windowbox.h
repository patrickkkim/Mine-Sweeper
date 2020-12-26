#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QPushButton>
#include "minegrid.h"
#include "event.h"
#include "infobox.h"

class WindowBox : public  QWidget {
public:
	MineGrid *minegrid;
	InfoBox *infoBox;

	QVBoxLayout *vBox;
	QHBoxLayout *topBox;
	QBoxLayout* qBox;
	QLabel *mineCountLbl;
	QLabel *timeLabel;
	QTimer *timer;
	QPushButton *retryBtn;
	TextChanged *textChanged;
	GameOver *gameOverSig;
	int time;

	void initUI();
	QLabel* createBorder();
	void setText(QString text);
	void timerSlot();
	void retryClicked(int r, int c, int max);
	void gameOver();
	void victory();
	WindowBox(int r, int c, int max, QWidget *parent = 0);
};