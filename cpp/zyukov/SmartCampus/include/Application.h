#pragma once

#include <stdafx.h>
#include <QMainWindow>
#include <ui_mainwindow.h>

namespace  SmartCampus {
#define TIMER_TIMEOUT_MS 500

class Application : public QMainWindow {
	public:
		explicit Application(const int width, const int height) noexcept;
		~Application();
		void UpdateStatus(const QString & status);
		void ConnectToDb(const QString & dbType);
		void OnGeneratorEmitsErrorSignal();
		void LoadData();
		void UpdateUi();
	public slots:
		void OnStartGeneratorClicked();
		void OnStopGeneratorClicked();
protected:
		void showEvent(QShowEvent* event) override;
		void closeEvent(QCloseEvent* event) override;
	private:
		void Timeout();
		void ClearData();
		Ui::MainWindow* ui;
		QVector<SmartCampus::ElectricalSensorPtr> sensorsUi;
		DbManagerPtr database;
		Database::ValueGeneratorPtr generator;
		int m_width;
		int m_height;
		QTimer m_timer;
		std::map<uint32_t, std::pair<uint32_t, QVector<SmartCampus::ElectricalSensorPtr>>> roomsUi;

		QVector<Database::DbElectricalSensorTypePtr> m_sensorTypes;
		QVector<Database::DbElectricalSensorPtr> m_electricalSensors;
		QVector<Database::DbRoomPtr> m_rooms;
		QVector<Database::DbBuildingPtr> m_buildings;
};

}