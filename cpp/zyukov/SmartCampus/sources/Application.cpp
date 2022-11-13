#include <Application.h>
#include <DbManager.h>
#include <DbValueGenerator.h>
#include <BuildingTreeModel.h>
#include <BuildingTreeItem.h>

namespace SmartCampus {

	Application::Application(const int width, const int height) noexcept :
	ui(new Ui::MainWindow()),
	m_guiBuildings(ui->selectedRoomsView, "", false)
	{
		ui->setupUi(this);
		resize(QDesktopWidget().availableGeometry(this).size() * 0.9);
		m_guiBuildings.setContentsMargins(QMargins(0,0,0,0));
		m_ptrBuildingTreeModel = Gui::BuildingTreeModelPtr(new Gui::BuildingTreeModel());
		ui->buildingTree->setModel(m_ptrBuildingTreeModel.get());
		ui->scrollArea->setWidget(&m_guiBuildings);
		ptrBuildingTreeRoomContextMenu = new QMenu(ui->buildingTree);
		ptrBuildingTreeFloorContextMenu = new QMenu(ui->buildingTree);
		ptrBuildingTreeSensorContextMenu = new QMenu(ui->buildingTree);
		ptrTransferRoomAction = new QAction(QString::fromLocal8Bit("Добавить аудиторию к наблюдению"), ptrBuildingTreeRoomContextMenu);
		ptrTransferFloorAction = new QAction(QString::fromLocal8Bit("Добавить этаж к наблюдению"), ptrBuildingTreeFloorContextMenu);
		ptrTransferSensorAction = new QAction(QString::fromLocal8Bit("Добавить датчик к наблюдению"), ptrBuildingTreeSensorContextMenu);
		ui->buildingTree->setContextMenuPolicy(Qt::CustomContextMenu);
		ui->buildingTree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
		ptrBuildingTreeRoomContextMenu->addAction(ptrTransferRoomAction);
		ptrBuildingTreeFloorContextMenu->addAction(ptrTransferFloorAction);
		ptrBuildingTreeSensorContextMenu->addAction(ptrTransferSensorAction);
		this->setBaseSize(QSize(width, height));
/* Register metatype objects */
		qRegisterMetaType<Gui::ElectricalSensor>();
		qRegisterMetaType<Gui::ElectricalSensor>("Gui::ElectricalSensor");
		qRegisterMetaType<std::shared_ptr<Database::DbElectricalSensorType>>();
		qRegisterMetaType<std::shared_ptr<Database::DbElectricalSensorType>>("std::shared_ptr<Database::DbElectricalSensorType>const&");
		qRegisterMetaType<std::shared_ptr<Gui::BaseContainer<Gui::ElectricalSensor>>>();
		qRegisterMetaType<std::shared_ptr<Gui::BaseContainer<Gui::ElectricalSensor>>>("std::shared_ptr<Gui::BaseContainer<Gui::ElectricalSensor>>&");
		qRegisterMetaType<std::shared_ptr<Gui::BaseContainer<Gui::BaseContainer<Gui::ElectricalSensor>>>>();
		qRegisterMetaType<std::shared_ptr<Gui::BaseContainer<Gui::BaseContainer<Gui::ElectricalSensor>>>>("std::shared_ptr<Gui::BaseContainer<Gui::BaseContainer<Gui::ElectricalSensor>>>&");

		// Create thread to update arrays and widgets
		m_updateThread = boost::thread(boost::bind(&Application::UpdateThreadFunction, this));
/* Connect slots */
		connect(ui->startGenerationButton, &QAction::triggered, this, &Application::OnStartGeneratorClicked);
		connect(ui->stopGenerationButton, &QAction::triggered, this, &Application::OnStopGeneratorClicked);
		connect(ui->hideButton, &QPushButton::clicked, this, &Application::OnHideButtonClicked);
		connect(ui->buildingTree, &QTreeView::customContextMenuRequested, this, &Application::OnCustomContextMenu);
		connect(ptrTransferRoomAction, &QAction::triggered, this, &Application::OnTransferRoomClicked);
		connect(ptrTransferFloorAction, &QAction::triggered, this, &Application::OnTransferFloorClicked);
		connect(ptrTransferSensorAction, &QAction::triggered, this, &Application::OnTransferSensorClicked);
		connect(this, SIGNAL(requestUpdateBuildTree()), 
			this, SLOT(BuildTree()));
		connect(this, SIGNAL(requestUpdateDbStatus(const QString, int)), 
			this, SLOT(UpdateStatus(const QString, int)));
		connect(this, SIGNAL(requestUpdateSensorWidget(Gui::ElectricalSensor*, QString, bool, double, std::shared_ptr<Database::DbElectricalSensorType>const&, QString)),
			this, SLOT(UpdateSensorWidget(Gui::ElectricalSensor*, QString, bool, double, std::shared_ptr<Database::DbElectricalSensorType>const&, QString)));
		connect(this, SIGNAL(requestDeleteSensor(std::shared_ptr<Gui::BaseContainer<Gui::ElectricalSensor>> &, quint32)), 
			this, SLOT(DeleteSensorWidget(std::shared_ptr<Gui::BaseContainer<Gui::ElectricalSensor>>&, quint32)));
		connect(this, SIGNAL(requestDeleteRoom(std::shared_ptr<Gui::BaseContainer<Gui::BaseContainer<Gui::ElectricalSensor>>>&, quint32)), 
			this, SLOT(DeleteRoomWidget(std::shared_ptr<Gui::BaseContainer<Gui::BaseContainer<Gui::ElectricalSensor>>>&, quint32)));
		connect(this, SIGNAL(requestDeleteBuilding(quint32)), 
			this, SLOT(DeleteBuilding(quint32)));
		m_width = width;
		m_height = height;
		countOfSensors = 0;
		ui->statusbar->showMessage(QString::fromLocal8Bit("Программа запущена"));
		// Create generator to update DB values
		generator = Database::ValueGeneratorPtr(new Database::ValueGenerator("settings.json"));
		generator->ConnectErrorSignal(boost::bind(&Application::OnGeneratorEmitsErrorSignal, this));
		treeIsVisible = true;
		this->show();
	}

	Application::~Application() {
		delete(ptrBuildingTreeRoomContextMenu);
		delete(ptrBuildingTreeFloorContextMenu);
		delete(ptrBuildingTreeSensorContextMenu);
		delete(ptrTransferSensorAction);
		delete(ptrTransferFloorAction);
		delete(ptrTransferSensorAction);
		if (m_updateThread.joinable()) {
			m_updateThread.interrupt();
			m_updateThread.join();
		}
		delete(ui);
	}

	void Application::UpdateStatus(const QString status, int type)
	{
		ui->statusbar->showMessage(status);
	}

	void Application::UpdateSensorWidget(Gui::ElectricalSensor* sensor, QString name, bool state, double value, std::shared_ptr<Database::DbElectricalSensorType> const & type, QString unit)
	{
		if (sensor != nullptr && !sensor->shouldBeDeleted) {
			//boost::mutex::scoped_lock lock(arrLock);
			sensor->SetName(name);
			sensor->SetState(state);
			sensor->SetValue(value);
			sensor->SetType(type);
			sensor->SetUnit(unit);
		}
	}

	void Application::DeleteSensorWidget(std::shared_ptr<Gui::BaseContainer<Gui::ElectricalSensor>>& room, quint32 sensorId)
	{
		boost::mutex::scoped_lock lock(arrLock);
		room->DeleteWidget(sensorId);
		countOfSensors--;
	}

	void Application::DeleteRoomWidget(std::shared_ptr<Gui::BaseContainer<Gui::BaseContainer<Gui::ElectricalSensor>>>& building, quint32 roomId)
	{
		boost::mutex::scoped_lock lock(arrLock);
		building->DeleteWidget(roomId);
	}

	void Application::DeleteBuilding(quint32 buildingId)
	{
		boost::mutex::scoped_lock lock(arrLock);
		m_guiBuildings.DeleteWidget(buildingId);
	}

	void Application::OnGeneratorEmitsErrorSignal()
	{
		UpdateStatus(QString::fromLocal8Bit(generator->GetLastError().c_str()), MessageType::ErrorMessage);
	}

	void Application::OnCustomContextMenu(const QPoint& point)
	{
		QModelIndex index = ui->buildingTree->indexAt(point);
		if (index.isValid() && index.parent().parent().parent().isValid())
		{ 
			ptrBuildingTreeSensorContextMenu->exec(ui->buildingTree->viewport()->mapToGlobal(point));
		}
		else if (index.isValid() && index.parent().parent().isValid()  && m_ptrBuildingTreeModel->rowCount(index) > 0) {
			ptrBuildingTreeRoomContextMenu->exec(ui->buildingTree->viewport()->mapToGlobal(point));
		}
		else if (index.isValid() && index.parent().isValid() && m_ptrBuildingTreeModel->rowCount(index) > 0) {
			ptrBuildingTreeFloorContextMenu->exec(ui->buildingTree->viewport()->mapToGlobal(point));
		}
	}

	void Application::OnTransferRoomClicked(bool checked)
	{
		QModelIndexList indexes = ui->buildingTree->selectionModel()->selectedIndexes();
		if (indexes.size() > 0) {
			QModelIndex selectedIndex = indexes.at(0);
			// Prepare all data to widget's processing
			uint32_t roomId = m_ptrBuildingTreeModel->data(selectedIndex, Qt::DisplayRole, 1).toUInt();
			uint32_t buildingId = m_ptrBuildingTreeModel->data(selectedIndex.parent().parent(), Qt::DisplayRole, 1).toUInt();
			QString buildingName = m_ptrBuildingTreeModel->data(selectedIndex.parent().parent(), Qt::DisplayRole, 0).toString();
			uint32_t roomNumber = m_ptrBuildingTreeModel->data(selectedIndex, Qt::DisplayRole, 0).toUInt();
			boost::mutex::scoped_lock lock(arrLock);
			// Try to find nested building
			auto foundBuilding = m_guiBuildings.findWidget(buildingId);
			if (foundBuilding.lock() == nullptr) {
				foundBuilding = m_guiBuildings.AddWidget(new Gui::GuiBuildings(&m_guiBuildings, QString::fromLocal8Bit("%1").arg(buildingName)), buildingId);
			}
			// Try to find nested room
			auto foundRoom = foundBuilding.lock()->findWidget(roomId);
			if (foundRoom.lock() == nullptr) {
				foundRoom = foundBuilding.lock()->AddWidget(new Gui::GuiRooms(foundBuilding.lock().get(), QString::fromLocal8Bit("Аудитория №%1").arg(roomNumber)), roomId);
			}
			for (auto & sensor : m_electricalSensors) {
				if (sensor->GetRoomId() == roomId) {
					// Try to find nested sensor
					auto foundSensor = foundRoom.lock()->findWidget(sensor->GetId());
					if (foundSensor.lock() == nullptr) {
						foundSensor = foundRoom.lock()->AddWidget(new Gui::ElectricalSensor(foundRoom.lock().get(), sensor), sensor->GetId());
						UpdateSensorWidget(foundSensor.lock().get(), sensor->GetName(), sensor->GetState(), sensor->GetValue(), sensor->GetType(), sensor->GetType()->GetUnit());
						countOfSensors++;
					}
				}
			}
			ui->scrollArea->setMinimumWidth(foundBuilding.lock()->width() + 30);
		}
	}

	void Application::OnTransferFloorClicked(bool checked)
	{
		QModelIndexList indexes = ui->buildingTree->selectionModel()->selectedIndexes();
		if (indexes.size() > 0) {
			QModelIndex selectedIndex = indexes.at(0);
			// Prepare all data to widget's processing
			uint32_t buildingId = m_ptrBuildingTreeModel->data(selectedIndex.parent(), Qt::DisplayRole, 1).toUInt();
			QString buildingName = m_ptrBuildingTreeModel->data(selectedIndex.parent(), Qt::DisplayRole, 0).toString();
			// Selected index - current floor
			size_t currentFloor = m_ptrBuildingTreeModel->data(selectedIndex, Qt::DisplayRole, 2).toUInt();
			// Try to find nested building
			boost::mutex::scoped_lock lock(arrLock);
			auto foundBuilding = m_guiBuildings.findWidget(buildingId);
			if (foundBuilding.lock() == nullptr) {
				foundBuilding = m_guiBuildings.AddWidget(new Gui::GuiBuildings(&m_guiBuildings, QString::fromLocal8Bit("%1").arg(buildingName)), buildingId);
			}
			auto foundBuildingPtr = foundBuilding.lock();
			int childCount = m_ptrBuildingTreeModel->rowCount(selectedIndex);
			for (int i = 0; i < childCount; i++) {
				// Get all child indexes
				uint32_t roomId = selectedIndex.child(i, 1).data(Qt::DisplayRole).toUInt();
				uint32_t roomNumber = selectedIndex.child(i, 0).data(Qt::DisplayRole).toUInt();
				auto foundRoom = foundBuildingPtr->findWidget(roomId);
				if (foundRoom.lock() == nullptr) {
					foundRoom = foundBuildingPtr->AddWidget(new Gui::GuiRooms(foundBuildingPtr.get(), QString::fromLocal8Bit("Аудитория №%1").arg(roomNumber)), roomId);
				}
				auto foundRoomPtr = foundRoom.lock();
				for (auto& sensor : m_electricalSensors) {
					if (sensor->GetRoomId() == roomId) {
						// Try to find nested sensor
						auto foundRoomPtr = foundRoom.lock();
						auto foundSensor = foundRoomPtr->findWidget(sensor->GetId());
						if (foundSensor.lock() == nullptr) {
							foundSensor = foundRoom.lock()->AddWidget(new Gui::ElectricalSensor(foundRoom.lock().get(), sensor), sensor->GetId());
							UpdateSensorWidget(foundSensor.lock().get(), sensor->GetName(), sensor->GetState(), sensor->GetValue(), sensor->GetType(), sensor->GetType()->GetUnit());
							countOfSensors++;
						}
					}
				}
			}
			ui->scrollArea->setMinimumWidth(foundBuilding.lock()->width() + 30);
		}
	}

	void Application::OnTransferSensorClicked(bool checked)
	{
		QModelIndexList indexes = ui->buildingTree->selectionModel()->selectedIndexes();
		if (indexes.size() > 0) {
			QModelIndex selectedIndex = indexes.at(0);
			// Prepare all data to widget's processing
			uint32_t roomId = m_ptrBuildingTreeModel->data(selectedIndex.parent(), Qt::DisplayRole, 1).toUInt();
			uint32_t buildingId = m_ptrBuildingTreeModel->data(selectedIndex.parent().parent().parent(), Qt::DisplayRole, 1).toUInt();
			QString buildingName = m_ptrBuildingTreeModel->data(selectedIndex.parent().parent().parent(), Qt::DisplayRole, 0).toString();
			uint32_t roomNumber = m_ptrBuildingTreeModel->data(selectedIndex.parent(), Qt::DisplayRole, 0).toUInt();
			uint32_t sensorId = m_ptrBuildingTreeModel->data(selectedIndex, Qt::DisplayRole, 1).toUInt();
			// Try to find nested building
			boost::mutex::scoped_lock lock(arrLock);
			auto foundBuilding = m_guiBuildings.findWidget(buildingId);
			if (foundBuilding.lock() == nullptr) {
				foundBuilding = m_guiBuildings.AddWidget(new Gui::GuiBuildings(&m_guiBuildings, QString::fromLocal8Bit("%1").arg(buildingName)), buildingId);
			}
			// Try to find nested room
			auto foundRoom = foundBuilding.lock()->findWidget(roomId);
			if (foundRoom.lock() == nullptr) {
				foundRoom = foundBuilding.lock()->AddWidget(new Gui::GuiRooms(foundBuilding.lock().get(), QString::fromLocal8Bit("Аудитория №%1").arg(roomNumber)), roomId);
			}
			auto sensor = std::find_if(m_electricalSensors.begin(), m_electricalSensors.end(), [sensorId](Database::DbElectricalSensorPtr& seek) {
					return seek->GetId() == sensorId;
				});
			if (sensor != m_electricalSensors.end()) {
				// Try to find nested sensor
				auto foundSensor = foundRoom.lock()->findWidget(sensorId);
				if (foundSensor.lock() == nullptr) {
					foundSensor = foundRoom.lock()->AddWidget(new Gui::ElectricalSensor(foundRoom.lock().get(), *sensor), (*sensor)->GetId());
					UpdateSensorWidget(foundSensor.lock().get(), (*sensor)->GetName(), (*sensor)->GetState(), (*sensor)->GetValue(), (*sensor)->GetType(), (*sensor)->GetType()->GetUnit());
					countOfSensors++;
				}
			}
			ui->scrollArea->setMinimumWidth(foundBuilding.lock()->width() + 30);
		}
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
	}

	void Application::closeEvent(QCloseEvent* event)
	{
	}

	void Application::BuildTree()
	{
		m_ptrBuildingTreeModel->redrawData();
		boost::mutex::scoped_lock lock(arrLock);
		for (auto& building : m_buildings) {
			QModelIndex index = m_ptrBuildingTreeModel->addItem({ building->GetDescription(), building->GetId(), building->GetBuildingNumber(), building->GetCountOfFloors() });
			for (size_t floor = 0; floor < building->GetCountOfFloors(); floor++) {
				QModelIndex floorIndex = m_ptrBuildingTreeModel->addItem({ QString::fromLocal8Bit("%1 этаж").arg(floor + 1), QVariant::fromValue(building->GetId()), QVariant::fromValue(floor + 1)}, index);
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
									tr("[%1]").arg(sensor->GetName()), sensor->GetId() }
								, roomIndex);
							}
						} // for (auto& sensor : m_electricalSensors)
					} // if (room->GetBuildingId() == building->GetId() && firstDigit == (floor+1))
				} // for (auto room : m_rooms)
			} // for (size_t floor = 0; floor < building->GetCountOfFloors(); floor++)
		} // for (auto& building : m_buildings)
	}

	void Application::UpdateThreadFunction()
	{
		//Create DB connection and transfer update status function into the signal in main thread
		DBManager database("QSQLITE", boost::bind(&Application::InternalUpdateStatusFunc, this, boost::placeholders::_1, boost::placeholders::_2));
		try {
			while (1) {
				boost::this_thread::sleep_until(boost::chrono::system_clock::now() + boost::chrono::milliseconds(TIMER_UPDATE_MS));
				boost::this_thread::interruption_point();

				bool needToUpdateTree = false;
				{
					boost::mutex::scoped_lock lock(arrLock);
					m_buildings = database.GetBuildings();
					m_rooms = database.GetRooms();
					m_electricalSensors = database.GetElectricalSensors();
					// Update tree if necessary
					if (cacheArr[0] != CalculateCheckSumm(m_buildings) ||
						cacheArr[1] != CalculateCheckSumm(m_rooms) ||
						cacheArr[2] != CalculateCheckSumm(m_electricalSensors)) {

						// Store arrays check summ to compare them later
						cacheArr[0] = CalculateCheckSumm(m_buildings);
						cacheArr[1] = CalculateCheckSumm(m_rooms);
						cacheArr[2] = CalculateCheckSumm(m_electricalSensors);

						needToUpdateTree = true;
					}
				}
				if (needToUpdateTree) {
					// Emit the signal to update tree in UI thread e.g. main thread
					emit requestUpdateBuildTree();
				}

				// Iterate buildings
				{
					boost::mutex::scoped_lock lock(arrLock);
					QVector<uint32_t> restInPeaceBuildingWidget = {};
					for (int i = 0; i < m_guiBuildings.GetWidgetsCount(); i++) {
						auto guiBuilding = m_guiBuildings.getWidget(i);
						auto guiBuildingPtr = guiBuilding.lock();
						// Iterate rooms
						QVector<uint32_t> restInPeaceRoomWidget = {};
						if (!guiBuildingPtr->IsMinimazedTop()) {
							for (int j = 0; j < guiBuildingPtr->GetWidgetsCount(); j++) {
								auto guiRoom = guiBuildingPtr->getWidget(j);
								auto guiRoomPtr = guiRoom.lock();
								if (!guiRoomPtr->IsMinimazedTop()) {
									// Update all sensors
									for (int k = 0; k < guiRoomPtr->GetWidgetsCount(); k++) {
										auto guiSensor = guiRoomPtr->getWidget(k);
										auto guiSensorPtr = guiSensor.lock();
										if (!guiSensorPtr->shouldBeDeleted) {
											auto sensor = std::find_if(m_electricalSensors.begin(), m_electricalSensors.end(), [guiSensorPtr](Database::DbElectricalSensorPtr& seek) {
												return seek->GetId() == guiSensorPtr->GetId();
												});

											if (sensor != m_electricalSensors.end()) {
												// Update sensor's data
												if (guiSensorPtr->GetName() != (*sensor)->GetName() ||
													guiSensorPtr->GetState() != (*sensor)->GetState() ||
													guiSensorPtr->GetValue() != (*sensor)->GetValue() ||
													guiSensorPtr->GetType() == nullptr ||
													guiSensorPtr->GetType()->GetUnit() != (*sensor)->GetType()->GetUnit()) {
													emit requestUpdateSensorWidget(guiSensorPtr.get(),
														(*sensor)->GetName(),
														(*sensor)->GetState(),
														(*sensor)->GetValue(),
														(*sensor)->GetType(),
														(*sensor)->GetType()->GetUnit());
												}
											}
										}
										else { // Need to remove sensor widget
											emit requestDeleteSensor(guiRoomPtr, guiSensorPtr->GetId());
										}
									}
								}
								if (guiRoomPtr->GetWidgetsCount() == 0)
									restInPeaceRoomWidget.push_back(guiBuildingPtr->getId(j));
							}
						}
						// Remove room widgets if needed
						for (int it = 0; it < restInPeaceRoomWidget.size(); it++)
							emit requestDeleteRoom(guiBuildingPtr, restInPeaceRoomWidget[it]);

						if (guiBuildingPtr->GetWidgetsCount() == 0)
							restInPeaceBuildingWidget.push_back(m_guiBuildings.getId(i));
					}
					// Remove building widget if needed
					for (int it = 0; it < restInPeaceBuildingWidget.size(); it++) {
						emit requestDeleteBuilding(restInPeaceBuildingWidget[it]);
					}
				}
			}
		}
		catch (boost::thread_interrupted&) {}
	}

	void Application::InternalUpdateStatusFunc(const QString status, MessageType type)
	{
		emit requestUpdateDbStatus(status, (int)type);
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