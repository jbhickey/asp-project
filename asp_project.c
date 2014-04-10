#include <stdio.h>
#include <string.h>

#include "file_io.h"
#include "prediction.h"
#include "encoder.h"

void cmd_handler(char *cmd);

char data_buf[256] = {0};


int main(void)
{    
	char cmd[8] = {0};

	while(1)
	{
		printf("Enter 'help' for commands\n");
		printf("> ");
		scanf ("%s",&cmd[0]);
		cmd_handler(&cmd[0]);			
	}
	
	return 0;
}

void cmd_handler(char *cmd)
{
	char arg[32] = {0};

	if(strncmp("debug",&cmd[0],5)
	{
		printf("Enter filename\n> ");
		scanf("%s",&arg[0]);
		debug_file(&arg[0]);
	}
	else if(strncmp("load",&cmd[0],4)
	{
		file_read(&arg[0], &data_buf[0]);
		printf("File '%s' loaded successfully",&arg[0]);
	}	
	else if(strncmp("encode",&cmd[0],6)
	{
		get_error(&data_buf[0]);
	}
	else if(strncmp("decode",&cmd[0],6)
	{	
		
	}
	else if(strncmp("save",&cmd[0],4)
	{
		
	}
	else if(strncmp("help",&cmd[0],strlen(cmd))==0)
	{
		printf("\n");
		printf("> debug\n");
		printf("> load\n");
		printf("> encode\n"); 
		printf("> decode\n");
		printf("> save\n");
		printf("\n");
	}
	else
	{
		printf("Enter 'help' for commands\n");
	}
}

