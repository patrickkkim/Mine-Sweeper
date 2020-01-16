#include <QMouseEvent>
#include "event.h"

QCustomPushButton::QCustomPushButton(QWidget *parent)
{}

void QCustomPushButton::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::RightButton) {
		emit rightClicked();
	}
	else {
		QPushButton::mousePressEvent(e);
	}
}

QCustomLabel::QCustomLabel(QWidget *parent){}

void QCustomLabel::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::RightButton) {
		emit rightClicked();
	}
}