#pragma once
#include <vector>
#include "event.h"

//�׸����� �����͸� �����ϴ� Ŭ����
class Data {
private:
	int row, col, mineMaxCount, btnCount;
	std::vector<std::vector<int>> mineData;
	std::vector<std::vector<int>> adjData;
	std::vector<std::vector<QCustomIconLabel*>> flagData;
	std::vector<std::vector<QCustomPushButton*>> mineBtnData;

	int checkAdjBtn(int, int);
	
public:
	void initMineData();
	void initAdjData();
	void initFlagData();
	void initMineBtnData();
	void eraseFlagData(int, int);
	void eraseMineBtnData(int, int);
	bool isMine(int, int);
	int getMineData(int, int);
	int getAdjData(int, int);
	static int getRandomNum(int, int min = 0);
	QCustomIconLabel* getFlagData(int, int);
	QCustomPushButton* getMineBtnData(int, int);
	int getMineBtnCount();
	void setMineData(int, int, int);
	void setAdjData(int, int ,int);
	void setFlagData(int, int, QCustomIconLabel*);
	void setMineBtnData(int, int, QCustomPushButton*);
	void setFirstMove(int, int);
	Data(int, int, int);
};