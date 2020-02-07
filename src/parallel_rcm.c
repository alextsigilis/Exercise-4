//! rcm.c
/*!
    \author Αλέξανδρος Τσιγγίλης.
    
    \date		2 February 2020.

    \short 	Implementation of the rcm() function defined in inc/rcm.h

    \long	-

*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "rcm.h"

//! Static global Array of (all) the vertices.
static Vertex *V;


//! Compare function for the qsort routine.
/*!
    \function cmp_n 	for sorting the neighbors Array
*/
static inline int cmp( const void* a, const void* b ) {
    int u = *(int*)a,
        w = *(int*)b;
		return V[u].degree - V[w].degree;
}


//! Performs Breadth First Search, using R as Queue. 
static inline int bfs(int R[], int l, int source ) {

	/* Declare and initialize head and tail of the queue */
	int h = l,
			t = l;
	
	/* Inserting the source to the queue. */
	R[t++] = source;
	V[source].visited = true;                                    // Mark as visited.


	for( int i = h; i < t; i++ ) {
	
		int x = R[i];                                              // Take the first Vertex in the queue.
		qsort(V[x].neighbors, V[x].degree, sizeof(int), cmp);      // Sorting the neighbors in increasing order of degree.

		for(int j = 0; j < V[x].degree; j++) {                     // For every neighbor of x... k
			int k = V[x].neighbors[j]; 
			if( ! V[k].visited ) {                                   // If k is un-visited,
				R[t++] = V[k].id;
				V[k].visited = true;                                   // and label k as visited.
			}
		}
	}
	
	return t;
}


//! The `main` function of this file. 
/*
    Implements the Reverse Cuthill-McKee algorithm.
*/
void parallel_rcm( const int n, Vertex vertices[], int R[] ) {

	/* Declaring variables. */
	int l = n-1, 
			min = 0;

	V = vertices;

	#pragma omp parallel shared(l,min,R)
	{

		/* Find the `first node` and perform BFS */
		#pragma omp for reduction(min:min)
		for( int i = 0; i < n; i++ ) {
			if( V[i].degree < min && V[i].degree > 0 )
				min = i;
		}
		
				
		#pragma omp master
		{

			l = bfs(R,l,min);
			
			for(int i = 0; i < n; i++) {        // For every vertex.
				if( !V[i].visited ) {             // If that vertex has not been visited,
					l = bfs(R, l, V[i].id);         // Perform BFS with V[i] as the starting vertex.
				}
			}

		} // master
			
	}  // parallel.

}
