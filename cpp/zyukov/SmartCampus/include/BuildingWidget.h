#pragma once
#include <stdafx.h>
#include <CGenericWidget.h>

namespace SmartCampus { namespace Gui {

	class BuildingWidget : public CGenericWidget {
		public:
			BuildingWidget(uint16_t id, const QString & svgName, const int color, QSize size, uint16_t E_offset, uint16_t N_offset, QWidget* parent = nullptr) noexcept;
			~BuildingWidget();
			uint16_t GetEOffset() const;
			uint16_t GetNOffset() const;
			void ConnectEnterButtonToSignal(boost::signals2::signal<void(uint16_t)>::slot_type slot);
		public slots:
			void OnEnterButtonClicked(bool checked = false);
		protected:
			void resizeEvent(QResizeEvent* event) override;
		private:
			QGraphicsDropShadowEffect* shadow;
			uint16_t Eoffset_m;
			uint16_t Noffset_m;
			QVBoxLayout * _internalLayout;
			QPushButton * _enterButton;
			uint16_t _id;
			boost::signals2::signal<void(uint16_t)>m_onEnterButtonClickedSignal;
	};

}} // SmartCampus::Gui