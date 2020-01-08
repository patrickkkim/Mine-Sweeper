#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QWidget window;
	window.resize(500, 350);
	window.setWindowTitle("Mine Sweeper");
	window.show();

	return app.exec();
}
