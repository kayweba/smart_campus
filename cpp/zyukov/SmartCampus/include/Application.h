#pragma once

#include <stdafx.h>
#include <QMainWindow>
#include <QMap>
#include <ui_mainwindow.h>
#include <ElectricalSensor.h>

namespace  SmartCampus {
#define TIMER_TIMEOUT_MS 50

class Application : public QMainWindow {
	public:
		explicit Application(const int width, const int height) noexcept;
		~Application();
		void UpdateStatus(const QString status, MessageType type);
		void ConnectToDb(const QString & dbType);
		void OnGeneratorEmitsErrorSignal();
		void LoadData();
		void UpdateUi();
	public slots:
		void OnStartGeneratorClicked();
		void OnStopGeneratorClicked();
		void OnHideButtonClicked(bool checked = false);
		void OnCustomContextMenu(const QPoint& point);

	private slots:
		void OnTransferRoomClicked(bool checked = false);
		void OnTransferFloorClicked(bool checked = false);
		void OnTransferSensorClicked(bool checked = false);
	protected:
		void showEvent(QShowEvent* event) override;
		void closeEvent(QCloseEvent* event) override;
	private:
		void Timeout();
		void ClearData();
		void BuildTree();
		template <class T>
		unsigned int CalculateCheckSumm(QVector<T>& arr);
		Ui::MainWindow* ui;
		bool treeIsVisible;
		DbManagerPtr database;
		Database::ValueGeneratorPtr generator;
		int m_width;
		int m_height;
		uint32_t countOfSensors;
		QTimer m_timer;
		boost::mutex sensorLock;

		QVector< Database::DbElectricalSensorTypePtr > m_sensorTypes;
		QVector< Database::DbElectricalSensorPtr > m_electricalSensors;
		unsigned int cacheArr[3];
		QVector< Database::DbRoomPtr > m_rooms;
		QVector< Database::DbBuildingPtr > m_buildings;
		Gui::BaseContainer<Gui::GuiBuildings> m_guiBuildings;
		QMenu* ptrBuildingTreeRoomContextMenu;
		QMenu* ptrBuildingTreeFloorContextMenu;
		QMenu* ptrBuildingTreeSensorContextMenu;
		QAction* ptrTransferRoomAction;
		QAction* ptrTransferFloorAction;
		QAction* ptrTransferSensorAction;
		Gui::BuildingTreeModelPtr m_ptrBuildingTreeModel;
};

}