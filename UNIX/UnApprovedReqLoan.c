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
	char path[50] = "Loan/Request/", path2[50] = "Loan/Result/Unapproved/";
	char buff[1024];
	char* token;
	char* str = "UnApproved";


	if (argc != 2)
	{
		printf("bad number of parameters");
		exit(1);
	}

	//Construct path 
	strcat(path, argv[1]);
	strcat(path, ".txt");
	if ((fd = open(path, O_RDWR)) == -1)
	{
		perror("Request Not Found!");
		exit(1);
	}

	if ((rbytes = read(fd, buff, sizeof(buff))) == -1)
	{
		perror("Read1");
		exit(1);
	}
	buff[rbytes] = '\0';

	//Tokenize the contents based on ":" and newline characters to find the status and its value
	token = strtok(buff, ":\n");
	while (token != NULL)
	{

		if ((strcmp(token, "Status")) == 0)
		{
			break;
		}
		token = strtok(NULL, ":\n");
	}

	token = strtok(NULL, ":\n");

	lseek(fd, 0, SEEK_END);
	lseek(fd, -(strlen(token)) - 1, SEEK_END);
	if ((wbytes = write(fd, str, strlen(str))) == -1)
	{
		perror("write1");
		exit(1);
	}

	strcat(path2, argv[1]);
	strcat(path2, ".txt");


	printf("Request UnApproved\n");
	close(fd);
	execlp("mv", "mv", path, path2, NULL);
	perror("exec");
	exit(1);

}