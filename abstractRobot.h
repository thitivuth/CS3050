/*  
 *  abstractRobot.h
 *
 *  Defines the necessary functions for a robot
 *
 */
#ifndef ABSTRACTROBOT_H
#define ABSTRACTROBOT_H

typedef struct _obj
  {
  int iMove;
  int jMove;
  int speed;
  void* locationVertex;
  } OBJ_T;

OBJ_T obstacleOne;
OBJ_T obstacleTwo;

void obstacleSetLocation(OBJ_T * obstacle, int i, int j);

void moveObstacle(OBJ_T * obstacle);

void robotNewLocation(int i, int j);

#endif
