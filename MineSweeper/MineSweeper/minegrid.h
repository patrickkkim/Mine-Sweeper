#pragma once
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <vector>
#include "data.h"
#include "event.h"

class MineGrid : public QGridLayout {
private:
	int row, col;
	int mineMaxCount;
	int remainingMine;
	bool isFirstMove;
	Data *data;
	QGridLayout *grid;

	void leftBtnClicked(int, int);
	void RightBtnClicked(int, int);
	void middleBtnClicked(int, int);
	void middleBtnReleased(int, int);
	void addAdjLabel(int, int);
	void addMineLabel(int, int);
	void openAllBlankBtn(int, int);
	void openBtn(int, int);
	void removeButton(int, int);
	void flagBtn(int, int);
	void unFlag(int, int);
	void setFirstMove(int, int);
	bool isFlagged(int, int);
	bool isButton(int, int);
	bool isVictory();
	void gameOver();
	void changeRmnMineBox(QString, bool);

public:
	TextChanged *changedSig;
	GameOver *gameOverSig;

	QGridLayout* getGrid();
	int getRemainingMine();
	MineGrid(int, int, int, QWidget *parent = 0);
};