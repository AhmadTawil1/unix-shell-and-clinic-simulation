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

	int fd1, rbytes1, wbytes1, fd2, wbytes2;
	char head[] = "Account Pass\n", id_path[] = "Loan/Request/";
	char buff[64], password[6], name[50], SurName[50], age[5], rating[10], rand_num[3];
	char add_to_user[256] = "", add_to_id[1024] = "";

	//Seed the random number generate
	srand(time(NULL));
	//open user file
	if ((fd1 = open("Loan/User.txt", O_RDWR)) == -1)
	{
		perror("Error opening file User.txt");
		exit(1);
	}
	//read from user file
	if ((rbytes1 = read(fd1, buff, 50)) == -1)
	{
		perror("Read1");
		close(fd1);
		exit(1);
	}

	//if User.txt is empty, write the header
	if (rbytes1 == 0)
	{
		if ((wbytes1 = write(fd1, head, strlen(head))) == -1)
		{
			perror("Write1");
			close(fd1);
			exit(1);
		}
	}

	//construct the path to the user id file
	strcat(id_path, argv[1]);
	strcat(id_path, ".txt");
	if ((fd2 = open(id_path, O_WRONLY)) == -1)
	{
		//if the user doesn't has a request create id file
		if ((fd2 = open(id_path, O_WRONLY | O_CREAT, 0664)) == 1)
		{
			perror("Error open file <id>.txt");
			close(fd1);
			exit(1);
		}
		//get user id and password
		printf("User: %s\n", argv[1]);
		printf("Password: ");
		scanf("%s", password);
		//add the user idd and password to user.txt
		snprintf(add_to_user, sizeof(add_to_user), "%s %s\n", argv[1], password);
		if ((wbytes1 = write(fd1, add_to_user, strlen(add_to_user))) == -1)
		{
			perror("Write2");
			close(fd1);
			exit(1);
		}

		//Get user details
		printf("User Created\nInsert Details:\n");
		printf("Name: ");
		scanf("%s", name);
		printf("SurName: ");
		scanf("%s", SurName);
		printf("Age: ");
		scanf("%s", age);
		//write user details to the user file
		snprintf(add_to_id, sizeof(add_to_id), "Name: %s\nSurName: %s\nAge:%s\nSum:%s\nPayment:%s\nRating: %d/10\nStatus:Waiting!", name, SurName, age, argv[2], argv[3], (rand() % 10) + 1);
		if ((wbytes2 = write(fd2, add_to_id, strlen(add_to_id))) == -1)
		{
			perror("Write2");
			close(fd1);
			exit(1);
		}
		printf("Request Saved!\n");
	}
	else
	{
		printf("Sorry! you have a request.\n");
		exit(1);
	}

	close(fd1);
	close(fd2);
	return 0;

}