#include "databaseSplit.h"
#include "stdio.h"
#include "string.h"
#include "err.h"
#include "ctype.h"
#include "unistd.h"
#include "stdlib.h"
#include "sqlite3.h"
int size = 2000;
char databaseFileName[1024];


void parse_command_line(int argc, char **argv);
int main (int argc, char **argv){
  sqlite3 *db;
  int rc;

  parse_command_line(argc,argv);

  rc = sqlite3_open(databaseFileName,&db);


  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return 1;
  }else{
    fprintf(stderr, "Opened database successfully\n");
  }
  sqlite3_close(db);

    return 0;
}
void parse_command_line(int argc, char **argv) {
    memset(databaseFileName,'\0',1024);
    int opt;
    long long sig;
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
        strcpy(databaseFileName,argv[optind]);
    }else{
        fprintf(stderr,"%s\n","Usage: databaseSplit [-s] databaseFileName");
        exit(1);
    }
}
