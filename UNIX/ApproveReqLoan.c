#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char* argv[])
{
	int fd, wbytes, rbytes;
	int offset = -1;
	char path[50] = "Loan/Request/", path2[50] = "Loan/Result/Approved/", command[1024];
	char buff[1024];
	char* token;
	char* str = "Awaiting signature";


	if (argc != 2)
	{
		printf("bad number of parameters");
		exit(1);
	}

	//Construct the path to the request file
	strcat(path, argv[1]);
	strcat(path, ".txt");
	if ((fd = open(path, O_RDWR)) == -1)
	{
		printf("Request Not Found!\n");
		exit(1);
	}

	if ((rbytes = read(fd, buff, sizeof(buff))) == -1)
	{
		perror("Read1");
		exit(1);
	}
	buff[rbytes] = '\0';

	//find the line starting with "Status"
	token = strtok(buff, ":\n");
	while (token != NULL)
	{

		if ((strcmp(token, "Status")) == 0)
		{
			break;
		}
		token = strtok(NULL, ":\n");
	}

	//Get the current status
	token = strtok(NULL, ":\n");

	//move the file pointer to the beginning of the Status to be replaced
	lseek(fd, 0, SEEK_END);
	lseek(fd, -(strlen(token)) - 1, SEEK_END);
	if ((wbytes = write(fd, str, strlen(str))) == -1)
	{
		perror("write1");
		exit(1);
	}

	strcat(path2, argv[1]);
	strcat(path2, ".txt");

	close(fd);
	printf("Request Approved\n");
	//Move the request file to the Approved directory
	execlp("mv", "mv", path, path2, NULL);
	perror("exec");
	exit(1);
}