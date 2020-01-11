#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <iostream>
#include <random>
#include <vector>

//그리드의 데이터를 생성하는 클래스
class MineData {
private:
	//행 과 열의 크기 설정
	int row = 10;
	int col = 20;
public:
	std::vector<std::vector<int>> data;
	MineData() {
		data.resize(col, std::vector<int>(row, 0)); //2차원벡터 데이터를 전부 0으로 초기화

		//행,열 랜덤변수생성기 생성
		std::random_device seeder;
		std::mt19937 engine(seeder());
		std::uniform_int_distribution<int> distRow(0, row-1);
		std::uniform_int_distribution<int> distCol(0, col-1);

		//벡터 행,열에 지뢰(1)를 랜덤으로 생성
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

//그리드를 생성하는 클래스
class Grid : public QWidget {
public: 
	Grid(QWidget *parent = 0) {
		QGridLayout *grid = new QGridLayout(this);
		grid->setSpacing(0);

		MineData mineData;

		int pos = 0;

		//그리드에 버튼 행열로 생성함
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

