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
*/
static inline int cmp( const void* a, const void* b ) {
    int u = (*(Vertex**)a)->degree,
        w = (*(Vertex**)a)->degree;
		return (u-w);	
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


//! The `main` function of this file. 
/*
    Implements the Reverse Cuthill-McKee algorithm.
*/
void rcm( const int n, const double *A, int *R ) {

		printf("OK\n");

    /* Declaring variables. */
    int l = n-1,                                            // `l` is the current level in R.
		    min = 0;
    Vertex V[n];                                            // The array of the verteces.
    Queue *Q = init(n);                                     // The Queue used in BFS.
    
    /* Initialization of variables. */
    for( int v = 0; v < n; v++ ) {
    	V[v].id = v;                                                           // Set the original id of the vertex.
    	V[v].degree = calcDegree(n,A,v);                                       // Computes it's degree.
    	createNeighborhood(n, A, V, &V[v]);                                    // Create is adjacent list.
    	V[v].visited = FALSE;                                                  // Set it un-visited.
    	min = (V[min].degree > V[v].degree && V[v].degree != 0)? v : min;	
    }	
	
		/* Swap min with the first element. */
		Vertex tmp = V[0];
		V[0] = V[min];
		V[min] = tmp;

		/* TODO : Add comments. */
    for(int i = 0; i < n; i++) {
    	
    	if( !V[i].visited ) {
    		push(Q,&V[i]);
    		V[i].visited = TRUE;
    		while( ! empty(Q) ){
    			Vertex *x = pop(Q);
    			R[l--] = x->id;
					qsort(x->neighbors,x->degree,sizeof(Vertex*), cmp);
    			for(int i = 0; i < x->degree; i++) {
    				Vertex *u = x->neighbors[i];
    				if( ! u->visited ) {
    					push(Q,u);
    					u->visited = TRUE;
    				}
    			}
    		}
    	}

    }
    

}
