//
// Created by Octavian Custura on 25/05/2020.
//

#ifndef ASSIGNMENT_5_10_ACTION_H
#define ASSIGNMENT_5_10_ACTION_H
#include <utility>

#include "Repository.h"
#include "Footage.h"

class Action {
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
	virtual ~Action() = default;
};

class ActionAdd: public Action {
private:
	Footage addedFootage;
	Repository* repository;
public:
	ActionAdd(Footage footage, Repository* repository1);
	void executeUndo() override;
	void executeRedo() override;
};

class ActionRemove: public Action {
private:
	Footage deletedFootage;
	Repository* repository;
public:
	ActionRemove(Footage footage, Repository* repository1);
	void executeUndo() override;
	void executeRedo() override;
};

class ActionUpdate: public Action {
private:
	Footage oldFootage;
	Footage newFootage;
	Repository* repository;
public:
	ActionUpdate(Footage oldFootage1, Footage newFootage1, Repository* repository1);
	void executeUndo() override;
	void executeRedo() override;
};

#endif //ASSIGNMENT_5_10_ACTION_H
