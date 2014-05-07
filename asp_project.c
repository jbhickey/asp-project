#include <stdio.h>
#include <stdbool.h>
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
	char error[3][BLOCK_SIZE] = {0};
	char write_buf[BLOCK_SIZE] = {0};
	int file_size = 0;
	int block_cnt = 0;
	static bool file_loaded = 0;

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

		file_size = read_file(&arg[0]);
		
		printf("File '%s' loaded successfully\n",&arg[0]);		
		
		file_loaded = 1;
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
		if(file_loaded)
		{
			for(block_cnt=0;block_cnt<file_size/BLOCK_SIZE;block_cnt++)
			{
				// Nth order avg predictor hence error[n-1]
				avg_predictor(&g_data_buf[block_cnt*BLOCK_SIZE], &error[0]);
				
				// Encode error vector
				encode(&error[0],&write_buf[0]);

				// Write encoded data to file
				write_block(&write_buf[0]);
				
				// Clear write buffer
				memset(&write_block[0], 0x00, strlen(&write_block));
			}
		}
		else
		{
			printf("No file loaded...\n");		
		}
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

