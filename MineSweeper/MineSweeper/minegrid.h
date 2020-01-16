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

	void buttonClicked(int x, int y);
	void openAllBlankBtn(int x, int y);
	void openBtn(int x, int y);
	bool isButton(int x, int y);
	bool isMine(int x, int y);

public:
	MineGrid(int r, int c, int maxMine, QWidget *parent = 0);
	//bool isGameOver();
};