/************************************************
 *	main.c
 *
 *	Main file for the final project: Motion planning of robots
 *
 *	Created by Chaikrit Ouisui				 con49
 *	  		   Chalermpon Thongmotai		 ctpq8
 *	  		   Thitivuth Rattanasriampaipong trgmc
 *	Due Date Dec 8, 2016
 ************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_error.h"
//#include "abstractGraph.h"

#define BUFFER 16

/* obs1[0]: x-axis of obstacle 1, obs1[1]: y-axis of obstacle 1
   obs2[0]: x-axis of obstacle 2, obs2[1]: y-axis of obstacle 2
   speed[0]: speed of obstacle 1, speed[1]: speed of obstacle 2
   */
int obs1[2], obs2[2], speed[2], obs1_direction[2], obs2_direction[2];

int validate(char* input)
{
	int i = 0;
	while(input[i] != '\0' && input[i] == '\n')
	{
		if (input[i] < '0' || input[i] > '9' || input[i] == '+' || input[i] == '-')
			return 0;
		i++;
	}
	return 1;
}

int main(int argc, char const *argv[])
{
 	FILE* pFile = NULL;
	char inputBuffer[BUFFER]; //buffer
	int i = 0, n = 0, roomLength = 0;
	int start[2], end[2];
	char x_temp[BUFFER], y_temp[BUFFER];
	char* token;

	if(argc != 2) //incorrect number of arguments
		exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);

	pFile = fopen(argv[1],"r"); //open the read file
	if(pFile == NULL) //file open failed
		exit(FILE_FAILED_TO_OPEN);

	//freeGraph(); //reset the graph
	if(fgets(inputBuffer,BUFFER,pFile) != NULL) //get total number of vertices
	{
		n++; //check empty file
		if(validate(inputBuffer)) //check validation
		{
			sscanf(inputBuffer,"%d",&roomLength);
			printf("Room size: %d\n", roomLength);
		}
		else
			exit(PARSING_ERROR_INVALID_FORMAT);
	}

	while(fgets(inputBuffer,BUFFER,pFile) != NULL) //read the file
	{
		n++; //check empty file
		memset(x_temp, 0, sizeof(x_temp));
		memset(y_temp, 0, sizeof(y_temp));

		if (inputBuffer[0] == '(' && (inputBuffer[strlen(inputBuffer)-2] == ')' || inputBuffer[strlen(inputBuffer)-1] == ')'))
		{
			/* Valid input before storing, exit the program if there is wrong input */
			// token = strtok(inputBuffer,"(");
			// token = strtok(token,","); //get the source vertex
			
			// strcpy(x_temp,token);
			// 
			// token = strtok(NULL,")"); //get the destination vertex
			// strcpy(y_temp,token);
			
			token = strtok (inputBuffer,"(,)");
			strcpy(x_temp,token);
			token = strtok (NULL,"(,)");
			strcpy(y_temp,token);

			printf("(%s,%s)\n",x_temp,y_temp);

			if(validate(x_temp) && validate(y_temp))
			{
				//if input is correct, set the starting point of the robot
				if ((start[0] == 0) && (start[1] == 0))
				{	
					sscanf(x_temp,"%d",&start[0]);
					sscanf(y_temp,"%d",&start[1]);
					printf("Robot starts at (%d,%d)\n",start[0],start[1]);
					//addEdge(src,dest);
				}
				//if input is correct, set the end point of the robot
				else if ((end[0] == 0) && (end[1] == 0))
				{	
					sscanf(x_temp,"%d",&end[0]);
					sscanf(y_temp,"%d",&end[1]);
					printf("Robot will end at (%d,%d)\n",end[0],end[1]);
					//addEdge(src,dest);
				}
				//if input is correct, set the starting point of the first obstacle
				else if ((obs1[0] == 0) && (obs1[1] == 0))
				{
					sscanf(x_temp,"%d",&obs1[0]);
					sscanf(y_temp,"%d",&obs1[1]);
					printf("Obstacle 1 starts at (%d,%d)\n",obs1[0],obs1[1]);
					//addEdge(src,dest);
				}
				//if input is correct, set the direction of the first obstacle
				else if ((obs1_direction[0] == 0) && (obs1_direction[1] == 0))
				{
					if (x_temp[0] == '+') //get rid of the "+" sign
					{
						x_temp[0] = x_temp[1];
						x_temp[1] = '\0';
					}
					if (y_temp[0] == '+') //get rid of the "+" sign
					{
						y_temp[0] = y_temp[1];
						y_temp[1] = '\0';
					}
					sscanf(x_temp,"%d",&obs1_direction[0]);
					sscanf(y_temp,"%d",&obs1_direction[1]);
					printf("Obstacle 1's direction: (%d,%d)\n",obs1_direction[0],obs1_direction[1]);
					//addEdge(src,dest);
				}
				//if input is correct, set the starting point of the second obstacle
				else if ((obs2[0] == 0) && (obs2[1] == 0))
				{
					sscanf(x_temp,"%d",&obs2[0]);
					sscanf(y_temp,"%d",&obs2[1]);
					printf("Obstacle 2 starts at (%d,%d)\n",obs2[0],obs2[1]);
					//addEdge(src,dest);
				}
				//if input is correct, set the direction of the second obstacle
				else if ((obs2_direction[0] == 0) && (obs2_direction[1] == 0))
				{
					if (x_temp[0] == '+') //get rid of the "+" sign
					{
						x_temp[0] = x_temp[1];
						x_temp[1] = '\0';
					}
					if (y_temp[0] == '+') //get rid of the "+" sign
					{
						y_temp[0] = y_temp[1];
						y_temp[1] = '\0';
					}
					sscanf(x_temp,"%d",&obs2_direction[0]);
					sscanf(y_temp,"%d",&obs2_direction[1]);
					printf("Obstacle 2's direction: (%d,%d)\n",obs2_direction[0],obs2_direction[1]);
					//addEdge(src,dest);
				}
			}
			else //if not, reset the graph and exit
			{
				//freeGraph();
				exit(PARSING_ERROR_INVALID_FORMAT);
			}
		}
		//if input is an integer, set the speed of the first obstacle
		else if(validate(inputBuffer) && (speed[0] == 0))
		{
			sscanf(inputBuffer,"%d",&speed[0]);
			printf("Obstacle 1's speed: %d\n", speed[0]);
		}
		//if input is an integer, set the speed of the second obstacle
		else if(validate(inputBuffer) && (speed[1] == 0))
		{
			sscanf(inputBuffer,"%d",&speed[1]);
			printf("Obstacle 2's speed: %d\n", speed[1]);
		}
		else
		{
			//freeGraph();
			exit(PARSING_ERROR_INVALID_FORMAT);
		}
	}
	fclose(pFile); //close the file
 	return 0;
}