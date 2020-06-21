//
// Created by Octavian Custura on 20/06/2020.
//

#ifndef FINALEXAM_WINDOWMODEL_H
#define FINALEXAM_WINDOWMODEL_H

#include<QAbstractTableModel>
#include <utility>
#include "Service.h"
class WindowModel: public QAbstractTableModel {
private:
	Service service;
	int loadedRows{};
	std::string text;
public:
	explicit WindowModel(Service& service1);;

	void setText(std::string newText);
	int rowCount(const QModelIndex &parent) const override;

	int columnCount(const QModelIndex &parent) const override;

	QVariant data(const QModelIndex &index, int role) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	void fetchMore(const QModelIndex &parent) override;

	bool canFetchMore(const QModelIndex &parent) const override;
};


#endif //FINALEXAM_WINDOWMODEL_H
