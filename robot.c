#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractRobot.h"
#include "abstractGraph.h"

void obstacleSetLocation(OBJ_T * obstacle, int i, int j)
	{
  VERTEX_T * newLocation = NULL;
  newLocation = (VERTEX_T *) findVertexByKey(i,j);

  if(newLocation != NULL)
  	{
  	obstacle->locationVertex = newLocation;
  	}
  else
  	{
  	printf("Error at obstacleSetLocation\n");
  	//exit(0);
  	}
	}

void moveObstacle(OBJ_T * obstacle)
  {
  int newI = 0;
  int newJ = 0;
  int overflow = 0;

  VERTEX_T * location = (VERTEX_T *) obstacle->locationVertex;
  
  //printf("%d %d | s=%d | %d %d\n", location->i, location->j, obstacle->speed, obstacle->iMove, obstacle->jMove);
  newI = location->i + (obstacle->iMove * obstacle->speed);
  newJ = location->j + (obstacle->jMove * obstacle->speed);

  //printf("%d %d | s=%d | %d %d\n", newI, newJ, obstacle->speed, obstacle->iMove, obstacle->jMove);

  if(newI == 0 || newI == maxHeight)
    {
    obstacle->iMove *= -1;
    }
  if(newJ == 0 || newJ == maxWidth)
    {
    obstacle->jMove *= -1;
    }

  while(newI < 0 || newI > maxHeight)
    {
    obstacle->iMove *= -1;
    if(newI > maxHeight)
      {
      overflow = newI - maxHeight;
      newI = maxHeight - overflow;
      }
    else if(newI < 0)
      {
      newI *= -1;
      }
    }

  while(newJ < 0 || newJ > maxWidth)
    {
    obstacle->jMove *= -1;
    if(newJ > maxWidth)
      {
      overflow = newJ - maxWidth;
      newJ = maxWidth - overflow;
      }
    else if(newJ < 0)
      {
      newJ *= -1;
      }
    }

  obstacleSetLocation(obstacle,newI,newJ);
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


	