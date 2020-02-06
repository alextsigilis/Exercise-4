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

//! Compare function for the qsort routine.
/*!
    \function cmp_n 	for sorting the neighbors Array
*/
static inline int cmp( const void* a, const void* b ) {
    int u = (*(Vertex**)a)->degree,
        w = (*(Vertex**)a)->degree;
		return (u-w);	
}


//! Performs Breadth First Search, using the Queue Q.
int bfs( Vertex V[], int R[], int l, int source ) {

	int h = l,
			t = l;
	R[h--] = source;
	V[source].visited = true;

	while( h < t ) {	                                            // While the Queue isn't empty.

		int x = R[t--];                                             // Take the first Vertex in the queue.
		
		for(int i = 0; i < V[x].degree; i++) {                     // For every neighbor of x... u
			int k = V[x].neighbors[i];                               // Take a pointer to u.
			if( ! V[k].visited ) {                                      // If u is un-visited,
				R[h--] = k;                                             // Add u to the queue,
				V[k].visited = true;                                    // and label u as visited.
			}
		}
	}
	return h;
}

//! The `main` function of this file. 
/*
    Implements the Reverse Cuthill-McKee algorithm.
*/
void rcm( const int n, Vertex V[], int R[] ) {

	/* Declaring variables. */
	int l = n-1,                                            // `l` is the current level in R.
			min = 0;
	
	min++;
	
	/* Perform BFS to all conected components of the graph. */
	for(int i = 0; i < n; i++) {           // For every vertex.
		                                     
		if( !V[i].visited ) {                // If that vertex has not been visited,
			l = bfs(V, R, l, V[i].id);         // Perform BFS with V[i] as the starting vertex.
		}

	}
}
