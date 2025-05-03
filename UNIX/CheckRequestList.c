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

int main()
{

	char* dirname = "Loan/Request";
	//Count the number of files in Loan/Request
	execlp("sh", "sh", "-c", "ls -l Loan/Request | grep \"^-\" | wc -l", NULL);
	perror("Error counting files");


	return 1;
}