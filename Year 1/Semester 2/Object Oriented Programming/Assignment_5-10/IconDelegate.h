//
// Created by Octavian Custura on 28/05/2020.
//

#ifndef ASSIGNMENT_5_10_ICONDELEGATE_H
#define ASSIGNMENT_5_10_ICONDELEGATE_H

#include <QStyledItemDelegate>
#include "Service.h"
class IconDelegate: public QStyledItemDelegate {
private:
	Service service;
public:
	explicit IconDelegate(const Service& service, QWidget* parent = Q_NULLPTR);

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
	                 const QModelIndex &index) override;
};


#endif //ASSIGNMENT_5_10_ICONDELEGATE_H
