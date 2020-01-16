#pragma once
#include <QWidget>
#include <QGridLayout>
#include "data.h"

class MineGrid : public QWidget {
private:
	int row, col;
	int mineMaxCount;
	Data *data;
	QGridLayout *grid;

	void leftBtnClicked(int x, int y);
	void RightBtnClicked(int x, int y);
	void openAllBlankBtn(int x, int y);
	void openWidget(int x, int y);
	void flagBtn(int x, int y);
	void unFlag(int x, int y);
	bool isFlagged(int x, int y);
	bool isButton(int x, int y);
	bool isMine(int x, int y);

public:
	void addAdjData(int x, int y, int count);
	MineGrid(int r, int c, int maxMine, QWidget *parent = 0);
	//bool isGameOver();
};