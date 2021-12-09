#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

char* toUpper(char input[]) {
    char* start = input;
    int i;
    for (i = 0; i < strlen(input); i++) {
        if (input[i] >= 'a' && input[i] <= 'z')
            input[i] -= 32;
    }
    return start;
}

int main() {
    int fds[2];
    int fds2[2];
    pipe( fds );
    pipe( fds2 );
    int f;
    int childpid, status;

    /*test toUpper function
    fgets(line, 100, stdin);
    toUpper(line);
    printf("%s", toUpper(line)); */
    
   
    f = fork();

    
    if (f != 0) {
        while (1) {
            char line[2048];
            close( fds[READ] );
            printf("Input: ");
            fgets(line, 2048, stdin);
            write( fds[WRITE], line, sizeof(line));
            //childpid = wait(&status);

            close( fds2[WRITE] );
            read( fds2[READ], line, sizeof(line) );
            printf("\nProcessed input: %s\n", line);
        }
    }
    if (f == 0) {
        while (1) {
            char line[2048];
            close( fds[WRITE] );
            read( fds[READ], line, sizeof(line) );
            toUpper(line);
            
            close( fds2[READ] );
            write( fds2[WRITE], line, sizeof(line));
        } 
    }
    
    
}
