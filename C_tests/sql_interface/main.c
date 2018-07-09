#include <unistd.h>
#include <stdio.h>
#include <sqlite3.h>
const int INSTRUCTIONS_PER_CALL = 1;
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

/*
 * Callback that that will be run every INSTRUCTIONS_PER_CALL instructions of
 * the database virtual machine
 */
int query_progress_callback(void *params)
{
  int *nb_instr = (int *) params;
  *nb_instr += INSTRUCTIONS_PER_CALL;

  static int i = 0;
  static int calls = 0;
  static char spinner[] = "-\\|/";
  static int spinner_chars = sizeof(spinner)/sizeof(char) - 1;
  calls++;
  if(calls % 10000 == 0){
    i = (i+1) % spinner_chars;
    fprintf(stderr, "\r %c ==== progress_callback_calls : %d =========        ", spinner[i], calls);
    sleep(1); // Artificially slow down the process.
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
   * Installing the progress callback
   */
  int nb_dbvm_instructions = 0;
  sqlite3_progress_handler(db, INSTRUCTIONS_PER_CALL, query_progress_callback, &nb_dbvm_instructions);

  /*
   * We can execute an sql statement on the database and also have a callback
   * function called.
   */
  rc = sqlite3_exec(db, sql_statement, NULL, 0, &zErrMsg);
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  /*
   * Keep doing the same query over and over just to make the progress
   * bar keep going
   */
  while(1){rc = sqlite3_exec(db, sql_statement, NULL, 0, &zErrMsg);}
  /*
   * Closing the connection to the database.
   */
  sqlite3_close(db);
  return 0;
}
