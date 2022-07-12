#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int fp, fq, i, key;
    ssize_t bytesRead, bytesWritten;                      /*bytes returned*/
    char buffer[BUF_SIZE];                                /*character buffer*/


    /*persmission set*/
    mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR ;

    /*opening the file in readonly mode*/
    fp = open (argv[1], O_RDONLY);
    if (fp == -1){
        perror("cant open source file.");
        return 1;
    }

    /*opening the file with write mode*/
    /*this creates the destination file*/
    fq = open (argv[2], O_WRONLY | O_EXCL | O_CREAT, mode);
    if (fq == -1){
        perror("cant open with write mode.");
        return 2;
    }

    /*key for encryption*/
    key = atoi(argv[3]);


    while ((bytesRead = read (fp, &buffer, BUF_SIZE)) >0){                      
        for(i=0; i<bytesRead; i++){                                                         /*reading the file till the end*/
            buffer[i] = buffer[i] - key;                                                    /*changing its ASCII values*/
            printf("%c", buffer[i]);                                                        /*printing the characters out*/
        }
        bytesWritten = write(fq, &buffer, (ssize_t) bytesRead);                             /*writing in the destination file*/
    }
    close(fp);
    close(fq);
    return 0;
}
