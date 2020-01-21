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

class QCustomIconLabel : public QLabel {
	Q_OBJECT
public:
	QCustomIconLabel(QWidget *parent = 0);
private slots:
	void mousePressEvent(QMouseEvent *e);
signals:
	void rightClicked();
};

class QCustomDataLabel : public QLabel {
	Q_OBJECT
public:
	QCustomDataLabel(QWidget *parent = 0);
private slots:
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
signals:
	void middleClicked();
	void middlePressed();
	void middleReleased();
};

class TextChanged : public QLabel {
	Q_OBJECT
public:
	TextChanged(QWidget *parent = 0);
public slots:
	void changeValue(QString);
signals:
	void valueChanged(QString);
};