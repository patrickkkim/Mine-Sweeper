#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_minesweeper.h"

class minesweeper : public QMainWindow
{
	Q_OBJECT

public:
	minesweeper(QWidget *parent = Q_NULLPTR);

private:
	Ui::minesweeperClass ui;
};
