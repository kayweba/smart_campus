#pragma once

#include <stdafx.h>

namespace SmartCampus { namespace Database {
	enum SensorType {
		LightType = 1,
		PlugType = 2,
		HeatType = 3
	};

	class BaseSize {
	protected:
		virtual unsigned int calculateSize() = 0;
	};

	using BaseSizePtr = std::shared_ptr<BaseSize>;

	struct Coordinates {
		Coordinates() {
			NValue = 90.0;
			EValue = 90.0;
		}
		double NValue;
		double EValue;
	};

	class DbElectricalSensorType : BaseSize {
		public:
			DbElectricalSensorType();
			DbElectricalSensorType(uint32_t id, QString description, QString unit);
			~DbElectricalSensorType();

			uint32_t GetId() const;
			QString GetDescription() const;
			QString GetUnit() const;
			unsigned int calculateSize() override;
		protected:
		private:
			uint32_t m_id;
			QString m_description;
			QString m_unit;
	};

	using DbElectricalSensorTypePtr = std::shared_ptr<DbElectricalSensorType>;

	class DbElectricalSensor : BaseSize {
		public:
			DbElectricalSensor();
			DbElectricalSensor(uint32_t id, QString name, DbElectricalSensorTypePtr type, bool state, double value, uint32_t roomId);
			~DbElectricalSensor();

			uint32_t GetId() const;
			QString GetName() const;
			DbElectricalSensorTypePtr GetType() const;
			bool GetState() const;
			double GetValue() const;
			uint32_t GetRoomId() const;

			void SetId(const uint32_t & id);
			void SetName(const QString & name);
			void SetType(const DbElectricalSensorTypePtr type);
			void SetState(const bool & state);
			void SetValue(const double & value);
			void SetRoomId(const uint32_t & roomId);
			unsigned int calculateSize() override;
		protected:
		private:
			uint32_t m_id;
			QString m_name;
			DbElectricalSensorTypePtr m_type;
			bool m_state;
			double m_value;
			uint32_t m_roomId;
	};

	using DbElectricalSensorPtr = std::shared_ptr<DbElectricalSensor>;

	class DbRoom : BaseSize {
		public:
			DbRoom();
			DbRoom(uint32_t id, QString description, uint32_t number, uint32_t buildingId);
			~DbRoom();

			uint32_t GetId() const;
			QString GetDescription() const;
			uint32_t GetNumber() const;
			uint32_t GetBuildingId() const;

			void SetId(const uint32_t & id);
			void SetDescription(const QString & description);
			void SetNumber(const uint32_t & number);
			void SetBuildingId(const uint32_t& buildingId);
			unsigned int calculateSize() override;
		protected:
		private:
			uint32_t m_id;
			QString m_description;
			uint32_t m_number;
			uint32_t m_buildingId;
	};

	using DbRoomPtr = std::shared_ptr<DbRoom>;

	class DbBuilding : BaseSize {
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
		unsigned int calculateSize() override;
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
Q_DECLARE_METATYPE(std::shared_ptr<SmartCampus::Database::DbElectricalSensorType>)