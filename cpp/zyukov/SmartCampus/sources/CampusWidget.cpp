#include <CampusWidget.h>

namespace SmartCampus { namespace Gui {

	CampusWidget::CampusWidget(const QString & svgName, const int color, QWidget * parent) noexcept
		: CGenericWidget(svgName, color, 5, parent)
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

}} // SmartCampus::Gui