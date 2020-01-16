#pragma once
#include <QPushButton>
#include <QLabel>

class QCustomPushButton : public QPushButton {
	Q_OBJECT
public:
	QCustomPushButton(QWidget *parent = 0);
private slots:
	void mousePressEvent(QMouseEvent *e);
signals:
	void rightClicked();
};

class QCustomLabel : public QLabel {
	Q_OBJECT
public:
	QCustomLabel(QWidget *parent = 0);
private slots:
	void mousePressEvent(QMouseEvent *e);
signals:
	void rightClicked();
};