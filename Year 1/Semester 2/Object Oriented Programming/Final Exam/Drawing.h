//
// Created by Octavian Custura on 20/06/2020.
//

#ifndef FINALEXAM_DRAWING_H
#define FINALEXAM_DRAWING_H
#include <QWidget>
#include <QPainter>
#include <utility>
#include "Domain.h"
class Drawing: public QWidget {
private:
	void setFloatBased(bool floatBased);
	void setAntialiased(bool antialiased);

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

	bool floatBased;
	bool antialiased;
	int frameNo;
	std::vector<Star> stars;
	Star theStar;
public:
	Drawing(QWidget* parent = Q_NULLPTR);
	void addStars(std::vector<Star> s, Star star);
protected:
	void paintEvent(QPaintEvent *event) override;

};


#endif //FINALEXAM_DRAWING_H
