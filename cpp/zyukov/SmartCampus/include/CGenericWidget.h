#pragma once
#include <stdafx.h>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QSvgRenderer>
#include <QPixmap>
#include <QResizeEvent>
#include <QPainter>
#include <QBitmap>
#include <QDir>
#include <QDebug>
#include <QLayout>

namespace SmartCampus { namespace Gui {
	enum SideType {
		Width = 0,
		Height = 1
	};

	class CGenericWidget : public QFrame {
		public:
			CGenericWidget(const QString & svgName, const int color, float shadowOffset, uint16_t width, uint16_t height, QWidget * parent = nullptr) noexcept;
			~CGenericWidget();
			QSize GetSize() const;
			float GetShadowOffset() const;
			QSize maskSize() const;
			float PixelRatio() const;
		protected:
			virtual void UpdateMask(QResizeEvent * _event);
			void resizeEvent(QResizeEvent* _event) override;
		private:
			QString m_name;
			int m_color;
			float ratio;
			QSvgRenderer * svgFile;
			QPixmap * maskmap;
			QWidget * m_parent;	
			float m_shadowOffset;
			uint16_t _width;
			uint16_t _height;
			uint16_t maskWidth;
			uint16_t maskHeight;
			float pixelRatio;
	};

}} // SmartCampus::Gui
