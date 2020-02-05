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
int bfs( Queue *Q, int R[], int l ) {
	while( ! empty(Q) ) {                                           // While the Queue isn't empty.

		Vertex *x = dequeue(Q);                                       // Take the first Vertex in the queue.
		R[l--] = x->id;                                               // Set the l-th vertex in the premuted graph to be x (and decrease l).
		qsort(x->neighbors,x->degree,sizeof(Vertex*), cmp);						// Sort the neighbors of x.
		
		for(int i = 0; i < x->degree; i++) {                          // For every neighbor of x... u
			Vertex *u = x->neighbors[i];                                // Take a pointer to u.
			if( ! u->visited ) {                                        // If u is un-visited,
				enqueue(Q,u);                                             // Add u to the queue,
				u->visited = true;                                        // and label u as visited.
			}
		}
	}
	return l;
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

	
	/* Perform BFS to all conected components of the graph. */
	for(int i = 0; i < n; i++) {           // For every vertex.
		                                     
		if( !V[i].visited ) {                // If that vertex has not been visited,
                                         
			enqueue(Q,&V[i]);                  // add it to the queue,
			V[i].visited = true;               // label it as visited.

				l = bfs(Q,R,l);                  // Perform BFS with V[i] as the starting vertex.
		}

	}
}
