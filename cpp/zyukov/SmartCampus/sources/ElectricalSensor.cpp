#include <ElectricalSensor.h>

namespace SmartCampus {

	ElectricalSensor::ElectricalSensor(QWidget* parent, Database::DbElectricalSensorPtr ptrSensor) noexcept :
		QWidget(parent),
		Database::DbElectricalSensor(*ptrSensor),
		ui(new Ui::ElectricalSensor())
	{
		m_parent = parent;
		m_ptrSensor = ptrSensor;
		ui->setupUi(this);
		if (ptrSensor) {
			SetName(ptrSensor->GetName());
			SetValue(ptrSensor->GetValue());
			SetState(ptrSensor->GetState());
		}
	}

	ElectricalSensor::ElectricalSensor(const ElectricalSensor& other) noexcept
	{
		m_parent = other.m_parent;
		ui = other.ui;
		m_ptrSensor = other.m_ptrSensor;
		m_ptrType = other.m_ptrType;
	}

	ElectricalSensor& ElectricalSensor::operator = (const ElectricalSensor& other)
	{
		m_parent = other.m_parent;
		ui = other.ui;
		m_ptrSensor = other.m_ptrSensor;
		m_ptrType = other.m_ptrType;

		return *this;
	}

	ElectricalSensor::~ElectricalSensor()
	{
		delete(ui);
	}

	void ElectricalSensor::SetName(const QString& name) 
	{
		Database::DbElectricalSensor::SetName(name);
		ui->lineEditName->setText(name);
		if (m_ptrType)
			ui->lineEditName->setToolTip(QString("<b>Id:</b> %1 <br> <b>Type:</b> %2").arg(Database::DbElectricalSensor::GetId()).arg(m_ptrType->GetDescription()));
	}

	void ElectricalSensor::SetState(const bool& state)
	{
		Database::DbElectricalSensor::SetState(state);
		if (!state) {
			ui->labelState->setStyleSheet("background-color: rgb(255, 0, 0);");
		}
		else {
			ui->labelState->setStyleSheet("background-color: rgb(0, 255, 0);");
		}
	}

	void ElectricalSensor::SetValue(const double& value)
	{
		Database::DbElectricalSensor::SetValue(value);
		ui->lineEditValue->setText(QString::number(value) + " V");
	}

	void ElectricalSensor::SetType(const Database::DbElectricalSensorTypePtr& ptrType)
	{
		m_ptrType = ptrType;
		SetName(Database::DbElectricalSensor::GetName());
	}

	void ElectricalSensor::SetParent(QWidget* parent)
	{
		m_parent = parent;
		QWidget::setParent(parent);
		update();
	}
}