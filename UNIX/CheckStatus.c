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
	int fd, rbytes, fd2, rbytes2, offset = -1;
	char buff[100], buff2[100];
	char path[100] = "Loan/Request/", path2[100] = "Loan/Result/Approved/", path3[100] = "Loan/Result/Unapproved/";
	char* token, * user_id, * user_pass;
	if (argc != 3)
	{
		printf("Bad number of parameters");
		exit(1);
	}

	if ((fd = open("Loan/User.txt", O_RDONLY)) == -1)
	{
		perror("Error cant open User.txt");
		exit(1);
	}

	//Read the head of the file
	if ((rbytes = read(fd, buff, 13)) == -1)
	{
		perror("Read1 Error");
		close(fd);
		exit(1);
	}

	//read the user id and password 
	while ((rbytes = read(fd, buff, 15)) > 0)
	{

		token = strtok(buff, " \n");
		user_id = token;
		user_pass = strtok(NULL, "\n");
		//Check if the provided user id and password match
		if ((strncmp(user_id, argv[1], strlen(argv[1]))) == 0)
		{

			if ((strncmp(user_pass, argv[2], strlen(argv[2]))) != 0)
			{
				printf("Wrong Pass!!!\n");
				exit(1);
			}
			else
			{
				//check the request folder
				strcat(path, argv[1]);
				strcat(path, ".txt");
				if ((fd2 = open(path, O_RDONLY)) == -1)
				{
					//check the approved folder
					strcat(path2, argv[1]);
					strcat(path2, ".txt");
					if ((fd2 = open(path2, O_RDONLY)) == -1)
					{
						//check unapproved folder
						strcat(path3, argv[1]);
						strcat(path3, ".txt");
						if ((fd2 = open(path3, O_RDONLY)) == -1)
						{
							perror("Error cant open <id>.txt");
							close(fd);
							exit(1);
						}
					}
				}

				//find the status from the end of the file
				do {
					offset--;
					lseek(fd2, offset, SEEK_END);
					if ((rbytes2 = read(fd2, buff2, sizeof(buff2))) == -1)
					{
						perror("Read2 Error");
						close(fd);
						close(fd2);
						exit(1);
					}
					buff2[rbytes2] = '\0';
				} while (buff2[0] != 'S' || strncmp(buff2, "Status", 6) != 0);

				printf("%s\n", buff2);
				close(fd);
				close(fd2);
				return 0;
			}
		}

	}
	printf("Cant find id");
	return 0;
}