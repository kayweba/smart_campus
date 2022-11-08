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
				if (!caption.isEmpty()) {
					uiLabel = new QLabel(caption, this);
					uiLabel->setMargin(2);
					uiLabel->setContentsMargins(QMargins(5, 0, 0, 0));
					uiLabel->adjustSize();
				}
				else uiLabel = nullptr;
				m_parent = parent;
				m_internalLayout = new QVBoxLayout(this);
				m_internalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
				m_internalLayout->setSpacing(12);
				m_internalLayout->setContentsMargins(QMargins(10, 15, 10, 15));
				m_arrWidgets.clear();
				this->setLayout(m_internalLayout);
				adjustSize();
			}
			~BaseContainer()
			{
				if (uiLabel != nullptr)
					delete (uiLabel);
				QLayoutItem* wItem;
				while ((wItem = m_internalLayout->takeAt(0)) != 0) {
					m_internalLayout->removeWidget(wItem->widget());
					delete(wItem);
				}
				delete(m_internalLayout);
				m_arrWidgets.clear();
			}
			std::weak_ptr<T> AddWidget(T * ptrWidget, uint32_t id)
			{
				// Try to find widget into array
				auto found = std::find_if(m_arrWidgets.begin(), m_arrWidgets.end(), [id](QPair<uint32_t, std::shared_ptr<T>>& seek) {
						return seek.first == id;
					});
				// Adding new widget if not found
				if (found != m_arrWidgets.end()) {
					found->second = std::shared_ptr<T>(ptrWidget);
					return std::weak_ptr<T>(found->second);
				}
				else {
					m_arrWidgets.push_back(qMakePair(id, std::shared_ptr<T>(ptrWidget)));
					m_internalLayout->addWidget(m_arrWidgets.last().second.get());
					adjustSize();
					return std::weak_ptr<T>(m_arrWidgets.last().second);
				}
				return std::weak_ptr<T>();
			}
			void DeleteWidget(uint32_t id)
			{
				auto found = std::find_if(m_arrWidgets.begin(), m_arrWidgets.end(), [id](QPair<uint32_t, std::shared_ptr<T>>& seek) {
						return seek.first == id;
					});
				if (found != m_arrWidgets.end()) {
					// Delete widget from layout and from array
					m_internalLayout->removeWidget(found->second.get());
					m_arrWidgets.erase(found);
				}
				adjustSize();
			}
			uint32_t getId(int index) {
				if (index >= 0 && index < m_arrWidgets.size()) {
					return m_arrWidgets[index].first;
				}
				return UINT32_MAX;
			}
			std::weak_ptr<T> getWidget(int & index) {
				if (index >= 0 && index < m_arrWidgets.size()) {
					return std::weak_ptr<T>(m_arrWidgets[index].second);
				}
				return std::weak_ptr<T>();
			}
			std::weak_ptr<T> findWidget(const uint32_t & id) {
				auto found = std::find_if(m_arrWidgets.begin(), m_arrWidgets.end(), [id](QPair<uint32_t, std::shared_ptr<T>>& seek) {
						return seek.first == id;
					});
				if (found != m_arrWidgets.end())
					return std::weak_ptr<T>(found->second);
				else
					return std::weak_ptr<T>();
			}
			int GetWidgetsCount() const { return m_arrWidgets.size(); }
		protected:

		private:
			QLabel* uiLabel;
			QWidget* m_parent;
			QVBoxLayout* m_internalLayout;
			QVector<QPair<uint32_t, std::shared_ptr<T>>> m_arrWidgets;
	};

	class ElectricalSensor : public QWidget, public Database::DbElectricalSensor {
	public:
		explicit ElectricalSensor(QWidget* parent = nullptr, Database::DbElectricalSensorPtr ptrSensor = nullptr) noexcept;
		explicit ElectricalSensor(const ElectricalSensor& other) noexcept;
		ElectricalSensor& operator = (const ElectricalSensor& other);
		Database::DbElectricalSensorPtr & InternalSensor();
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
		QString stylePattern;
	};

}} // SmartCampus::Gui