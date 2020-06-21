//
// Created by Octavian Custura on 20/06/2020.
//

#include "Drawing.h"

void Drawing::setFloatBased(bool floatBased) {
	this->floatBased = floatBased;
	update();
}

void Drawing::setAntialiased(bool antialiased) {
	this->antialiased = antialiased;
	update();
}

QSize Drawing::minimumSizeHint() const {
	return QSize(50, 50);
}

QSize Drawing::sizeHint() const {
	return QSize(180, 180);
}

Drawing::Drawing(QWidget *parent) {
	floatBased = false;
	antialiased = false;
	frameNo = 0;
	setBackgroundRole(QPalette::Base);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Drawing::addStars(std::vector<Star> s, Star star) {
	stars = std::move(s);
	theStar = star;
}

void Drawing::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, antialiased);
	painter.translate(width() / 2, height() / 2);
	for (auto el: stars) {
		if (el == theStar) {
			QPen pen;
			pen.setColor(QColor(255,0,0,255));
			painter.setPen(pen);
			painter.drawEllipse(QPoint(el.getRightAscension(), el.getDeclination()), el.getDiameter(),
			                    el.getDiameter());
		}else {
			QPen pen;
			pen.setColor(QColor(0,0,0,255));
			painter.setPen(pen);
			painter.drawEllipse(QPoint(el.getRightAscension(), el.getDeclination()), el.getDiameter(),
			                    el.getDiameter());
		}
	}
}
