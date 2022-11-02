#pragma once

#include <stdafx.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <DbData.h>

namespace SmartCampus {
	class DBManager : QSqlDatabase {
		public:
			DBManager(const QString& dbType, std::shared_ptr<Application> ptrApplication);
			~DBManager();

			QVector<Database::DbElectricalSensorPtr> GetElectricalSensors() const;
			void UpdateElectricalSensor(const Database::DbElectricalSensor & sensor);
			QVector<Database::DbRoomPtr> GetRooms() const;
			QVector<Database::DbElectricalSensorTypePtr> GetElectricalSensorTypes() const;
			QVector<Database::DbBuildingPtr> GetBuildings() const;
			bool IsOpened() const; 
			QString GetDbType() const;
		protected:
		private:
			bool dbState;
			QString m_dbType;
			ApplicationPtr m_ptrApplication;
			mutable boost::mutex m_selfProtectionMutex;
	};
}
