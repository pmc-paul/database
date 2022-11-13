// #include "database/sqlite_logging_database.h"
#include <ros/ros.h>
#include <sqlite3.h>
#include <stdio.h>
#include "std_msgs/String.h"
#include "database/itemDetails.h"
#include "database/itemDetailsName.h"

int sql_response;
std::string image_name;
float level;
float width;
float height;
std::string id;

static int callback(void *data, int argc, char **argv, char **azColName){
   image_name = argv[3];
   level = (float)strtod(argv[4],NULL);
   width = (float)strtod(argv[5],NULL);
   height = (float)strtod(argv[6],NULL);
   id = argv[0];
   return 0;
}

bool sqlSrv(database::itemDetails::Request  &req, database::itemDetails::Response &res)
{
   //reset global variables
   image_name = "";
   level = 0.0;
   width = 0.0;
   height = 0.0;
   id = "";
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   const char *sql;
   char const *data = "Callback function called";

   rc = sqlite3_open("/home/victoria/paul/dev_ws/src/database/database/PAUL.db", &db);
   
   std::string query_string = "SELECT * FROM items WHERE id IS '" + req.id + "'";
   sql = query_string.c_str();

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

   // close database
   sqlite3_close(db);

   //set response
   res.image_name = image_name;
   res.level = level;
   res.width = width;
   res.height = height;
   res.id = id;
   return true;
}

bool sqlSrvName(database::itemDetailsName::Request  &req, database::itemDetailsName::Response &res)
{
   //reset global variables
   image_name = "";
   level = 0.0;
   width = 0.0;
   height = 0.0;
   id = "";
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   const char *sql;
   char const *data = "Callback function called";

   rc = sqlite3_open("/home/victoria/paul/dev_ws/src/database/database/PAUL.db", &db);
   
   std::string query_string = "SELECT * FROM items WHERE image IS '" + req.name + "'";
   sql = query_string.c_str();

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

   // close database
   sqlite3_close(db);

   //set response
   res.image_name = image_name;
   res.level = level;
   res.width = width;
   res.height = height;
   res.id = id;
   return true;
}

int main(int argc, char* argv[]) {

ros::init(argc, argv, "sql_server");

ros::NodeHandle n;
ros::ServiceServer service = n.advertiseService("sqlRequest", sqlSrv);
ros::ServiceServer serviceName = n.advertiseService("sqlRequestName", sqlSrvName);

ros::spin();
}
