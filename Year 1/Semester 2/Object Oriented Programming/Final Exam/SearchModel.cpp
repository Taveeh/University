//
// Created by Octavian Custura on 20/06/2020.
//

#include "SearchModel.h"

void SearchModel::setText(const std::string &text) {
	SearchModel::text = text;
}

SearchModel::SearchModel(Service service, const std::string &text) : service(service), text(text) {
	loadedRows = 0;
}

int SearchModel::columnCount(const QModelIndex &parent) const {
	return 2;
}

QVariant SearchModel::data(const QModelIndex &index, int role) const {
	int row = index.row();
	int col = index.column();
	Star star = service.getStarsByName(text)[row];
	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		return QString::fromStdString(star.toString());
	}
	return QVariant();
}

void SearchModel::fetchMore(const QModelIndex &parent) {
	int remainedItems = service.getStarsByName(text).size() - loadedRows;
	int itemsToFetch = remainedItems;
	beginInsertRows(QModelIndex{}, loadedRows, loadedRows+itemsToFetch-1);
	loadedRows += itemsToFetch;
	endInsertRows();
}

bool SearchModel::canFetchMore(const QModelIndex &parent) const {
	return service.getStarsByName(text).size() > loadedRows;
}
