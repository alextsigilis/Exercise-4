//! rcm.c
/*!
	\author Αλέξανδρος Τσιγγίλης.
	
	\date		2 February 2020.

	\short 	Implementation of the rcm() function defined in inc/rcm.h

	\long	-

*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "rcm.h"

//! Compare function for the qsort routine.
/*!
	\function cmp_n 	for sorting the neighbors Array
	\function cmp_v		for sorting the V vertex array
*/
static inline int cmp_n( const void* a, const void* b ) {
	Vertex **u = (Vertex**)a,
				 **w = (Vertex**)b;
	return ( (*u)->degree - (*w)->degree ); 
}
static inline int cmp_v( const void* a, const void* b) {
	Vertex* u = (Vertex*)a,
				 *w = (Vertex*)b;
	return ( u->degree - w->degree ); 
}

//! Calculate the degree of a vertex.
static inline int calcDegree( const int n, const double *A, const int v ) {
	int k = 0;																		// Start with degree 0
	for(int i=0; i < n; i++)											// For every i vertex in the Graph,
		k += (Amat(v,i) == 0 || v == i)? 0 : 1;			// 	If i is connected to v and thery are not the same, then  increment k
	return k;
}

//! Create an array which contains references to every neighbor vertex of a given vertex v.
static inline void createNeighborhood( const int n, const double* A, Vertex V[], Vertex* v) {
	
	v->neighbors = malloc( v->degree  * sizeof(Vertex*));						// Allocate memory for all the neibhors, |N(v)| = degree(v).

	int l = 0, i = v->id;																						// `l` hold the number of elements that have been added so far,
																																	// `i` is the index of the given vertex. 
	for( int j = 0; j < n; j++ )
		if( Amat(i,j) != 0 && i != j )																// if i and j are neighbors,
			v->neighbors[l++] = &V[j];																	// add j to N(v) and increment l.
}


//! The `main` functioni of this file. 
/*
	Implements the Reverse Cuthill-McKee algorithm.
*/
void rcm( const int n, const double *A, int *R ) {

	/* Declaring variables. */
	int l = n-1;																						// `l` is the current level in R.
	Vertex V[n];																						// The array of the verteces.
	Queue *Q = init(n);																			// The Queue used in BFS.
	
	/* Initialization of variables. */
	for( int v = 0; v < n; v++ ) {
		V[v].id = v;																					// Set the original id of the vertex.
		V[v].degree = calcDegree(n,A,v);											// Computes it's degree.
		createNeighborhood(n, A, V, &V[v]);										// Create is adjacent list.
		V[v].visited = FALSE;																	// Set it un-visited.
		
	}
	
	/* Verteces need to be sorted by ascending degree. */
	qsort( V, n, sizeof(Vertex), cmp_v );


	for( int r = 0; r < n; r++ ) {													// For each Vertex.
		
		if( ! V[r].visited ) {																// If the r is unvisited.
				
				push( Q , &V[r] );																// Add r to the queue.

				while( ! empty(Q) ) {															// While there are elements to the queue...
					
					Vertex *v = pop(Q);															// Remove the fist element,
					v->visited = TRUE;															// mark it as visited
					R[l--] = v->id;																	// and add it to R

					/* Sort the neighbors of v. */
					qsort(v->neighbors, v->degree, sizeof(Vertex*), cmp_n);

					for( int i = 0; i < v->degree; i++ ) {					// For every neighbor of v,
						Vertex *u = v->neighbors[i];									// get the vertex object
						if( ! u->visited )														// if u is un-visited,
							push(Q, u);																	// 	add it ot the queue.
					}

				}
	
		}

	}
}
