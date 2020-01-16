#pragma once
#include <vector>

//�׸����� �����͸� �����ϴ� Ŭ����
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