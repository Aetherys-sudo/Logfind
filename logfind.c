#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include <string.h>
#include <ctype.h>
#include <glob.h>

#define MAX_BUFFER 1024
#define MAX_WORD 50
#define LETTER(A) (A >= 'a' && A <= 'z') || (A >= 'A' && A <= 'Z')

	
//function that checks if the word passed as argument is in the file or not
int read(FILE *input, char words[][MAX_WORD], int w_count, char mode, const char *f_name)
{
	char buff[MAX_WORD];
	int i, j;
	int count = 0;
	char line[MAX_BUFFER];
	FILE *temp;
	temp = fopen("temp", "w");
	check(temp != NULL, "Could not create temp file.");
	int l_count = 0;
	
	while (fgets(line, MAX_BUFFER, input) != NULL)
	{
		l_count ++;
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
			printf("LINE [%s: %d] %s", f_name, l_count, line);
	}
	
	if (mode == 'o')
	{
		while (fgets(line, MAX_BUFFER, temp) != NULL)
			printf("LINE [%s: %d] %s", f_name, l_count, line);
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
	//argument parsing
	if (argc == 1)
	{
		printf("Specify arguments");
		return 1;
	}
		
	char words[argc - 1][MAX_WORD];
	int i;
	char mode;
	for (i = 0; i < argc - 1; i ++)
	{
		if (argv[i + 1][0] == '-')
			mode = argv[i + 1][1];
		else
			strcpy(words[i], argv[i + 1]);
	}
	
	//file handling
	glob_t paths;
	paths.gl_pathc = 0;
	paths.gl_pathv = NULL;
	paths.gl_offs = 0;
	glob("~/.logfind/*", GLOB_NOSORT | GLOB_TILDE , NULL, &paths);
	
	
	int idx;
	char path[MAX_BUFFER];
	FILE *file = NULL;
	for (idx = 0; idx < paths.gl_pathc; idx ++)
	{
		strcpy(path, paths.gl_pathv[idx]);
		file = fopen(path, "r");
		read(file, words, argc - 1, mode, path);
		fclose(file);
	}
	
		
	return 0;	

}
