#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include <string.h>
#include <ctype.h>
#include <glob.h>

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
int read(FILE *input, char words[][MAX_WORD], int w_count, const char *f_name, char mode)
{
	char buff[MAX_WORD];
	int i, j;
	int count = 0;
	char line[MAX_BUFFER];
	FILE *temp;
	temp = fopen("temp", "w");
	check(temp != NULL, "Could not create temp file.");
	
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
						fprintf(temp, "%s", line);
					}
				}
			}
			
			if (!LETTER(line[i]))
			{
				memset(buff, 0, sizeof(buff));
			}
			
		}
	}
	
	fclose(temp);
	memset(line, 0, sizeof(line));
	temp = fopen("temp", "r");
	
	if (count >= w_count && mode != 'o')
	{
		while (fgets(line, MAX_BUFFER, temp) != NULL)
			printf("%s\n", line);
	}
	
	if (mode == 'o')
	{
		while (fgets(line, MAX_BUFFER, temp) != NULL)
			printf("%s\n", line);
	}
	
	fclose(temp);
	int c = remove("temp");
	check(c == 0, "Could not remove temp file.");
	
	return 0;
	
error:
	fclose(input);
	fclose(temp);
	return -1;
}
	
int main(int argc, char *argv[])
{
	FILE *file = NULL;
	file = file_open(argv[1], "r");
	if (file)
		printf("File %s opened successfully.\n", argv[1]);
		
	
	char words[argc - 2][MAX_WORD];
	int i;
	char mode;
	for (i = 0; i < argc - 2; i ++)
	{
		if (argv[i + 2][0] == '-')
			mode = argv[i + 2][1];
		else
			strcpy(words[i], argv[i + 2]);
	}
	
	read(file, words, argc - 2, argv[1], mode);
	
	

	fclose(file);
	return 0;	
}
