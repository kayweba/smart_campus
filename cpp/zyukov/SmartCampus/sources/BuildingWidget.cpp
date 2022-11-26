#include <BuildingWidget.h>

namespace SmartCampus { namespace Gui {

	BuildingWidget::BuildingWidget(uint16_t id, const QString& svgName, const int color, QSize size, uint16_t E_offset, uint16_t N_offset, QWidget* parent) noexcept
		: CGenericWidget(svgName, color, 3, size.width(), size.height(), parent)
	{
		shadow = new QGraphicsDropShadowEffect();
		shadow->setBlurRadius(3);
		shadow->setColor(QColor(0, 0, 0, 190));
		shadow->setOffset(3);
		setGraphicsEffect(shadow);
		Eoffset_m = E_offset;
		Noffset_m = N_offset;
		_id = id;
		_internalLayout = new QVBoxLayout(this);
		_internalLayout->setAlignment(Qt::AlignmentFlag::AlignVCenter | Qt::AlignmentFlag::AlignHCenter);
		this->setLayout(_internalLayout);
		_enterButton = new QPushButton(this);
		_enterButton->setFixedSize(this->size().width() / 4, this->size().width() / 4);
		_enterButton->setIcon(QIcon(":/enter.png"));
		_internalLayout->addWidget(_enterButton);
		connect(_enterButton, &QPushButton::clicked, this, &BuildingWidget::OnEnterButtonClicked);
	}

	BuildingWidget::~BuildingWidget()
	{
		delete(_enterButton);
		delete(_internalLayout);
		m_onEnterButtonClickedSignal.disconnect_all_slots();
	}

	uint16_t BuildingWidget::GetEOffset() const
	{
		return Eoffset_m;
	}

	uint16_t BuildingWidget::GetNOffset() const
	{
		return Noffset_m;
	}

	void BuildingWidget::ConnectEnterButtonToSignal(boost::signals2::signal<void(uint16_t)>::slot_type slot)
	{
		m_onEnterButtonClickedSignal.connect(slot);
	}

	void BuildingWidget::OnEnterButtonClicked(bool checked)
	{
		if (!m_onEnterButtonClickedSignal.empty()) m_onEnterButtonClickedSignal(_id);
	}

	void BuildingWidget::resizeEvent(QResizeEvent* event)
	{
		qDebug() << "BuildingWidget resizeEvent. New size is " << event->size();
		CGenericWidget::resizeEvent(event);
	}

}} // SmartCampus::Gui
