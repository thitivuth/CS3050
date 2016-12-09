#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractRobot.h"
#include "abstractGraph.h"

void obstacleNewLocation(OBJ_T * obstacle, int i, int j)
	{
  VERTEX_T * newLocation = NULL;

  newLocation = (VERTEX_T *) findVertexByKey(i, j);

  if(newLocation != NULL)
  	{
  	obstacle->location = newLocation;
  	}
  else
  	{
  	printf("Error at obstacleNewLocation\n");
  	exit(0);
  	}
	}

void moveObstacle(OBJ_T * obstacle)
  {
  int newI = 0;
  int newJ = 0;
  int overflow = 0;
  VERTEX_T * newLocation = NULL;
  VERTEX_T * obstacleLocation = (VERTEX_T *) obstacle->location;

  newI = (obstacle->speed * obstacle->yMove) + obstacleLocation->i;
  newJ = (obstacle->speed * obstacle->xMove) + obstacleLocation->j;

  if(newI == maxHeight || newI == 0)
  	{
  	obstacle->yMove = obstacle->yMove * -1;
  	}
  if(newJ == maxWidth || newJ == 0)
  	{
  	obstacle->xMove = obstacle->xMove * -1;
  	}

  while(newI > maxHeight || newI < 0)
  	{
  	obstacle->yMove = obstacle->yMove * -1;
	  if(newI > maxHeight)
	  	{
	  	overflow = newI - maxHeight;
	  	newI = maxHeight - overflow;
	  	}
	  else if(newI < 0)
	  	{
	  	newI = newI * -1;
	  	}
  	}
  while(newJ > maxWidth || newJ < 0)
  	{
  	obstacle->xMove = obstacle->xMove * -1;
	  if(newJ > maxWidth)
	  	{
	  	overflow = newJ - maxWidth;
	  	newJ = maxWidth - overflow;
	  	}
	  else if(newJ < 0)
	  	{
	  	newJ = newJ * -1;
	  	}
  	}

  obstacleNewLocation(obstacle, newI, newJ);
  }


void robotNewLocation(int i, int j)
	{
  VERTEX_T * newLocation = NULL;

  newLocation = (VERTEX_T *) findVertexByKey(i, j);

  if(newLocation != NULL)
  	{
  	robotLocation = newLocation;
  	}
  else
  	{
  	printf("Error at robotNewLocation\n");
  	exit(0);
  	}
	}


	