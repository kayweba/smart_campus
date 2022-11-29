#include <BuildingWindow.h>

namespace SmartCampus { namespace Gui {

	BuildingWindow::BuildingWindow(Database::DbBuilding self, QVector<Database::DbRoom> rooms, QWidget* parent) noexcept
	{
		ui = new Ui::BuildingForm();
		ui->setupUi(this);
		this->setWindowTitle(self.GetDescription());
		m_self = self;
		m_rooms = rooms;
		ui->spinBox->setMaximum(self.GetCountOfFloors());
		ui->spinBox->setMinimum(1);
		setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
		setWindowModality(Qt::ApplicationModal);

		QSvgRenderer svgFile(":/svgs/img/" + self.GetFileName());
		if (!svgFile.isValid())
			return;
		QString bgColorString = "background-color: #" + QString("%1").arg(0x78b0f0, 2, 16) + ";";
		ui->buildingContentFrame->setStyleSheet(bgColorString);
		float defaultSvgWidth = svgFile.defaultSize().width();
		float defaultSvgHeight = svgFile.defaultSize().height();
		this->resize(QSize(defaultSvgWidth * 3, defaultSvgHeight * 3 + ui->floorPromptLabel->height() + 20));
		QSize pixmapSize(defaultSvgWidth * 3, defaultSvgHeight * 3);
		QPixmap maskmap(pixmapSize);
		maskmap.fill(Qt::transparent);
		QPainter painter(&maskmap);
		svgFile.render(&painter);
		painter.end();
		ui->buildingContentFrame->setMask(maskmap.mask());
		QFrame* roomsFrame = new QFrame(ui->buildingContentFrame);
		QGridLayout* roomsLayout = new QGridLayout(ui->buildingContentFrame);
		roomsFrame->setLayout(roomsLayout);
	}

	BuildingWindow::~BuildingWindow()
	{
		delete(ui);
	}

}} // SmartCampus::Gui