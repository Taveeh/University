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
#include <QVBoxLayout>
#include <QShortcut>
#include "MyListWidget.h"
#include "MyFilteredListTableModel.h"
#include <QSortFilterProxyModel>
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
	QPushButton* buttonUndo{};
	QPushButton* buttonRedo{};

	QPushButton* saveMyList{};
	QPushButton* next{};
	QPushButton* openMyList{};
	QPushButton* showMyList{};
	QPushButton* advanced{};
	QPushButton* undoMyList{};
	QPushButton* redoMyList{};

	QTabWidget* tabWidget{};
	QChart* dataRepresentation{};

	QPushButton* filterList{};
	QPushButton* myList{};
	QLineEdit* filterTypeLineEdit{};
	QLineEdit* filterCountLineEdit{};
	QVBoxLayout* modeBLayout{};
	QGridLayout* newLayout{};
	QWidget* modeBWidget{};

	QShortcut* undoShortcut{};
	QShortcut* redoShortcut{};

	std::vector<MyListWidget*> myListWidgets;
	MyListWidget* myListWidget{};
	MyListTableModel* myListTableModel;
	QSortFilterProxyModel* myFilteredListTableModel{};
public:
	explicit GUI(Service& service1);
private:
	bool advancedState;
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
	void advancedSettings();
	void filterFunction();
	void unFilterFunction();
	void undoAction();
	void redoAction();
	void showMyListNewWindow();
};



#endif //ASSIGNMENT_9_GUI_H
