//
// Created by Octavian Custura on 25/05/2020.
//
#include "Action.h"

void ActionAdd::executeRedo() {
	repository->addFootage(addedFootage);
}

void ActionAdd::executeUndo() {
	repository->deleteFootage(addedFootage.getTitle());
}

ActionAdd::ActionAdd(Footage footage, Repository *repository1) : addedFootage(std::move(footage)), repository(repository1) {}

ActionRemove::ActionRemove(Footage footage, Repository *repository1)
		:deletedFootage(std::move(footage)), repository(repository1) {}

void ActionRemove::executeUndo() {
	repository->addFootage(deletedFootage);
}

void ActionRemove::executeRedo() {
	repository->deleteFootage(deletedFootage.getTitle());
}

ActionUpdate::ActionUpdate(Footage oldFootage1, Footage newFootage1, Repository* repository1) : oldFootage(oldFootage1), newFootage(newFootage1), repository(repository1) {}

void ActionUpdate::executeUndo() {
	repository->updateFootage(oldFootage);
}

void ActionUpdate::executeRedo() {
	repository->updateFootage(newFootage);
}
