//
// Created by Octavian Custura on 01/06/2020.
//

#ifndef ASSIGNMENT_5_10_MYFILTEREDLISTTABLEMODEL_H
#define ASSIGNMENT_5_10_MYFILTEREDLISTTABLEMODEL_H
#include "ActualAbstractTableModel.h"
#include "Service.h"

class MyFilteredListTableModel: public QAbstractTableModel {
private:
	const std::string& type;
	const std::string& maxAccessCount;
	Service& service;
	int loadedRows;
public:
	MyFilteredListTableModel(Service& service1, const std::string& typeToFilter, const std::string& maxAccess);

	int rowCount(const QModelIndex &parent) const override;

	int columnCount(const QModelIndex &parent) const override;

	QVariant data(const QModelIndex &index, int role) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

//	void fetchMore(const QModelIndex &parent) override;
//
//	bool canFetchMore(const QModelIndex &parent) const override;

	Qt::ItemFlags flags(const QModelIndex &index) const override;
};


#endif //ASSIGNMENT_5_10_MYFILTEREDLISTTABLEMODEL_H
