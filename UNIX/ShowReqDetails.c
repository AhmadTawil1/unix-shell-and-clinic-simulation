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
	int fd, rbytes;
	char* token, buff[1024], path[50] = "Loan/Request/", path2[50] = "Loan/Result/Approved/", path3[50] = "Loan/Result/Unapproved/";

	if (argc != 2)
	{
		printf("Bad number of parameters");
		exit(1);
	}

	//Construct path to the file based on the argument
	strcat(path, argv[1]);
	strcat(path, ".txt");

	//Try open file in Request
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		//try to open a file in Approved
		strcat(path2, argv[1]);
		strcat(path2, ".txt");
		if ((fd = open(path2, O_RDONLY)) == -1)
		{
			//try to open a file in UnApproved
			strcat(path3, argv[1]);
			strcat(path3, ".txt");
			if ((fd = open(path3, O_RDONLY)) == -1)
			{
				perror("Error cant open <id>.txt");
				close(fd);
				exit(1);
			}
		}

	}

	//read the content of the file into buff
	if ((rbytes = read(fd, buff, 1024)) == -1)
	{
		perror("read1");
		exit(1);
	}

	//Tokinize the contents based on newline characters and print each token unless it "Status"
	token = strtok(buff, "\n");
	while (token != NULL)
	{
		if (strncmp(token, "Status", 6) != 0)
		{
			printf("%s\n", token);
		}
		token = strtok(NULL, "\n");
	}

	close(fd);

	return 0;

}