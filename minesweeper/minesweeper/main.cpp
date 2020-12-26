#include <QApplication>
#include "windowbox.h"

const int WIDTH = 300; //������ â�� ũ��
const int HEIGHT = 600;
const int ROW = 10; //���ڹ迭�� ũ��
const int COL = 20;
const int MINEMAXCOUNT = 40; //�����ִ� ����

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	WindowBox *window = new WindowBox(ROW, COL, MINEMAXCOUNT);
	window->resize(WIDTH, HEIGHT);
	window->setWindowTitle("Mine Sweeper"); //������ â ����
	window->setWindowFlags(window->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	window->show();

	return app.exec();
}