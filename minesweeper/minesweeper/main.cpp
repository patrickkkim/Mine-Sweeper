#include <QApplication>
#include "windowbox.h"

const int WIDTH = 300; //윈도우 창의 크기
const int HEIGHT = 600;
const int ROW = 10; //지뢰배열의 크기
const int COL = 20;
const int MINEMAXCOUNT = 40; //지뢰최대 갯수

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	WindowBox *window = new WindowBox(ROW, COL, MINEMAXCOUNT);
	window->resize(WIDTH, HEIGHT);
	window->setWindowTitle("Mine Sweeper"); //윈도우 창 제목
	window->setWindowFlags(window->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	window->show();

	return app.exec();
}