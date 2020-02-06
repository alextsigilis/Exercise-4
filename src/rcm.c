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
int bfs( Queue *Q, int R[], int l, Vertex V[], int source ) {

	int h = l,
			t = l;
	R[h--] = source;

	while( h < t ) {	                                              // While the Queue isn't empty.

		Vertex *x = &V[ R[t--] ];                                       // Take the first Vertex in the queue.
		
		for(int i = 0; i < x->degree; i++) {                          // For every neighbor of x... u
			int k = x->neighbors[i];                                    // Take a pointer to u.
			Vertex *u = &V[k];
			if( ! u->visited ) {                                        // If u is un-visited,
				R[h--] = u->id;                                           // Add u to the queue,
				u->visited = true;                                        // and label u as visited.
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
	Queue *Q = init(n);                                     // The Queue used in BFS.
	
	min++;
	
	/* Perform BFS to all conected components of the graph. */
	for(int i = 0; i < n; i++) {           // For every vertex.
		                                     
		if( !V[i].visited ) {                // If that vertex has not been visited,
			l = bfs(Q,R,l,V,V[i].id);                  // Perform BFS with V[i] as the starting vertex.
		}

	}
}
