#include "databaseSplit.h"
#include "stdio.h"
#include "string.h"
#include "err.h"
#include "ctype.h"
#include "unistd.h"
#include "stdlib.h"
#include "sqlite3.h"
int size = 2000;
int numOfDb = 0;
char databaseFileName[1024];
FILE *f;
char *buffer;

void parse_command_line(int argc, char **argv);
void readFileToString();
static int callback(void *data, int argc, char **argv, char **azColName);
int main (int argc, char **argv){
  sqlite3 *db,*pomdb;
  int rc;
  int i = 0;
  char *errorMsg=0;
  const char* data = "Callback function called";
  parse_command_line(argc,argv);

  for (i = 1; i< numOfDb;++i){
      memset(databaseFileName,'\0',1024);
      sprintf(databaseFileName,"Databases/db%d.db",i);
      rc = sqlite3_open(databaseFileName,&db);
      if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
      }else{
        fprintf(stderr, "Opened database successfully\n");
      }
      rc = sqlite3_exec(db,"SELECT * FROM albums",callback,(void*)data,&errorMsg);
      if( rc != SQLITE_OK ){
          fprintf(stderr, "SQL error: %s\n", errorMsg);
          sqlite3_free(errorMsg);
       }else{
          fprintf(stdout, "Operation done successfully\n");
       }
  }



  sqlite3_close(db);
  return 0;
}
void parse_command_line(int argc, char **argv) {
    memset(databaseFileName,'\0',1024);
    int opt;
    //long long sig;
    while ((opt = getopt(argc, argv, "s")) != -1) {
        switch (opt) {
        case 's':
            size = atoi(argv[optind]);
            break;
        default:
            fprintf(stderr,"%s\n","Usage: databaseSplit [-s] databaseFileName");
        }
    }
    if(argv[optind]){
        numOfDb = atoi(argv[optind]);
    }else{
        fprintf(stderr,"%s\n","Usage: databaseSplit [-s] databaseFileName");
        exit(1);
    }
}
void readFileToString(){
    int length=0;
    f = fopen("Split.sql","r");
    if (f){
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = (char *)malloc(length);
        if (buffer){
            fread (buffer, 1, length, f);
        }
        fclose(f);
    }
}
static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
