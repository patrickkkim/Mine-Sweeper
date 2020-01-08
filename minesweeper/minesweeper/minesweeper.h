#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MineSweeper.h"

class MineSweeper : public QMainWindow
{
	Q_OBJECT

public:
	MineSweeper(QWidget *parent = Q_NULLPTR);

private:
	Ui::MineSweeperClass ui;
};
