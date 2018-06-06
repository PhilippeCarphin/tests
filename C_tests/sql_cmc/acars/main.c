#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#define DEBUG
#include "/home/cmss/afsm/pca/Documents/GitHub/tests/C_tests/debug.h"
/*
 * Function that is given to sqlite to be called on query results using the
 * function sqlite3_ecec()
 */
// static int callback(void *NotUsed, int argc, char **argv, char **azColName){
//    int i;
//    printf("The callback\n");
//    for(i=0; i<argc; i++){
//       printf("  %s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//    }
//    return 0;
// }

int show_tables(sqlite3 *db)
{
   static const char *statement_str = "SELECT name FROM sqlite_master WHERE type='table';";
   /*
    * ref : https://www.sqlite.org/c3ref/prepare.html
    * If the nByte argument is negative, then zSql is read up to the first zero
    * terminator. If nByte is positive, then it is the number of bytes read from
    * zSql. If nByte is zero, then no prepared statement is generated. If the
    * caller knows that the supplied string is nul-terminated, then there is a
    * small performance advantage to passing an nByte parameter that is the
    * number of bytes in the input string including the nul-terminator.
    */
   sqlite3_stmt *s;
   sqlite3_prepare_v2(
         db,
         statement_str,
         -1,
         &s,
         NULL
   );

   while(sqlite3_step(s) != SQLITE_DONE){
      printf("TABLE : %s\n", sqlite3_column_text(s, 0));
   }
   sqlite3_finalize(s);
   return 0;
}

/*******************************************************************************
 *
*******************************************************************************/
void show_column(sqlite3_stmt *s, int col)
{
   int int_val;
   const unsigned char *string_val;
   float float_val;
   switch(sqlite3_column_type(s, col)){
   case SQLITE3_TEXT:
      string_val = sqlite3_column_text(s, col);
      // printf("%s, ", string_val);
      break;
   case SQLITE_INTEGER:
      int_val = sqlite3_column_int(s,col);
      // printf("%d, ", int_val);
      break;
   case SQLITE_FLOAT:
      float_val = sqlite3_column_double(s,col);
      // printf("%f, ", float_val);
      break;
   }
}

/*******************************************************************************
 *
*******************************************************************************/
void print_Rapport(sqlite3_stmt *s)
{
   printf("id_rapport=%d, id_stn=%s, lat=%f, lon=%f\n",
         sqlite3_column_int(s, 0),
         sqlite3_column_text(s, 1),
         sqlite3_column_double(s, 6),
         sqlite3_column_double(s, 7)
   );
}

/*******************************************************************************
 *
*******************************************************************************/
void print_row(sqlite3_stmt *s)
{
   int nb_col = sqlite3_column_count(s);
   for(int col = 0; col < nb_col; col++){
      show_column(s,col);
   }
}

/*******************************************************************************
 *
*******************************************************************************/
int show_rapport(sqlite3 *db)
{
   sqlite3_stmt *s;
   sqlite3_prepare_v2(
         db,
         "SELECT * FROM Rapport;",
         -1,
         &s,
         NULL
   );

   int nb_rapport = 0;
   while(sqlite3_step(s) != SQLITE_DONE){
      // print_Rapport(s);
      print_row(s);
      nb_rapport++;
   }

   sqlite3_finalize(s);
   return nb_rapport;
}

/*******************************************************************************
 *
*******************************************************************************/
int show_observation(sqlite3 *db)
{
   sqlite3_stmt *s;
   sqlite3_prepare_v2(
         db,
         "SELECT * FROM Observation;",
         -1,
         &s,
         NULL
   );

   int nb_observations = 0;
   while(sqlite3_step(s) != SQLITE_DONE){
      print_row(s);
      nb_observations++;
   }

   sqlite3_finalize(s);
   return nb_observations;
}

/*******************************************************************************
 *
*******************************************************************************/
int main(int argc, char **argv){
   int rc;

   char *database_filename = "acars.sqlite";

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
   show_tables(db);
   // printf("nb_rapports = %d\n", show_rapport(db));
   printf("nb_observations = %d\n", show_observation(db));

   /*
    * Closing the connection to the database.
    */
   sqlite3_close(db);
   return 0;
}
