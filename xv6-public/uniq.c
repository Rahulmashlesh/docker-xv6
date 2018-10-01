//
// Created by rahul on 9/26/18.

//if ((s1[i] | 32) < (s2[i] | 32))
//

#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
char *str;
int arrayOfDelimitr[512];
int count;

void display(int index) {
    while( (str[index] != '\n') || (str[index] == str[strlen(str)]) ){
        printf(1,"%c",str[index]);
        index++;
    }
    printf(1,"\n");
}

char* readFile (int fd) {
    int n;
    char *str;
    n = read(fd, buf, sizeof(buf));
    if(n < 0) {
        printf(1, "uniq: read error\n");
        exit();
    }

    str = malloc(strlen(buf) + 1);
    strcpy(str,buf);
    return str;
}


int compare (int thisPoint, int nextPoint) {
    int flag=0,j; //o is same , 1 is diff.
    for (j = 0; j<=5; j++) {
        if(str[arrayOfDelimitr[thisPoint]+j] != str[arrayOfDelimitr[nextPoint]+j]){
            flag =1;
        }
    }
    return flag;
}

int parseFile () {
    arrayOfDelimitr[0]=0;
    int i, j =1;
    for (i = 0;i <= strlen(str) ;i++) {
        if (str[i]=='\n') {
            printf(1, "position = %d\n", i);
            count++;
            arrayOfDelimitr[j]=i+1;
            j++;
        }
        if (str[i] == str[strlen(str)]) {
            printf(1, "position = %d\n", i);
            printf(1,"!!you reached the last line!!\n");
            count++;
            arrayOfDelimitr[j]=i+1;
            j++;
        }
    }
    return count;
}


void uniq(int fd) {

    str = readFile(fd);
    count = parseFile();
    int i, occurence, j;

    for (i=1; i<=count;i=i+occurence) {
        occurence = 1;
        display(arrayOfDelimitr[i - 1]);

        for (j = i; j < count; j++) {
            //printf(1,"%d,%d\n",i-1,j);
            if (compare(i -1, j) == 0) {
                occurence++; //true ie same
            } else {
                //printf(1,"Ocrn = %d, i = %d \n",occurence,i-1);
                break;
            }
        }
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
            printf(1, "uniq: cannot open %s\n", argv[i]);
            exit();
        }
        uniq(fd);
        close(fd);
    }
    exit();
}
