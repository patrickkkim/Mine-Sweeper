#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

//�׸��带 �����ϴ� Ŭ����
class Grid : public QWidget {
public:
	Grid(QWidget *parent = 0) {
		QGridLayout *grid = new QGridLayout(this);
		grid->setSpacing(0);

		int pos = 0;

		//����,���� �׸��带 ��ư���� ������
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				QPushButton *btn = new QPushButton(this);
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
