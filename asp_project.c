#include <stdio.h>
#include <string.h>

#include "file_io.h"
#include "prediction.h"
#include "encoder.h"

void cmd_handler(char *cmd);

char *g_data_buf;

int main(void)
{    
	char cmd[32] = {0};

	while(1)
	{
		printf("\nEnter 'help' for commands\n");
		printf("> ");
		scanf ("%s",&cmd[0]);
		cmd_handler(&cmd[0]);			
	}
	
	return 0;
}

void cmd_handler(char *cmd)
{
	char arg[32] = {0};
	int block_cnt = 0;

	if(strncmp("debug",&cmd[0],5)==0)
	{
		printf("Enter filename\n> ");
		scanf("%s",&arg[0]);
		debug_file(&arg[0]);
	}
	else if(strncmp("load",&cmd[0],4)==0)
	{
		printf("Enter filename\n> ");
		scanf("%s",&arg[0]);

		read_file(&arg[0]);
		
		printf("File '%s' loaded successfully\n",&arg[0]);		
	}	
	else if(strncmp("write",&cmd[0],5)==0)
	{
		printf("Preparing to write test blocks\n");
		
		for(block_cnt=0;block_cnt<4;block_cnt++)
			write_block(&g_data_buf[block_cnt*BLOCK_SIZE]);
		
		printf("Test blocks written\n"); 
	}
	else if(strncmp("encode",&cmd[0],6)==0)
	{
		get_error(&data_buf[0]);
	}
	else if(strncmp("decode",&cmd[0],6)==0)
	{	
		
	}
	else if(strncmp("save",&cmd[0],4)==0)
	{
		
	}
	else if(strncmp("help",&cmd[0],4)==0)
	{
		printf("\n");
		printf("> debug\n");
		printf("> load\n");
		printf("> encode\n"); 
		printf("> decode\n");
		printf("> save\n");
		printf("\n");
	}
}

