#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Bad Number of parameters");
        exit(1);
    }
    int pid, status, fd, rbytes;
    char buff[100], * file_account, * file_pass;

    fd = open("Manager_pass.txt", O_RDONLY);
    if (fd == -1) {
        printf("Error opening file");
        return 1;
    }

    //read the file line by line
    while ((rbytes = read(fd, buff, sizeof(buff))) > 0) {
        buff[rbytes] = '\0';  // Null-terminate the string
        file_account = strtok(buff, " ");
        file_pass = strtok(NULL, " \n");
        //Check if the provided account and password match
        while (file_account && file_pass) {
            if (strcmp(argv[1], file_account) == 0 && strcmp(argv[2], file_pass) == 0)
            {
                close(fd);
                pid = fork();
                if (pid == 0)
                {
                    execl("./Manager_shell", "Manager_shell", NULL);
                    perror("Exec");
                    exit(1);
                }
                else
                {
                    pid = wait(&status);
                }
            }
            //move to the next account and password pair
            file_account = strtok(NULL, " ");
            file_pass = strtok(NULL, " \n");
        }
    }
    close(fd);
    return 0;
}