#include <iostream>
#include <QApplication>
#include "Observer.h"
#include "Service.h"
#include "WindowModel.h"
#include "Window.h"
#include "SearchModel.h"
#include <cstring>
#include <cassert>
void test_addStar_validInput_starAdded() {
	std::ofstream fout("testStar.txt");
	fout.close();
	Service s{"testAstronomer.txt", "testStar.txt"};
	s.addStar("name", s.getAllAstronomers().begin()->getConstellation(), 1, 2, 3);
	assert(s.getAllStars().size() == 1);
}
void test_addStar_invalidInput_throwsException() {
	std::ofstream fout("testStar.txt");
	fout.close();
	Service s{"testAstronomer.txt", "testStar.txt"};
	try {
		s.addStar("", s.getAllAstronomers().begin()->getConstellation(), 1, 2, 3);
		assert(false);
	}catch(Exception& e) {
		assert(strcmp(e.what(), "Empty name") == 0);
	}
}
int main(int argc, char** argv) {
	test_addStar_invalidInput_throwsException();
	test_addStar_validInput_starAdded();
	QApplication app(argc, argv);
	auto* observer = new Observer{};
	Service service{"astronomers.txt", "stars.txt"};
	for (auto as: service.getAllAstronomers()) {
		auto* model = new WindowModel(service);
		observer->add(model);
		auto* searchModel = new SearchModel(service, "");
		observer->add(searchModel);
		auto* window = new Window(model, observer, service, as, searchModel);
		window->show();
	}
	return app.exec();
}
