//
// Created by rahul on 9/26/18.
//

#include "types.h"
#include "stat.h"
#include "user.h"

char buf[8*1024];


char* getNextLine(int index, char* string ) {

    int j = 0;
    char *nextLine = "";

    while (index < strlen(string)) {
        if ( (string[index] == '\n' ) || (string[index]== string[strlen(string)]) ){
            nextLine[j] = '\0';
            return nextLine;
        }
        /*if (string[index] == str[strlen(str) ) {
            nextLine[j] = '\0';
            printf(1,"you reached the end");
            return nextLine;
        }*/
        nextLine[j++] = string[index];
        index++;
    }
    printf(1,"IF you reach here !! some thing went wrong in getNextLine function");
    return "ERROR!!!";
}


void uniq(int fd) {

    int i, n, count=0;
    char *str = "" ;

    char *line;

    n = read(fd, buf, sizeof(buf));
    if(n < 0) {
        printf(1, "uniq: read error\n");
        exit();
    }

    str = malloc(strlen(buf) + 1);
    strcpy(str,buf);

    for (i = 0;i <= strlen(str) ;i++) {
        if (str[i]=='\n') {
            printf(1, "position = %d\n", i);
            count++;
        }
    }
  /*  int g = strlen(str);   // code for the last line issue.
    str[g+2]=str[g+1];
    str[g+1]='\n';*/

  //printf(1,"last past of str - %s\n",str[strlen(str)]);

    int p=1;
    int point=0;
   // char *PrevLine, *CurnLine;
    line = getNextLine(point,str);
   // PrevLine = line;
    printf(1,"1--0--->%s\n", line);
    while (p<count) {
        point = point +strlen(line)+1;
        line = getNextLine(point,str);
        //CurnLine = line;
        printf(1,"%d--%d--->%s\n",p+1, point-1 ,line);
        p++;

       /* if(strcmp(CurnLine,PrevLine)==0) {
            printf(1,"current %s is same as prev %s\n", CurnLine, PrevLine);*/
        //}
    }
}



int
main(int argc, char *argv[]) {

    int fd, i;

    if(argc <= 1){
        uniq(0);
        exit();
    }

    for(i = 1; i < argc; i++){
        if((fd = open(argv[i], 0)) < 0){
            printf(1, "cat: cannot open %s\n", argv[i]);
            exit();
        }
        uniq(fd);
        close(fd);
    }
    exit();
}
