#include "databaseSplit.h"
#include "stdio.h"
#include "string.h"
#include "err.h"
#include "ctype.h"
#include "unistd.h"
#include "stdlib.h"

int size = 2000;
char databaseFileName[1024];


void parse_command_line(int argc, char **argv);
int main (int argc, char **argv){

    parse_command_line(argc,argv);
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
    }else err(1,"Usage: databaseSplit [-s] databaseFileName");
}
