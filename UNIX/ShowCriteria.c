#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
	int fd,rbytes;
	char buff[10];
	
	if((fd=open("Criteria.txt",O_RDONLY)) == -1)
	{
		perror("Cant open file");
		exit(1);
	}
	
	if((rbytes=read(fd,buff,sizeof(buff))) == -1)
	{
		perror("Read1");
		exit(1);
	}
	
	printf("Min Rating %s",buff);
	close(fd);
	return 0;
	
}