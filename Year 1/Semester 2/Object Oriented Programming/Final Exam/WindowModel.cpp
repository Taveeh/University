//
// Created by Octavian Custura on 20/06/2020.
//

#include "WindowModel.h"

WindowModel::WindowModel(Service &service1) : service{std::move(service1)} {
	loadedRows = 0;
	text = "";
}

void WindowModel::setText(std::string newText) {
	text = std::move(newText);
}

int WindowModel::rowCount(const QModelIndex &parent) const {
	int size = service.getStarByConstellation(text).size();
	if (size < loadedRows) {
		return size;
	}
	return loadedRows;
}

int WindowModel::columnCount(const QModelIndex &parent) const {
	return 4;
}

QVariant WindowModel::data(const QModelIndex &index, int role) const {
	int row = index.row();
	int col = index.column();
	Star star = service.getStarByConstellation(text)[row];
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		switch (col) {
			case 0:
				return QString::fromStdString(star.getName());
			case 1:
				return QString::fromStdString(std::to_string(star.getRightAscension()));
			case 2:
				return QString::fromStdString(std::to_string(star.getDeclination()));
			case 3:
				return QString::fromStdString(std::to_string(star.getDiameter()));
			default:
				break;
		}

	}
	return QVariant();
}

QVariant WindowModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
				case 0:
					return QString("Name");
				case 1:
					return QString("Right Ascension");
				case 2:
					return QString("Declination");
				case 3:
					return QString("Diameter");
				default:
					break;
			}
		}
	}
	return QVariant();
}

void WindowModel::fetchMore(const QModelIndex &parent) {
	int remainedItems = service.getStarByConstellation(text).size() - loadedRows;
	int itemsToFetch = remainedItems;
	beginInsertRows(QModelIndex{}, loadedRows, loadedRows+itemsToFetch-1);
	loadedRows += itemsToFetch;
	endInsertRows();
}

bool WindowModel::canFetchMore(const QModelIndex &parent) const {
	return service.getStarByConstellation(text).size() > loadedRows;
}
