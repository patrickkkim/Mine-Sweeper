#include <random>
#include "data.h"

Data::Data(int r, int c, int maxMine) {
	row = r, col = c, mineMaxCount = maxMine;
	initMineData();
	initAdjData();
	initFlagData();
	initMineBtnData();
}

void Data::initMineData() {
	mineData.resize(col, std::vector<int>(row, 0)); //2차원벡터 데이터를 전부 0으로 초기화

		//행,열 랜덤변수생성기 생성
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> distRow(0, row - 1);
	std::uniform_int_distribution<int> distCol(0, col - 1);

	//벡터 행,열에 지뢰(1)를 랜덤으로 생성
	int mineCount = mineMaxCount;
	int randCol;
	int randRow;
	while (mineCount > 0) {
		randCol = distCol(engine);
		randRow = distRow(engine);
		if (mineData[randCol][randRow] != 1) {
			mineData[randCol][randRow] = 1;
			mineCount--;
		}
	}
}

void Data::initAdjData() {
	adjData.resize(col, std::vector<int>(row, 0)); //2차원벡터 데이터를 전부 0으로 초기화

	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			adjData[x][y] = checkAdjBtn(x, y);
		}
	}
}

void Data::initFlagData() {
	flagData.resize(col, std::vector<QCustomIconLabel*>(row, nullptr));
}

void Data::initMineBtnData() {
	mineBtnData.resize(col, std::vector<QCustomPushButton*>(row, nullptr));

	for (int x = 0; x < col; x++) {
		for (int y = 0; y < row; y++) {
			QCustomPushButton *button = new QCustomPushButton();
			button->setFixedSize(28, 28);
			button->setStyleSheet("QCustomPushButton{background-color:grey;}");
			mineBtnData[x][y] = button;
		}
	}
}

void Data::eraseFlagData(int x, int y) {
	QCustomIconLabel* flagItem = flagData[x][y];
	flagData[x].erase(flagData[x].begin() + y);
	flagData[x].insert(flagData[x].begin() + y, nullptr);
	delete(flagItem);
}

int Data::checkAdjBtn(int x, int y) {
	int xStart = -1, yStart = -1;
	int xRange = 2, yRange = 2;
	if (x == 0 || y == 0) {
		if (x == 0) {
			xStart++;
		}
		if (y == 0) {
			yStart++;
		}
	}
	if (x == col - 1 || y == row - 1) {
		if (x == col - 1) {
			xRange--;
		}
		if (y == row - 1) {
			yRange--;
		}
	}

	int count = 0;
	for (int i = xStart; i < xRange; i++) {
		for (int j = yStart; j < yRange; j++) {
			if (isMine(x + i, y + j)) {
				count++;
			}
		}
	}
	return count;
}

bool Data::isMine(int x, int y) {
	if (mineData[x][y] == 1) {
		return true;
	}
	else {
		return false;
	}
}

int Data::getMineData(int x, int y) {
	return mineData[x][y];
}

int Data::getAdjData(int x, int y) {
	return adjData[x][y];
}
QCustomIconLabel* Data::getFlagData(int x, int y) {
	return flagData[x][y];
}

QCustomPushButton* Data::getMineBtnData(int x, int y) {
	return mineBtnData[x][y];
}

void Data::setMineData(int x, int y, int value) {
	mineData[x][y] = value;
}

void Data::setAdjData(int x, int y, int value) {
	adjData[x][y] = value;
}
void Data::setFlagData(int x, int y, QCustomIconLabel* object) {
	flagData[x][y] = object;
}

void Data::setMineBtnData(int x, int y, QCustomPushButton* object) {
	mineBtnData[x][y] = object;
}