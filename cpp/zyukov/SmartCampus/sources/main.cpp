#include <stdafx.h>
#include <Application.h>
#include <clocale>

int main(int argc, char ** argv)
{
	srand(time(NULL));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QApplication app(argc, argv);
	SmartCampus::Application * window = new SmartCampus::Application(1920, 1080);
	try {
		app.exec();
	}
	catch(...) {
		return -1;
	}
	return 0;
}