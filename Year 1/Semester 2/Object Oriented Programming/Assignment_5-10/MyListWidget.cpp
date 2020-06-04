//
// Created by Octavian Custura on 27/05/2020.
//

#include "MyListWidget.h"
#include <QBoxLayout>
#include <QShortcut>
#include <QMessageBox>
#include <QTimer>
#include <limits>
#include "IconDelegate.h"

MyListWidget::MyListWidget(const Service& service1, QAbstractItemModel* mode, QWidget *parent): myListModel{mode}, service{service1} {
	initGUI();
	myListView->setModel(myListModel);
	myListView->horizontalHeader();
	myListView->setItemDelegate(new IconDelegate{service});
}

void MyListWidget::initGUI() {
	auto* mainLayout = new QHBoxLayout{this};
	myListView = new QTableView{};
	myListView->setVisible(false);
	QRect viewportRect = myListView->viewport()->geometry();
	QRect viewportNew = viewportRect;
	viewportNew.setWidth(std::numeric_limits<int>::max());
//	myListView->resizeRowsToContents();
	myListView->resizeColumnsToContents();
//	myListView->resizeColumnToContents(5);
	myListView->setColumnWidth(5, 1);
	myListView->viewport()->setGeometry(viewportRect);
	this->resize(myListView->size());
	myListView->setVisible(true);
	mainLayout->addWidget(myListView);
}
