//
// Created by Octavian Custura on 08/05/2020.
//

#include "GUI.h"
#include <fstream>
#include <QtWidgets>
#include <qlayout.h>
#include <QFormLayout>
#include <vector>
#include <iostream>
#include <qmessagebox.h>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE

GUI::GUI(Service &service1): service(service1){
	initGUI();
	readProperties();
	makeConnections();
}

void GUI::initGUI() {
	// Initiate elements
	footageListWidget = new QListWidget;
	footageListWidgetModeB = new QListWidget{};
	footageMyList = new QListWidget{};
	titleLineEdit = new QLineEdit;
	typeLineEdit = new QLineEdit;
	dateLineEdit = new QLineEdit;
	accessCountLineEdit = new QLineEdit;
	linkLineEdit = new QLineEdit;
	repositoryLineEdit = new QLineEdit{};
	myListLineEdit = new QLineEdit{};
	setPathRepository = new QPushButton{"Set repository"};
	setPathMyList = new QPushButton{"Set My List"};

	repositoryLineEditB = new QLineEdit{};
	myListLineEditB = new QLineEdit{};
	setPathRepositoryB = new QPushButton{"Set repository"};
	setPathMyListB = new QPushButton{"Set My List"};

	buttonAdd = new QPushButton{"Add"};
	buttonRemove = new QPushButton{"Remove"};
	buttonUpdate = new QPushButton{"Update"};

	saveMyList = new QPushButton{"Save"};
	next = new QPushButton{"Next"};
	openMyList = new QPushButton{"Open"};

	tabWidget = new QTabWidget;
	auto *parentLayout = new QVBoxLayout(this);
	parentLayout->addWidget(tabWidget);

	QWidget* mainWidget = new QWidget();
	QWidget* modeAWidget = new QWidget();
	// Initiate main layout
	QVBoxLayout* mainLayout = new QVBoxLayout(modeAWidget);

	//Set path
	QVBoxLayout* setPathLayout = new QVBoxLayout{};

	QHBoxLayout* setRepositoryLayout = new QHBoxLayout{};
	QLabel* repoLabel = new QLabel("Repository");
	repoLabel->setFixedWidth(75);
	setRepositoryLayout->addWidget(repoLabel);
	setPathRepository->setFixedWidth(150);
	setRepositoryLayout->addWidget(repositoryLineEdit);
	setRepositoryLayout->addWidget(setPathRepository);
	setPathLayout->addLayout(setRepositoryLayout);

	QHBoxLayout* setMyListLayout = new QHBoxLayout{};
	QLabel* myListLabel = new QLabel("My list");
	myListLabel->setFixedWidth(75);
	setMyListLayout->addWidget(myListLabel);
	setPathMyList->setFixedWidth(150);
	setMyListLayout->addWidget(myListLineEdit);
	setMyListLayout->addWidget(setPathMyList);
	setPathLayout->addLayout(setMyListLayout);

	mainLayout->addLayout(setPathLayout);

	QHBoxLayout * adminMode = new QHBoxLayout();
	// Initiate functionality
	QVBoxLayout * functionality = new QVBoxLayout();
	// Text edits for Footage
	QFormLayout * footageDetails = new QFormLayout{};
	footageDetails->addRow("Title", titleLineEdit);
	footageDetails->addRow("Type", typeLineEdit);
	footageDetails->addRow("Date", dateLineEdit);
	footageDetails->addRow("Access Count", accessCountLineEdit);
	footageDetails->addRow("Link", linkLineEdit);
	functionality->addLayout(footageDetails);

	// Buttons
	QGridLayout* buttonsLayout = new QGridLayout{};
	buttonsLayout->addWidget(buttonAdd, 0, 0);
	buttonsLayout->addWidget(buttonRemove, 0, 1);
	buttonsLayout->addWidget(buttonUpdate, 0, 2);
	functionality->addLayout(buttonsLayout);

	adminMode->addLayout(functionality);
	adminMode->addWidget(footageListWidget);

	mainLayout->addLayout(adminMode);
	modeAWidget->setLayout(mainLayout);
	tabWidget->addTab(modeAWidget, "Admin Mode");
	QVBoxLayout* statisticLayout = new QVBoxLayout();
	QWidget* statisticsWidget = new QWidget();

	dataRepresentation = new QChart();
	dataRepresentation->setTitle("Views");
	dataRepresentation->setAnimationOptions(QChart::SeriesAnimations);
	QChartView* chartView = new QChartView(dataRepresentation);
	statisticLayout->addWidget(chartView);
	statisticsWidget->setLayout(statisticLayout);
	tabWidget->addTab(statisticsWidget, "Statistics");

	//Mode B
	QWidget* modeBWidget = new QWidget{};
	QVBoxLayout* modeBLayout = new QVBoxLayout{};
	QVBoxLayout* setPathLayoutB = new QVBoxLayout{};
	QHBoxLayout* setRepoLayoutB = new QHBoxLayout{};
	QHBoxLayout* setMyListLayoutB = new QHBoxLayout{};


	// Set path Layout
	repoLabel->setFixedWidth(75);
	setRepoLayoutB->addWidget(repoLabel);
	setPathRepositoryB->setFixedWidth(150);
	setRepoLayoutB->addWidget(repositoryLineEditB);
	setRepoLayoutB->addWidget(setPathRepositoryB);
	setPathLayoutB->addLayout(setRepoLayoutB);

	myListLabel->setFixedWidth(75);
	setMyListLayoutB->addWidget(myListLabel);
	setPathMyListB->setFixedWidth(150);
	setMyListLayoutB->addWidget(myListLineEditB);
	setMyListLayoutB->addWidget(setPathMyListB);
	setPathLayoutB->addLayout(setMyListLayoutB);
	modeBLayout->addLayout(setPathLayoutB);
	QHBoxLayout* functionalityLayout = new QHBoxLayout{};

	functionalityLayout->addWidget(footageListWidgetModeB);
	QVBoxLayout* buttonsMyList = new QVBoxLayout{};
	buttonsMyList->addWidget(saveMyList);
	buttonsMyList->addWidget(next);
	buttonsMyList->addWidget(openMyList);
	functionalityLayout->addLayout(buttonsMyList);
	functionalityLayout->addWidget(footageMyList);
	modeBLayout->addLayout(functionalityLayout);

	modeBWidget->setLayout(modeBLayout);
	tabWidget->addTab(modeBWidget, "User Mode");

}

void GUI::populateList(QListWidget* listWidget) {
	listWidget->clear();

	std::vector<Footage> listOfFootage = service.getAllElements();
	for (const auto& footage: listOfFootage) {
		listWidget->addItem(QString::fromStdString(footage.getTitle() + " - " + footage.getType()));
	}
}

void GUI::makeConnections() {
	QObject::connect(footageListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->getSelectedFootage(footageListWidget);

		if (selectedIndex < 0){
			titleLineEdit->clear();
			typeLineEdit->clear();
			dateLineEdit->clear();
			accessCountLineEdit->clear();
			linkLineEdit->clear();
			return;
		}
		Footage footage = service.getAllElements().at(selectedIndex);
		this->titleLineEdit->setText(QString::fromStdString(footage.getTitle()));
		this->typeLineEdit->setText(QString::fromStdString(footage.getType()));
		this->dateLineEdit->setText(QString::fromStdString(footage.getDate().toString()));
		this->accessCountLineEdit->setText(QString::fromStdString(std::to_string(footage.getAccessCount())));
		this->linkLineEdit->setText(QString::fromStdString(footage.getLink()));
	});
	QObject::connect(setPathRepository, &QPushButton::clicked, this, &GUI::setRepository);
	QObject::connect(setPathRepositoryB, &QPushButton::clicked, this, &GUI::setRepositoryB);
	QObject::connect(setPathMyListB, &QPushButton::clicked, this, &GUI::setMyListB);
	QObject::connect(setPathMyList, &QPushButton::clicked, this, &GUI::setMyList);
	QObject::connect(buttonAdd, &QPushButton::clicked, this, &GUI::addFootage);
	QObject::connect(buttonRemove, &QPushButton::clicked, this, &GUI::removeFootage);
	QObject::connect(buttonUpdate, &QPushButton::clicked, this, &GUI::updateFootage);
	QObject::connect(saveMyList, &QPushButton::clicked, this, &GUI::saveFootage);
	QObject::connect(next, &QPushButton::clicked, this, &GUI::nextFootage);
	QObject::connect(openMyList, &QPushButton::clicked, this, &GUI::openList);

}

int GUI::getSelectedFootage(QListWidget* listWidget) const {
	QModelIndexList selectedIndexes = listWidget->selectionModel()->selectedIndexes();
	if (selectedIndexes.empty()) {
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void GUI::setRepository() {
	std::string path = repositoryLineEdit->text().toStdString();
	service.setPath(path, "repository");
	populateList(footageListWidget);
	populateList(footageListWidgetModeB);
	createStatistics();
}

void GUI::setMyList() {
	std::string path = myListLineEdit->text().toStdString();
	service.setPath(path, "mylist");
	populateMyList(footageMyList);
}

void GUI::addFootage() {
	std::string newTitle = titleLineEdit->text().toStdString();
	std::string newType = " " + typeLineEdit->text().toStdString();
	std::string newDateString = " " + dateLineEdit->text().toStdString();
	std::string newAccessCountString = " " + accessCountLineEdit->text().toStdString();
	std::string newLink = " " + linkLineEdit->text().toStdString();
	try {
		service.addFootage(newTitle, newType, newDateString, newAccessCountString, newLink);
	}catch(ValidationException& e) {
		QMessageBox::critical(this, "Error", e.what());
		return;
	}catch(RepositoryException& e) {
		QMessageBox::critical(this, "Error", e.what());
		return;
	}
	populateList(footageListWidget);
	populateList(footageListWidgetModeB);

	createStatistics();
	int lastElement = static_cast<int>(service.getAllElements().size() - 1);
	footageListWidget->setCurrentRow(lastElement);
}

void GUI::removeFootage() {
	std::string titleToBeRemoved = titleLineEdit->text().toStdString();
	try {
		service.deleteFootage(titleToBeRemoved);
	}catch(ValidationException& e) {
		QMessageBox::critical(this, "Error", e.what());
		return;
	}catch(RepositoryException& e) {
		QMessageBox::critical(this, "Error", e.what());
		return;
	}
	populateList(footageListWidget);
	populateList(footageListWidgetModeB);

	createStatistics();

}

void GUI::updateFootage() {
	std::string newTitle = titleLineEdit->text().toStdString();
	std::string newType = " " + typeLineEdit->text().toStdString();
	std::string newDateString = " " + dateLineEdit->text().toStdString();
	std::string newAccessCountString = " " + accessCountLineEdit->text().toStdString();
	std::string newLink = " " + linkLineEdit->text().toStdString();
	try {
		service.updateFootage(newTitle, newType, newDateString, newAccessCountString, newLink);
	} catch (ValidationException& e) {
		QMessageBox::critical(this, "Error", e.what());
		return;
	}
	populateList(footageListWidget);
	populateList(footageListWidgetModeB);

	createStatistics();

	auto footageList = service.getAllElements();
	int index = 0;
	for (const auto& footage: footageList) {
		if (footage.getTitle() == newTitle) {
			break;
		}
		index++;
	}
	footageListWidget->setCurrentRow(index);

}

void GUI::createStatistics() {
	std::vector<QBarSet*> chartSets;
	chartSets.clear();
	std::vector<Footage> footageList = service.getAllElements();
	for (const auto& footage: footageList) {
		QBarSet* set = new QBarSet(QString::fromStdString(footage.getTitle()));
		*set << footage.getAccessCount();
		chartSets.push_back(set);
	}
	dataRepresentation->removeAllSeries();
	QBarSeries* series = new QBarSeries();
	for (auto set: chartSets) {
		series->append(set);
	}
	QStringList category;
	category << "Footage title";
	QBarCategoryAxis* axis = new QBarCategoryAxis();
	axis->append(category);
	dataRepresentation->addSeries(series);
	dataRepresentation->createDefaultAxes();
	dataRepresentation->setAxisX(axis, series);
	dataRepresentation->legend()->setVisible(true);
	dataRepresentation->legend()->setAlignment(Qt::AlignBottom);

}

void GUI::setRepositoryB() {
	std::string path = repositoryLineEditB->text().toStdString();
	service.setPath(path, "repository");
	populateList(footageListWidget);
	populateList(footageListWidgetModeB);
	createStatistics();
}

void GUI::setMyListB() {
	std::string path = myListLineEditB->text().toStdString();
	service.setPath(path, "mylist");
	populateMyList(footageMyList);
}

void GUI::populateMyList(QListWidget * myListWidget) {
	myListWidget->clear();
	std::vector<Footage> listOfFootage = service.getMyList();
	for (const auto& footage: listOfFootage) {
		myListWidget->addItem(QString::fromStdString(footage.getTitle() + " - " + footage.getType()));
	}
}

void GUI::saveFootage() {
	int selectedIndex = getSelectedFootage(footageListWidgetModeB);
	if (selectedIndex < 0) {
		QMessageBox::critical(this, "Error", "No selected footage");
		return;
	}
	service.addToMyList(service.getAllElements()[selectedIndex].getTitle());
	populateMyList(footageMyList);
}

void GUI::nextFootage() {
	int selectedIndex = getSelectedFootage(footageListWidgetModeB);
	if (selectedIndex < 0 or selectedIndex >= service.getAllElements().size() - 1) {
		selectedIndex = 0;
	}else {
		selectedIndex++;
	}
	footageListWidgetModeB->setCurrentRow(selectedIndex);
}

void GUI::openList() {
	service.openMyList();
}

void GUI::readProperties() {
	std::ifstream parseProperties("settings.properties");
	if (!parseProperties) {
		std::ofstream setBasicProperties("setting.properties");
		setBasicProperties << "repository = file" << std::endl << "fileLocation = database.sqlite3" << std::endl << "myList = file" << std::endl << "myListLocation = newFile.html";
		setBasicProperties.close();
	}
	parseProperties.close();
	parseProperties.open("settings.properties", std::fstream::in);
	std::string repositoryLine;
	std::getline(parseProperties, repositoryLine);
	int spaceIndex = 0;
	std::string repositoryType;
	for (auto character: repositoryLine) {
		if (character == ' ') {
			spaceIndex++;
		}else if (spaceIndex == 2) {
			repositoryType += character;
		}
	}
	if (repositoryType == "memory") {
		service.setPath("memory", "repository");
		repositoryLineEdit->setText(QString::fromStdString("memory"));
		repositoryLineEditB->setText(QString::fromStdString("memory"));
		std::getline(parseProperties, repositoryLine);
	}else {
		std::string repositoryFileLine;
		spaceIndex = 0;
		std::getline(parseProperties, repositoryFileLine);
		std::string repositoryFile;
		for (auto character: repositoryFileLine) {
			if (character == ' ') {
				spaceIndex++;
			}else if (spaceIndex == 2) {
				repositoryFile += character;
			}
		}
		service.setPath(repositoryFile, "repository");
		repositoryLineEdit->setText(QString::fromStdString(repositoryFile));
		repositoryLineEditB->setText(QString::fromStdString(repositoryFile));
	}
	std::string myListLine;
	std::getline(parseProperties, myListLine);
	spaceIndex = 0;
	std::string myListType;
	for (auto character: myListLine) {
		if (character == ' ') {
			spaceIndex++;
		}else if (spaceIndex == 2) {
			myListType += character;
		}
	}
	if (myListType == "memory") {
		service.setPath("memory", "mylist");
		myListLineEdit->setText(QString::fromStdString("memory"));
		myListLineEditB->setText(QString::fromStdString("memory"));
		std::getline(parseProperties, myListLine);
	}else {
		std::string myListFileLine;
		std::getline(parseProperties, myListFileLine);
		std::string myListFile;
		spaceIndex = 0;
		for (auto character: myListFileLine) {
			if (character == ' ') {
				spaceIndex++;
			}else if (spaceIndex == 2) {
				myListFile += character;
			}
		}
		service.setPath(myListFile, "mylist");
		myListLineEdit->setText(QString::fromStdString(myListFile));
		myListLineEditB->setText(QString::fromStdString(myListFile));
	}
	populateList(footageListWidget);
	populateList(footageListWidgetModeB);
	populateMyList(footageMyList);
	createStatistics();

}

