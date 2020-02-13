//! rcm.c
/*!
    \author Αλέξανδρος Τσιγγίλης.
    
    \date		2 February 2020.

    \short 	Implementation of the rcm() function defined in inc/rcm.h

    \long	-

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rcm.h"

//! Static global Array of (all) the vertices.
static Vertex *V;


//! Compare function for the qsort routine.
/*!
    \function cmp 	for sorting the neighbors Array
*/
static inline int cmp( const void* a, const void* b ) {
    int u = *(int*)a,
        w = *(int*)b;
		return V[u].degree - V[w].degree;
}


//! Finds the node from whom the bfs will start.
//! typicaly the one with the smallest degree (that isn't zero)
static inline int firstNode( int n ) {

	int min = 0;
	
	/* Find an unvisited conected component. */
	for( int i = 1; i < n; i++ ) {
		if( V[i].degree > 0 && V[i].visited==false) {
			min = i;
			break;
		}
	}
	
	/* Find the vertex with the smallest degree in that connected component. */
	for( int i = 0; i < n; i++ ) 
		if( V[i].degree < V[min].degree && V[i].degree > 0 )
			min = i;

	return min;	

}

//! Performs Breadth First Search, using R as Queue. 
static inline int bfs(int n, int R[], int l, int source ) {
	
	int head = l,
			tail = l;

	R[tail++] = source;          // Push source to the queue.
	V[source].visited = true;
                               
	while( head < tail ) {       // While Queue isn't empty...
	    
		int x = R[head++];

		qsort(V[x].neighbors, V[x].degree, sizeof(int), cmp);

		for( int j = 0; j < V[x].degree; j++ ) {

			int k = V[x].neighbors[j];

			if( ! V[k].visited ) {
				R[tail++] = k;//V[k].id;
				V[k].visited = true;
			}//end_if

		}//end_for
	
	}//end_while

	return tail;

}

//! The `main` function of this file. 
/*
    Implements the Reverse Cuthill-McKee algorithm.
*/
void rcm( const int n, Vertex vertices[], int R[] ) {

	/* Declaring variables. */
	int l = 0, 
			min = 0;
	
	/* Setting the `global` vertices array. */
	V = vertices;

	/* Find the `first node` and perform BFS */
	min = firstNode(n);
	l = bfs(n,R,l,min);

	/* Perform BFS to the rest un-visited conected components of the graph. */
	for(int i = 0; i < n; i++) {        // For every vertex.
		                                     
		if( !V[i].visited ) {             // If that vertex has not been visited,
			l = bfs(n, R, l, i);      // Perform BFS with V[i] as the starting vertex.
		}
	}

	/* Reverse the reorsering. */
	for( int i = 0; i < n/2; i++ )
	{
		int tmp = R[i];
		R[i] = R[n-i-1];
		R[n-i-1] = tmp;
	}

}
