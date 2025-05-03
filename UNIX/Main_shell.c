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
	char command[256], * args[5], * token;
	int i = 0, pid, status, p = 1;
	while (p == 1)
	{
		i = 0;
		printf("MainShell> ");
		fgets(command, sizeof(command), stdin);

		// Remove newline character from the command
		command[strcspn(command, "\n")] = 0;
		token = strtok(command, " ");
		//Tokenize the command into arguments
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		pid = fork();
		if (pid == 0)
		{

			if ((strcmp(args[0], "GetLoan")) == 0)
			{
				if (execvp("./GetLoan", args) == -1)
				{
					perror("failed to execute1");
					exit(1);
				}
			}

			else if ((strcmp(args[0], "CheckStatus")) == 0)
			{
				if (execvp("./CheckStatus", args) == -1)
				{
					perror("failed to execute2");
					exit(1);
				}
			}
			else if ((strcmp(args[0], "ApproveLoan")) == 0)
			{
				if (execvp("./ApproveLoan", args) == -1)
				{
					perror("failed to execute3");
					exit(1);
				}
			}
			else if ((strcmp(args[0], "LoginM")) == 0)
			{
				if (execvp("./LoginM", args) == -1)
				{
					perror("failed to execute4");
					exit(1);
				}
			}
			else
			{
				if ((strcmp(args[0], "exit")) != 0)
					printf("Not Supported\n");
				return 0;
			}


		}
		else
		{
			pid = wait(&status);
			if ((strcmp(args[0], "exit")) == 0)
			{
				if (execvp("./exit", args) == -1)
				{
					perror("failed to execute5");
					exit(1);
				}
				p = 0;
			}

		}

	}
	return 0;
}