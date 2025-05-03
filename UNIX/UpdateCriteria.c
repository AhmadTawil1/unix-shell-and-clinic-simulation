#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
	int fd,wbytes,random_number;
	char buff[10];
	if(argc != 2)
	{
		printf("Wrong parameters!\n");
		exit(1);
	}
	
	srand(time(NULL));
	random_number = atoi(argv[1]) + rand() % (10 - atoi(argv[1]) + 1);
	if((fd = open("Criteria.txt", O_WRONLY)) == -1)
	{
		perror("Cant open file");
		exit(1);
	}
	
	lseek(fd,0,SEEK_SET);
	sprintf(buff,"%d",random_number);
	
	buff[strlen(buff)] = '\0';
	if((wbytes = write(fd,buff,strlen(buff))) == -1)
	{
		perror("Error writing");
		close(fd);
		exit(1);
	}
	strcpy(buff,"\n");
	if((wbytes = write(fd,buff,strlen(buff))) == -1)
	{
		perror("Error writing");
		close(fd);
		exit(1);
	}
	lseek(fd,0,SEEK_SET);
	close(fd);
	return 0;
}