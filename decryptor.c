#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int fp, fq, i, key;
    ssize_t bytesRead, bytesWritten;                      /*bytes returned*/
    char buffer[BUF_SIZE];                                /*character buffer*/

    mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR ;
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
    /*key for decryption*/
    key = atoi(argv[3]);

    while ((bytesRead = read (fp, &buffer, BUF_SIZE)) >0){              /*reading the file till the end*/                                          
        for(i=0; i<bytesRead; i++){                                     /*changing its ASCII values*/
            buffer[i] = buffer[i] + key;                                /*printing the characters out*/
            printf("%c", buffer[i]);
        }
        bytesWritten = write(fq, &buffer, (ssize_t) bytesRead);         /*writing in the destination file*/
    }
    close(fp);
    close(fq);
    return 0;
}
