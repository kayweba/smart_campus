#include <DbValueGenerator.h>
#include <DbManager.h>

namespace SmartCampus {
	namespace Database {
		namespace pt = boost::property_tree;
		ValueGenerator::ValueGenerator(std::string jsonFileName) noexcept
		{
			m_ptrDatabaseManager = DbManagerPtr(new DBManager("QSQLITE", boost::bind(&ValueGenerator::m_onDbMessage, this, boost::placeholders::_1, boost::placeholders::_2)));
			m_updateInfo = DbUpdateValue();
			boost::filesystem::path jsonConfig = boost::dll::program_location().parent_path() / (jsonFileName);
			m_jsonFilePath = jsonConfig.string();
		}

		ValueGenerator::~ValueGenerator()
		{
			this->Stop();
			errorSignal.disconnect_all_slots();
		}

		void ValueGenerator::Start()
		{
			pt::ptree dbUpdateConfiguration;
			if (boost::filesystem::exists(m_jsonFilePath)) {
				try {
					pt::json_parser::read_json(m_jsonFilePath, dbUpdateConfiguration);
					pt::ptree configurationElement = dbUpdateConfiguration.get_child("data");
					m_updateInfo.updatingIntervalMs = configurationElement.get<uint32_t>("interval");
					m_updateInfo.maxValue = configurationElement.get<uint32_t>("max_value");
				}
				catch (pt::json_parser::json_parser_error const& error) {
					m_lastError = error.message();
					if (!errorSignal.empty()) errorSignal();
				}
			}
			else {
				m_lastError = "Р¤Р°Р№Р»Р° РєРѕРЅС„РёРіСѓСЂР°С†РёРё " + m_jsonFilePath + " РЅРµ СЃСѓС‰РµСЃС‚РІСѓРµС‚.";
				m_internalState = StateType::FILE_NOT_FOUND;
				if (!errorSignal.empty()) errorSignal();
			}
			m_updatingThread = boost::thread(boost::bind(&ValueGenerator::UpdateThreadFunction, this));
		}

		void ValueGenerator::Stop()
		{
			if (m_updatingThread.joinable()) {
				m_updatingThread.interrupt();
				m_updatingThread.join();
			}
		}

		std::string ValueGenerator::GetLastError() const {
			return m_lastError;
		}

		void ValueGenerator::ConnectErrorSignal(boost::signals2::signal<void()>::slot_type _errorSignalHandler)
		{
			errorSignal.connect(_errorSignalHandler);
		}

		void ValueGenerator::m_onDbMessage(QString dbMessage, MessageType type)
		{
			if (type == MessageType::ErrorMessage) {
				m_lastError = dbMessage.toStdString();
				if (!errorSignal.empty()) errorSignal();
			}
		}

		void ValueGenerator::UpdateThreadFunction()
		{
			try {
				uint32_t counter = 0;
				while (1) {
					if (m_internalState == StateType::SUCCESS) {
						boost::this_thread::sleep_until(boost::chrono::steady_clock::now() + boost::chrono::milliseconds(m_updateInfo.updatingIntervalMs));
						auto sensors = m_ptrDatabaseManager->GetElectricalSensors();
						for (auto sensor : sensors) {
							sensor->SetState(std::rand() % 2 > 0 ? true : false);
							if (sensor->GetState())
								sensor->SetValue(std::rand() % m_updateInfo.maxValue);
							else
								sensor->SetValue(0);
							m_ptrDatabaseManager->UpdateElectricalSensor(sensor);
						}
					}
					boost::this_thread::interruption_point();
				}
			}
			catch (boost::thread_interrupted &) {
			}
		}

	}
}