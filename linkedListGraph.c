/*
 *  linkedListGraph.c
 *
 *  Implements an abstractGraph using adjacency lists (linked lists).
 *  This is a structure with two levels of list. There is a master
 *  list of vertices, linked in series. Each vertex points to a subsidiary
 *  linked list with references to all the other vertices to which it
 *  is connected. This will work only with undirected graph.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abstractGraph.h"
#include "abstractQueue.h"


VERTEX_T * vListHead = NULL;  /* head of the vertex list */
VERTEX_T * vListTail = NULL;  /* tail of the vertex list */
int vertexCount = 0;          /* keep track of the number of vertices */

/* Free the adjacencyList for a vertex 
 * Argument
 *   pVertex    - vertex whose edges we want to delete 
 */
void freeAdjacencyList(VERTEX_T *pVertex)
  {
   ADJACENT_T * pCurRef = pVertex->adjacentHead;
   while (pCurRef != NULL)
      {
      ADJACENT_T * pDelRef = pCurRef;
      pCurRef = pCurRef->next;
      free(pDelRef);
      }
   pVertex->adjacentHead = NULL;
   pVertex->adjacentTail = NULL;
  }


/* Free all memory associated with the graph and
 * reset all parameters.
 */
void clearGraph()
  {
  VERTEX_T * pCurVertex = vListHead;
  while (pCurVertex != NULL)
    {
    freeAdjacencyList(pCurVertex);
    VERTEX_T * pDelVtx = pCurVertex;
    pCurVertex = pCurVertex->next;
    free(pDelVtx);
    }
  vListHead = NULL;  
  vListTail = NULL; 
  }

/* Set all vertices to the passed color.
 * Argument
 *    A color constant
 */
void colorAll(int color)
  {
  VERTEX_T* pVertex = vListHead;
  while (pVertex != NULL)
     {
     pVertex->color = color;
     pVertex = pVertex->next;
     }
  }

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
int generateMap(int width, int height)
  {
  int i;
  int j;
  int bOk;
  int count = 0;
  
  maxWidth = width-1;
  maxHeight = height-1;

  for(i=0; i<height; i++)
    {
    for(j=0; j<width; j++)
      {
      bOk = addVertex(i,j);
      if(bOk != 1)
        return bOk;
      }
    }
  for(i=0; i<height; i++)
    {
    for(j=0; j<width; j++)
      {
      if(j+1 < width)
        {
        bOk = addEdge(i,j,i,j+1);
        count++;
        if(bOk != 1)
          return bOk;      
        }
      if(i+1 < height)
        {
        bOk = addEdge(i,j,i+1,j);
        count++;
        if(bOk != 1)
          return bOk;              
        }
      if(i+1 < height && j+1 < width)
        {
        bOk = addEdge(i,j,i+1,j+1);
        count++;
        if(bOk != 1)
          return bOk;         
        }
      if(i+1 < height && j-1 >= 0)
        {
        bOk = addEdge(i,j,i+1,j-1);
        count++;
        if(bOk != 1)
          return bOk;         
        }        
      }
    }
  return bOk;
  }

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
int addVertex(int i, int j)
  {
  int bOk = 1;

  VERTEX_T * pNewVtx = (VERTEX_T *) calloc(1,sizeof(VERTEX_T));
  pNewVtx->count = 99999;

  if (pNewVtx == NULL)
    {
    bOk = 0;  /* allocation error */
    }
  else
    {
    pNewVtx->i = i;
    pNewVtx->j = j;
    if (vListHead == NULL)  /* first vertex */
       {
       vListHead = pNewVtx;
       }
    else
       {
       vListTail->next = pNewVtx; 
       }
    vListTail = pNewVtx;
    vertexCount++;
    }

  return bOk;
  }

/* Find a vertex and return its data
 * Arguments
 *    i,j  -  Key for the vertex to find
 * Returns the data for the vertex or NULL
 * if not found.
 */
void * findVertexByKey(int i, int j)
  {
  VERTEX_T * pFoundVtx = NULL;
  VERTEX_T * pCurVertex = vListHead;

  /* while there are vertices left and we haven't found
   * the one we want.
   */
  while ((pCurVertex != NULL) && (pFoundVtx == NULL))
    {
    if(pCurVertex->i == i && pCurVertex->j == j)
      {
      pFoundVtx = pCurVertex;
      }
    else
      {
      pCurVertex = pCurVertex->next;
      }
    }
  return pFoundVtx;
  }

/* Check if there is already an edge between
 * two vertices. We do not want to add a duplicate.
 * Arguments
 *   pFrom        -  Start point of edge
 *   pTo          -  End point of edge
 * Return 1 if an edge already exists, 0 if it does
 * not.
 */
int edgeExists(VERTEX_T* pFrom, VERTEX_T* pTo)
  {
  int bEdgeExists = 0;
  ADJACENT_T * pAdjacent = pFrom->adjacentHead;
  while ((pAdjacent != NULL) && (!bEdgeExists))
    {
    if (pAdjacent->pVertex == pTo)
      {
      bEdgeExists = 1;  /* the 'To' vertex is already in the
                             * 'From' vertex's adjacency list */ 
      }
    else
      {
      pAdjacent = pAdjacent->next;
      }
    } 
  return bEdgeExists;
  }


/* Add an edge between two vertices
 * Arguments
 *    i1,j1  -  Key for the first vertex in the edge
 *    i2,j2  -  Key for the second vertex
 * Returns 1 if successful, 0 if failed due to
 * memory allocation error, or if either vertex
 * is not found. Returns -1 if an edge already
 * exists in this direction.
 */
int addEdge(int i1, int j1, int i2, int j2)
  {
  int bOk = 1;

  VERTEX_T * pFromVtx = (VERTEX_T *) findVertexByKey(i1, j1);
  VERTEX_T * pToVtx = (VERTEX_T *) findVertexByKey(i2, j2);

  /* If both vertex not exist */
  if ((pFromVtx == NULL) || (pToVtx == NULL))
    {
    bOk = -1;
    }
  else
    {
    if(edgeExists(pFromVtx,pToVtx) || edgeExists(pToVtx,pFromVtx))
      {
      bOk = -2;
      }
    else
      {
      /* Add link */
      ADJACENT_T * pNewRef = (ADJACENT_T*) calloc(1,sizeof(ADJACENT_T));
      
      if (pNewRef == NULL)
        {
        bOk = -3;
        }
      else
        {
        pNewRef->pVertex = pToVtx;

        if (pFromVtx->adjacentTail != NULL)
          {
          pFromVtx->adjacentTail->next = pNewRef;
          }
        else
          {
          pFromVtx->adjacentHead = pNewRef;
          }
        pFromVtx->adjacentTail = pNewRef;
        }

      ADJACENT_T * pNewRef2 = (ADJACENT_T*) calloc(1,sizeof(ADJACENT_T));
      
      if (pNewRef2 == NULL)
        {
        bOk = -3;
        }
      else
        {
        pNewRef2->pVertex = pFromVtx;

        if (pToVtx->adjacentTail != NULL)
          {
          pToVtx->adjacentTail->next = pNewRef2;
          }
        else
          {
          pToVtx->adjacentHead = pNewRef2;
          }
        pToVtx->adjacentTail = pNewRef2;      
        }

      }
    } 
  return bOk;
  }


void printPath(VERTEX_T* pEndVertex)
  {
  VERTEX_T** pathVertices = calloc(vertexCount,sizeof(VERTEX_T*));
    /* this array is big enough to hold all the vertices we have */
  int pathCount = 0;
  if (pathVertices == NULL) 
    {
    printf("Allocation error at printPath\n");
    }
  else
    {
    int i = 0;
    VERTEX_T * pCurrent = pEndVertex;
    while (pCurrent != NULL)  /* traverse the pFrom links */
      {
      pathVertices[pathCount] = pCurrent;
      pathCount++;
      pCurrent = pCurrent->pFrom;
      }
    /* Now start at the end of the array to print the path */
    for (i = pathCount-1; i >= 0; i--)
      {
      printf(" %d,%d ",pathVertices[i]->i,pathVertices[i]->j);
      if (i > 0)
        printf("==>");
      } 
    printf("\n");
    free(pathVertices);
    }
  }
  
void printAllEdge()
  {
  VERTEX_T* pCurrent = vListHead;
  ADJACENT_T* pRef;
  VERTEX_T * pAdjacent = NULL;

  while(pCurrent != NULL)
    {
    pRef = pCurrent->adjacentHead;
    printf("(%d,%d) -> ",pCurrent->i,pCurrent->j);
    while(pRef != NULL)
      {
      pAdjacent = (VERTEX_T *) pRef->pVertex;
      printf("(%d,%d), ",pAdjacent->i,pAdjacent->j);
      pRef = pRef->next;
      }
    printf("\n");
    pCurrent = pCurrent->next;
    }
  }

void reachablePath(VERTEX_T * pStartVertex, VERTEX_T * pEndVertex)
  {
  VERTEX_T * pAdjacent = NULL;

  queueClear();
  colorAll(WHITE);
  enqueue(pStartVertex);
  pStartVertex->count = 0;

  while (queueSize() > 0)
    {
    VERTEX_T* pCurrent = (VERTEX_T*) dequeue();
    if (pCurrent->color != BLACK)
      {
      pCurrent->color = BLACK;
      pCurrent->count = pCurrent->count+1;
      ADJACENT_T* pRef = pCurrent->adjacentHead;
      while (pRef != NULL)
        {
        pAdjacent = (VERTEX_T*) pRef->pVertex;
        if (pAdjacent->color != BLACK)
          {
          if(pCurrent->count+1 < pAdjacent->count)
            {
            pAdjacent->count = pCurrent->count+1;
            pAdjacent->pFrom = pCurrent;
            }
          enqueue(pAdjacent);
          }
        pRef = pRef->next;
        }
      }
    }

  printf("Path from %d,%d to %d,%d:\n",pStartVertex->i,pStartVertex->j,pEndVertex->i,pEndVertex->j); 
  printPath(pEndVertex);
  }