#pragma once

#include <stdafx.h>
#include <QMainWindow>
#include <QMap>
#include <ui_mainwindow.h>
#include <ElectricalSensor.h>
#include <CampusWidget.h>
#include <BuildingWidget.h>

namespace  SmartCampus {
#define TIMER_UPDATE_MS 50

class Application : public QMainWindow {
	Q_OBJECT
	public:
		explicit Application(const int width, const int height) noexcept;
		~Application();
		void OnGeneratorEmitsErrorSignal();
	signals:
		void requestUpdateBuildTree();
		void requestUpdateDbStatus(const QString status, int type);
		void requestUpdateSensorWidget(Gui::ElectricalSensor* sensor, QString name, bool state, double value, std::shared_ptr<Database::DbElectricalSensorType> const & type, QString unit);
		void requestDeleteSensor(std::shared_ptr<Gui::BaseContainer<Gui::ElectricalSensor>> & room, quint32 sensorId);
		void requestDeleteRoom(std::shared_ptr<Gui::BaseContainer<Gui::BaseContainer<Gui::ElectricalSensor>>>& building, quint32 roomId);
		void requestDeleteBuilding(quint32 buildingId);
	public slots:
		void OnStartGeneratorClicked();
		void OnStopGeneratorClicked();
		void OnHideButtonClicked(bool checked = false);
		void OnCustomContextMenu(const QPoint& point);
		void BuildTree();
		void UpdateStatus(const QString status, int type);
		void UpdateSensorWidget(Gui::ElectricalSensor* sensor, QString name, bool state, double value, std::shared_ptr<Database::DbElectricalSensorType> const & type, QString unit);
		void DeleteSensorWidget(std::shared_ptr<Gui::BaseContainer<Gui::ElectricalSensor>>& room, quint32 sensorId);
		void DeleteRoomWidget(std::shared_ptr<Gui::BaseContainer<Gui::BaseContainer<Gui::ElectricalSensor>>>& building, quint32 roomId);
		void DeleteBuilding(quint32 buildingId);
private slots:
		void OnTransferRoomClicked(bool checked = false);
		void OnTransferFloorClicked(bool checked = false);
		void OnTransferSensorClicked(bool checked = false);
	protected:
		void showEvent(QShowEvent* event) override;
		void closeEvent(QCloseEvent* event) override;
	private:
		void OnBuildingEnterButtonClicked(uint16_t id);
		void UpdateThreadFunction();
		void InternalUpdateStatusFunc(const QString status, MessageType type);
		void DrawCampus();
		template <class T>
		unsigned int CalculateCheckSumm(QVector<T>& arr);
		Ui::MainWindow* ui;
		bool treeIsVisible;
		Database::ValueGeneratorPtr generator;
		int m_width;
		int m_height;
		uint32_t countOfSensors;
		boost::mutex sensorLock;
		boost::thread m_updateThread;
		boost::mutex arrLock;

		QVector< Database::DbElectricalSensorTypePtr > m_sensorTypes;
		QVector< Database::DbElectricalSensorPtr > m_electricalSensors;
		unsigned int cacheArr[3];
		QVector< Database::DbRoomPtr > m_rooms;
		QVector< Database::DbBuildingPtr > m_buildings;
		Gui::BaseContainer<Gui::GuiBuildings> * m_guiBuildings;
		QMenu* ptrBuildingTreeRoomContextMenu;
		QMenu* ptrBuildingTreeFloorContextMenu;
		QMenu* ptrBuildingTreeSensorContextMenu;
		QAction* ptrTransferRoomAction;
		QAction* ptrTransferFloorAction;
		QAction* ptrTransferSensorAction;
		QHBoxLayout* campusWidgetLayout;
		Gui::CampusWidget* m_campusWidget;
		Gui::BuildingTreeModelPtr m_ptrBuildingTreeModel;
};

}