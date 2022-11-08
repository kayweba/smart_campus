#include <ElectricalSensor.h>

namespace SmartCampus { namespace Gui {

	ElectricalSensor::ElectricalSensor(QWidget* parent, Database::DbElectricalSensorPtr ptrSensor) noexcept :
		QWidget(parent),
		Database::DbElectricalSensor(*ptrSensor),
		ui(new Ui::ElectricalSensor())
	{
		m_parent = parent;
		m_ptrSensor = ptrSensor;
		ui->setupUi(this);
		this->setMinimumSize(this->size());
		if (ptrSensor) {
			SetName(ptrSensor->GetName());
			SetValue(ptrSensor->GetValue());
			SetState(ptrSensor->GetState());
			SetUnit(ptrSensor->GetType()->GetUnit());
		}
		connect(ui->closeButton, &QPushButton::clicked, this, &ElectricalSensor::OnCloseButtonClicked);
		ui->closeButton->setMaximumSize(QSize(20, 20));
		shouldBeDeleted = false;
		stylePattern.clear();

		if (ptrSensor->GetType()->GetId() == Database::SensorType::LightType)
			stylePattern = "background-image: url(:/light.png);";
		else if (ptrSensor->GetType()->GetId() == Database::SensorType::PlugType)
			stylePattern = "background-image: url(:/plug.png);";
		else if (ptrSensor->GetType()->GetId() == Database::SensorType::HeatType)
			stylePattern = "background-image: url(:/heat.png);";
		ui->labelState->setStyleSheet(stylePattern);
		ui->labelState->setMinimumSize(QSize(20, 20));
		ui->labelState->setMaximumSize(QSize(20, 20));
		adjustSize();
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
		ui->labelName->setText(name);
	}

	void ElectricalSensor::SetState(const bool& state)
	{
		Database::DbElectricalSensor::SetState(state);
		if (!state) {
			ui->labelState->setStyleSheet(stylePattern + "background-color: rgba(255, 0, 0, 100); border-radius: 4px;");
			SetValue(0.0);
		}
		else {
			ui->labelState->setStyleSheet(stylePattern + "background-color: rgba(0, 255, 0, 100); border-radius: 4px;");
		}
	}

	void ElectricalSensor::SetValue(const double& value)
	{
		Database::DbElectricalSensor::SetValue(value);
		ui->labelValue->setText(QString::number(value));
	}

	void ElectricalSensor::SetType(const Database::DbElectricalSensorTypePtr& ptrType)
	{
		m_ptrType = ptrType;
		SetName(Database::DbElectricalSensor::GetName());
	}

	void ElectricalSensor::SetUnit(const QString& unit)
	{
		ui->labelUnit->setText(unit);
	}

	void ElectricalSensor::SetParent(QWidget* parent)
	{
		m_parent = parent;
		QWidget::setParent(parent);
		update();
	}

	void ElectricalSensor::SetSensorPtr(Database::DbElectricalSensorPtr & ptrSensor)
	{
		m_ptrSensor = ptrSensor;
	}

	Database::DbElectricalSensorPtr& ElectricalSensor::InternalSensor()
	{
		return m_ptrSensor;
	}

	void ElectricalSensor::OnCloseButtonClicked(bool checked)
	{
		shouldBeDeleted = true;
		this->hide();
	}
}} // SmartCampus::Gui