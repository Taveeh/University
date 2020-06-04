//
// Created by Octavian Custura on 27/05/2020.
//

#ifndef ASSIGNMENT_5_10_MYLISTWIDGET_H
#define ASSIGNMENT_5_10_MYLISTWIDGET_H
#include <QWidget>
#include <QAbstractTableModel>
#include <QTableView>
#include "MyListTableModel.h"
#include "ActualAbstractTableModel.h"
class MyListWidget: public QWidget {
private:
	QAbstractItemModel* myListModel;
	QTableView* myListView;
	void initGUI();
	Service service;
public:
	MyListWidget(const Service&, QAbstractItemModel* mode, QWidget* parent = Q_NULLPTR);
};


#endif //ASSIGNMENT_5_10_MYLISTWIDGET_H
