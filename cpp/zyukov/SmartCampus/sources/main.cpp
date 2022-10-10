#include <stdafx.h>
#include <Application.h>
#include <clocale>

int main(int argc, char ** argv)
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
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