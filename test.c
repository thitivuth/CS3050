#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractGraph.h"
#include "abstractQueue.h"
#include "abstractRobot.h"

int main(int argc, char const *argv[])
	{
	generateMap(5,5);

	VERTEX_T * from = findVertexByKey(4,3);
	VERTEX_T * to = findVertexByKey(0,2);
	
	reachablePath(from,to);
	printAllEdge();
	return 0;
	}
