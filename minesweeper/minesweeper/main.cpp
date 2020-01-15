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
const int ROW = 10; //지뢰배열의 크기
const int COL = 20;
const int MINEMAXCOUNT = 50; //지뢰최대 갯수

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

//그리드를 생성하는 클래스
class Grid : public QWidget {
public: 
	MineData mineData;

	Grid(QWidget *parent = 0) {
		QGridLayout *grid = new QGridLayout(this);
		grid->setSpacing(0);

		//그리드에 버튼 행열로 생성함
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

	// 버튼이 눌렷을시 버튼을 없애고 그자리에 지뢰데이터를 표시함
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
		
		// 게임오버 임시적으로 구현. 수정바람
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
	window.setWindowTitle("Mine Sweeper"); //윈도우 창 제목
	window.show();

	return app.exec();
}