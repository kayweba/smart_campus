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
		if (ptrSensor) {
			SetName(ptrSensor->GetName());
			SetValue(ptrSensor->GetValue());
			SetState(ptrSensor->GetState());
			SetUnit(ptrSensor->GetType()->GetUnit());
		}
		connect(ui->closeButton, &QPushButton::clicked, this, &ElectricalSensor::OnCloseButtonClicked);
		ui->closeButton->setMaximumSize(QSize(20, 20));
		shouldBeDeleted = false;
		adjustSize();
	}

	ElectricalSensor::ElectricalSensor(const ElectricalSensor& other) noexcept
	{
		m_parent = other.m_parent;
		ui = other.ui;
		m_ptrSensor = other.m_ptrSensor;
		m_ptrType = other.m_ptrType;
	}

	ElectricalSensor::ElectricalSensor() noexcept
	{
		m_parent = nullptr;
		ui = nullptr;
		m_ptrSensor = nullptr;
		m_ptrType = nullptr;
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
			ui->labelState->setStyleSheet("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, \
				stop:0 rgba(255, 0, 0, 255), stop:1 rgba(255, 255, 255, 0)); \
				border - radius: 8px;");
			SetValue(0.0);
		}
		else {
			ui->labelState->setStyleSheet("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, \
				stop:0 rgba(0, 255, 0, 255), stop:1 rgba(255, 255, 255, 0)); \
				border - radius: 8px;");
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

	Database::DbElectricalSensorPtr& const ElectricalSensor::InternalSensor()
	{
		return m_ptrSensor;
	}

	void ElectricalSensor::OnCloseButtonClicked(bool checked)
	{
		shouldBeDeleted = true;
		this->hide();
	}
}} // SmartCampus::Gui