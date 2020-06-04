//
// Created by Octavian Custura on 28/05/2020.
//

#include "IconDelegate.h"
#include <QPainter>
#include <iostream>
#include <QPixmap>
#include <QToolButton>
#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include "Footage.h"
void IconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	if (index.column() != 5) {
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}else {
		QIcon playIcon("play.jpg");
//		painter->fillRect(option.rect, option.palette.highlight());
//		playIcon.paint(painter, option.rect, option.palette, QIcon::);
//		painter->drawPixmap(option.rect, pixmap);
//		auto* playButton = new QPushButton{};
//		playButton->setGeometry(option.rect);
//		playButton->setIcon(playIcon);
//		if (option.state == QStyle::State_Selected) {
//			painter->fillRect(option.rect, option.palette.highlight());
//		}
//		QPixmap pixmap = playButton->grab();
//		painter->drawPixmap(option.rect.x(), option.rect.y(), pixmap);
//		playButton.text = "Text";
//		playButton.rect = option.rect;
//		playButton.state = QStyle::State_Enabled;
//		QApplication::style()->drawControl(QStyle::CE_PushButtonLabel, &playButton, painter);
//		QIcon playIcon("play.jpg");
//		QObject::connect(playIcon, SIGNAL(QMouseEvent), this, [this]() {
//			system("open safari");
//		});
		playIcon.paint(painter, option.rect);

	}

}

QSize IconDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
	if (index.column() == 5) {
		return {2, 1};
	}
	return QStyledItemDelegate::sizeHint(option, index);
}

IconDelegate::IconDelegate(const Service& service1, QWidget *parent): service{service1}, QStyledItemDelegate{parent} {

}

bool IconDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                               const QModelIndex &index) {

	if (event->type() == QEvent::MouseButtonPress and index.column() == 5) {
		int row = index.row();
		std::string command = "open " + service.getMyList()[row].getLink();
		system(command.c_str());
	}
	return true;
}


