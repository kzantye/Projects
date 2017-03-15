#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
#include<limits.h>


char *line=NULL;
pid_t pid;
pid_t current_pid;
int cmd_count;
int status;
int exit_status=0;
char *word[20];
char *commands[20][20];
pid_t pidArray[20];
int pidCount=0;
char *pidName[20];



typedef void Sigfunc(int);

/* This function  installs a signal handler for 'signo' signal */
Sigfunc *install_signal_handler(int signo, Sigfunc *handler)
{
	struct sigaction act, oact;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if( sigaction(signo, &act, &oact) < 0 )
		return (SIG_ERR);
	return(oact.sa_handler);
}



/* SIGINT handler */
void int_handler(int signalValue)
{
	signal(signalValue, SIG_IGN);
	kill(current_pid, SIGKILL);
	install_signal_handler(SIGINT, int_handler);
	printf("\n");
}

void tstp_handler(int signalValue)
{
	signal(signalValue, SIG_DFL);

	kill(current_pid,SIGSTOP);
	printf("\n");
	install_signal_handler(SIGTSTP, tstp_handler);

}
void cont_handler(int signalValue)
{

	signal(signalValue, SIG_IGN);
	kill(current_pid,SIGCONT);
	printf("\n");
    install_signal_handler(SIGCONT, cont_handler);
}

int getProcessIdFromJob(int jobIdIn){

	int jobId=jobIdIn-1;
	if(jobIdIn <=pidCount )
		printf("%s",pidName[jobId]);
	else
		exit(1);
	return pidArray[jobId];
}

void bringForeground(int jobId){
		printf("Job id in foreground:%d\n",jobId);
		int processId=0;
		processId = getProcessIdFromJob(jobId);
		if(kill(processId, SIGCONT) < 0)
			printf("-bash: fg: %d: no such job.\n",processId);
}

void kill_all(){
	int i=0;
	for(i=0;i<pidCount;i++)
	{	
		kill(pidArray[i], SIGKILL);

	}
}

void insertIntoJobList(int pid){

	pidArray[pidCount]=pid;
	pidName[pidCount]=commands[0][0];
	pidCount++;

}

void removeFromJobList(int pid){
	int z=0,c;	
	//Identify index in pidCount to remove after termination
	for(z=0;z<pidCount;z++)
	{
		if(pid==pidArray[z])
		break;
	}

	//Remove process id from pidArray after termination
	for ( c = z - 1 ; c < pidCount ; c++ )
         pidArray[c] = pidArray[c+1];
	pidCount--;
}


void showJobs(){
	int z=0;

		printf("Job\t");
		printf("Process id\t");
		printf("Process Name\n");
	
	for(z=0;z<pidCount;z++)
	{

		printf("%d\t",z+1);
		printf("%d\t\t",pidArray[z]);
		printf("%s\n",pidName[z]);


	}
}	


int change_dir()
{
	char *dir_name;
	char *buffer=0;
	if (strcmp(commands[0][0],"cd")==0 && commands[0][1] !=NULL)
	{
		if(chdir(commands[0][1])==0)
		{	

			dir_name=getcwd(buffer,PATH_MAX);

			if (dir_name!=NULL)
			{
				printf("Directory changed to: %s\n",dir_name);
			}
		}
		else
		{
			perror(commands[0][1]);
		}
		
		return 1;
	}
	return 0;
}


void parseCmd(char * line)
{
	int i=0,j=0,k=0;
	char *token;
	//token = strtok(line," \n");
	for (i = 0; i < 20; ++i)
	{
		for (j = 0; j < 20; ++j)
		{
			commands[i][j]=NULL;
		}
	}
	token = strtok(line," \n");
	k=0;
	i=0;
	while(i<=cmd_count)
	{
			j=0;
			while (token!=NULL)
			{	
				
				word[i] = malloc(strlen(token) + 1);
				if (strcmp(token,"|")==0)
				{
					token = strtok(NULL," \n");
					break;
				}
				else if (strcmp(token,"<")==0)
				{
					token = strtok(NULL," \n");
					strcpy(word[k++],token);
					token = strtok(NULL," \n");
					token = strtok(NULL," \n");
					break;
				}
				else if (strcmp(token,">")==0)
				{
					token = strtok(NULL," \n");
					strcpy(word[k++],token);
					token = strtok(NULL," \n");
					token = strtok(NULL," \n");
					break;
				}
				else if (strcmp(token,"&")==0)
				{
					token = strtok(NULL," \n");
					
					break;
				}
				
				
				commands[i][j++] = token;
				token = strtok(NULL," \n");
			}
			i++;
	}
	
}

void processBG(int background)
{
		 
	insertIntoJobList(pid);
	current_pid=pid;

	//printf("Parent Process:%d \n",getpid());
	//printf("Child created:%d \n",pid);		
	if(background ==0)
	{
		pid=wait(&status);
		removeFromJobList(pid);

	}
	else
	{
		printf("[%d] %d \n",pidCount,pid);		
	}
}

int check_InOut(int opr)
{

	char *file[20],*token;
	int outfd,infd,i;
	if (opr==1)
	{
		i=0;
		token = strtok(line,">");
		while (token!=NULL)
		{	
				file[i] = malloc(strlen(token) + 1);
				strcpy(file[i],token);
				token = strtok(NULL,"> &\n");
				i++;
		}
		
		parseCmd(file[0]);

		if ((outfd = open(file[1], O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
			perror(file[1]);	/* open failed */
			//exit(1);
		}
		return outfd;
	}
	else
	{
		i=0;
		token = strtok(line,"<");
		while (token!=NULL)
		{	
				file[i] = malloc(strlen(token) + 1);
				strcpy(file[i],token);
				token = strtok(NULL,"< &\n");
					i++;
		}
		
		parseCmd(file[0]);


		if((infd = open(file[1], O_RDONLY))<0)
		{
			perror(file[1]);
		}
		return infd;
	}
}


void file_Out(int background)
{

	int writefd;
	writefd=check_InOut(1);
	pid=fork();
	if (pid==-1)
	{
			printf("Fork Error\n");
			//exit(1);
	}
	if (pid==0)
	{
			dup2(writefd,1);
			//close(0);
			close(writefd);
			execvp(commands[0][0],commands[0]);
			perror("-bash: Command not found");
	}
	else if (pid>0)
	{
				//printf("Parent process\n");
				//wait(&status);
				//exit(0);
				processBG(background);
	}
}

void file_IN(int background)
{
	
	int readfd=check_InOut(0);
	pid=fork();

	if (pid==-1)
	{
			printf("Fork Error\n");
			//exit(1);
	}
	if (pid==0)
	{
			dup2(readfd,STDIN_FILENO);
			close(readfd);
			execvp(commands[0][0],commands[0]);
			perror("-bash: Command not found");
	}
	else if (pid>0)
	{
				//printf("Parent process\n");
				//wait(&status);
				//exit(0);
				processBG(background);
	}
}

void pipe_process(int p, int background)
{

	int i,j,k,pfd[20][2];
	parseCmd(line);
	for (i = 0; i <=cmd_count-1; ++i)
	{
		pipe(pfd[i]);
	}

	for (i = 0; i <= cmd_count; ++i)
	{
		pid=fork();
		if (pid==-1)
		{
			printf("Fork Error\n");
			//exit(1);
		}
		if (pid==0)
		{
			if (i==0) 
			{
				if (p==1)
				{
					int readfd;

					if((readfd = open(word[0], O_RDONLY))<0)
					{
						perror(word[0]);
					}
					dup2(readfd,STDIN_FILENO);
					close(readfd);

				}
				dup2(pfd[i][1],1);
				j=0;
				while(j<=cmd_count-1)
				{
					close(pfd[j][0]);
					close(pfd[j][1]);
					j++;
				}
				execvp(commands[i][0],commands[i]);
				perror("-bash: Command not found");
			}
			else if(i>0 && i<cmd_count) 
			{	
				dup2(pfd[i-1][0],0);
				dup2(pfd[i][1],1);
				j=0;
				while(j<=cmd_count-1)
				{
					close(pfd[j][0]);
					close(pfd[j][1]);
					j++;
				}
				execvp(commands[i][0],commands[i]);
				perror("-bash: Command not found");

			}
			else
			{
				int newfd;
				if (p==1)
				{
					if ((newfd = open(word[1], O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
						perror(word[1]);	/* open failed */
		//exit(1);
					}
					dup2(newfd,1);
			//close(0);
					close(newfd);
			//execvp(commands[0][0],commands[0]);
				}
				dup2(pfd[i-1][0],0);
				j=0;
				while(j<=cmd_count-1)
				{
					close(pfd[j][0]);
					close(pfd[j][1]);
					j++;
				}
				execvp(commands[i][0],commands[i]);
				perror("-bash: Command not found");
			}

			
		}
		
	}
	for (i = 0;i <= cmd_count-1; i++)
	{
		close(pfd[i][0]);
		close(pfd[i][1]);
	}
	for (i = 0;i <= cmd_count; i++)
	{
		
		processBG(background);
	}
}

void single_Command(int background)
{
		int i=0;
		if (line[i]=='e' && line[i+1]=='x' && line[i+2]=='i' && line[i+3]=='t')
		{
			exit_status=0;
			kill_all();
			exit(0);

		}
		parseCmd(line);

		pid=fork();
		if (pid==-1)
		{
			printf("Fork Error\n");
			//exit(1);		
		}
		if (pid==0)
		{
	
			if(strcmp(commands[0][0],"kill") == 0)
			{
				kill(atoi(commands[0][1]), SIGKILL);
			}
			else if(strcmp(commands[0][0],"fg") == 0)
			{
				
				char *word = commands[0][1];  
				memmove(&word[0], &word[0 + 1], strlen(word) - 0);
				bringForeground(atoi(word));
			}
			else if(strcmp(commands[0][0],"jobs") == 0)
			{
				showJobs();
			}
			else
			{

				int k=0;
				k=change_dir();
				if(k!=1)
				{
				execvp(commands[0][0],commands[0]);
				perror("-bash: Command not found");
				}
			}
		}
		else if (pid>0)
		{
			processBG(background);	
		}
}

void process()
{
	int i=0,flag=-1,pipe_flag=0,in_flag=0,out_flag=0,bg_flag=0;
	cmd_count=0;
	char word[20];
	char read_buffer[BUFSIZ];
	FILE *fptr1;
	while(line[i]!='\n')
	{
		if (line[i]=='&')
		{
			//printf("Multiple commands\n");
			//cmd_count++;
			flag=1;
			bg_flag=1;
		}
		else if (line[i]=='|')
		{
			//printf("Pipe commands\n");
			cmd_count++;
			flag=2;
			pipe_flag=1;
		}
		else if (line[i]=='>')
		{
			
			//printf("Output commands\n");
			flag=3;
			out_flag=1;
		}
		else if (line[i]=='<')
		{
			//printf("Input commands\n");
			flag=4;
			in_flag=1;
		}else{
			flag=0;
		}
		
		i++;
	}
	
	 if (pipe_flag==1 && in_flag==1 && out_flag==1)
	{
		pipe_process(1,0);

	}
	else if (bg_flag==1 && out_flag==1)
	{
		file_Out(1);
	}
	else if (bg_flag==1 && in_flag==1)
	{
		file_IN(1);
	}
	else if (bg_flag==1 && pipe_flag==1)
	{
		pipe_process(0,1);
	}
	else if (bg_flag==1 && pipe_flag==1 && in_flag==1 && out_flag==1)
	{
		pipe_process(1,1);
	}
	else
	{
		switch(flag)
		{
			case -1: break;
			case 0:single_Command(0);
					break;
			case 1:single_Command(1);
					break;
			case 2:pipe_process(0,0);
					break;
			case 3:file_Out(0);
					break;
			case 4:file_IN(0);
					break;
			default : break;
		}
	}
	//printf("%d\n",cmd_count );

}

void parseLine()
{
	char stop;
	size_t bufsize=0,i;
	printf("minish>");
	getline(&line,&bufsize, stdin);	
}
int main(int argc, char **argv)
{

    install_signal_handler(SIGINT, int_handler);
    install_signal_handler(SIGTSTP, tstp_handler);
    install_signal_handler(SIGCONT, cont_handler);





	/*printf("\n===============================================================================\n");
	printf("\t\t\tCS550_Assignment 1: Mini shell\n");
	printf("================================================================================\n");*/
	while(1)
	{
		parseLine();
		process();
	}

	return 0;
}

