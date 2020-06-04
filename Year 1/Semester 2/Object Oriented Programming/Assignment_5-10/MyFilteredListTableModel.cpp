//
// Created by Octavian Custura on 01/06/2020.
//

#include "MyFilteredListTableModel.h"
#include <iostream>
MyFilteredListTableModel::MyFilteredListTableModel(Service &service1, const std::string &typeToFilter,
                                                   const std::string& maxAccess) :  type{typeToFilter}, maxAccessCount{maxAccess}, service{service1} {
	loadedRows = 0;
}

int MyFilteredListTableModel::rowCount(const QModelIndex &parent) const {
	return service.getFilteredList(type, maxAccessCount).size();
}

int MyFilteredListTableModel::columnCount(const QModelIndex &parent) const {
	return 6;
}

QVariant MyFilteredListTableModel::data(const QModelIndex &index, int role) const {
	int row = index.row();
	int col = index.column();
	Footage currentFootage = service.getFilteredList(type, maxAccessCount)[row];
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

QVariant MyFilteredListTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
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

//void MyFilteredListTableModel::fetchMore(const QModelIndex &parent) {
//	int remainedItems = service.getFilteredList(type, maxAccessCount).size() - loadedRows;
//	int itemsToFetch = remainedItems;
//	std::cout << itemsToFetch;
//	beginInsertRows(QModelIndex{}, loadedRows, loadedRows + itemsToFetch - 1);
//	loadedRows += itemsToFetch;
//	endInsertRows();
//}
//
//bool MyFilteredListTableModel::canFetchMore(const QModelIndex &parent) const {
//	return service.getFilteredList(type, maxAccessCount).size() > loadedRows;
//}

Qt::ItemFlags MyFilteredListTableModel::flags(const QModelIndex &index) const {
	auto column = index.column();
	if (column == 0) {
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
	}
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
