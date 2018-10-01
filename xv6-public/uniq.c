//
// Created by rahul on 9/26/18.
//

#include "types.h"
#include "stat.h"
#include "user.h"

char buf[1024*4];
char *str;
int arrayOfDelimitr[512];
int count;
int flagc=0, flagi=0, flagd=0;

void display(int index, int occurance) {
    if (flagc==1) {
        printf(1,"%4d ", occurance);
    }
    while( (str[index] != '\n') || (str[index] == str[strlen(str)]) ){
        printf(1,"%c",str[index]);
        index++;
    }
    printf(1,"\n");
}

char* readFile (int fd) {
    int n;
    n = read(fd, buf, sizeof(buf));
    if(n < 0) {
        printf(1, "uniq: read error\n");
        exit();
    }
    str = malloc(strlen(buf) + 1);
    strcpy(str,buf);
    return str;
}

int compare (int thisPoint, int nextPoint) {    // case sensitive
    int flag=0,j;
    for (j = 0; j<=5; j++) {
        if(str[arrayOfDelimitr[thisPoint]+j] != str[arrayOfDelimitr[nextPoint]+j]){
            flag =1;
        }
    }
    return flag;
}

int icompare (int thisPoint, int nextPoint) {   // not case sensitive
    int flag=0,j;
    for (j = 0; j<=5; j++) {
        if( (str[arrayOfDelimitr[thisPoint]+j] | 32) != (str[arrayOfDelimitr[nextPoint]+j] | 32)) {
            flag =1;
        }
    }
    return flag;
}

/*Get the positions of the delimiter '\n' or EOF.
 * Returns the Number of lines in the file*/
int parseFile () {
    arrayOfDelimitr[0]=0;
    int i, j =1;
    for (i = 0;i <= strlen(str) ;i++) {
        if (str[i] == str[strlen(str)]) {
            count++;
            arrayOfDelimitr[j]=i+1;
            j++;
        }
        if (str[i]=='\n') {
            count++;
            arrayOfDelimitr[j]=i+1;
            j++;
        }
    }
    return count;
}
/*This is where the Magic! happens*/
void uniq(int fd) {
    str = readFile(fd);
    count = parseFile();
    int i, occurence, j;
    for (i=1; i<=count;i=i+occurence) {
        occurence = 1;
        if (flagd==1) {
            /*finding the duplicates */
            for (j = i; j <= count; j++) {
                if (flagi == 1) {
                    //Case-sensitive
                    if (icompare(i - 1, j) == 0) {
                        occurence++;
                    } else {
                        if (occurence>1) {
                            display(arrayOfDelimitr[i - 1], occurence);
                        }
                        break;
                    }
                } else {
                    //Not case-sensitive
                    if (compare(i - 1, j) == 0) {
                        occurence++;
                    } else {
                        if (occurence>1) {
                            display(arrayOfDelimitr[i - 1], occurence);
                        }
                        break;
                    }
                }
            }
        }
        /*Regular use case to print the unique*/
        else {
            for (j = i; j <= count; j++) {
                if (flagi == 1) {
                    //Case-sensitive
                    if (icompare(i - 1, j) == 0) {
                        occurence++;
                    } else {
                        display(arrayOfDelimitr[i - 1], occurence);
                        break;
                    }
                } else {
                    //Not case-sensitive
                    if (compare(i - 1, j) == 0) {
                        occurence++;
                    } else {
                        display(arrayOfDelimitr[i - 1], occurence);
                        break;
                    }
                }
            }
        }
    }
}

/*command usage*/
void usage() {
   printf(1,"uniq [-c count,prefix lines by number of occurrences] [-d repeated,  only duplicate lines] [-i ignore-case, ignore case when comparin ]... [INPUT [OUTPUT]]\n");
}

int
main(int argc, char *argv[]) {
    int fd, i;
    if(argc <= 1){
        uniq(0);
        exit();
    }
    for(i = 1; i < argc; i++) {
        if (strcmp(argv[i],"-c")==0) {
            flagc=1;
        } else if (strcmp(argv[i],"-i")==0) {
            flagi=1;
        } else if (strcmp(argv[i],"-d")==0) {
            flagd=1;
        }
        /*-c and -d are mutually exclusive*/
        if ((flagc==1 ) && (flagd==1)) {
            printf(2,"Error uniq: arguments -c and -d cant be used together\n");
            usage();
            exit();
        }
    }
    if((fd = open(argv[i-1], 0)) < 0){
        printf(1, "uniq: cannot open %s\n", argv[i]);
        usage();
        exit();
    }
    uniq(fd);
    close(fd);
    free(str);  // free memory !!
    exit();
}
