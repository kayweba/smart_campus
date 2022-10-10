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

		void LoadData();
		void UpdateUi();
	protected:
		void showEvent(QShowEvent* event) override;
		void closeEvent(QCloseEvent* event) override;
	private:
		void Timeout();

		Ui::MainWindow* ui;
		QVector<SmartCampus::ElectricalSensorPtr> sensorsUi;
		DbManagerPtr database;
		int m_width;
		int m_height;
		QTimer m_timer;
		std::map<uint32_t, std::pair<uint32_t, QVector<SmartCampus::ElectricalSensorPtr>>> roomsUi;
};

}