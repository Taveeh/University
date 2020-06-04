//
// Created by Octavian Custura on 27/05/2020.
//

#ifndef ASSIGNMENT_5_10_MYLISTTABLEMODEL_H
#define ASSIGNMENT_5_10_MYLISTTABLEMODEL_H
#include <QAbstractTableModel>
#include "Service.h"
#include "ActualAbstractTableModel.h"

class MyListTableModel: public QAbstractTableModel {
private:
	Service& repository;
	int loadedRows;
public:
	explicit MyListTableModel(Service& repository1);

	int rowCount(const QModelIndex &parent) const override;

	int columnCount(const QModelIndex &parent) const override;

	QVariant data(const QModelIndex &index, int role) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	bool setData(const QModelIndex &index, const QVariant &value, int role) override;

	Qt::ItemFlags flags(const QModelIndex &index) const override;

	Service& getService();

	void fetchMore(const QModelIndex &parent) override;

	bool canFetchMore(const QModelIndex &parent) const override;


};


#endif //ASSIGNMENT_5_10_MYLISTTABLEMODEL_H
