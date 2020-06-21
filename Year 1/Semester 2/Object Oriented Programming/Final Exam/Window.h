//
// Created by Octavian Custura on 20/06/2020.
//

#ifndef FINALEXAM_WINDOW_H
#define FINALEXAM_WINDOW_H
#include <QWidget>
#include <QTableView>
#include <QCheckBox>
#include <QAbstractItemModel>
#include "Observer.h"
#include "Service.h"
#include <QListView>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include "SearchModel.h"
#include <QFormLayout>
#include <QMessageBox>
#include "WindowModel.h"
#include "Drawing.h"
class Window: public QWidget {
private:
	QTableView* tableView;
	WindowModel* tableModel;
	Observer* observer;
	Service service;
	Astronomer astronomer;
	QListView* searchView{};
	QLineEdit* searchLineEdit;
	SearchModel* searchModel;
	QLineEdit* starNameLineEdit;
	QLineEdit* starRightAscensionsLineEdit;
	QLineEdit* starDeclinationLineEdit;
	QLineEdit* starDiameterLineEdit;
	QPushButton* addButton;
	QPushButton* viewButton;
	QCheckBox* checkBox;
	bool isChecked;
	void initGUI();
	void makeConnections();
	int getSelectedIndex();
public:
	Window(WindowModel* model, Observer* observer, Service service, Astronomer astronomer1, SearchModel* search);

};


#endif //FINALEXAM_WINDOW_H
