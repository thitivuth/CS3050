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
#include "abstractGraph.h"
#include "abstractQueue.h"
#include "abstractRobot.h"

#define BUFFER 16

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

void displayTable(VERTEX_T * startPoint, VERTEX_T * endPoint)
	{
	int i, j;
	VERTEX_T * obOne = NULL;
	VERTEX_T * obTwo = NULL;
	printf("   \t");
	for(j=0; j<= maxWidth; j++)
		{
		printf("%-5d\t", j+1);
		}
	printf("\n");

	for(i=0; i<= maxHeight; i++)
		{
		for(j = 0; j <= maxWidth; j++)
			{
			if(j == 0)
				{
				printf("%3d\t", i+1);
				}
			obOne = (VERTEX_T *) obstacleOne.locationVertex;
			obTwo = (VERTEX_T *) obstacleTwo.locationVertex;
			if(robotLocation->i == i && robotLocation->j == j)
				printf("%-5s\t","R");
			else if(obOne->i == i && obOne->j == j && obTwo->i == i && obTwo->j == j)
				printf("%-5s\t","O1,O2");
			else if(obOne->i == i && obOne->j == j)
				printf("%-5s\t","Ob1");
			else if(obTwo->i == i && obTwo->j == j)
				printf("%-5s\t","Ob2");			
			else if(startPoint->i == i && startPoint->j == j)
				printf("%-5s\t","STA");			
			else if(endPoint->i == i && endPoint->j == j)
				printf("%-5s\t","END");			
			else
				printf("     \t");

			}
		printf("\n");
		}
	}

int main(int argc, char const *argv[])
{
 	FILE* pFile = NULL;
	char inputBuffer[BUFFER]; //buffer
	int i = 0, n = 0, roomLength = 0;
	int start[2], end[2], obOneI = 0, obOneJ = 0, obTwoI = 0, obTwoJ = 0;
	char x_temp[BUFFER], y_temp[BUFFER];
	char* token;
	VERTEX_T * from;
	VERTEX_T * to;
	
	start[0] = 0;
	start[1] = 0;
	end[0] = 0;
	end[1] = 0;

	if(argc != 2) //incorrect number of arguments
		exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);

	pFile = fopen(argv[1],"r"); //open the read file
	if(pFile == NULL) //file open failed
		exit(FILE_FAILED_TO_OPEN);

	clearGraph(); //clear the graph

	if(fgets(inputBuffer,BUFFER,pFile) != NULL) //get total number of vertices
	{
		n++; //check empty file
		if(validate(inputBuffer)) //check validation
		{
			sscanf(inputBuffer,"%d",&roomLength);
			printf("Room size: %d\n", roomLength);
		}
		else //clear the graph and exit the program
		{
			clearGraph();
			exit(PARSING_ERROR_INVALID_FORMAT);
		}
	}
	generateMap(roomLength,roomLength); //create a room with room length

	while(fgets(inputBuffer,BUFFER,pFile) != NULL) //read the file
	{
		n++; //check empty file
		memset(x_temp, 0, sizeof(x_temp));
		memset(y_temp, 0, sizeof(y_temp));

		if (inputBuffer[0] == '(' && (inputBuffer[strlen(inputBuffer)-2] == ')' || inputBuffer[strlen(inputBuffer)-1] == ')'))
		{
			/* Valid input before storing, exit the program if there is wrong input */			
			token = strtok (inputBuffer,"(,)");
			strcpy(x_temp,token);
			token = strtok (NULL,"(,)");
			strcpy(y_temp,token);

			if(validate(x_temp) && validate(y_temp))
			{
				//if input is correct, set the starting point of the robot
				if ((start[0] == 0) && (start[1] == 0))
				{	
					sscanf(x_temp,"%d",&start[0]);
					sscanf(y_temp,"%d",&start[1]);
					printf("Robot starts at (%d,%d)\n",start[0],start[1]);
					from = findVertexByKey(start[0]-1,start[1]-1); //set 
				}
				//if input is correct, set the end point of the robot
				else if ((end[0] == 0) && (end[1] == 0))
				{
					sscanf(x_temp,"%d",&end[0]);
					sscanf(y_temp,"%d",&end[1]);
					printf("Robot will end at (%d,%d)\n",end[0],end[1]);
					to = findVertexByKey(end[0]-1,end[1]-1);
				}
				//if input is correct, set the starting point of the first obstacle
				else if ((obOneI == 0) && (obOneJ == 0))
				{
					sscanf(x_temp,"%d",&obOneI);
					sscanf(y_temp,"%d",&obOneJ);
					printf("Obstacle 1 starts at (%d,%d)\n",obOneI,obOneJ);
					obstacleSetLocation(&obstacleOne, obOneI-1, obOneJ-1);
				}
				//if input is correct, set the direction of the first obstacle
				else if ((obstacleOne.iMove == 0) && (obstacleOne.jMove == 0))
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
					sscanf(x_temp,"%d",&obstacleOne.iMove);
					sscanf(y_temp,"%d",&obstacleOne.jMove);
					printf("Obstacle 1's direction: (%d,%d)\n",obstacleOne.iMove,obstacleOne.jMove);
				}
				//if input is correct, set the starting point of the second obstacle
				else if ((obTwoI == 0) && (obTwoJ == 0))
				{
					sscanf(x_temp,"%d",&obTwoI);
					sscanf(y_temp,"%d",&obTwoJ);
					printf("Obstacle 2 starts at (%d,%d)\n",obTwoI,obTwoJ);
					obstacleSetLocation(&obstacleTwo, obTwoI-1, obTwoJ-1);
				}
				//if input is correct, set the direction of the second obstacle
				else if ((obstacleTwo.iMove == 0) && (obstacleTwo.jMove == 0))
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
					sscanf(x_temp,"%d",&obstacleTwo.iMove);
					sscanf(y_temp,"%d",&obstacleTwo.jMove);
					printf("Obstacle 2's direction: (%d,%d)\n",obstacleTwo.iMove,obstacleTwo.jMove);
				}
			}
			else //clear the graph and exit the program
			{
				clearGraph();
				exit(PARSING_ERROR_INVALID_FORMAT);
			}
		}
		//if input is an integer, set the speed of the first obstacle
		else if(validate(inputBuffer) && (obstacleOne.speed == 0))
		{
			sscanf(inputBuffer,"%d",&obstacleOne.speed);
			printf("Obstacle 1's speed: %d\n", obstacleOne.speed);
		}
		//if input is an integer, set the speed of the second obstacle
		else if(validate(inputBuffer) && (obstacleTwo.speed == 0))
		{
			sscanf(inputBuffer,"%d",&obstacleTwo.speed);
			printf("Obstacle 2's speed: %d\n", obstacleTwo.speed);
		}
		else //clear the graph and exit the program
		{
			clearGraph();
			exit(PARSING_ERROR_INVALID_FORMAT);
		}
	}
	fclose(pFile); //close the file

	int count = 0;
	VERTEX_T * nextVertex = NULL;
	robotLocation = from;

	printf("\n");
	while(robotLocation != to)
	{
		VERTEX_T * obOne = NULL;
		VERTEX_T * obTwo = NULL;

		moveObstacle(&obstacleOne);
		moveObstacle(&obstacleTwo);

		robotLocation = reachablePath(robotLocation,to);

		obOne = (VERTEX_T *) obstacleOne.locationVertex;
		obTwo = (VERTEX_T *) obstacleTwo.locationVertex;

		obOneI = obOne->i;
		obOneJ = obOne->j;
		obTwoI = obTwo->i;
		obTwoJ = obTwo->j;
		printf("\n\nTime %d : Robot(%d,%d) Obstacle1(%d,%d) Obstacle2(%d,%d)\n\n", ++count,robotLocation->i+1,robotLocation->j+1,obOneI+1,obOneJ+1,obTwoI+1,obTwoJ+1);
		displayTable(from,to);
		printf("\n\n");
	}

 	return 0;
}