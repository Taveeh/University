#include "Repository.h"

////
//// Created by Octavian Custura on 18/03/2020.
////
//
#include "Repository.h"
#include <exception>
//
Repository::Repository() {
    arrayOfTapes = DynamicArray<Footage>();
}

//int Repository::getSize() {
//    return arrayOfTapes.getSize();
//}
//
//void Repository::addFootage(const Footage& newFootage) {
//    for (int indexRepository = 0; indexRepository < arrayOfTapes.getSize(); ++indexRepository) {
//        if (arrayOfTapes.getElement(indexRepository).getTitle() == newFootage.getTitle()) {
//            throw std::exception();
//        }
//    }
//    arrayOfTapes.addElement(newFootage);
//}
//
//void Repository::deleteFootage(const std::string& titleToBeRemoved) {
//    for (int indexRepository = 0; indexRepository < arrayOfTapes.getSize(); ++indexRepository) {
//        if (arrayOfTapes.getElement(indexRepository).getTitle() == titleToBeRemoved) {
//            arrayOfTapes.removeElementFromPosition(indexRepository);
//            return;
//        }
//    }
//    throw std::exception();
//}
//
//void Repository::updateFootage(const Footage &newFootage) {
//    for (int indexRepository = 0; indexRepository < arrayOfTapes.getSize(); ++indexRepository) {
//        if (arrayOfTapes.getElement(indexRepository).getTitle() == newFootage.getTitle()) {
//            arrayOfTapes.setElement(newFootage, indexRepository);
//            return;
//        }
//    }
//    throw std::exception();
//}
//
