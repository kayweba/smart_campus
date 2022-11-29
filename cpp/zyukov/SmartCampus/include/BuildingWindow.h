#include  <stdafx.h>
#include <DbData.h>
#include <QWindow>
#include <ui_Building.h>
#include <QSvgRenderer>
#include <QPainter>
#include <QBitmap>
#include <QGridLayout>

namespace SmartCampus { namespace Gui {

class BuildingWindow : public QWidget {
	public:
		BuildingWindow(Database::DbBuilding self, QVector<Database::DbRoom> rooms, QWidget* parent = nullptr) noexcept;
		~BuildingWindow();
	protected:
	private:
		Ui::BuildingForm* ui;
		Database::DbBuilding m_self;
		QVector<Database::DbRoom> m_rooms;
};

}} // SmartCampus::Gui