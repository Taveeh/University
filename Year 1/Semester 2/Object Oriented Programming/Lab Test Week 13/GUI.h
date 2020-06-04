#pragma once
#include "QtWidgets/qwidget.h"
#include "Service.h"
#include "qlayout.h"
#include "QListWidget.h"
#include "QLabel.h"
#include "QLineEdit.h"
#include "QPushButton.h"
#include "QString.h"
#include "QMessageBox.h"



class GUI : public QWidget
{

Q_OBJECT
private: 
	Service ApplicationService;
	QHBoxLayout* MainLayout;
	QListWidget* Display;
	QVBoxLayout* FieldsLayout;
	QHBoxLayout* manufacturerLayout;
	QLabel* manufacturerLabel;
	QLineEdit* manufacturerLineEdit;
	QHBoxLayout* modelLayout;
	QLabel* modelLabel;
	QLineEdit* modelLineEdit;
	QHBoxLayout* yearLayout;
	QLabel* yearLabel;
	QLineEdit* yearLineEdit;
	QHBoxLayout* colourLayout;
	QLabel* colourLabel;
	QLineEdit* colourLineEdit;
	QVBoxLayout* ButtonLayout;
	QPushButton* AddButton;
	QPushButton* UpdateButton;
	QPushButton* RemoveButton;
	QPushButton* filterButton;
	QLineEdit* manufacturerFilterLineEdit;
	QLineEdit* numberPerManufacturerLineEdit;

	void addSlot();
	void updateSlot();
	void removeSlot();
	void selectionSlot();
	void getNumberByMan();

public: 
	GUI(Service ApplicationService = Service(), QWidget* Parent = Q_NULLPTR);
   

	void loadServiceObjects();
	void connectSignalsAndSlots();


};
