#include "database/sqlite_logging_database.h"
#include <ros/ros.h>
#include <sqlite3.h>
#include <stdio.h>
#include "std_msgs/String.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}

void sqlCallback(const std_msgs::String msg){

   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   const char *sql;
   char const *data = "Callback function called";

   rc = sqlite3_open("/home/victoria/paul/dev_ws/src/database/database/PAUL.db", &db);
   
   std::string query_string = "select * from items where name is " + msg.data;
   sql = query_string.c_str();

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

   if( rc != SQLITE_OK ) {
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
   sqlite3_free(zErrMsg);
   } else {
   fprintf(stdout, "Operation done successfully\n");
   }
   // sqlite3_close(db);
}


int main(int argc, char* argv[]) {

ros::init(argc, argv, "listener");

ros::NodeHandle n;
ros::Subscriber sub = n.subscribe("sqlRequest", 10, sqlCallback);

ros::spin();
}
