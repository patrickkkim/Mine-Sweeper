#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QPushButton>
#include "minegrid.h"
#include "event.h"

class WindowBox : public  QWidget {
public:
	MineGrid *minegrid;

	QVBoxLayout *vBox;
	QHBoxLayout *topBox;
	QLabel *mineCountLbl;
	QLabel *timeLabel;
	QTimer *timer;
	QPushButton *retryBtn;
	TextChanged *textChanged;
	GameOver *gameOverSig;
	int time;

	void initUI();
	void setText(QString text);
	void timerSlot();
	void retryClicked(int r, int c, int max);
	void gameOver();
	void victory();
	WindowBox(int r, int c, int max, QWidget *parent = 0);
};