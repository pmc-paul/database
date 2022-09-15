// #include "database/sqlite_logging_database.h"
#include <ros/ros.h>
#include <sqlite3.h>
#include <stdio.h>
#include "std_msgs/String.h"
#include "database/itemDetails.h"

int sql_response;
std::string image_name;
float level;
float width;
float height;

static int callback(void *data, int argc, char **argv, char **azColName){
   image_name = argv[1];
   level = (float)strtod(argv[2],NULL);
   width = (float)strtod(argv[3],NULL);
   height = (float)strtod(argv[4],NULL);
   return 0;
}

bool sqlSrv(database::itemDetails::Request  &req, database::itemDetails::Response &res)
{
   //reset global variables
   image_name = "";
   level = 0.0;
   width = 0.0;
   height = 0.0;
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   const char *sql;
   char const *data = "Callback function called";

   rc = sqlite3_open("/home/victoria/paul/dev_ws/src/database/database/PAUL.db", &db);
   
   std::string query_string = "SELECT * FROM items WHERE name IS '" + req.id + "'";
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
   return true;
}


int main(int argc, char* argv[]) {

ros::init(argc, argv, "sql_server");

ros::NodeHandle n;
ros::ServiceServer service = n.advertiseService("sqlRequest", sqlSrv);

ros::spin();
}
