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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind/bind.hpp>
#include <boost/dll.hpp>

// Forward declarations
namespace SmartCampus {
	class Application;
	class DBManager;
	class ElectricalSensor;
	namespace Database {
		class ValueGenerator;
		using ValueGeneratorPtr = std::shared_ptr<ValueGenerator>;
	}
	using DbManagerPtr = std::shared_ptr<DBManager>;
	using ApplicationPtr = std::shared_ptr<Application>;
	using ElectricalSensorPtr = std::shared_ptr<ElectricalSensor>;
}