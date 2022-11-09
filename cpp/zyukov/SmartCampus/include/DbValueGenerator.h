#include <stdafx.h>

namespace SmartCampus { namespace Database {

	struct DbUpdateValue {
		uint32_t updatingIntervalMs;
		uint32_t maxValue;
	};

	enum StateType {
		SUCCESS = 0,
		FILE_NOT_FOUND = 1,
		DB_CANT_BE_REACHED = 2
	};

	class ValueGenerator {
		public:
			explicit ValueGenerator(std::string jsonFileName = "") noexcept;
			~ValueGenerator();
			void Start();
			void Stop();
			std::string GetLastError() const;
			void ConnectErrorSignal(boost::signals2::signal<void()>::slot_type _errorSignalHandler);
		protected:
			boost::signals2::signal<void()> errorSignal;
			void UpdateThreadFunction();
			StateType m_internalState = SUCCESS;
		private:
			void m_onDbMessage(QString dbMessage, MessageType type);
			std::string m_lastError;
			std::string m_jsonFilePath;
			QSqlDatabase m_database;
			boost::thread m_updatingThread;
			DbManagerPtr m_ptrDatabaseManager;
			DbUpdateValue m_updateInfo;
	};

}}