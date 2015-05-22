#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc,char ** argv)
{
	char * p;
//if argv[1] == NULL	
	if(argc == 1)
	{
		p = malloc(sizeof(char) * 2);
		strncpy(p,"y\0",1);
	}
	else
//if argv[1] != NULL
	{
		p = malloc(sizeof(argv[1] + sizeof(char)));
		strcpy(p,argv[1]);
		strncat(p,"\0",1);
	}

//print the things which need to be printed
	while(1)
		printf("%s\n",p);
		
}
