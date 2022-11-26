#include <CGenericWidget.h>

namespace SmartCampus { namespace Gui {

	CGenericWidget::CGenericWidget(const QString & svgName, const int color, float shadowOffset, uint16_t width, uint16_t height, QWidget * parent) noexcept
		: QFrame(parent)
	{
		m_shadowOffset = shadowOffset;
		m_parent = parent;
		m_name = svgName;
		m_color = color;
		_width = width; // Width of rect in meters
		_height = height; // Height of rec in meters
		svgFile = new QSvgRenderer(":/svgs/img/" + svgName);
		pixelRatio = (int)(this->size().width() / _width);
		if (!svgFile->isValid()) 
			return;
		QString bgColorString = "background-color: #" + QString("%1").arg(color, 2, 16) + ";";
		qDebug() << bgColorString;
		setStyleSheet(bgColorString);
	}

	CGenericWidget::~CGenericWidget()
	{
		delete(svgFile);
		delete(maskmap);
	}

	void CGenericWidget::UpdateMask(QResizeEvent * _event)
	{
		float defaultSvgWidth = svgFile->defaultSize().width();
		float defaultSvgHeight = svgFile->defaultSize().height();
		// Check which state of new size is higher
		ratio = 0.0;
		if (defaultSvgWidth > defaultSvgHeight) {
			// SVG's width is higher than height
			ratio = _event->size().width() / defaultSvgWidth;
		}
		else {
			// SVG's height is higher than width
			ratio = _event->size().height() / defaultSvgHeight;
		}
		QSize pixmapSize(defaultSvgWidth * ratio - m_shadowOffset, defaultSvgHeight * ratio- m_shadowOffset);
		maskWidth = pixmapSize.width();
		maskHeight = pixmapSize.height();
		pixelRatio = maskWidth / _width;
		maskmap = new QPixmap(pixmapSize);
		maskmap->fill(Qt::transparent);
		QPainter* painter = new QPainter(maskmap);
		svgFile->render(painter);
		setMask(maskmap->mask());
	}

	QSize CGenericWidget::GetSize() const { 
		return QSize(_width, _height);
	}

	float CGenericWidget::GetShadowOffset() const
	{
		return m_shadowOffset;
	}

	void CGenericWidget::resizeEvent(QResizeEvent* _event)
	{
		UpdateMask(_event);
		QFrame::resizeEvent(_event);
	}

	QSize CGenericWidget::maskSize() const
	{
		return QSize(maskWidth, maskHeight);
	}
	float CGenericWidget::PixelRatio() const
	{
		return pixelRatio;
	}

}} // SmartCampus::Gui