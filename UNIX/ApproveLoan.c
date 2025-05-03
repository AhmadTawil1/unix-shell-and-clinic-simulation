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
	int fd, pid, status, rbytes, wbytes;
	char path[50] = "Loan/Result/Approved/", stat[8], pass[5], buff[1024];
	char* str = "Status:Approved           ", * token, * user_id, * user_pass;
	//Check if the correct number of arguments
	if (argc != 3)
	{
		printf("Wrong number of parameters\n");
		exit(1);
	}

	//Create the path to the file
	strcat(path, argv[1]);
	strcat(path, ".txt");

	if ((fd = open(path, O_RDWR)) == -1)
	{
		printf("No approve request!\n");
		exit(1);
	}

	pid = fork();

	if (pid == 0)
	{
		execlp("./ShowReqDetails", "ShowReqDetails", argv[1], NULL);
		perror("execlp");
		exit(1);
	}

	pid = wait(&status);

	printf("Plz type Approve: ");
	scanf("%s", stat);


	while (1)
	{
		printf("Password:");
		scanf("%s", pass);
		if (strcmp(argv[2], pass) == 0)
		{
			break;
		}
		printf("Wrong Password!!!\n");
	}

	//Read the content of the file
	if ((rbytes = read(fd, buff, sizeof(buff))) == -1)
	{
		perror("Read1");
		exit(1);
	}
	buff[rbytes] = '\0';
	
	//find the line starting with "Rating"
	token = strtok(buff, "\n");
	while (token != NULL)
	{
		if ((strncmp(token, "Rating", 6)) == 0)
		{
			break;
		}
		token = strtok(NULL, "\n");
	}

	// Move the file pointer to the brginning of the line to be replaced
	token = strtok(NULL, "\n");
	lseek(fd, 0, SEEK_END);
	lseek(fd, -(strlen(token)) - 1, SEEK_END);
	if ((wbytes = write(fd, str, strlen(str))) == -1)
	{
		perror("write1");
		exit(1);
	}

	printf("Good Luck!!");
	close(fd);
	return 0;
}