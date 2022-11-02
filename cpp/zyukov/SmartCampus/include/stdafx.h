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
		class DbElectricalSensorType;
		class DbElectricalSensor;
		class DbRoom;
		class DbBuilding;
		using ValueGeneratorPtr = std::shared_ptr<ValueGenerator>;
		using DbElectricalSensorTypePtr = std::shared_ptr<DbElectricalSensorType>;
		using DbElectricalSensorPtr = std::shared_ptr<DbElectricalSensor>;
		using DbRoomPtr = std::shared_ptr<DbRoom>;
		using DbBuildingPtr = std::shared_ptr<DbBuilding>;
	}
	using DbManagerPtr = std::shared_ptr<DBManager>;
	using ApplicationPtr = std::shared_ptr<Application>;
	using ElectricalSensorPtr = std::shared_ptr<ElectricalSensor>;
}