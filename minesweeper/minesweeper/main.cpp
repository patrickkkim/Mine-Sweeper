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
const int MINEMAXCOUNT = 50; //�����ִ� ����

//�׸����� �����͸� �����ϴ� Ŭ����
class MineData {
public:
	std::vector<std::vector<int>> data;

	MineData() {
		data.resize(COL, std::vector<int>(ROW, 0)); //2�������� �����͸� ���� 0���� �ʱ�ȭ

		//��,�� �������������� ����
		std::random_device seeder;
		std::mt19937 engine(seeder());
		std::uniform_int_distribution<int> distRow(0, ROW -1);
		std::uniform_int_distribution<int> distCol(0, COL -1);

		//���� ��,���� ����(1)�� �������� ����
		int mineCount = MINEMAXCOUNT;
		int randCol;
		int randRow;
		while (mineCount > 0) {
			randCol = distCol(engine);
			randRow = distRow(engine);
			if (data[randCol][randRow] != 1) {
				data[randCol][randRow] = 1;
				mineCount--;
			}
		}
	}
};

//�׸��带 �����ϴ� Ŭ����
class Grid : public QWidget {
public: 
	MineData mineData;

	Grid(QWidget *parent = 0) {
		QGridLayout *grid = new QGridLayout(this);
		grid->setSpacing(0);

		//�׸��忡 ��ư �࿭�� ������
		int pos = 0;
		for (int i = 0; i < COL; i++) {
			for (int j = 0; j < ROW; j++) {
				QPushButton *button = new QPushButton(this);
				button->setFixedSize(28, 28);
				connect(button, &QPushButton::clicked, grid, [this, grid, i, j] {buttonClicked(grid, i, j); });
				grid->addWidget(button, i, j);
				pos++;
			}
		}
	}

	// ��ư�� �������� ��ư�� ���ְ� ���ڸ��� ���ڵ����͸� ǥ����
	void buttonClicked(QGridLayout *grid, int x, int y) {
		QWidget *btn = grid->itemAtPosition(x, y)->widget();
		layout()->removeWidget(btn);
		delete btn;
		if (isMine(x, y)) {
			QLabel *label = new QLabel(this);
			QPixmap pixmap("../icons/Mine.png");
			label->setPixmap(pixmap.scaled(26, 26, Qt::KeepAspectRatio));
			grid->addWidget(label, x, y);
		}
		else {
			int count = 0;
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
			for (int i = xStart; i < xRange; i++) {
				for (int j = yStart; j < yRange; j++) {
					if (isMine(x+i, y+j)) {
						count++;
					}
				}
			}
			if (count != 0) {
				QLabel *label = new QLabel(QString::number(count), this);
				label->setAlignment(Qt::AlignCenter);
				grid->addWidget(label, x, y);
			}
			else {
				QLabel *label = new QLabel(this);
			}
		}
		
		// ���ӿ��� �ӽ������� ����. �����ٶ�
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

	bool isGameOver() {}

	bool isMine(int x, int y) {
		if (mineData.data[x][y] == 1) {
			return true;
		}
		else {
			return false;
		}
	}
};

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	Grid window;
	window.resize(WIDTH, HEIGHT);
	window.setWindowTitle("Mine Sweeper"); //������ â ����
	window.show();

	return app.exec();
}