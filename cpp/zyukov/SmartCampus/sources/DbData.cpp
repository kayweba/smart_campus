#include <DbData.h>

namespace SmartCampus {
	namespace Database {

		DbElectricalSensorType::DbElectricalSensorType() : DbElectricalSensorType(0, "") {}

		DbElectricalSensorType::DbElectricalSensorType(uint32_t id, QString description)
		{
			m_id = id;
			m_description = description;
		}
		DbElectricalSensorType::~DbElectricalSensorType()
		{

		}

		uint32_t DbElectricalSensorType::GetId() const
		{
			return m_id;
		}

		QString DbElectricalSensorType::GetDescription() const
		{
			return m_description;
		}

		DbElectricalSensor::DbElectricalSensor() : DbElectricalSensor(0, "", 0, false, 0.0, 0) {}

		DbElectricalSensor::DbElectricalSensor(uint32_t id, QString name, uint32_t typeId, bool state, double value, uint32_t roomId)
		{
			m_id = id;
			std::string _name = name.toStdString();
			m_name = name;
			m_typeId = typeId;
			m_state = state;
			m_value = value;
			m_roomId = roomId;
		}

		DbElectricalSensor::~DbElectricalSensor()
		{

		}

		uint32_t DbElectricalSensor::GetId() const { return m_id; }
		QString DbElectricalSensor::GetName() const { return m_name; }
		uint32_t DbElectricalSensor::GetTypeId() const { return m_typeId; }
		bool DbElectricalSensor::GetState() const { return m_state; }
		double DbElectricalSensor::GetValue() const { return m_value; }
		uint32_t DbElectricalSensor::GetRoomId() const { return m_roomId; }

		void DbElectricalSensor::SetId(const uint32_t& id) { m_id = id; }
		void DbElectricalSensor::SetName(const QString& name) { m_name = name; }
		void DbElectricalSensor::SetTypeId(const uint32_t& typeId) { m_typeId = typeId; }
		void DbElectricalSensor::SetState(const bool& state) { m_state = state; }
		void DbElectricalSensor::SetValue(const double& value) { m_value = value; }
		void DbElectricalSensor::SetRoomId(const uint32_t& roomId) { m_roomId = roomId; }

		DbRoom::DbRoom() : DbRoom(0, QString(""), 0) {};

		DbRoom::DbRoom(uint32_t id, QString description, uint32_t number)
		{
			m_id = id;
			m_description = description;
			m_number = number;
		}

		DbRoom::~DbRoom()
		{

		}

		uint32_t DbRoom::GetId() const { return m_id; }
		QString DbRoom::GetDescription() const { return m_description; }
		uint32_t DbRoom::GetNumber() const { return m_number; }

		void DbRoom::SetId(const uint32_t& id) { m_id = id; }
		void DbRoom::SetDescription(const QString& description) { m_description = description; }
		void DbRoom::SetNumber(const uint32_t& number) { m_number = number; }
}}