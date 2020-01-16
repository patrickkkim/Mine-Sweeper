#include <QApplication>
#include "minegrid.h"

const int WIDTH = 300; //������ â�� ũ��
const int HEIGHT = 200;
const int ROW = 10; //���ڹ迭�� ũ��
const int COL = 20;
const int MINEMAXCOUNT = 40; //�����ִ� ����

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	MineGrid *window = new MineGrid(ROW, COL, MINEMAXCOUNT);
	window->resize(WIDTH, HEIGHT);
	window->setWindowTitle("Mine Sweeper"); //������ â ����
	window->show();

	return app.exec();
}