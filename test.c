#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractGraph.h"
#include "abstractQueue.h"
#include "abstractRobot.h"

int main(int argc, char const *argv[])
	{
	generateMap(5,5);

	int count  = 0;
	int obOneI,obOneJ,obTwoI,obTwoJ;

	VERTEX_T * from = findVertexByKey(4,3);
	VERTEX_T * to = findVertexByKey(0,2);
	VERTEX_T * nextVertex = NULL;
	robotLocation = from;

	obstacleOne.xMove = 1;
	obstacleOne.yMove = 0;
	obstacleOne.speed = 1;
	obstacleNewLocation(&obstacleOne,2,1);

	obstacleTwo.xMove = 1;
	obstacleTwo.yMove = 0;
	obstacleTwo.speed = 1;
	obstacleNewLocation(&obstacleTwo,3,1);
	
	while(robotLocation != to)
		{
		VERTEX_T * obOne = NULL;
		VERTEX_T * obTwo = NULL;

		moveObstacle(&obstacleOne);
		moveObstacle(&obstacleTwo);

		robotLocation = reachablePath(robotLocation,to);

		obOne = obstacleOne.location;
		obTwo = obstacleTwo.location;

		obOneI = obOne->i;
		obOneJ = obOne->j;
		obTwoI = obTwo->i;
		obTwoJ = obTwo->j;
		printf("Time %d : Robot(%d,%d) Obstacle1(%d,%d) Obstacle2(%d,%d)\n\n", ++count,robotLocation->i,robotLocation->j,obOneI,obOneJ,obTwoI,obTwoJ);
		}

	return 0;
	}
