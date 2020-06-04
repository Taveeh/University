#include "GUI.h"
#include <iostream>

GUI::GUI(Service ApplicationService, QWidget* Parent) 
 : ApplicationService(ApplicationService), QWidget(Parent)
{
	this->setWindowTitle("App");
	MainLayout = new QHBoxLayout(this);
	Display = new QListWidget();
	FieldsLayout = new QVBoxLayout();
	manufacturerLayout = new QHBoxLayout();
	manufacturerLabel = new QLabel("manufacturer");
	manufacturerLineEdit = new QLineEdit();
	FieldsLayout->addLayout(manufacturerLayout);
	manufacturerLayout->addWidget(manufacturerLabel);
	manufacturerLayout->addWidget(manufacturerLineEdit);
	modelLayout = new QHBoxLayout();
	modelLabel = new QLabel("model");
	modelLineEdit = new QLineEdit();
	FieldsLayout->addLayout(modelLayout);
	modelLayout->addWidget(modelLabel);
	modelLayout->addWidget(modelLineEdit);
	yearLayout = new QHBoxLayout();
	yearLabel = new QLabel("year");
	yearLineEdit = new QLineEdit();
	FieldsLayout->addLayout(yearLayout);
	yearLayout->addWidget(yearLabel);
	yearLayout->addWidget(yearLineEdit);
	colourLayout = new QHBoxLayout();
	colourLabel = new QLabel("colour");
	colourLineEdit = new QLineEdit();
	FieldsLayout->addLayout(colourLayout);
	colourLayout->addWidget(colourLabel);
	colourLayout->addWidget(colourLineEdit);
	ButtonLayout = new QVBoxLayout();
	AddButton = new QPushButton("Add");
	UpdateButton = new QPushButton("Update");
	RemoveButton = new QPushButton("Remove");

	MainLayout->addWidget(Display);
	MainLayout->addLayout(FieldsLayout);
	MainLayout->addLayout(ButtonLayout);
	ButtonLayout->addWidget(AddButton);
	ButtonLayout->addWidget(UpdateButton);
	ButtonLayout->addWidget(RemoveButton);

	auto filterLayout = new QVBoxLayout{};
	filterButton = new QPushButton{"Show cars"};
	manufacturerFilterLineEdit = new QLineEdit{};
	numberPerManufacturerLineEdit = new QLineEdit{};

	filterLayout->addWidget(filterButton);
	auto anotherLayout = new QHBoxLayout{};
	anotherLayout->addWidget(new QLabel("Manufacturer:"));
	anotherLayout->addWidget(manufacturerFilterLineEdit);
	auto anotherLayout1 = new QHBoxLayout{};
	anotherLayout1->addWidget(new QLabel("Number: "));
	anotherLayout1->addWidget(numberPerManufacturerLineEdit);
	filterLayout->addLayout(anotherLayout);
	filterLayout->addLayout(anotherLayout1);
	MainLayout->addLayout(filterLayout);
	this->loadServiceObjects();

	this->connectSignalsAndSlots();

}

void GUI::addSlot() 
{
	try {
	this->ApplicationService.add(
		this->manufacturerLineEdit->text().toStdString(),
		this->modelLineEdit->text().toStdString(),
		this->yearLineEdit->text().toStdString(),
		this->colourLineEdit->text().toStdString()
		);
	} catch(std::exception& Error)
	{
		QMessageBox::critical(this, "Error", Error.what());
		return;
	}
	this->Display->clear();
	this->loadServiceObjects();

}

void GUI::updateSlot() 
{
	try {
	this->ApplicationService.update(
		this->manufacturerLineEdit->text().toStdString(),
		this->modelLineEdit->text().toStdString(),
		this->yearLineEdit->text().toStdString(),
		this->colourLineEdit->text().toStdString()
		);
	} catch(std::exception& Error)
	{
		QMessageBox::critical(this, "Error", Error.what());
		return;
	}
	this->Display->clear();

	this->loadServiceObjects();

}

void GUI::removeSlot() 
{
	try {
	this->ApplicationService.remove(
	this->manufacturerLineEdit->text().toStdString());

	} catch(std::exception& Error)
	{
		QMessageBox::critical(this, "Error", Error.what());
		return;
	}
	this->Display->clear();

	this->loadServiceObjects();

}

void GUI::selectionSlot() 
{
	QModelIndexList selectedIndexes = this->Display->selectionModel()->selectedIndexes();
	if(selectedIndexes.size() == 0)
	{
		this->manufacturerLineEdit->clear();
		this->modelLineEdit->clear();
		this->yearLineEdit->clear();
		this->colourLineEdit->clear();
	}
	else {
		int selectedIndex = selectedIndexes.at(0).row();
		Car selectedObject = this->ApplicationService.list()[selectedIndex];
		this->manufacturerLineEdit->setText(QString::fromStdString(selectedObject.getmanufacturer()));
		this->modelLineEdit->setText(QString::fromStdString(selectedObject.getmodel()));
		this->yearLineEdit->setText(QString::fromStdString(std::to_string(selectedObject.getyear())));
		this->colourLineEdit->setText(QString::fromStdString(selectedObject.getcolour()));
	}

}

void GUI::loadServiceObjects() 
{
	std::vector<Car> container = ApplicationService.list();
	sort(container.begin(), container.end(), [](Car a, Car b) {
		return a.getmanufacturer() < b.getmanufacturer();
	});
	int index = 0;
	for (Car currentObject : container)
	{
		this->Display->addItem(QString::fromStdString(currentObject.getmanufacturer() + " - " + currentObject.getmodel()));
		Display->item(index)->setTextColor(currentObject.getcolour().c_str());
		index++;

	}
}

void GUI::connectSignalsAndSlots() 
{
	QObject::connect(AddButton, &QPushButton::clicked, this, &GUI::addSlot);
	QObject::connect(UpdateButton, &QPushButton::clicked, this, &GUI::updateSlot);
	QObject::connect(RemoveButton, &QPushButton::clicked, this, &GUI::removeSlot);
	QObject::connect(Display, &QListWidget::itemSelectionChanged, this, &GUI::selectionSlot);
	QObject::connect(filterButton, &QPushButton::clicked, this, &GUI::getNumberByMan);

}

void GUI::getNumberByMan() {
	auto elements = ApplicationService.getNumberByMan(manufacturerFilterLineEdit->text().toStdString());
	numberPerManufacturerLineEdit->setText(QString::fromStdString(std::to_string(elements)));
}

