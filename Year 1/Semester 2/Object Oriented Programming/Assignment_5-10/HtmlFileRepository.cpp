//
// Created by Octavian Custura on 15/04/2020.
//

#include "HtmlFileRepository.h"
#include <fstream>
#include <sstream>

#define StartOfList 2
HtmlFileRepository::HtmlFileRepository(std::string fileName): pathName(std::move(fileName)), currentElement(0) {
	std::ifstream checkIfFileExists(pathName);
	if (!checkIfFileExists) {
		std::ofstream createFileIfNotExist(pathName);
		createFileIfNotExist.close();
	}
	checkIfFileExists.close();
}

void HtmlFileRepository::writeToFile(const std::vector<Footage>& arrayToBeWritten) {
	std::ofstream fileOut(pathName);
	fileOut << "<!DOCTYPE html><html><head><title>" << "Footage" << "</title></head>";
	fileOut << "<body><table border=\"1\">\n<tr><td>Title</td><td>Type</td><td>Date</td><td>Access Count</td><td>Link</td></tr>\n";
	for (const auto& footage: arrayToBeWritten) {
		fileOut << "<tr><td>" << footage.getTitle() << "</td><td>" << footage.getType() << "</td><td>" << footage.getDate() << "</td><td>" << footage.getAccessCount();
		fileOut << "</td><td><a href = \"" << footage.getLink() << "\">Link</a></td></tr>\n";
	}
	fileOut << "</table></body></html>";
	fileOut.close();
}

std::vector<Footage> HtmlFileRepository::readHtmlFile() {
	std::ifstream fileIn(pathName);
	std::string htmlFileLine;
	int lineNumber = 0, index = 0;
	std::string stringFootage;
	std::vector<Footage> arrayOfFootage;
	std::string link;
	while (std::getline(fileIn, htmlFileLine, '<')) {
		if (!htmlFileLine.empty() and htmlFileLine != "\n") {
			stringFootage += htmlFileLine + ',';
			index++;
		}
		if (htmlFileLine == "\n") {
			if (lineNumber >= StartOfList) {
				auto positionLink = stringFootage.find(("Link"));
				stringFootage.replace(positionLink, positionLink + 3, link);
				std::stringstream computeFootage(stringFootage);
				Footage newFootage;
				computeFootage >> newFootage;
				arrayOfFootage.push_back(newFootage);
			}
			index = 0;
			lineNumber++;
			stringFootage = "";
			link = "";

		}
		std::getline(fileIn, htmlFileLine, '>');
		bool isLink = false;
		if (index == 4 and lineNumber >= StartOfList) {
			if (htmlFileLine.find("a href") != std::string::npos) {
				for (auto character: htmlFileLine) {
					if (character == '=') {
						isLink = true;
					}
					if (isLink) {
						link += character;
					}
				}
				link = link.substr(3);
				link.pop_back();

			}
		}
	}
	fileIn.close();
	return arrayOfFootage;
}

void HtmlFileRepository::addFootage(const Footage &newFootage) {
	auto arrayOfFootage = readHtmlFile();
	for (const auto& footage: arrayOfFootage) {
		if (footage.getTitle() == newFootage.getTitle()) {
			throw RepositoryException("Duplicate footage");
		}
	}
	arrayOfFootage.push_back(newFootage);
	writeToFile(arrayOfFootage);
}

void HtmlFileRepository::deleteFootage(const std::string &titleToBeRemoved) {
	auto arrayOfFootage = readHtmlFile();
	auto elementToRemove = std::find_if(arrayOfFootage.begin(), arrayOfFootage.end(), [titleToBeRemoved](Footage footage) {
		return footage.getTitle() == titleToBeRemoved;
	});
	if (elementToRemove == arrayOfFootage.end()) {
		throw RepositoryException("Footage does not exist");
	}else {
		arrayOfFootage.erase(elementToRemove);
	}
	writeToFile(arrayOfFootage);
}

void HtmlFileRepository::updateFootage(const Footage &newFootage) {
	auto arrayOfFootage = readHtmlFile();
	for (auto& footage: arrayOfFootage) {
		if (footage.getTitle() == newFootage.getTitle()) {
			footage = newFootage;
			writeToFile(arrayOfFootage);
			return;
		}
	}
	throw RepositoryException("Footage does not exist");
}

std::vector<Footage> HtmlFileRepository::getAllFootage() {
	return readHtmlFile();
}

Footage HtmlFileRepository::getCurrentElement() {
	if (currentElement == readHtmlFile().size()) {
		currentElement = 0;
	}
	return *(readHtmlFile().begin() + currentElement++);
}

void HtmlFileRepository::openList() {
	std::string systemString = "open " + pathName;
	const char* openListString = systemString.c_str();
	system(openListString);
}

