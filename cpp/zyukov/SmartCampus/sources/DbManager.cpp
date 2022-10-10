#include <DBManager.h>
#include <Application.h>

namespace SmartCampus {

	DBManager::DBManager(const QString & dbType, ApplicationPtr ptrApplication) :
		QSqlDatabase(dbType)
	{
		m_dbType = dbType;
		m_ptrApplication = ptrApplication;
		auto dbPath = QDir(QApplication::applicationFilePath());
		dbPath.cdUp();
		dbPath.cd(QString("Database"));
		QFile db(dbPath.absolutePath() + "/korpus_1.db");
		if (db.exists()) {
			this->setDatabaseName(db.fileName());
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("Успешно подключились к базе данных"));
			dbState = open();
			if (!dbState) {
				if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("Не удалось подключиться к базе данных"));
			}
		}
		else {
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("Файл базы данных не найден по пути %1").arg(dbPath.absolutePath()));
		}
	}

	DBManager::~DBManager()
	{
		this->close();
	}

	QVector<Database::DbElectricalSensorPtr> DBManager::GetElectricalSensors() const
	{
		QVector<Database::DbElectricalSensorPtr> result = {};
		if (!IsOpened())
		{
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("Не удалось получить список датчиков. Нет подключения к БД."));
			return result;
		}

		//Для запроса
		QSqlQuery query(*this);
		//Название таблицы
		static const QString table = "ElectricalSensors";
		//Строка SQL запроса
		static const QString cmd = QString("SELECT * FROM %1").arg(table);

		//Выполнение запроса
		if (!query.exec(cmd))
		{
			//Ошибка выполнение запроса
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("Ошибка выполнения запроса в таблице %1. %2").arg(table).arg(query.lastError().text()));
			return result;
		}
		//Пока можно читать результат
		while (query.next())
		{
			result.append(Database::DbElectricalSensorPtr(new Database::DbElectricalSensor(query.value(3).toUInt(), query.value(0).toString(), query.value(4).toUInt(),
				query.value(1).toBool(), query.value(2).toDouble(), query.value(5).toUInt())));
		}
		return result;
	}

	void DBManager::UpdateElectricalSensor(const Database::DbElectricalSensor& sensor)
	{
		if (!IsOpened())
		{
			//База неоткрыта
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("Не удалось обновить значение датчика. Нет подключения к БД."));
			return;
		}

		//Для запроса
		QSqlQuery query(*this);
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
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("Ошибка выполнения запроса в таблице %1. %2").arg(table).arg(query.lastError().text()));
			return;
		}
		//Подставляем в запрос своим параметры
		query.bindValue(":id", sensor.GetId());
		query.bindValue(":name", sensor.GetName());
		query.bindValue(":type_id", sensor.GetTypeId());
		query.bindValue(":state", sensor.GetState());
		query.bindValue(":value", sensor.GetValue());
		query.bindValue(":room_id", sensor.GetRoomId());

		//Выполнение запроса
		if (!query.exec())
		{
			//Ошибка выполнение запроса
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("Ошибка выполнения запроса в таблице %1. %2").arg(table).arg(query.lastError().text()));
			return;
		}
	}

	QVector<Database::DbRoomPtr> DBManager::GetRooms() const
	{
		QVector<Database::DbRoomPtr> result = {};
		if (!IsOpened())
		{
			//База неоткрыта
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("Не удалось получить список комнат. Нет подключения к БД."));
			return result;
		}

		//Для запроса
		QSqlQuery query(*this);
		//Название таблицы
		static const QString table = "Rooms";
		//Строка SQL запроса
		static const QString cmd = QString("SELECT * FROM %1").arg(table);

		//Выполнение запроса
		if (!query.exec(cmd))
		{
			//Ошибка выполнение запроса
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("Ошибка выполнения запроса в таблице %1. %2").arg(table).arg(query.lastError().text()));
			return result;
		}
		//Пока можно читать результат
		while (query.next())
		{
			result.append(Database::DbRoomPtr(new Database::DbRoom(query.value(2).toUInt(), query.value(0).toString(), query.value(1).toUInt())));
		}
		return result;
	}

	QVector<Database::DbElectricalSensorTypePtr> DBManager::GetElectricalSensorTypes() const
	{
		QVector<Database::DbElectricalSensorTypePtr> result = {};
		if (!IsOpened())
		{
			//База неоткрыта
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("Не удалось получить список типов датчиков. Нет подключения к БД."));
			return result;
		}

		//Для запроса
		QSqlQuery query(*this);
		//Название таблицы
		static const QString table = "ElectricalSensorType";
		//Строка SQL запроса
		static const QString cmd = QString("SELECT * FROM %1").arg(table);

		//Выполнение запроса
		if (!query.exec(cmd))
		{
			//Ошибка выполнение запроса
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("Ошибка выполнения запроса в таблице %1. %2").arg(table).arg(query.lastError().text()));
			return result;
		}
		//Пока можно читать результат
		while (query.next())
		{
			result.append(Database::DbElectricalSensorTypePtr(new Database::DbElectricalSensorType(query.value(1).toUInt(), query.value(0).toString())));
		}
		return result;
	}

	bool DBManager::IsOpened() const { return dbState; }

	QString DBManager::GetDbType() const { return m_dbType; }
}