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
	int fd,rbytes, counter=0;
	char buff[100];
	
	if((fd = open("Loan/User.txt", O_RDONLY)) == -1)
	{
		perror("Cant open file User.txt");
		exit(1);
	}
	//Read the head of the file
	if((rbytes = read(fd,buff, 13)) == -1)
	{
		perror("Read1 Error");
		close(fd);
		exit(1);
	}
	
	while((rbytes = read(fd,buff, 15)) > 0)
	{
		counter++;
	}
	
	printf("%d\n",counter);
	close(fd)
	return 0;
}