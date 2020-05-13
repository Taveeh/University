//
// Created by Octavian Custura on 08/05/2020.
//

#ifndef ASSIGNMENT_9_GUI_H
#define ASSIGNMENT_9_GUI_H
#include <QApplication>
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "Service.h"
#include <QtCharts/QChart>

QT_CHARTS_USE_NAMESPACE
class GUI: public QWidget {
private:
	Service service;
	void initGUI();
	void populateList(QListWidget*);
	void makeConnections();
	int getSelectedFootage(QListWidget*) const;
	void createStatistics();
	void populateMyList(QListWidget*);
	void readProperties();

	// graphical element
	QLineEdit* repositoryLineEdit{};
	QLineEdit* myListLineEdit{};
	QPushButton* setPathRepository{};
	QPushButton* setPathMyList{};

	QLineEdit* repositoryLineEditB{};
	QLineEdit* myListLineEditB{};
	QPushButton* setPathRepositoryB{};
	QPushButton* setPathMyListB{};

	QListWidget* footageListWidget{};
	QListWidget* footageListWidgetModeB{};
	QListWidget* footageMyList{};
	QLineEdit* titleLineEdit{};
	QLineEdit* typeLineEdit{};
	QLineEdit* dateLineEdit{};
	QLineEdit* accessCountLineEdit{};
	QLineEdit* linkLineEdit{};
	QPushButton * buttonAdd{};
	QPushButton * buttonRemove{};
	QPushButton * buttonUpdate{};

	QPushButton* saveMyList{};
	QPushButton* next{};
	QPushButton* openMyList{};

	QTabWidget* tabWidget{};
	QChart* dataRepresentation{};

public:
	explicit GUI(Service& service1);
private:
	void setRepository();
	void setMyList();
	void addFootage();
	void removeFootage();
	void updateFootage();
	void setRepositoryB();
	void setMyListB();
	void saveFootage();
	void nextFootage();
	void openList();

};



#endif //ASSIGNMENT_9_GUI_H
