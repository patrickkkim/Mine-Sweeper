#include <random>
#include "data.h"

Data::Data(int r, int c, int maxMine) {
	row = r, col = c, mineMaxCount = maxMine;
	btnCount = r * c;
	initMineData();
	initAdjData();
	initFlagData();
	initMineBtnData();
}

void Data::initMineData() {
	mineData.resize(col, std::vector<int>(row, 0)); //2차원벡터 데이터를 전부 0으로 초기화

	//벡터 행,열에 지뢰(1)를 랜덤으로 생성
	int mineCount = mineMaxCount;
	int randCol;
	int randRow;
	while (mineCount > 0) {
		randCol = getRandomNum(col);
		randRow = getRandomNum(row);
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
			button->setStyleSheet("QCustomPushButton{background-color:grey;}\
			QCustomPushButton:checked{background-color:red;}");
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

void Data::eraseMineBtnData(int x, int y) {
	QCustomPushButton* mineBtn = mineBtnData[x][y];
	mineBtnData[x].erase(mineBtnData[x].begin() + y);
	mineBtnData[x].insert(mineBtnData[x].begin() + y, nullptr);
	delete(mineBtn);
	btnCount--;
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
	if (x < 0 || x >= col || y < 0 || y >= row) {
		return false;
	}
	else if (mineData[x][y] == 1) {
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

int Data::getRandomNum(int max, int min) {
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(min, max - 1);
	int randNum = dist(engine);
	return randNum;
}

QCustomIconLabel* Data::getFlagData(int x, int y) {
	return flagData[x][y];
}

QCustomPushButton* Data::getMineBtnData(int x, int y) {
	return mineBtnData[x][y];
}

int Data::getMineBtnCount() {
	return btnCount;
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

void Data::setFirstMove(int x, int y) {
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			while (isMine(i, j)) {
				int randCol = getRandomNum(col);
				int randRow = getRandomNum(row);

				//exception where you put your mine into the adjacent square where you clicked.
				if (randCol >= x - 1 && randCol <= x + 1) {
					continue;
				}
				else if (randRow >= y - 1 && randRow <= y + 1) {
					continue;
				}

				if (isMine(randCol, randRow) == false) {
					setMineData(i, j, 0);
					setMineData(randCol, randRow, 1);
					break;
				}
				else {
					continue;
				}
			}
		}
	}
}