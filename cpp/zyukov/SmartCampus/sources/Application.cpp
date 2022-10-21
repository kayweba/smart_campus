#include <Application.h>
#include <DbManager.h>
#include <ElectricalSensor.h>
#include <DbValueGenerator.h>

namespace SmartCampus {

	Application::Application(const int width, const int height) noexcept :
	ui(new Ui::MainWindow()) {
		this->setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);
		ui->setupUi(this);
		this->setBaseSize(QSize(width, height));
		connect(ui->startGenerationButton, &QAction::triggered, this, &Application::OnStartGeneratorClicked);
		connect(ui->stopGenerationButton, &QAction::triggered, this, &Application::OnStopGeneratorClicked);
		m_width = width;
		m_height = height;
		ui->statusbar->showMessage(QString::fromLocal8Bit("Программа запущена"));
		ConnectToDb("QSQLITE");
		generator = Database::ValueGeneratorPtr(new Database::ValueGenerator(database, "settings.json"));
		generator->ConnectErrorSignal(boost::bind(&Application::OnGeneratorEmitsErrorSignal, this));
		this->show();
	}

	Application::~Application() {
		m_timer.stop();
		delete(ui);
	}

	void Application::UpdateStatus(const QString& status)
	{
		ui->statusbar->showMessage(status);
	}

	void Application::ConnectToDb(const QString& dbType)
	{
		database = DbManagerPtr(new DBManager(dbType, ApplicationPtr(this)));
	}

	void Application::OnGeneratorEmitsErrorSignal()
	{
		UpdateStatus(QString::fromLocal8Bit(generator->GetLastError().c_str()));
	}

	void Application::LoadData()
	{
		auto sensorTypes = database->GetElectricalSensorTypes();
		auto sensors = database->GetElectricalSensors();
		auto rooms = database->GetRooms();
		sensorsUi.clear();
		roomsUi.clear();
		for (auto sensor : sensors) {
			ElectricalSensorPtr ptrSensor = ElectricalSensorPtr(new ElectricalSensor(this, sensor));
			auto found = std::find_if(sensorTypes.begin(), sensorTypes.end(), [sensor](const Database::DbElectricalSensorTypePtr& type)
				{
					return (sensor->GetTypeId() == type->GetId());
				}
			);
			if (found != sensorTypes.end()) {
				ptrSensor->SetType(*found);
			}
			ptrSensor->adjustSize();
			sensorsUi.push_back(ptrSensor);
		}
//		for (auto room : rooms) {
//			roomsUi.insert(std::make_pair(room->GetId(), QVector<SmartCampus::ElectricalSensorPtr>()));
//		}
		for (auto sensor : sensorsUi) {
			auto & roomVector = roomsUi[sensor->GetRoomId()];
			roomVector.second.push_back(sensor);
		}
		for (auto& room : roomsUi) {
			auto it = std::find_if(rooms.begin(), rooms.end(), [room](const Database::DbRoomPtr& db_room) {
					return (room.first == db_room->GetId());
				});
			if (it != rooms.end()) {
				room.second.first = (*it)->GetNumber();
			}
		}
}

	void Application::UpdateUi()
	{
		while (ui->sensorsGrid->count() != 0) {
			auto widget = ui->sensorsGrid->itemAt(0)->widget();
			ui->sensorsGrid->removeWidget(widget);
			delete(widget);
		}
		uint32_t rowCount = 0;
		uint32_t colCount = 0;
		for (auto room : roomsUi) {
			QFrame* roomFrame = new QFrame(this);
			roomFrame->setFrameShape(QFrame::Shape::WinPanel);
			roomFrame->setFrameShadow(QFrame::Shadow::Raised);
			QVBoxLayout* roomLayout = new QVBoxLayout();
			roomFrame->setLayout(roomLayout);
			QLabel* label = new QLabel(QString::fromLocal8Bit("Комната № %1").arg(room.second.first));
			//label->setAlignment(Qt::AlignmentFlag::AlignTop);
			roomLayout->setAlignment(Qt::AlignmentFlag::AlignTop);
			roomLayout->addWidget(label);
			if (colCount % 2 == 0) {
				rowCount++;
				colCount = 0;
			}
			ui->sensorsGrid->addWidget(roomFrame, rowCount, colCount);
			colCount++;
			for (auto & sensor : room.second.second) {
				roomLayout->addWidget(sensor.get());
				//ui->sensorsGrid->addWidget(sensor.get());
			}
		}
		UpdateStatus(QString::fromLocal8Bit("Количество датчиков: %1. Количество комнат: %2").arg(sensorsUi.size()).arg(roomsUi.size()));
	}

	void Application::OnStartGeneratorClicked()
	{
		generator->Start();
	}

	void Application::OnStopGeneratorClicked()
	{
		generator->Stop();
	}

	void  Application::showEvent(QShowEvent* event)
	{
		m_timer.start(TIMER_TIMEOUT_MS);
		LoadData();
		UpdateUi();
		connect(&m_timer, &QTimer::timeout, this, &Application::Timeout);
	}

	void Application::closeEvent(QCloseEvent* event)
	{

	}

	void Application::Timeout()
	{
		LoadData();
		UpdateUi();
	}
}