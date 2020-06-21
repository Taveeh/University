//
// Created by Octavian Custura on 20/06/2020.
//

#include "Observer.h"

void Observer::add(QAbstractItemModel *model) {
	array.push_back(model);
}

void Observer::propagate() {
	for (auto element: array) {
		emit element->layoutChanged();
	}
}

void Observer::remove(QAbstractItemModel *model) {
	auto el = std::find_if(array.begin(), array.end(), [model](auto x) {
		return model == x;
	});
	if (el != array.end()) {
		array.erase(el);
	}
}
