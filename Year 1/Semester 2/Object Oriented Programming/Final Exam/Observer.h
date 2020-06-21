//
// Created by Octavian Custura on 20/06/2020.
//

#ifndef FINALEXAM_OBSERVER_H
#define FINALEXAM_OBSERVER_H

#include <QAbstractItemModel>

class Observer {
private:
	std::vector<QAbstractItemModel*> array;
public:
	Observer() = default;

	void add(QAbstractItemModel* model);

	void propagate();

	void remove(QAbstractItemModel* model);
};

#endif //FINALEXAM_OBSERVER_H
