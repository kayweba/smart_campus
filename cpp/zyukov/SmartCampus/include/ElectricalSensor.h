#pragma once

#include <stdafx.h>
#include <DbData.h>
#include <ui_electricalsensor.h>

namespace SmartCampus {

class ElectricalSensor : public QWidget,  public Database::DbElectricalSensor {
	public:
		explicit ElectricalSensor(QWidget *parent = nullptr, Database::DbElectricalSensorPtr ptrSensor = nullptr) noexcept;
		explicit ElectricalSensor(const ElectricalSensor & other) noexcept;
		ElectricalSensor& operator = (const ElectricalSensor& other);
		~ElectricalSensor();

		void SetName(const QString& name);
		void SetState(const bool& state);
		void SetValue(const double& value);
		void SetType(const Database::DbElectricalSensorTypePtr& ptrType);
		void SetParent(QWidget* parent);
	protected:
	private:
		Ui::ElectricalSensor*  ui;
		QWidget* m_parent;
		Database::DbElectricalSensorTypePtr m_ptrType;
		Database::DbElectricalSensorPtr m_ptrSensor;
};

}