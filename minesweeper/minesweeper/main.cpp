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

const int ROW = 10; //����ĭ�� ũ��
const int COL = 20;

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
		int mineCount = 25;
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

		int pos = 0;

		//�׸��忡 ��ư �࿭�� ������
		for (int i = 0; i < COL; i++) {
			for (int j = 0; j < ROW; j++) {
				QPushButton *button = new QPushButton(this);
				button->setFixedSize(28, 28);
				connect(button, &QPushButton::clicked, grid, [this, grid, i, j] {removeBtn(grid, i, j); });
				grid->addWidget(button, i, j);
				pos++;
			}
		}
	}
	// ��ư�� �������� ��ư�� ���ְ� ���ڸ��� ���ڵ����͸� ǥ����
	void removeBtn(QGridLayout *grid, int x, int y) {
		QWidget *btn = grid->itemAtPosition(x, y)->widget();
		layout()->removeWidget(btn);
		delete btn;
		QLabel *label = new QLabel(QString::number(mineData.data[x][y]), this);
		label->setAlignment(Qt::AlignCenter);
		grid->addWidget(label, x, y);
	}
};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Grid window;
	window.resize(WIDTH, HEIGHT);
	window.setWindowTitle("Mine Sweeper"); //������ â ����
	window.show();

	return app.exec();
}