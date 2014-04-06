#include <stdio.h>
#include <string.h>

#include "file_io.h"
#include "prediction.h"
#include "encoder.h"

void cmd_handler(char *cmd, char *arg);

char data_buf[256] = {0};

int main(void)
{    
	char cmd[8] = {0};
	char arg[32] = {0};

	while(1)
	{
		printf("> ");
		scanf ("%s %s",&cmd[0],&arg[0]);
		cmd_handler(&cmd[0],&arg[0]);			
	}
	
	return 0;
}

void cmd_handler(char *cmd, char *arg)
{
	if(strncmp("load",&cmd[0],strlen(cmd))==0)
	{
		file_read(&arg[0], &data_buf[0]);
		printf("File '%s' loaded successfully",&arg[0]);
	}	
	else if(strncmp("encode",&cmd[0],strlen(cmd))==0)
	{
		get_error(&data_buf[0]);
	}
	else if(strncmp("decode",&cmd[0],strlen(cmd))==0)
	{	
		
	}
	else if(strncmp("save",&cmd[0],strlen(cmd))==0)
	{
		
	}
	else if(strncmp("help",&cmd[0],strlen(cmd))==0)
	{
		// TODO : list of commands and arguments
		printf(">load -filename\n");
		printf(">encode -sizeofblock\n"); 
		printf(">decode\n");
		printf(">save -filename\n");
	}
	else
	{
		printf("Enter 'help me' for commands\n");
	}
}

