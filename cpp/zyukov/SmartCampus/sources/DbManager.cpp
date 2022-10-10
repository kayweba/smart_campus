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
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("������� ������������ � ���� ������"));
			dbState = open();
			if (!dbState) {
				if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("�� ������� ������������ � ���� ������"));
			}
		}
		else {
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("���� ���� ������ �� ������ �� ���� %1").arg(dbPath.absolutePath()));
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
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("�� ������� �������� ������ ��������. ��� ����������� � ��."));
			return result;
		}

		//��� �������
		QSqlQuery query(*this);
		//�������� �������
		static const QString table = "ElectricalSensors";
		//������ SQL �������
		static const QString cmd = QString("SELECT * FROM %1").arg(table);

		//���������� �������
		if (!query.exec(cmd))
		{
			//������ ���������� �������
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("������ ���������� ������� � ������� %1. %2").arg(table).arg(query.lastError().text()));
			return result;
		}
		//���� ����� ������ ���������
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
			//���� ���������
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("�� ������� �������� �������� �������. ��� ����������� � ��."));
			return;
		}

		//��� �������
		QSqlQuery query(*this);
		//�������� �������
		static const QString table = "ElectricalSensors";
		//������ SQL �������
		static const QString cmd = QString("UPDATE %1 SET \"sname\"=:name, \"id_type\"=:type_id,"
			" \"nstate\"=:state, \"rvalue\"=:value, \"id_room\"=:room_id "
			"WHERE \"id\"=:id").arg(table);

		//���������� �������
		if (!query.prepare(cmd))
		{
			//������ ���������� �������
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("������ ���������� ������� � ������� %1. %2").arg(table).arg(query.lastError().text()));
			return;
		}
		//����������� � ������ ����� ���������
		query.bindValue(":id", sensor.GetId());
		query.bindValue(":name", sensor.GetName());
		query.bindValue(":type_id", sensor.GetTypeId());
		query.bindValue(":state", sensor.GetState());
		query.bindValue(":value", sensor.GetValue());
		query.bindValue(":room_id", sensor.GetRoomId());

		//���������� �������
		if (!query.exec())
		{
			//������ ���������� �������
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("������ ���������� ������� � ������� %1. %2").arg(table).arg(query.lastError().text()));
			return;
		}
	}

	QVector<Database::DbRoomPtr> DBManager::GetRooms() const
	{
		QVector<Database::DbRoomPtr> result = {};
		if (!IsOpened())
		{
			//���� ���������
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("�� ������� �������� ������ ������. ��� ����������� � ��."));
			return result;
		}

		//��� �������
		QSqlQuery query(*this);
		//�������� �������
		static const QString table = "Rooms";
		//������ SQL �������
		static const QString cmd = QString("SELECT * FROM %1").arg(table);

		//���������� �������
		if (!query.exec(cmd))
		{
			//������ ���������� �������
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("������ ���������� ������� � ������� %1. %2").arg(table).arg(query.lastError().text()));
			return result;
		}
		//���� ����� ������ ���������
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
			//���� ���������
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("�� ������� �������� ������ ����� ��������. ��� ����������� � ��."));
			return result;
		}

		//��� �������
		QSqlQuery query(*this);
		//�������� �������
		static const QString table = "ElectricalSensorType";
		//������ SQL �������
		static const QString cmd = QString("SELECT * FROM %1").arg(table);

		//���������� �������
		if (!query.exec(cmd))
		{
			//������ ���������� �������
			if (m_ptrApplication) m_ptrApplication->UpdateStatus(QString::fromLocal8Bit("������ ���������� ������� � ������� %1. %2").arg(table).arg(query.lastError().text()));
			return result;
		}
		//���� ����� ������ ���������
		while (query.next())
		{
			result.append(Database::DbElectricalSensorTypePtr(new Database::DbElectricalSensorType(query.value(1).toUInt(), query.value(0).toString())));
		}
		return result;
	}

	bool DBManager::IsOpened() const { return dbState; }

	QString DBManager::GetDbType() const { return m_dbType; }
}