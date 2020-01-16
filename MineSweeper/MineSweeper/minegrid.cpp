#include <QLabel>
#include <QPushButton>
#include "minegrid.h"

MineGrid::MineGrid(int r, int c, int maxMine, QWidget *parent) {
	row = r, col = c;
	mineMaxCount = maxMine;
	data = new Data(r, c, maxMine);
	grid = new QGridLayout(this);
	grid->setSpacing(0);

	//그리드에 버튼 행열로 생성함
	int pos = 0;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			QPushButton *button = new QPushButton(this);
			button->setFixedSize(28, 28);
			connect(button, &QPushButton::clicked, grid, [this, i, j] { buttonClicked(i, j); });
			grid->addWidget(button, i, j);
			pos++;
		}
	}
}

// 버튼이 눌렷을시 버튼을 없애고 그자리에 지뢰데이터를 표시함
void MineGrid::buttonClicked(int x, int y) {
	if (isMine(x, y)) {
		openBtn(x, y);
		QLabel *label = new QLabel(this);
		QPixmap pixmap("../icons/Mine.png");
		label->setPixmap(pixmap.scaled(26, 26, Qt::KeepAspectRatio));
		grid->addWidget(label, x, y);
	}
	else {
		int adjCount = data->adjData[x][y];
		if (adjCount != 0) {
			openBtn(x, y);
			QLabel *label = new QLabel(QString::number(adjCount), this);
			label->setAlignment(Qt::AlignCenter);
			grid->addWidget(label, x, y);
		}
		else {
			openAllBlankBtn(x, y);
		}
	}
}

// 해당 빈칸과 서로 접하고있는 모든 빈칸을 열어놓음
void MineGrid::openAllBlankBtn(int x, int y) {
	if (isButton(x, y) == false || data->adjData[x][y] != 0) {
		return;
	}
	else {
		openBtn(x, y);
		QLabel *label = new QLabel(this);
		grid->addWidget(label, x, y);
		openAllBlankBtn(x - 1, y);
		openAllBlankBtn(x + 1, y);
		openAllBlankBtn(x, y - 1);
		openAllBlankBtn(x, y + 1);
	}
}

// 해당 버튼을 열음
void MineGrid::openBtn(int x, int y) {
	QWidget *btn = grid->itemAtPosition(x, y)->widget();
	layout()->removeWidget(btn);
	delete btn;
}

// 해당 칸에 버튼이 있는지 확인
bool MineGrid::isButton(int x, int y) {
	if (x < 0 || y < 0 || x >= col || y >= row) {
		return false;
	}

	QPushButton *type = qobject_cast<QPushButton*>(grid->itemAtPosition(x, y)->widget());
	if (type == nullptr) {
		return false;
	}
	else {
		return true;
	}
}

bool MineGrid::isMine(int x, int y) {
	if (data->mineData[x][y] == 1) {
		return true;
	}
	else {
		return false;
	}
}