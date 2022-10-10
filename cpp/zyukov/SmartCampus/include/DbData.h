#pragma once

#include <stdafx.h>

namespace SmartCampus { namespace Database {

	class DbElectricalSensorType {
		public:
			DbElectricalSensorType();
			DbElectricalSensorType(uint32_t id, QString description);
			~DbElectricalSensorType();

			uint32_t GetId() const;
			QString GetDescription() const;
		protected:
		private:
			uint32_t m_id;
			QString m_description; 
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
			DbRoom(uint32_t id, QString description, uint32_t number);
			~DbRoom();

			uint32_t GetId() const;
			QString GetDescription() const;
			uint32_t GetNumber() const;

			DbRoom& GetRoomById(uint32_t id);

			void SetId(const uint32_t & id);
			void SetDescription(const QString & description);
			void SetNumber(const uint32_t & number);
		protected:
		private:
			uint32_t m_id;
			QString m_description;
			uint32_t m_number;
	};

	using DbRoomPtr = std::shared_ptr<DbRoom>;
}}