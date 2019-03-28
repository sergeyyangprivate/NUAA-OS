#include "mysys.h"

static int command_size = 10;

void split(char *command, int *argc, char **argv){
	int count = 0;
	if(command == NULL || strlen(command) == 0)
		return;
	char *pNext = strtok(command, " ");
	while(pNext != NULL){
		*argv++ = pNext;
		++count;
		pNext = strtok(NULL, " ");
	}
	*argv = NULL;
	*argc = count;
}

void mysys(char *com){
	int error = -1;
	char *command = malloc(sizeof(char)*strlen(com));
	strcpy(command, com);
	int wordc = 0;
	char *wordv[command_size];
	split(command, &wordc, wordv);
	if(wordv[2] && (strcmp(wordv[2], ">") == 0)){
		int fd = open(wordv[3], O_CREAT|O_RDWR, 0666);
		dup2(fd, 1);
		close(fd);
		write(1, wordv[1], 6);
		error = 0;
	}
	else{
		error = execvp(wordv[0], wordv);
	}

	//int i;
	//for(i=0; i<command_size; i++){
	//	printf("%d ", i);
	//	puts(wordv[i]);
	//}
	
	if(error < 0)
		perror("execvp");
	exit(0);
}
