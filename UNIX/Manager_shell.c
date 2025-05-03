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
	char command[256],* args[5], *token;
	int i=0,pid,status;
	while(1)
	{
		i=0;
		printf("ManagerShell> ");
		fgets(command,sizeof(command),stdin);
		command[strcspn(command, "\n")] = 0;
		
		token = strtok(command, " ");
		while(token !=NULL)
		{
			args[i++] = token;
			token = strtok(NULL," ");
		}
		args[i]=NULL;
		if (i=0)
		{
			continue;
		}
		
		pid = fork();
		if(pid == 0)
		{
		
			if((strcmp(args[0],"ShowReqNum")) == 0)
			{
				if(execvp("./ShowReqNum",args) == -1)
				{
					perror("failed to execute1");
					exit(1);
				}
			}
		
			else if((strcmp(args[0],"ShowAReqNum")) == 0)
			{
				if(execvp("./ShowAReqNum",args) == -1)
				{
					perror("failed to execute2");
					exit(1);
				}
			}
			else if((strcmp(args[0],"ShowUnAReqNum")) == 0)
			{
				if(execvp("./ShowUnAReqNum",args) == -1)
				{
					perror("failed to execute3");
					exit(1);
				}
			}
			else if((strcmp(args[0],"CheckRequestList")) == 0)
			{
				if(execvp("./CheckRequestList",args) == -1)
				{
					perror("failed to execute4");
					exit(1);
				}
			}
		   	else if((strcmp(args[0],"ShowReqDetails")) == 0)
			{
				if(execvp("./ShowReqDetails",args) == -1)
				{
					perror("failed to execute5");
					exit(1);
				}
			}
		    	else if((strcmp(args[0],"ShowCriteria")) == 0)
			{
				if(execvp("./ShowCriteria",args) == -1)
				{
					perror("failed to execute6");
					exit(1);
				}
			}
		    	else if((strcmp(args[0],"UpdateCriteria")) == 0)
			{
				if(execvp("./UpdateCriteria",args) == -1)
				{
					perror("failed to execute7");
					exit(1);
				}
			}
		    	else if((strcmp(args[0],"ApproveReqLoan")) == 0)
			{
				if(execvp("./ApproveReqLoan",args) == -1)
				{
					perror("failed to execute8");
					exit(1);
				}
			}
		    	else if((strcmp(args[0],"UnApproveReqLoan")) == 0)
			{
				if(execvp("./UnApproveReqLoan",args) == -1)
				{
					perror("failed to execute9");
					exit(1);
				}
			}
			else if((strcmp(args[0],"LogOut")) == 0)
			{
				if(execvp("./LogOut",args) == -1)
				{
					perror("failed to execute10");
					exit(1);
				}
			}
			else
			{
				if((strcmp(args[0],"LogOut")) != 0)
				printf("Not Supported\n");
				return 0;
			}
		}
		else
		{
			pid = wait(&status);
			if((strcmp(args[0],"LogOut")) == 0)
			{
				if(execvp("./LogOut",args) == -1)
				{
					perror("failed to execute10");
					exit(1);
				}
				return 0;
			}
		}
		
	}
}