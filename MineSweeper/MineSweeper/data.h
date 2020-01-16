#pragma once
#include <vector>

//그리드의 데이터를 생성하는 클래스
class Data {
private:
	int row, col, mineMaxCount;

	void setMineData();
	void setAdjData();
	int checkAdjBtn(int x, int y);
	bool isMine(int x, int y);

public:
	std::vector<std::vector<int>> mineData;
	std::vector<std::vector<int>> adjData;
	Data(int r, int c, int maxMine);

	void setter(int r, int c, int m) {
		row = r;
		col = c;
		mineMaxCount = m;
	}
};