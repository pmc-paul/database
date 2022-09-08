#pragma once

// #include "database/logging_database.h"
#include <sqlite3.h>

namespace database
{
    class SQLiteLoggingDatabase //: public LoggingDatabase
    {
        public:

            SQLiteLoggingDatabase(std::string sqlite_database_file);
            ~SQLiteLoggingDatabase();

            bool logEvent(Event event);
            bool logError(Error error);
            bool logTiming(Timing timing);
            bool logMetric(Metric metric);
            Event loadEvent(std::string uuid);
            Error loadError(std::string uuid);
            Timing loadTiming(std::string uuid);
            Metric loadMetric(std::string uuid);

        private:
            sqlite3* db_connection;
            void checkError(int error_code);
    };

    class SQLiteError : public std::runtime_error
    {
        public:
            explicit SQLiteError(std::string what) : std::runtime_error(what)
            {

            }
    };
}
