#include <CampusWidget.h>
#include <cmath>

namespace SmartCampus { namespace Gui {

	CampusWidget::CampusWidget(const QString& svgName, const int color, uint16_t width, uint16_t height, QWidget* parent) noexcept
		: CGenericWidget(svgName, color, 5, width, height, parent)
	{
		shadow = new QGraphicsDropShadowEffect();
		shadow->setBlurRadius(5);
		shadow->setColor(QColor(0, 0, 0, 190));
		shadow->setOffset(5);
		setGraphicsEffect(shadow);
	}

	CampusWidget::~CampusWidget()
	{
	}

	void CampusWidget::AddNewBuilding(uint16_t id, CGenericWidget* buildingWidget)
	{
		if (buildings[id] == nullptr) {
			//There is no building yet
			buildings[id] = std::shared_ptr<CGenericWidget>(buildingWidget);
		}
	}

	std::weak_ptr<CGenericWidget> CampusWidget::GetWidgetById(uint16_t id) const
	{
		return buildings[id];
	}

	void CampusWidget::resizeEvent(QResizeEvent* event)
	{
		qDebug() << "CampusWidget resizeEvent. New size is " << event->size();
		CGenericWidget::resizeEvent(event);
		for (auto building : buildings) {
			QSize buildingSize = building->GetSize();
			float pixelsInMeters = this->PixelRatio();
			building->setGeometry(pixelsInMeters * static_cast<BuildingWidget*>(building.get())->GetEOffset(),
				pixelsInMeters * static_cast<BuildingWidget*>(building.get())->GetNOffset(),
				pixelsInMeters* buildingSize.width(),
				pixelsInMeters* buildingSize.height());
		}
	}

}} // SmartCampus::Gui