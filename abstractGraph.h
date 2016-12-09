/*  
 *  abstractGraph.h
 *
 *  Defines the necessary functions for a graph
 *
 */
#ifndef ABSTRACTGRAPH_H
#define ABSTRACTGRAPH_H

#define WHITE 0
#define GRAY  1
#define BLACK 2
 
/* List items for the adjacency list.
 * Each one is a reference to an existing vertex
 */
typedef struct _adjVertex
  {
  void * pVertex;           /* pointer to the VERTEX_T this item refers to */
  struct _adjVertex* next;  /* next item in the ajacency list */ 
  } ADJACENT_T;

/* List items for the main vertex list.*/
typedef struct _vertex
  {
    int i;                        /* key i for this vertex */
    int j;                        /* key j for this vertex */
    int color;                    /* used to mark nodes as visited */
    int count;
    struct _vertex * pFrom;
    struct _vertex * next;        /* next vertex in the list */
    ADJACENT_T * adjacentHead;    /* pointer to the head of the adjacent vertices list */
    ADJACENT_T * adjacentTail;    /* pointer to the tail of the adjacent vertices list */
  } VERTEX_T;

int maxWidth;
int maxHeight;

/* Free all memory associated with the graph and
 * reset all parameters.
 */
void clearGraph();

/* Setup the map by using undirected and unweighted graph
 * Arguments
 *     width   -   Key value or label for the 
 *               vertex (row)
 *     height   -   Key value or label for the 
 *               vertex (column)
 * Returns 1 unless there is an error, in which case
 * it returns a 0. An error could mean a memory allocation 
 * error or running out of space, depending on how the 
 * graph is implemented. Returns -1 if the caller tries
 * to add a vertex with a key that matches a vertex
 * already in the graph.
 */
int generateMap(int width, int height);

/* Add a vertex into the graph.
 * Arguments
 *     i   -   Key value or label for the 
 *               vertex (row)
 *     j   -   Key value or label for the 
 *               vertex (column)
 * Returns 1 unless there is an error, in which case
 * it returns a 0. An error could mean a memory allocation 
 * error or running out of space, depending on how the 
 * graph is implemented. Returns -1 if the caller tries
 * to add a vertex with a key that matches a vertex
 * already in the graph.
 */
int addVertex(int i, int j);


/* Add an edge between two vertices
 * Arguments
 *    i1,j1  -  Key for the first vertex in the edge
 *    i2,j2  -  Key for the second vertex
 * Returns 1 if successful, 0 if failed due to
 * memory allocation error, or if either vertex
 * is not found. Returns -1 if an edge already
 * exists in this direction.
 */
int addEdge(int i1, int j1, int i2, int j2);


/* Find a vertex and return its data
 * Arguments
 *    i,j  -  Key for the vertex to find
 * Returns the data for the vertex or NULL
 * if not found.
 */
void * findVertexByKey(int i, int j);

void reachablePath(VERTEX_T * pStartVertex, VERTEX_T * pEndVertex);
#endif
