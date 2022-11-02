#pragma once

#include <stdafx.h>

namespace SmartCampus { namespace Database {
	struct Coordinates {
		Coordinates() {
			NValue = 90.0;
			EValue = 90.0;
		}
		double NValue;
		double EValue;
	};

	class DbElectricalSensorType {
		public:
			DbElectricalSensorType();
			DbElectricalSensorType(uint32_t id, QString description, QString unit);
			~DbElectricalSensorType();

			uint32_t GetId() const;
			QString GetDescription() const;
			QString GetUnit() const;
		protected:
		private:
			uint32_t m_id;
			QString m_description;
			QString m_unit;
	};

	using DbElectricalSensorTypePtr = std::shared_ptr<DbElectricalSensorType>;

	class DbElectricalSensor {
		public:
			DbElectricalSensor();
			DbElectricalSensor(uint32_t id, QString name, uint32_t typeId, bool state, double value, uint32_t roomId);
			~DbElectricalSensor();

			uint32_t GetId() const;
			QString GetName() const;
			uint32_t GetTypeId() const;
			bool GetState() const;
			double GetValue() const;
			uint32_t GetRoomId() const;

			void SetId(const uint32_t & id);
			void SetName(const QString & name);
			void SetTypeId(const uint32_t & typeId);
			void SetState(const bool & state);
			void SetValue(const double & value);
			void SetRoomId(const uint32_t & roomId);
		protected:
		private:
			uint32_t m_id;
			QString m_name;
			uint32_t m_typeId;
			bool m_state;
			double m_value;
			uint32_t m_roomId;
	};

	using DbElectricalSensorPtr = std::shared_ptr<DbElectricalSensor>;

	class DbRoom {
		public:
			DbRoom();
			DbRoom(uint32_t id, QString description, uint32_t number, uint32_t buildingId);
			~DbRoom();

			uint32_t GetId() const;
			QString GetDescription() const;
			uint32_t GetNumber() const;
			uint32_t GetBuildingId() const;

			DbRoom& GetRoomById(uint32_t id);

			void SetId(const uint32_t & id);
			void SetDescription(const QString & description);
			void SetNumber(const uint32_t & number);
			void SetBuildingId(const uint32_t& buildingId);
		protected:
		private:
			uint32_t m_id;
			QString m_description;
			uint32_t m_number;
			uint32_t m_buildingId;
	};

	using DbRoomPtr = std::shared_ptr<DbRoom>;

	class DbBuilding {
	public:
		DbBuilding();
		DbBuilding(uint32_t id, uint32_t buildingNumber, QString description, uint32_t countOfFloors, Coordinates coordinates);
		~DbBuilding();

		uint32_t GetId() const;
		uint32_t GetBuildingNumber() const;
		QString GetDescription() const;
		uint32_t GetCountOfFloors() const;
		Coordinates GetCoordinates() const;

		void SetId(uint32_t id);
		void SetBuildingNumber(uint32_t buildingNumber);
		void SetDescription(QString description);
		void SetCountOfFloors(uint32_t countOfFloors);
		void SetCoordinates(Coordinates coordinates);
	protected:
	private:
		uint32_t m_id;
		uint32_t m_buildingNumber;
		QString m_description;
		uint32_t m_countOfFloors;
		Coordinates m_coordinates;
	};

	using DbBuildingPtr = std::shared_ptr<DbBuilding>;
}}