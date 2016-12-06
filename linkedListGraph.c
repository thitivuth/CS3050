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


VERTEX_T * vListHead = NULL;  /* head of the vertex list */
VERTEX_T * vListTail = NULL;  /* tail of the vertex list */
int vertexCount = 0;          /* keep track of the number of vertices */
int bDagGraph = 1;


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
  for(i=0; i<height; i++)
    {
    for(j=0; j<width; i++)
      {
      bOk = addVertex(i,j);
      if(bOk != 1)
        return bOk;
      }
    }
  for(i=0; i<height; i++)
    {
    for(j=0; j<width; i++)
      {
      if(j+1 < width)
        {
        bOk = addEdge(i,j,i,j+1);
        if(bOk != 1)
          return bOk;      
        }
      if(i+1 < height)
        {
        bOk = addEdge(i,j,i+1,j);
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

  VERTEX_T * pFromVtx = (VERTEX_T *) findVertexByKey(i1, j2);
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