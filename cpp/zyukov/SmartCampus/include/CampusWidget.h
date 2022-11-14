#pragma once
#include <stdafx.h>
#include <CGenericWidget.h>
#include <QGraphicsDropShadowEffect>

namespace SmartCampus { namespace Gui {

	class CampusWidget : public CGenericWidget {
		public:
			CampusWidget(const QString & svgName, const int color, QWidget * parent = nullptr) noexcept;
			~CampusWidget();
		protected:
		private:
			QGraphicsDropShadowEffect* shadow;
	};

}} // SmartCampus::Gui