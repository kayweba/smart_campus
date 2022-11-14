#include <DbManager.h>
#include <Application.h>

namespace SmartCampus {

	int  DBManager::dbCount = 0;
	DBManager::DBManager(const QString & dbType, boost::signals2::signal<void(QString, MessageType)>::slot_type m_messageSignalHandler)
	{
		// Increment count to create new database later if needed
		dbCount++;
		m_messageSignal.connect(m_messageSignalHandler);
		m_dbType = dbType;
		QString m_dbName = QString("DbManager" + QString::number(dbCount));
		m_database = QSqlDatabase::addDatabase(m_dbType, m_dbName);
		auto dbPath = QDir(QApplication::applicationFilePath());
		dbPath.cdUp();
		dbPath.cd(QString("Database"));
		QFile db(dbPath.absolutePath() + "/korpus_1.db");
		if (db.exists()) {
			m_database.setDatabaseName(db.fileName());
			if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Успешно подключились к базе данных"), MessageType::LogMessage);
			dbState = m_database.open();
			if (!dbState) {
				if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Не удалось подключиться к базе данных"), MessageType::ErrorMessage);
			}
		}
		else {
			if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Файл базы данных не найден по пути %1").arg(dbPath.absolutePath()), MessageType::ErrorMessage);
		}
	}

	DBManager::~DBManager()
	{
		m_database.close();
		QSqlDatabase::removeDatabase(m_dbName);
	}

	QVector<Database::DbElectricalSensorPtr> DBManager::GetElectricalSensors() const
	{
		QVector<Database::DbElectricalSensorPtr> result = {};
		if (!IsOpened())
		{
			if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Не удалось получить список датчиков. Нет подключения к БД."), MessageType::ErrorMessage);
			return result;
		}

		//Для запроса
		QSqlQuery query(m_database);
		//Название таблицы
		static const QString table = "ElectricalSensors";
		//Строка SQL запроса
		static const QString cmd = QString("SELECT * FROM %1").arg(table);

		//Выполнение запроса
		if (!query.exec(cmd))
		{
			//Ошибка выполнение запроса
			if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Ошибка выполнения запроса в таблице %1. %2").arg(table).arg(query.lastError().text()), MessageType::ErrorMessage);
			return result;
		}
		//Пока можно читать результат
		while (query.next())
		{
			auto sensorTypes = GetElectricalSensorTypes();
			Database::DbElectricalSensorTypePtr currentSensorType = nullptr;
			for (auto sensorType : sensorTypes) {
				if (sensorType->GetId() == query.value(4).toUInt())
					currentSensorType = sensorType;
			}
			if (currentSensorType != nullptr) {
				result.append(Database::DbElectricalSensorPtr(new Database::DbElectricalSensor(query.value(3).toUInt(), query.value(0).toString(), currentSensorType,
					query.value(1).toBool(), query.value(2).toDouble(), query.value(5).toUInt())));
			}
			else {
				//Не удалось найти нужный тип датчика. Текущий датчик не попадет в общий список
				if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("При попытке добавить датчик в список произошла ошибка. Датчик имеет неизвестный тип данных"), MessageType::ErrorMessage);
			}
		}
		return result;
	}

	void DBManager::UpdateElectricalSensor(const Database::DbElectricalSensorPtr sensor)
	{
		if (!IsOpened())
		{
			//База неоткрыта
			if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Не удалось обновить значение датчика. Нет подключения к БД."), MessageType::ErrorMessage);
			return;
		}

		//Для запроса
		QSqlQuery query(m_database);
		//Название таблицы
		static const QString table = "ElectricalSensors";
		//Строка SQL запроса
		static const QString cmd = QString("UPDATE %1 SET \"sname\"=:name, \"id_type\"=:type_id,"
			" \"nstate\"=:state, \"rvalue\"=:value, \"id_room\"=:room_id "
			"WHERE \"id\"=:id").arg(table);

		//Подготовка запроса
		if (!query.prepare(cmd))
		{
			//Ошибка выполнение запроса
			if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Ошибка выполнения запроса в таблице %1. %2").arg(table).arg(query.lastError().text()), MessageType::ErrorMessage);
			return;
		}
		//Подставляем в запрос своим параметры
		query.bindValue(":id", sensor->GetId());
		query.bindValue(":name", sensor->GetName());
		query.bindValue(":type_id", sensor->GetType()->GetId());
		query.bindValue(":state", sensor->GetState());
		query.bindValue(":value", sensor->GetValue());
		query.bindValue(":room_id", sensor->GetRoomId());

		//Выполнение запроса
		if (!query.exec())
		{
			//Ошибка выполнение запроса
			if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Ошибка выполнения запроса в таблице %1. %2").arg(table).arg(query.lastError().text()), MessageType::ErrorMessage);
			return;
		}
	}

	QVector<Database::DbRoomPtr> DBManager::GetRooms() const
	{
		QVector<Database::DbRoomPtr> result = {};
		if (!IsOpened())
		{
			//База неоткрыта
			if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Не удалось получить список комнат. Нет подключения к БД."), MessageType::ErrorMessage);
			return result;
		}

		//Для запроса
		QSqlQuery query(m_database);
		//Название таблицы
		static const QString table = "Rooms";
		//Строка SQL запроса
		static const QString cmd = QString("SELECT * FROM %1").arg(table);

		//Выполнение запроса
		if (!query.exec(cmd))
		{
			//Ошибка выполнение запроса
			if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Ошибка выполнения запроса в таблице %1. %2").arg(table).arg(query.lastError().text()), MessageType::ErrorMessage);
			return result;
		}

		//Пока можно читать результат
		while (query.next())
		{
			result.append(Database::DbRoomPtr(new Database::DbRoom(query.value(2).toUInt(), query.value(0).toString(), query.value(1).toUInt(), query.value(3).toUInt())));
		}
		return result;
	}

	QVector<Database::DbElectricalSensorTypePtr> DBManager::GetElectricalSensorTypes() const
	{
		QVector<Database::DbElectricalSensorTypePtr> result = {};
		if (!IsOpened())
		{
			//База неоткрыта
			if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Не удалось получить список типов датчиков. Нет подключения к БД."), MessageType::ErrorMessage);
			return result;
		}

		//Для запроса
		QSqlQuery query(m_database);
		//Название таблицы
		static const QString table = "ElectricalSensorType";
		//Строка SQL запроса
		static const QString cmd = QString("SELECT * FROM %1").arg(table);

		//Выполнение запроса
		if (!query.exec(cmd))
		{
			//Ошибка выполнение запроса
			if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Ошибка выполнения запроса в таблице %1. %2").arg(table).arg(query.lastError().text()), MessageType::ErrorMessage);
			return result;
		}

		//Пока можно читать результат
		while (query.next())
		{
			result.append(Database::DbElectricalSensorTypePtr(new Database::DbElectricalSensorType(query.value(1).toUInt(), query.value(0).toString(), query.value(2).toString())));
		}
		return result;
	}

	QVector<Database::DbBuildingPtr> DBManager::GetBuildings() const
	{
		QVector<Database::DbBuildingPtr> result = {};
		if (!IsOpened())
		{
			//База неоткрыта
			if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Не удалось получить список зданий. Нет подключения к БД."), MessageType::ErrorMessage);
			return result;
		}

		//Для запроса
		QSqlQuery query(m_database);
		//Название таблицы
		static const QString table = "buildings";
		//Строка SQL запроса
		static const QString cmd = QString("SELECT * FROM %1").arg(table);

		//Выполнение запроса
		if (!query.exec(cmd))
		{
			//Ошибка выполнение запроса
			if (!m_messageSignal.empty()) m_messageSignal(QString::fromLocal8Bit("Ошибка выполнения запроса в таблице %1. %2").arg(table).arg(query.lastError().text()), MessageType::ErrorMessage);
			return result;
		}

		//Пока можно читать результат
		while (query.next())
		{
			Database::Coordinates coordinates;
			coordinates.NValue = query.value(4).toDouble();
			coordinates.EValue = query.value(5).toDouble();
			result.append(Database::DbBuildingPtr(new Database::DbBuilding(query.value(0).toUInt(), 
						query.value(1).toUInt(), 
						query.value(2).toString(), 
						query.value(3).toUInt(),
						coordinates)));
		}
		return result;
	}

	bool DBManager::IsOpened() const { return dbState; }

	QString DBManager::GetDbType() const { return m_dbType; }
}