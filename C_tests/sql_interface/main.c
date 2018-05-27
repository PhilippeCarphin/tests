#include <stdio.h>
#include <sqlite3.h>
/*
 * Function that is given to sqlite to be called on query results using the
 * function sqlite3_ecec()
 */
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  printf("The callback\n");
  for(i=0; i<argc; i++){
    printf("  %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  return 0;
}

int main(int argc, char **argv){
  char *zErrMsg = 0;
  int rc;

  if( argc!=3 ){
    fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
    return(1);
  }
  char *database_filename = argv[1];
  char *sql_statement = argv[2];

  /*
   * Opening the database file and creating a handle
   */
  sqlite3 *db;
  rc = sqlite3_open(database_filename, &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1 ;
  }

  /*
   * We can execute an sql statement on the database and also have a callback
   * function called.
   */
  rc = sqlite3_exec(db, sql_statement, callback, 0, &zErrMsg);
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  /*
   * Closing the connection to the database.
   */
  sqlite3_close(db);
  return 0;
}
