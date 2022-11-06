#include <DbData.h>

namespace SmartCampus {
	namespace Database {

		DbElectricalSensorType::DbElectricalSensorType() : DbElectricalSensorType(0, "", "units") {}

		DbElectricalSensorType::DbElectricalSensorType(uint32_t id, QString description, QString unit)
		{
			m_id = id;
			m_description = description;
			m_unit = unit;
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

		QString DbElectricalSensorType::GetUnit() const
		{
			return m_unit;
		}

		unsigned int DbElectricalSensorType::calculateSize()
		{
			return (m_id + m_description.size() + m_unit.size());
		}

		DbElectricalSensor::DbElectricalSensor() : DbElectricalSensor(0, "", DbElectricalSensorTypePtr(), false, 0.0, 0) {}

		DbElectricalSensor::DbElectricalSensor(uint32_t id, QString name, DbElectricalSensorTypePtr type, bool state, double value, uint32_t roomId)
		{
			m_id = id;
			std::string _name = name.toStdString();
			m_name = name;
			m_type = type;
			m_state = state;
			m_value = value;
			m_roomId = roomId;
		}

		DbElectricalSensor::~DbElectricalSensor()
		{

		}

		uint32_t DbElectricalSensor::GetId() const { return m_id; }
		QString DbElectricalSensor::GetName() const { return m_name; }
		DbElectricalSensorTypePtr DbElectricalSensor::GetType() const { return m_type; }
		bool DbElectricalSensor::GetState() const { return m_state; }
		double DbElectricalSensor::GetValue() const { return m_value; }
		uint32_t DbElectricalSensor::GetRoomId() const { return m_roomId; }

		void DbElectricalSensor::SetId(const uint32_t& id) { m_id = id; }
		void DbElectricalSensor::SetName(const QString& name) { m_name = name; }
		void DbElectricalSensor::SetType(const DbElectricalSensorTypePtr type) { m_type = type; }
		void DbElectricalSensor::SetState(const bool& state) { m_state = state; }
		void DbElectricalSensor::SetValue(const double& value) { m_value = value; }
		void DbElectricalSensor::SetRoomId(const uint32_t& roomId) { m_roomId = roomId; }
		unsigned int DbElectricalSensor::calculateSize() {
			return m_id + m_name.size() + m_type->calculateSize() + m_roomId;
		}

		DbRoom::DbRoom() : DbRoom(0, QString(""), 0, 0) {};

		DbRoom::DbRoom(uint32_t id, QString description, uint32_t number, uint32_t buildingId)
		{
			m_id = id;
			m_description = description;
			m_number = number;
			m_buildingId = buildingId;
		}

		DbRoom::~DbRoom()
		{

		}

		uint32_t DbRoom::GetId() const { return m_id; }
		QString DbRoom::GetDescription() const { return m_description; }
		uint32_t DbRoom::GetNumber() const { return m_number; }
		uint32_t DbRoom::GetBuildingId() const { return m_buildingId; }

		void DbRoom::SetId(const uint32_t& id) { m_id = id; }
		void DbRoom::SetDescription(const QString& description) { m_description = description; }
		void DbRoom::SetNumber(const uint32_t& number) { m_number = number; }
		void DbRoom::SetBuildingId(const uint32_t& buildingId) { m_buildingId = buildingId; }
		unsigned int DbRoom::calculateSize() {
			return (m_id + m_description.size() + m_number + m_buildingId);
		}

		DbBuilding::DbBuilding() : DbBuilding(0, 0, "", 0, Coordinates()) {}

		DbBuilding::DbBuilding(uint32_t id, uint32_t buildingNumber, QString description, uint32_t countOfFloors, Coordinates coordinates)
		{
			m_id = id;
			m_buildingNumber = buildingNumber;
			m_description = description;
			m_countOfFloors = countOfFloors;
			m_coordinates = coordinates;
		}
		
		DbBuilding::~DbBuilding()
		{

		}

		uint32_t DbBuilding::GetId() const { return m_id; }
		uint32_t DbBuilding::GetBuildingNumber() const { return m_buildingNumber; }
		QString DbBuilding::GetDescription() const { return m_description; }
		uint32_t DbBuilding::GetCountOfFloors() const { return m_countOfFloors; }
		Coordinates DbBuilding::GetCoordinates() const { return m_coordinates; }

		void DbBuilding::SetId(uint32_t id) { m_id = id; }
		void DbBuilding::SetBuildingNumber(uint32_t buildingNumber) { m_buildingNumber = buildingNumber; }
		void DbBuilding::SetDescription(QString description) { m_description = description; }
		void DbBuilding::SetCountOfFloors(uint32_t countOfFloors) { m_countOfFloors = countOfFloors; }
		void DbBuilding::SetCoordinates(Coordinates coordinates) { m_coordinates = coordinates; }
		unsigned int DbBuilding::calculateSize()
		{
			return (m_id + m_buildingNumber + m_description.size() + m_countOfFloors + m_coordinates.EValue + m_coordinates.NValue);
		}
}}