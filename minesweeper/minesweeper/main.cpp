#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <iostream>
#include <random>
#include <vector>

const int WIDTH = 300; //윈도우 창의 크기
const int HEIGHT = 200;

const int ROW = 10; //지뢰칸의 크기
const int COL = 20;

//그리드의 데이터를 생성하는 클래스
class MineData {
public:
	std::vector<std::vector<int>> data;

	MineData() {
		data.resize(COL, std::vector<int>(ROW, 0)); //2차원벡터 데이터를 전부 0으로 초기화

		//행,열 랜덤변수생성기 생성
		std::random_device seeder;
		std::mt19937 engine(seeder());
		std::uniform_int_distribution<int> distRow(0, ROW -1);
		std::uniform_int_distribution<int> distCol(0, COL -1);

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
	}
};

//그리드를 생성하는 클래스
class Grid : public QWidget {
public: 
	MineData mineData;

	Grid(QWidget *parent = 0) {
		QGridLayout *grid = new QGridLayout(this);
		grid->setSpacing(0);

		int pos = 0;

		//그리드에 버튼 행열로 생성함
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
	// 버튼이 눌렷을시 버튼을 없애고 그자리에 지뢰데이터를 표시함
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
	window.setWindowTitle("Mine Sweeper"); //윈도우 창 제목
	window.show();

	return app.exec();
}