#include <QMouseEvent>
#include <QDebug>
#include "event.h"

QCustomPushButton::QCustomPushButton(QWidget *parent){}
void QCustomPushButton::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::RightButton) {
		emit rightClicked();
	}
	else {
		QPushButton::mousePressEvent(e);
	}
}

QCustomIconLabel::QCustomIconLabel(QWidget *parent){}
void QCustomIconLabel::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::RightButton) {
		emit rightClicked();
	}
}

QCustomDataLabel::QCustomDataLabel(QWidget *parent) {}
void QCustomDataLabel::mousePressEvent(QMouseEvent *e) {
	if (e->button() == Qt::MiddleButton) {
		emit middlePressed();
	}
}
void QCustomDataLabel::mouseReleaseEvent(QMouseEvent *e) {
	if (e->button() == Qt::MiddleButton) {
		emit middleReleased();
	}
}

TextChanged::TextChanged(QWidget *parent) {}
void TextChanged::changeValue(QString text) {
	emit valueChanged(text);
}

void GameOver::gameOverEvent() {
	emit gameOver();
}
void GameOver::victoryEvent() {
	emit victory();
}