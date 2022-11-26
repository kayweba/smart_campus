#pragma once
#include <stdafx.h>
#include <CGenericWidget.h>
#include <BuildingWidget.h>
#include <QGraphicsDropShadowEffect>
#include <QMap>
#include <QStackedLayout>

namespace SmartCampus { namespace Gui {

	class CampusWidget : public CGenericWidget {
		public:
			CampusWidget(const QString & svgName, const int color, uint16_t width, uint16_t height, QWidget* parent = nullptr) noexcept;
			~CampusWidget();
			void AddNewBuilding(uint16_t id, CGenericWidget* buildingWidget);
			std::weak_ptr<CGenericWidget> GetWidgetById(uint16_t id) const;
		protected:
			void resizeEvent(QResizeEvent* event) override;
		private:
			QGraphicsDropShadowEffect* shadow;
			QMap<uint16_t, std::shared_ptr<CGenericWidget>> buildings;
	};

}} // SmartCampus::Gui