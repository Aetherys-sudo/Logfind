#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include <string.h>
#include <ctype.h>

#define MAX_BUFFER 1024
#define MAX_WORD 50
#define LETTER(A) (A >= 'a' && A <= 'z') || (A >= 'A' && A <= 'Z')


//function that deals with file handling
FILE *file_open(const char *name, const char *mode)
{
	FILE *file;
	file = fopen(name, mode);
	check(file != NULL, "Could not open file.");
	
	return file;
error:
	fclose(file);
	return NULL;
}
	
//function that checks if the word passed as argument is in the file or not
int read(FILE *input, char words[][MAX_WORD], int w_count, const char *f_name)
{
	char buff[MAX_WORD];
	int i, j;
	int count = 0;
	char line[MAX_BUFFER];
	
	/*while(!feof(input))
	{
		memset(buff, 0, sizeof(buff));
		ch = fgetc(input);
		for (i = 0; LETTER(ch); i ++)
		{
			buff[i] = ch;
			ch = fgetc(input);
		}
		buff[i] = '\0';
			
	}*/
	
	while (fgets(line, MAX_BUFFER, input) != NULL)
	{
		for (i = 0; line[i] != '\0'; i ++)
		{
			for (j = 0; LETTER(line[i]); j ++)
			{
				buff[j] = line[i];
				i ++;
			}
			buff[j] = '\0';
			
			
			if (buff[0] != 0)
			{
				
				for (j = 0; j < w_count; j ++)
				{
					if (strcmp(buff, words[j]) == 0)
					{
						count ++;
						fprintf("Line: %s\n", line);
					}
				}
			}
			
			if (!LETTER(line[i]))
			{
				memset(buff, 0, sizeof(buff));
			}
			
		}
	}
	
	
	
	return 0;
}
	
int main(int argc, char *argv[])
{
	FILE *file = NULL;
	file = file_open(argv[1], "r");
	if (file)
		printf("File %s opened successfully.\n", argv[1]);
	
	char words[argc - 2][MAX_WORD];
	int i;
	for (i = 0; i < argc - 2; i ++)
	{
		strcpy(words[i], argv[i + 2]);
	}
	//check(argc == 3, "You need to specify word to search.");
	read(file, words, argc - 2, argv[1]);
	
	

	fclose(file);
	return 0;
	
/*error:
	if (file) fclose(file);
	return -1;*/
	
}
