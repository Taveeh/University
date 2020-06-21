//
// Created by Octavian Custura on 20/06/2020.
//

#include "Window.h"

void Window::initGUI() {
	auto* mainLayout = new QVBoxLayout{this};
	auto* listLayout = new QHBoxLayout{};
	tableView = new QTableView{};
	tableView->horizontalHeader();
	tableView->setModel(tableModel);
	listLayout->addWidget(tableView);
	searchView = new QListView{};
	searchView->setModel(searchModel);
	auto* searchLayout = new QVBoxLayout{};
	searchLineEdit = new QLineEdit{};
	searchLayout->addWidget(searchLineEdit);
	searchLayout->addWidget(searchView);
	listLayout->addLayout(searchLayout);
	mainLayout->addLayout(listLayout);
	auto* formLayout = new QFormLayout{};
	starNameLineEdit = new QLineEdit{};
	formLayout->addRow("Name", starNameLineEdit);
	starRightAscensionsLineEdit = new QLineEdit{};
	formLayout->addRow("Right Ascension", starRightAscensionsLineEdit);
	starDeclinationLineEdit = new QLineEdit{};
	formLayout->addRow("Declination", starDeclinationLineEdit);
	starDiameterLineEdit = new QLineEdit{};
	formLayout->addRow("Diameter", starDiameterLineEdit);
	mainLayout->addLayout(formLayout);
	auto* buttonsLayout = new QHBoxLayout{};
	addButton = new QPushButton{"Add"};
	viewButton = new QPushButton{"View"};
	checkBox = new QCheckBox{};
	buttonsLayout->addWidget(addButton);
	buttonsLayout->addWidget(viewButton);
	buttonsLayout->addWidget(checkBox);
	mainLayout->addLayout(buttonsLayout);

}

void Window::makeConnections() {
	QObject::connect(searchLineEdit, &QLineEdit::textEdited, this, [this] {
		searchModel->setText(searchLineEdit->text().toStdString());
		observer->propagate();
	});
	QObject::connect(addButton, &QPushButton::clicked, this, [this]() {
		std::string name = starNameLineEdit->text().toStdString();
		int x = starRightAscensionsLineEdit->text().toInt();
		int y = starDeclinationLineEdit->text().toInt();
		int d = starDiameterLineEdit->text().toInt();
		try {
			service.addStar(name, astronomer.getConstellation(), x, y, d);
		}catch(Exception& e) {
			QMessageBox::critical(this, "Error on add", e.what());
			return;
		}
		observer->propagate();
	});
	QObject::connect(checkBox, &QCheckBox::clicked, this, [this]() {
		if (!isChecked)
			tableModel->setText(astronomer.getConstellation());
		else
			tableModel->setText("");
		isChecked = not isChecked;
		observer->propagate();
	});
	QObject::connect(viewButton, &QPushButton::clicked, this, [this]() {
		int poz = getSelectedIndex();
		Star star{};
		if (poz < 0) {
			QMessageBox::critical(this, "Error", "No star selected");
			return;
		}
		std::vector<Star> starsArray;
		if (!isChecked) {
			star = service.getAllStars().at(poz);
		}else {
			star = service.getStarByConstellation(astronomer.getConstellation()).at(poz);
		}
		starsArray = service.getStarByConstellation(star.getConstellation());

		auto* drawing = new Drawing{};
		drawing->addStars(starsArray, star);
		drawing->show();
	});
}

int Window::getSelectedIndex() {
	auto list = tableView->selectionModel()->selectedIndexes();
	if (list.empty()) {
		return -1;
	}else {
		return list.at(0).row();
	}
}

Window::Window(WindowModel *model, Observer *observer, Service service, Astronomer astronomer1, SearchModel *search) : tableModel(model), observer(observer), service(service), astronomer(astronomer1), searchModel(search){
	initGUI();
	setWindowTitle(QString::fromStdString(astronomer.getName()));
	isChecked = false;
	makeConnections();
}
