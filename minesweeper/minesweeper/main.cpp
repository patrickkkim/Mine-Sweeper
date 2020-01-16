#include <QApplication>
#include "minegrid.h"

const int WIDTH = 300; //윈도우 창의 크기
const int HEIGHT = 200;
const int ROW = 10; //지뢰배열의 크기
const int COL = 20;
const int MINEMAXCOUNT = 40; //지뢰최대 갯수

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	MineGrid *window = new MineGrid(ROW, COL, MINEMAXCOUNT);
	window->resize(WIDTH, HEIGHT);
	window->setWindowTitle("Mine Sweeper"); //윈도우 창 제목
	window->show();

	return app.exec();
}