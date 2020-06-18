    //
// Created by Octavian Custura on 27/05/2020.
//

#include "MyListTableModel.h"
#include <QShortcut>
#include <iostream>
MyListTableModel::MyListTableModel(Service& repository1) : repository{repository1} {
	loadedRows = 0;
}

int MyListTableModel::rowCount(const QModelIndex &parent) const {
	int size = repository.getMyList().size();
	if (size < loadedRows) {
		return size;
	}
	return loadedRows;
}

int MyListTableModel::columnCount(const QModelIndex &parent) const {
	return 6 ;
}

QVariant MyListTableModel::data(const QModelIndex &index, int role) const {
	int row = index.row();
	int col = index.column();
	Footage currentFootage = repository.getMyList()[row];
	if (role == Qt::DisplayRole) {
		switch (col) {
			case 0:
				return QString::fromStdString(currentFootage.getTitle());
			case 1:
				return QString::fromStdString(currentFootage.getType());
			case 2:
				return QString::fromStdString(currentFootage.getDate().toString());
			case 3:
				return QString::fromStdString(std::to_string(currentFootage.getAccessCount()));
			case 4:
				return QString::fromStdString(currentFootage.getLink());
			default:
				break;
		}
	}
	return QVariant();
}

QVariant MyListTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
				case 0:
					return QString("Name");
				case 1:
					return QString("Type");
				case 2:
					return QString("Date");
				case 3:
					return QString("Access Count");
				case 4:
					return QString("Link");
				case 5:
					return QString("Play");
				default:
					break;
			}
		}
	}
	return QVariant();
}

bool MyListTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
	if (role != Qt::EditRole) {
		return false;
	}
	int row = index.row();
	int column = index.column();
	Footage currentFootage = repository.getMyList()[row];   
	switch (column) {
		case 0:
			break;
		case 1:
			repository.editMyList(currentFootage.getTitle(), 1, value.toString().toStdString());
			break;
		case 2:
			repository.editMyList(currentFootage.getTitle(), 2, value.toString().toStdString());
			break;
		case 3:
			repository.editMyList(currentFootage.getTitle(), 3, value.toString().toStdString());
			break;
		case 4:
			repository.editMyList(currentFootage.getTitle(), 4, value.toString().toStdString());
			break;
		default:
			break;
	}
	emit dataChanged(index, index);
	return true;
}

Qt::ItemFlags MyListTableModel::flags(const QModelIndex &index) const {
	auto column = index.column();
	if (column == 0) {
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	}
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

Service &MyListTableModel::getService() {
	return repository;
}

void MyListTableModel::fetchMore(const QModelIndex &parent) {
	int remainedItems = repository.getMyList().size() - loadedRows;
	int itemsToFetch = remainedItems;
	beginInsertRows(QModelIndex{}, loadedRows, loadedRows + itemsToFetch - 1);
	loadedRows += itemsToFetch;
	endInsertRows();
}

bool MyListTableModel::canFetchMore(const QModelIndex &parent) const {
	return repository.getMyList().size() > loadedRows;
}
