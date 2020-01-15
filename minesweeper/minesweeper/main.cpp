#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <iostream>
#include <random>
#include <vector>

const int WIDTH = 300; //������ â�� ũ��
const int HEIGHT = 200;
const int ROW = 10; //���ڹ迭�� ũ��
const int COL = 20;
const int MINEMAXCOUNT = 40; //�����ִ� ����

struct Coordinate {
	int x;
	int y;
	int xStart;
	int yStart;
	int xRange;
	int yRange;
};

//�׸����� �����͸� �����ϴ� Ŭ����
class Data {
public:
	std::vector<std::vector<int>> mineData;
	std::vector<std::vector<int>> adjData;

	Data() {
		setMineData();
		setAdjData();
	};

	void setMineData() {
		mineData.resize(COL, std::vector<int>(ROW, 0)); //2�������� �����͸� ���� 0���� �ʱ�ȭ

		//��,�� �������������� ����
		std::random_device seeder;
		std::mt19937 engine(seeder());
		std::uniform_int_distribution<int> distRow(0, ROW - 1);
		std::uniform_int_distribution<int> distCol(0, COL - 1);

		//���� ��,���� ����(1)�� �������� ����
		int mineCount = MINEMAXCOUNT;
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

	void setAdjData() {
		adjData.resize(COL, std::vector<int>(ROW, 0)); //2�������� �����͸� ���� 0���� �ʱ�ȭ

		for (int x = 0; x < COL; x++) {
			for (int y = 0; y < ROW; y++) {
				Coordinate point = { x, y };
				adjData[x][y] = checkAdjBtn(point);
			}
		}
	}

	// �ֺ�ĭ�� ���ڰ� ��ִ��� ����
	int checkAdjBtn(Coordinate point) {
		int x = point.x, y = point.y;
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
		if (x == COL - 1 || y == ROW - 1) {
			if (x == COL - 1) {
				xRange--;
			}
			if (y == ROW - 1) {
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

	bool isMine(int x, int y) {
		if (mineData[x][y] == 1) {
			return true;
		}
		else {
			return false;
		}
	}
};

//�׸��带 ����, �����ϴ� Ŭ����
class MineGrid : public QWidget {
public:
	Data data;
	QGridLayout *grid = new QGridLayout(this);

	MineGrid(QWidget *parent = 0) {
		grid->setSpacing(0);

		//�׸��忡 ��ư �࿭�� ������
		int pos = 0;
		for (int i = 0; i < COL; i++) {
			for (int j = 0; j < ROW; j++) {
				QPushButton *button = new QPushButton(this);
				button->setFixedSize(28, 28);
				Coordinate point = { i , j };
				connect(button, &QPushButton::clicked, grid, [this, point] { buttonClicked(point); });
				grid->addWidget(button, i, j);
				pos++;
			}
		}
	}

	// ��ư�� �������� ��ư�� ���ְ� ���ڸ��� ���ڵ����͸� ǥ����
	void buttonClicked(Coordinate point) {
		int x = point.x, y = point.y;

		if (isMine(x, y)) {
			openBtn(point);
			QLabel *label = new QLabel(this);
			QPixmap pixmap("../icons/Mine.png");
			label->setPixmap(pixmap.scaled(26, 26, Qt::KeepAspectRatio));
			grid->addWidget(label, x, y);
		}
		else {
			int adjCount = data.adjData[x][y];
			if (adjCount != 0) {
				openBtn(point);
				QLabel *label = new QLabel(QString::number(adjCount), this);
				label->setAlignment(Qt::AlignCenter);
				grid->addWidget(label, x, y);
			}
			else {
				openAllBlankBtn(x, y);
			}
		}
	}

	// �ش� ��ĭ�� ���� ���ϰ��ִ� ��� ��ĭ�� �������
	void openAllBlankBtn(int x, int y) {
		Coordinate point = { x, y };
		if (isButton(point) == false || data.adjData[x][y] != 0) {
			return;
		}
		else {
			openBtn(point);
			QLabel *label = new QLabel(this);
			grid->addWidget(label, point.x, point.y);
			openAllBlankBtn(x-1, y);
			openAllBlankBtn(x+1, y);
			openAllBlankBtn(x, y-1);
			openAllBlankBtn(x, y+1);
		}
	}
	
	// �ش� ��ư�� ����
	void openBtn(Coordinate point) {
		QWidget *btn = grid->itemAtPosition(point.x, point.y)->widget();
		layout()->removeWidget(btn);
		delete btn;
	}

	// �ش� ĭ�� ��ư�� �ִ��� Ȯ��
	bool isButton(Coordinate point) {
		int x = point.x, y = point.y;
		if (x < 0 || y < 0 || x >= COL || y >= ROW) {
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

	bool isGameOver() {
		/*
		if (isMine(x, y) == true) {
			for (int i = 0; i < COL; i++) {
				for (int j = 0; j < ROW; j++) {
					QWidget *widget = grid->itemAtPosition(i, j)->widget();
					layout()->removeWidget(widget);
					delete(widget);
				}
			}
			QLabel *label = new QLabel("GAME OVER", this);
			label->setAlignment(Qt::AlignCenter);
			grid->addWidget(label);
		}
		*/
	}

	bool isMine(int x, int y) {
		if (data.mineData[x][y] == 1) {
			return true;
		}
		else {
			return false;
		}
	}
};

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	MineGrid window;
	window.resize(WIDTH, HEIGHT);
	window.setWindowTitle("Mine Sweeper"); //������ â ����
	window.show();

	return app.exec();
}