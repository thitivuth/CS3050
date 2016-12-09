#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractGraph.h"
#include "abstractQueue.h"
#include "abstractRobot.h"

int main(int argc, char const *argv[])
	{
	generateMap(4,4);
	VERTEX_T * from = findVertexByKey(3,0);
	VERTEX_T * to = findVertexByKey(0,3);
	reachablePath(from,to);
	return 0;
	}
