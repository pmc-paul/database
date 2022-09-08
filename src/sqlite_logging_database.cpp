#include "database/sqlite_logging_database.h"
#include <ros/ros.h>

namespace database
{
    SQLiteLoggingDatabase::SQLiteLoggingDatabase(std::string sqlite_database_file)
    {
        int err = 0;
        err = sqlite3_open(sqlite_database_file.c_str(), &(this->db_connection));
        if(err)
        {
            ROS_ERROR_STREAM("Error opening sqlite database file: " << sqlite_database_file << " : " << sqlite3_errmsg(this->db_connection));            
        }
    }

    SQLiteLoggingDatabase::~SQLiteLoggingDatabase()
    {
        sqlite3_close(this->db_connection);
    }

    bool SQLiteLoggingDatabase::logEvent(Event event)
    {
        sqlite3_stmt * stmt;
        std::string sql = "INSERT INTO events (uuid,  type, parent_event_uuid, timestamp) VALUES (?, ?, ?, ?)";

        try
        {
            int err = sqlite3_prepare_v2(this->db_connection, sql.c_str(), -1, &stmt, NULL);
            this->checkError(err);
            err = sqlite3_bind_text(stmt, 1, event.uuid.c_str(), event.uuid.length(), SQLITE_TRANSIENT);
            this->checkError(err);
            err = sqlite3_bind_text(stmt, 2, event.type.c_str(), event.type.length(), SQLITE_TRANSIENT);
            this->checkError(err);
            err = sqlite3_bind_text(stmt, 3, event.parent_uuid.c_str(), event.parent_uuid.length(), SQLITE_TRANSIENT);
            this->checkError(err);
            err = sqlite3_bind_int64(stmt, 4, event.timestamp.toNSec());
            this->checkError(err);
            err = sqlite3_step(stmt);
            this->checkError(err);
            err = sqlite3_finalize(stmt);
            this->checkError(err);
        }
        catch(const SQLiteError e)
        {
            ROS_ERROR_STREAM(e.what() << '\n');
        }
    }

    bool SQLiteLoggingDatabase::logError(Error error)
    {

    }

    bool SQLiteLoggingDatabase::logTiming(Timing timing)
    {

    }

    bool SQLiteLoggingDatabase::logMetric(Metric metric)
    {

    }

    Event SQLiteLoggingDatabase::loadEvent(std::string uuid)
    {

    }

    Error SQLiteLoggingDatabase::loadError(std::string uuid)
    {

    }

    Timing SQLiteLoggingDatabase::loadTiming(std::string uuid)
    {

    }

    Metric SQLiteLoggingDatabase::loadMetric(std::string uuid)
    {

    }

    void SQLiteLoggingDatabase::checkError(int error_code)
    {
        if(error_code)
        {
            std::string err_msg = sqlite3_errmsg(this->db_connection);
            ROS_ERROR_STREAM("SQLITE ERROR: " << err_msg);
            throw SQLiteError(err_msg);
        }
    }

}
c++
sqlite
cmake
