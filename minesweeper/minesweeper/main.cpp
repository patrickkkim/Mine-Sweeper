#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <iostream>
#include <random>
#include <vector>

//�׸����� �����͸� �����ϴ� Ŭ����
class MineData {
private:
	//�� �� ���� ũ�� ����
	int row = 10;
	int col = 20;
public:
	std::vector<std::vector<int>> data;
	MineData() {
		data.resize(col, std::vector<int>(row, 0)); //2�������� �����͸� ���� 0���� �ʱ�ȭ

		//��,�� �������������� ����
		std::random_device seeder;
		std::mt19937 engine(seeder());
		std::uniform_int_distribution<int> distRow(0, row-1);
		std::uniform_int_distribution<int> distCol(0, col-1);

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

		for (int i = 0; i < col; ++i) {
			for (int j = 0; j < row; ++j) {
				break;
			}
		}
	}
};

//�׸��带 �����ϴ� Ŭ����
class Grid : public QWidget {
public: 
	Grid(QWidget *parent = 0) {
		QGridLayout *grid = new QGridLayout(this);
		grid->setSpacing(0);

		MineData mineData;

		int pos = 0;

		//�׸��忡 ��ư �࿭�� ������
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				QPushButton *btn = new QPushButton(QString::number(mineData.data[i][j]), this);
				btn->setFixedSize(25, 25);
				grid->addWidget(btn, i, j);
				pos++;
			}
		}
	}
};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Grid window;
	window.resize(300, 200);
	window.setWindowTitle("Mine Sweeper");
	window.show();

	return app.exec();
}

