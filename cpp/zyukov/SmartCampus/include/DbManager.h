#pragma once

#include <stdafx.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <DbData.h>

namespace SmartCampus {
	class DBManager {
		public:
			DBManager(const QString& dbType, boost::signals2::signal<void(QString, MessageType)>::slot_type m_messageSignalHandler);
			~DBManager();

			QVector<Database::DbElectricalSensorPtr> GetElectricalSensors() const;
			void UpdateElectricalSensor(const Database::DbElectricalSensorPtr sensor);
			QVector<Database::DbRoomPtr> GetRooms() const;
			QVector<Database::DbElectricalSensorTypePtr> GetElectricalSensorTypes() const;
			QVector<Database::DbBuildingPtr> GetBuildings() const;
			bool IsOpened() const; 
			QString GetDbType() const;
		protected:
		private:
			static int dbCount;
			boost::signals2::signal<void(QString, MessageType)> m_messageSignal;
			bool dbState;
			QSqlDatabase m_database;
			QString m_dbType;
			QString m_dbName;
	};
}
