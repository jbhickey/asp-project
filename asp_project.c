#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "file_io.h"

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
	static bool loaded = 0;
	static bool decoded = 0;
	static bool encoded = 0;

	if(strncmp("load",&cmd[0],strlen(cmd))==0)
	{
		file_read(&arg[0], &data_buf[0]);
		loaded = 1;
		printf("File '%s' loaded successfully",&arg[0]);
	}	
	else if(strncmp("encode",&cmd[0],strlen(cmd))==0)
	{
		if(loaded)
		{
			printf("Loaded file encoded successfully\n");
		}
	}
	else if(strncmp("decode",&cmd[0],strlen(cmd))==0)
	{	
		if(loaded)
		{
			printf("Loaded file encoded successfully\n");
		}
	}
	else if(strncmp("save",&cmd[0],strlen(cmd))==0)
	{
		if(decoded || encoded)
		{
			printf("Decoded file saved successfully as %s\n",&arg[0]);
		}
	}
	else if(strncmp("help",&cmd[0],strlen(cmd))==0)
	{
		// TODO : list of commands and arguments
		printf("encode\n");
		printf("eg. >encode -size -samples \n"); 
	}
	else
	{
		printf("Enter 'help' for instructions\n");
	}
}

