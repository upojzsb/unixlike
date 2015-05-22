#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <strings.h>
#include <sys/stat.h>
#include <stdlib.h>

void go_in_dir(const char * dir, const char * file);
int found = 0;//if find file(s) which needed be found

int main(int argc, char ** argv)
{
	DIR * temp;
	
	//usage error
	if(argc != 3)
	{
		fprintf(stderr,"%s: Usage: %s path filename \n", argv[0], argv[0]);
		exit(EXIT_FAILURE);
	}
	if((temp = opendir(argv[1])) == NULL)
	{
		fprintf(stderr,"%s is not a real path.\n",argv[1]);
		exit(EXIT_FAILURE);
	}
	else
		closedir(temp);
	go_in_dir(argv[1], argv[2]);
}

void go_in_dir(const char * dir, const char * file)
{
	DIR * dp;
	struct dirent * entry;
	struct stat statbuf;

	dp = opendir(dir);
	chdir(dir);
	while((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name, &statbuf);
		if(S_ISDIR(statbuf.st_mode))
		{
			//ignore . & ..
			if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
					continue;

			go_in_dir(entry->d_name, file);
		}
		else
		{
			if(strcmp(entry->d_name, file) == 0)
				{
					printf("%s/%s\n",getcwd(NULL, 0), entry->d_name);
					found++;
				}
		}
	}
	chdir("..");
	closedir(dp);
}
