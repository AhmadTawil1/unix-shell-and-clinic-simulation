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

	char *dirname = "Loan/Result/Unapproved";
	
	execlp("sh", "sh", "-c", "ls -l Loan/Result/Unapproved | grep \"^-\" | wc -l", NULL);
	perror("Error counting files");
	
	
	return 1; 
}