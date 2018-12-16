/*
 ============================================================================
 Name        : 2017-10-18-linux-fork.c
 Author      : Paolo Torroni
 Version     :
 Copyright   : Use as you wish
 Description : Template for the first programming exercise (fork, wait, and exec) proposed on 2017-01-08
 	 Using the system calls seen today, write a C program myshell that:
	 - reads from standard input a command (for simplicity, a single string, no arguments);
	 - if the input command is "halt", exit 0, indicating success;
	 - otherwise, see to it that the command is executed;
	 - upon completion, output the PID and return value of the process that has executed the command;
	 - if a command returns a non-zero value, exit 1 (indicating an error condition);
	 - if a command returns 0, read the next command (forever).
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for exec
#include <sys/types.h> // for wait
#include <sys/wait.h> // for wait

#define FOREVER for(;;)
pid_t child_pid;
int wstatus;

int main(void) {
	char command[250];

	FOREVER {
		printf("please type your command ... ");
		scanf("%s", command);
		if(!strcmp(command,"halt")) {
			puts("So long");
			return EXIT_SUCCESS; // same as exit(0)
		}

		child_pid = fork();

		if(child_pid==0) {
			char path[250] = "/bin/";
			strcat(path, command);
			execl(path, command, NULL);
		}
		else if(child_pid>0) {
			wait(NULL);
			printf("PID: %d \n", child_pid);
		}
		
		/*else{
			system(command);
		}*/
	}
	return EXIT_SUCCESS;
}
