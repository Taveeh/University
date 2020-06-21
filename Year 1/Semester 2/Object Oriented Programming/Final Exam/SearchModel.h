//
// Created by Octavian Custura on 20/06/2020.
//

#ifndef FINALEXAM_SEARCHMODEL_H
#define FINALEXAM_SEARCHMODEL_H

#include <QAbstractListModel>
#include "Service.h"
class SearchModel: public QAbstractListModel {
private:
	Service service;
	std::string text;
	int loadedRows{};
public:
	void setText(const std::string &text);

	SearchModel(Service service, const std::string& text);
	int rowCount(const QModelIndex &parent) const override {
		int size = service.getStarsByName(text).size();
		if (size < loadedRows) {
			return size;
		}
		return loadedRows;
	}

	int columnCount(const QModelIndex &parent) const override;

	QVariant data(const QModelIndex &index, int role) const override;

	void fetchMore(const QModelIndex &parent) override;

	bool canFetchMore(const QModelIndex &parent) const override;
};


#endif //FINALEXAM_SEARCHMODEL_H
