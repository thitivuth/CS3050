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
    int xMove;                        
    int yMove;                        
    int speed;
    VERTEX_T * location;
  } OBJ_T;

OBJ_T obstacleOne;
OBJ_T obstacleTwo;
VERTEX_T robot;

void obstacleNewLocation(OBJ_T * obstacle, int i, int j);

void moveObstacle(OBJ_T * Obstacle);

void robotNewLocation(int i, int j);

#endif
