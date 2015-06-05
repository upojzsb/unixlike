#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define CVMAX 26
#define VER "1.0"
#define TRUE 1
#define FALSE 0
#define LINEBUFF 4096

char * GetInputLine(void);
void logical(char * line);

double CV[CVMAX]; /*Character variable from a to z*/
double ANS = 0;
int main(void)
{
	for(int i = 0; i < CVMAX; i++)
		CV[i] = 0;

	char *line;

	printf("calc %s\nCopyRight 2015\nA software is simlar to bc\n", VER);

	while(TRUE)
	{
		line = GetInputLine();
		logical(line);
	}
}

/*
   This section used to get a series of characters form stdin,and return then to main fuction as char *
 */

char * GetInputLine(void)
{
	char * line;
	char tmp;
	int count = 0;

	line = (char *)malloc(LINEBUFF);
	
	while((tmp = getchar()) != '\n')
	{
		line[count] = tmp;
		count++;
	}
		
	line[count + 1] = '\0';

	return line;
}

/*
   This section used to analyze characters and solve the answer, call other fuction to print them out
 */
void logical(char * line)
{
	int sol; //size of line
	int location = 0;
	int location1 = 0;
	int symbolp = 0; // Symbol place
	double o1 = 0, o2 = 0;//operate number 1 and operate number 2
	char * buf;

	sol = strlen(line);

	/*
	   The first character is a digit
	 */	
	if( isdigit(line[0]) )
	{
		/*
		   Operate operation number 1
		 */
		for(int i = 0; i < sol; i++)
		{
			if((line[i] < '0' || line[i] > '9') && line[i] != '.')
			{
				location = i;
				break;
			}
		}
		if(location != 0)
			buf = (char *)malloc(location + 1);
		else
		{
			buf = (char *)malloc(sol);
			if( isdigit(line[0]) )
				location = sol;
		}
		for(int i = 0; i < location; i++)
			buf[i] = line[i];
		strcat(buf, "\0");
	
		if(buf[0] != '\0')
			o1 = atof(buf);
		
		free(buf);

		if(location == sol)
		{
			printf("%lf\n", o1);
			ANS = o1;
			return;
		}
		/*
		   Find symbol
		 */
		if(line[location] == '+' || line[location] == '-' || line[location] == '*' || line[location] == '/' || line[location] == '%')
		{

		}
		else
		{
			fprintf(stderr, "Error Symble %c, It only support +-*/%%\n", line[location]);
			return;
		}

		symbolp = location;
		location++;

		/*
		   Operate operation number 2
		 */
		if(isalpha(line[location]) && line[location + 1] == '\0')
			o2 = CV[line[location] - 'a'];
		else
		{
			for(int i = location; i < sol; i++)
			{   
				if((line[i] < '0' || line[i] > '9') && line[i] != '.')
				{
					fprintf(stderr, "Error Operation number\n");
					return;
				}
			}
			if(line[location] == '.')
			{
				fprintf(stderr, "Error Operation number\n");
				return;
			}

			buf = &line[location];
			o2 = atof(buf);
		}

		/*
		   Operate
		 */
		switch(line[symbolp])
		{
			case '+':
				ANS = o1 + o2;
				break;
			case '-':
				ANS = o1 - o2;
				break;
			case '*':
				ANS = o1 * o2;
				break;
			case '/':
				ANS = o1 / o2;
				break;
			case '%':
				ANS = (int)o1 % (int)o2;
				break;
			default:
				fprintf(stderr, "Error Symble");
				break;
		}

		printf("%lf\n",ANS);
		return;
	}

	/*
	   The first character is an alpha
	 */

	if( islower(line[0]) )
	{
		/*
		   If need bestow value to character
		 */
		if(line[1] == '=')
		{
			if(isalpha(line[2]) && line[3] == '\0')
			{
				ANS = CV[line[2] - 'a'];
				CV[line[0] -'a'] = ANS;
				printf("%lf\n",ANS);
				return;
			}
			else
			{
				for(int i = 2; i < sol; i++)
				{   
					if((line[i] < '0' || line[i] > '9') && line[i] != '.')
					{
						fprintf(stderr, "Error Operation number\n");
						return;
					}
				}
				if(line[2] == '.')
				{
					fprintf(stderr, "Error Operation number\n");
					return;
				}
	
				buf = &line[2];
				ANS = atof(buf);
				CV[line[0] - 'a'] = ANS;
				printf("%lf\n",ANS);
				return;
			}
		}
		
		/*
		   Operate operation number 1
		 */
		o1 = CV[line[0] - 'a'];
		
		if(line[1] == '\0')
		{
			printf("%lf\n", o1);
			ANS = o1;
			return;
		}
		/*
		   Find symbol
		 */
		if(line[1] == '+' || line[1] == '-' || line[1] == '*' || line[1] == '/' || line[1] == '%')
		{

		}
		else
		{
			fprintf(stderr, "Error Symble %c, It only support +-*/%%\n", line[1]);
			return;
		}

		symbolp = 1;

		/*
		   Operate operation number 2
		 */
		if(isalpha(line[2]) && line[3] == '\0')
			o2 = CV[line[2] - 'a'];
		else
		{
			for(int i = 2; i < sol; i++)
			{   
				if((line[i] < '0' || line[i] > '9') && line[i] != '.')
				{
					fprintf(stderr, "Error Operation number\n");
					return;
				}
			}
			if(line[2] == '.')
			{
				fprintf(stderr, "Error Operation number\n");
				return;
			}

			buf = &line[2];
			o2 = atof(buf);
		}

		/*
		   Operate
		 */
		switch(line[symbolp])
		{
			case '+':
				ANS = o1 + o2;
				break;
			case '-':
				ANS = o1 - o2;
				break;
			case '*':
				ANS = o1 * o2;
				break;
			case '/':
				ANS = o1 / o2;
				break;
			case '%':
				ANS = (int)o1 % (int)o2;
				break;
			default:
				fprintf(stderr, "Error Symble");
				break;
		}

		printf("%lf\n",ANS);
		return;
	}
}

