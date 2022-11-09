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
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <map>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind/bind.hpp>
#include <boost/dll.hpp>
#include <boost/crc.hpp>

// Forward declarations
namespace SmartCampus {
	enum MessageType {
		ErrorMessage = 0,
		LogMessage = 1
	};
	class Application;
	class DBManager;
	namespace Database {
		class BaseSize;
		class ValueGenerator;
		class DbElectricalSensorType;
		class DbElectricalSensor;
		class DbRoom;
		class DbBuilding;
		using ValueGeneratorPtr = std::shared_ptr<ValueGenerator>;
		using BaseSizePtr = std::shared_ptr<BaseSize>;
		using DbElectricalSensorTypePtr = std::shared_ptr<DbElectricalSensorType>;
		using DbElectricalSensorPtr = std::shared_ptr<DbElectricalSensor>;
		using DbRoomPtr = std::shared_ptr<DbRoom>;
		using DbBuildingPtr = std::shared_ptr<DbBuilding>;
	}
	namespace Gui {
		class ElectricalSensor;
		class BuildingItem;
		class BuildingTreeModel;
		template<class T>
		class BaseContainer;
		using ElectricalSensorPtr = std::shared_ptr<ElectricalSensor>;
		using BuildingItemPtr = std::shared_ptr<BuildingItem>;
		using BuildingTreeModelPtr = std::shared_ptr<BuildingTreeModel>;
		using GuiRooms = BaseContainer<ElectricalSensor>;
		using GuiBuildings = BaseContainer<GuiRooms>;
	}
	using DbManagerPtr = std::shared_ptr<DBManager>;
	using ApplicationPtr = std::shared_ptr<Application>;
}