#pragma once

#include <QApplication>
#include <QWidget>
#include <QSqlDatabase>
#include <QString>
#include <QVector>
#include <QDir>
#include <QTextCodec>
#include <QPushButton>
#include <QTimer>
#include <map>
#include <memory>
#include <thread>
#include <mutex>

// Forward declarations
namespace SmartCampus {
	class Application;
	class DBManager;
	class ElectricalSensor;
	using DbManagerPtr = std::shared_ptr<DBManager>;
	using ApplicationPtr = std::shared_ptr<Application>;
	using ElectricalSensorPtr = std::shared_ptr<ElectricalSensor>;
}