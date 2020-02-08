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
    \function cmp_n 	for sorting the neighbors Array
*/
static inline int cmp( const void* a, const void* b ) {
    int u = *(int*)a,
        w = *(int*)b;
		return V[u].degree - V[w].degree;
}


static inline int firstNode( int n ) {

	int min = 0;

	for( int i = 1; i < n; i++ ) {
		if( V[i].degree > 0 && V[i].visited==false) {
			min = i;
			break;
		}
	}

	for( int i = 0; i < n; i++ ) 
		if( V[i].degree < V[min].degree && V[i].degree > 0 )
			min = i;

	return min;	

}

//! Performs Breadth First Search, using R as Queue. 
static inline int bfs(int n, int R[], int l, int source ) {
	
	int NL[n],
			head = l,
			tail = l;

	
	R[tail++] = source;

	while( head < tail ) {
		
		int h = 0, t = 0;

		for( int i = head; i < tail; i++ ) {
			int u = R[i];
			for( int j = 0; j < V[u].degree; j++ ) {
				int v = V[u].neighbors[j];
				if( ! V[v].visited ) {
					NL[t++] = v;
					V[v].visited = true;
				}//end_if
			}//end_for
		}//end_for
		
		head = tail;
		for( int i = h; i < t; i++)
			R[tail++] = NL[i];

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
			l = bfs(n, R, l, V[i].id);      // Perform BFS with V[i] as the starting vertex.
		}
	}
	
	/* Reverse R */
	for( int i = 0; i < n/2; i++ ) {
		int tmp = R[i];
		R[i] = R[n-i-1];
		R[n-i-1] = tmp;
	}

}
