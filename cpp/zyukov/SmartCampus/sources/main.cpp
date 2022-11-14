#include <stdafx.h>
#include <Application.h>
#include <QLockFile>
#include <QMessageBox>
#include <clocale>

int main(int argc, char ** argv)
{
	srand(time(NULL));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QApplication app(argc, argv);
	QLockFile lockFile(QDir::temp().absoluteFilePath("lurity.lock"));
	if (!lockFile.tryLock(100)) {
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setText(QString::fromLocal8Bit("One instance of this app is already running\nYou can't start another one"));
		msgBox.exec();
		return -1;
	}
	SmartCampus::Application * window = new SmartCampus::Application(1920, 1080);
	try {
		app.exec();
	}
	catch(...) {
		return -1;
	}
	return 0;
}