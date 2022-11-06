#include <Application.h>
#include <DBManager.h>
#include <ElectricalSensor.h>
#include <DbValueGenerator.h>
#include <BuildingTreeModel.h>
#include <BuildingTreeItem.h>

namespace SmartCampus {

	Application::Application(const int width, const int height) noexcept :
	ui(new Ui::MainWindow()) {
		ui->setupUi(this);
		m_ptrBuildingTreeModel = Gui::BuildingTreeModelPtr(new Gui::BuildingTreeModel());
		ui->buildingTree->setModel(m_ptrBuildingTreeModel.get());
		ui->selectedRoomLayout->setAlignment(Qt::AlignmentFlag::AlignTop);
		ptrBuildingTreeRoomContextMenu = new QMenu(ui->buildingTree);
		ptrBuildingTreeFloorContextMenu = new QMenu(ui->buildingTree);
		ptrTransferSensorAction = new QAction(QString::fromLocal8Bit("Добавить аудиторию к наблюдению"), ptrBuildingTreeRoomContextMenu);
		ptrTransferFloorAction = new QAction(QString::fromLocal8Bit("Добавить этаж к наблюдению"), ptrBuildingTreeFloorContextMenu);
		ui->buildingTree->setContextMenuPolicy(Qt::CustomContextMenu);
		ui->buildingTree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
		ptrBuildingTreeRoomContextMenu->addAction(ptrTransferSensorAction);
		ptrBuildingTreeFloorContextMenu->addAction(ptrTransferFloorAction);
		this->setBaseSize(QSize(width, height));
		connect(ui->startGenerationButton, &QAction::triggered, this, &Application::OnStartGeneratorClicked);
		connect(ui->stopGenerationButton, &QAction::triggered, this, &Application::OnStopGeneratorClicked);
		connect(ui->hideButton, &QPushButton::clicked, this, &Application::OnHideButtonClicked);
		connect(ui->buildingTree, &QTreeView::customContextMenuRequested, this, &Application::OnCustomContextMenu);
		connect(ptrTransferSensorAction, &QAction::triggered, this, &Application::OnTransferSensorClicked);
		connect(ptrTransferFloorAction, &QAction::triggered, this, &Application::OnTransferFloorClicked);
		m_width = width;
		m_height = height;
		countOfSensors = 0;
		ui->statusbar->showMessage(QString::fromLocal8Bit("Программа запущена"));
		ConnectToDb("QSQLITE");
		generator = Database::ValueGeneratorPtr(new Database::ValueGenerator(database, "settings.json"));
		generator->ConnectErrorSignal(boost::bind(&Application::OnGeneratorEmitsErrorSignal, this));
		treeIsVisible = true;
		// Initialize map empty
		m_guiBuildingsPtr.clear();
		LoadData();
		// Initialize cache array {0}
		BuildTree();
		this->show();
	}

	Application::~Application() {
		m_timer.stop();
		delete(ptrBuildingTreeRoomContextMenu);
		delete(ptrBuildingTreeFloorContextMenu);
		delete(ptrTransferSensorAction);
		delete(ptrTransferFloorAction);
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

	void Application::OnCustomContextMenu(const QPoint& point)
	{
		QModelIndex index = ui->buildingTree->indexAt(point);
		if (index.isValid() && index.parent().parent().parent().isValid())
		{ 
			/*Sensor call context menu. Actually there is no handler*/
		}
		else if (index.isValid() && index.parent().parent().isValid()) {
			ptrBuildingTreeRoomContextMenu->exec(ui->buildingTree->viewport()->mapToGlobal(point));
		}
		else if (index.isValid() && index.parent().isValid()) {
			ptrBuildingTreeFloorContextMenu->exec(ui->buildingTree->viewport()->mapToGlobal(point));
		}
	}

	void Application::OnTransferSensorClicked(bool checked)
	{
		QModelIndexList indexes = ui->buildingTree->selectionModel()->selectedIndexes();
		if (indexes.size() > 0) {
			QModelIndex selectedIndex = indexes.at(0);
			// Prepare all data to widget's processing
			uint32_t roomId = m_ptrBuildingTreeModel->data(selectedIndex, Qt::DisplayRole, 1).toUInt();
			uint32_t buildingId = m_ptrBuildingTreeModel->data(selectedIndex.parent(), Qt::DisplayRole, 1).toUInt();
			QString buildingName = m_ptrBuildingTreeModel->data(selectedIndex.parent().parent(), Qt::DisplayRole, 0).toString();
			uint32_t roomNumber = m_ptrBuildingTreeModel->data(selectedIndex, Qt::DisplayRole, 0).toUInt();
			// Try to find building in map
			auto buildingFound = m_guiBuildingsPtr.find(buildingId);
			// Adding new building widget if not found
			if (buildingFound == m_guiBuildingsPtr.end()) {
				buildingFound = m_guiBuildingsPtr.insert(m_ptrBuildingTreeModel->data(selectedIndex.parent(), Qt::DisplayRole, 1).toUInt(),
					Gui::GuiBuildingsPtr(
						new Gui::BaseContainer<std::shared_ptr<Gui::BaseContainer<Gui::ElectricalSensorPtr>>>
						(ui->campusView, QString::fromLocal8Bit("%1").arg(buildingName))
					));
				ui->selectedRoomLayout->addWidget(buildingFound.value().get());
			}

			// Try to find room in building widget
			auto roomFound = buildingFound.value()->findWidget(roomId);
			if (roomFound == nullptr) {
				// Adding new room widget if not found
				Gui::GuiRoomsPtr roomWidget = Gui::GuiRoomsPtr(
					new Gui::BaseContainer< Gui::ElectricalSensorPtr >(
						buildingFound.value().get(), QString::fromLocal8Bit("Аудитория №%1").arg(roomNumber)
						));
				roomFound = buildingFound.value()->AddWidget(roomWidget, roomId);
			}

			for (auto sensor : m_electricalSensors) {
				if (sensor->GetRoomId() == roomId) {
					// If there is no sensor yet
					if (roomFound->findWidget(sensor->GetId()) == nullptr) {
						// Adding sensor to inspect
						roomFound->AddWidget(Gui::ElectricalSensorPtr(new Gui::ElectricalSensor(roomFound.get(), sensor)), sensor->GetId());
						countOfSensors++;
					}
				}
			}
		}
	}

	void Application::OnTransferFloorClicked(bool checked)
	{
		QModelIndexList indexes = ui->buildingTree->selectionModel()->selectedIndexes();
		if (indexes.size() == 1) {
			QModelIndex selectedIndex = indexes.at(0);
		}
	}

	void Application::LoadData()
	{
		ClearData();
		m_sensorTypes = database->GetElectricalSensorTypes();
		m_electricalSensors = database->GetElectricalSensors();
		m_rooms = database->GetRooms();
		m_buildings = database->GetBuildings();
/*
		for (auto & sensor : m_electricalSensors) {
			auto & found = m_inspectedSensors.find(sensor->GetId());
			if (found != m_inspectedSensors.end()) {

			}
		}
*/
	}

	void Application::UpdateUi()
	{
		if (cacheArr[0] != CalculateCheckSumm(m_buildings) ||
			cacheArr[1] != CalculateCheckSumm(m_rooms) ||
			cacheArr[2] != CalculateCheckSumm(m_electricalSensors)) {
			// Update tree view and store new cached values
			m_ptrBuildingTreeModel->redrawData();
			BuildTree();
		}
		// Iterate buildings
		for (auto & guiBuilding = m_guiBuildingsPtr.begin(); guiBuilding != m_guiBuildingsPtr.end();) {
			// Iterate rooms
			for (uint32_t i = 0; i < guiBuilding.value()->GetWidgetsCount(); i++) {
				auto guiRoom = guiBuilding.value()->getWidget(i);
				if (guiRoom != nullptr) {
					// Update all sensors
					for (uint32_t j = 0; j < guiRoom->GetWidgetsCount(); j++) {
						auto guiSensor = guiRoom->getWidget(j);
						if (guiSensor != nullptr) {
							if (!guiSensor->shouldBeDeleted) {
								auto sensor = std::find_if(m_electricalSensors.begin(), m_electricalSensors.end(), [guiSensor](Database::DbElectricalSensorPtr& seek) {
									return seek->GetId() == guiSensor->GetId();
									});
								if (sensor != m_electricalSensors.end()) {
									// Update sensor's data
									guiSensor->SetName((*sensor)->GetName());
									guiSensor->SetState((*sensor)->GetState());
									guiSensor->SetValue((*sensor)->GetValue());
									guiSensor->SetType((*sensor)->GetType());
									guiSensor->SetUnit((*sensor)->GetType()->GetUnit());
									guiSensor->SetSensorPtr(*sensor);
								}
							}
							// TODO разобраться с удалением умного указателя на Gui::ElectricalSensor (кто-то убивает его раньше, чем это сделает shared_ptr)
							// TODO:2 не удаляются аудитории, у которых изначально не было датчиков
							else { // Sensor should be deleted
								// Delete sensor from update
								guiRoom->DeleteWidget(guiSensor);
								countOfSensors--;
								if (guiRoom->GetWidgetsCount() == 0) {
									// Delete room
									guiBuilding.value()->DeleteWidget(guiRoom);
									if (guiBuilding.value()->GetWidgetsCount() == 0) {
										// Delete building
										//guiBuilding = m_guiBuildingsPtr.erase(guiBuilding);
										//continue;
									}
								}
							}
						}
					}
				}
			}
			guiBuilding++;
		}
		// TODO количество отслеживаемых датчиков обновляется на корректное значение только если датчики не удаляются.
		ui->sensCountLabel->setText(QString::fromLocal8Bit("Отслеживаемые датчики: %1").arg(countOfSensors));
	}

	void Application::OnStartGeneratorClicked()
	{
		generator->Start();
	}

	void Application::OnStopGeneratorClicked()
	{
		generator->Stop();
	}

	void Application::OnHideButtonClicked(bool checked)
	{
		treeIsVisible = !treeIsVisible;
		if (!treeIsVisible) {
			ui->buildingTree->hide();
			ui->hideButton->setText(QString(">"));
		}
		else {
			ui->buildingTree->show();
			ui->hideButton->setText(QString("<"));
		}
	}

	void  Application::showEvent(QShowEvent* event)
	{
		m_timer.start(TIMER_TIMEOUT_MS);
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

	void Application::ClearData()
	{
		m_sensorTypes.clear();
		m_electricalSensors.clear();
		m_rooms.clear();
		m_buildings.clear();
	}

	void Application::BuildTree()
	{
		for (auto& building : m_buildings) {
			QModelIndex index = m_ptrBuildingTreeModel->addItem({ building->GetDescription(), building->GetId(), building->GetBuildingNumber(), building->GetCountOfFloors() });
			for (size_t floor = 0; floor < building->GetCountOfFloors(); floor++) {
				QModelIndex floorIndex = m_ptrBuildingTreeModel->addItem({ QString::fromLocal8Bit("%1 этаж").arg(floor + 1), building->GetId() }, index);
				for (auto room : m_rooms) {
					int firstDigit;
					// Calculate first digit in room number and check if its matches with the floor number
					for (firstDigit = room->GetNumber(); firstDigit >= 10; firstDigit = firstDigit / 10);
					if (room->GetBuildingId() == building->GetId() && firstDigit == (floor + 1)) {
						// Adding room in this floor
						QModelIndex roomIndex = m_ptrBuildingTreeModel->addItem({ room->GetNumber(),  room->GetId(), room->GetDescription(), room->GetBuildingId() }, floorIndex);
						for (auto& sensor : m_electricalSensors) {
							if (sensor->GetRoomId() == room->GetId()) {
								// Adding sensor to this room
								m_ptrBuildingTreeModel->addItem({
									tr("[%1]").arg(sensor->GetName()) }
								, roomIndex);
							}
						} // for (auto& sensor : m_electricalSensors)
					} // if (room->GetBuildingId() == building->GetId() && firstDigit == (floor+1))
				} // for (auto room : m_rooms)
			} // for (size_t floor = 0; floor < building->GetCountOfFloors(); floor++)
		} // for (auto& building : m_buildings)
		for (size_t i = 0; i < 3; i++)
			cacheArr[i] = 0;
		// Store arrays check summ to compare them later
		Database::DbBuildingPtr ptrBuilding = Database::DbBuildingPtr(new Database::DbBuilding(0, 0, "", 0, Database::Coordinates()));
		cacheArr[0] = CalculateCheckSumm(m_buildings);
		cacheArr[1] = CalculateCheckSumm(m_rooms);
		cacheArr[2] = CalculateCheckSumm(m_electricalSensors);
	}

	template <class T>
	unsigned int Application::CalculateCheckSumm(QVector<T> & arr)
	{
		unsigned int result = 0;
		// Actually that is no safe convertation
		for (auto arr_element : arr) {
			result += arr_element->calculateSize();
		}
		return result;
	}
}