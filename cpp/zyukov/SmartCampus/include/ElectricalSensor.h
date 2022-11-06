#pragma once

#include <stdafx.h>
#include <DbData.h>
#include <ui_electricalsensor.h>

namespace SmartCampus {	namespace Gui {

	template <class T>
	class BaseContainer : public QFrame {
		public:
			explicit BaseContainer(QWidget* parent, const QString& caption) : QFrame(parent)
			{
				this->setFrameStyle(QFrame::Panel | QFrame::Raised);
				uiLabel = new QLabel(caption, this);
				uiLabel->adjustSize();
				m_internalLayout = new QVBoxLayout(this);
				m_internalLayout->setSpacing(10);
				m_internalLayout->setContentsMargins(QMargins(10, 15, 10, 15));
				m_arrWidgets.clear();
				this->setLayout(m_internalLayout);
				adjustSize();
			}
			~BaseContainer()
			{
				delete (uiLabel);
				QLayoutItem* wItem;
				while ((wItem = m_internalLayout->takeAt(0)) != 0)
					delete(wItem);
				delete(m_internalLayout);
				m_arrWidgets.clear();
			}
			T & AddWidget(T &  widget, uint32_t id)
			{
				// Try to find widget into array
				auto found = std::find_if(m_arrWidgets.begin(), m_arrWidgets.end(), [id](QPair<uint32_t, T>& seek) {
						return seek.first == id;
					});
				// Adding new widget if not found
				if (found != m_arrWidgets.end()) {
					return found->second;
				}
				else {
					m_arrWidgets.push_back(qMakePair(id, widget));
					m_internalLayout->addWidget(widget.get());
					adjustSize();
					return (m_arrWidgets.last().second);
				}
				return T();
			}
			void DeleteWidget(T & widget)
			{
				auto found = std::find_if(m_arrWidgets.begin(), m_arrWidgets.end(), [widget](QPair<uint32_t, T>& seek) {
						return  seek.second == widget;
					});
				if (found != m_arrWidgets.end()) {
					// Delete widget from layout and from array
					m_internalLayout->removeWidget(found->second.get());
					m_arrWidgets.erase(found);
				}
				adjustSize();
			}
			void DeleteWidget(uint32_t id)
			{
				auto found = std::find_if(m_arrWidgets.begin(), m_arrWidgets.end(), [id](QPair<uint32_t, T>& seek) {
						return seek.first == id;
					});
				if (found != m_arrWidgets.end()) {
					// Delete widget from layout and from array
					m_internalLayout->removeWidget(found->second.get());
					m_arrWidgets.erase(found);
				}
				adjustSize();
			}
			T getWidget(uint32_t & index) {
				if (index >= 0 && index < m_arrWidgets.size()) {
					return m_arrWidgets[index].second;
				}
				return nullptr;
			}
			T findWidget(const uint32_t & id) {
				auto found = std::find_if(m_arrWidgets.begin(), m_arrWidgets.end(), [id](QPair<uint32_t, T>& seek) {
						return seek.first == id;
					});
				if (found != m_arrWidgets.end())
					return found->second;
				else
					return nullptr;
				return nullptr;
			}
			int GetWidgetsCount() const { return m_arrWidgets.size(); }
		protected:

		private:
			QLabel* uiLabel;
			QVBoxLayout* m_internalLayout;
			QVector<QPair<uint32_t, T>> m_arrWidgets;
			uint32_t m_id;
	};

	class ElectricalSensor : public QWidget, public Database::DbElectricalSensor {
	public:
		explicit ElectricalSensor(QWidget* parent = nullptr, Database::DbElectricalSensorPtr ptrSensor = nullptr) noexcept;
		explicit ElectricalSensor(const ElectricalSensor& other) noexcept;
		explicit ElectricalSensor() noexcept;
		ElectricalSensor& operator = (const ElectricalSensor& other);
		Database::DbElectricalSensorPtr & const InternalSensor();
		~ElectricalSensor();

		void SetName(const QString& name);
		void SetState(const bool& state);
		void SetValue(const double& value);
		void SetType(const Database::DbElectricalSensorTypePtr& ptrType);
		void SetUnit(const QString& unit);
		void SetParent(QWidget* parent);
		void SetSensorPtr(Database::DbElectricalSensorPtr & ptrSensor);

		bool  shouldBeDeleted;
	protected:
	private:
		void OnCloseButtonClicked(bool checked = false);
		Ui::ElectricalSensor* ui;
		QWidget* m_parent;
		Database::DbElectricalSensorTypePtr m_ptrType;
		Database::DbElectricalSensorPtr m_ptrSensor;
	};

}} // SmartCampus::Gui