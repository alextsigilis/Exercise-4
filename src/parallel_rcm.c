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
#include <assert.h>
#include <omp.h>
#include "rcm.h"

//! Static global Array of (all) the vertices.
static Vertex *V;


//! Compare function for the qsort routine.
/*!
    \function cmp_n 	for sorting the neighbors Array
*/
static int cmp_l( const void* a, const void* b ) {
	
	Vertex *v = (Vertex*)a,
				 *u = (Vertex*)b;

	return (v->level - u->level);

}
static int cmp_d( const void* a, const void* b ) {
	
	Vertex *v = (Vertex*)a,
				 *u = (Vertex*)b;

	return (v->degree - u->degree);

}

static inline int firstNode( int n ) {

	int min = 0;

	for( int i = 1; i < n; i++ ) {
		if( V[i].degree > 0 && V[i].level==INT_MAX) {
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
static inline int bfs(const int n, const int source, const int level ) {

	int wl[n],
			local_wl[n],
			max_level = level,
			tail = 0,
			t = 0;

	V[source].level = level;
	wl[tail++] = source;

	while( tail > 0 ) {
		
		t = 0;
		#pragma omp parallel for
		for( int i = 0; i < tail; i++ ){
			int v = wl[i];
			for( int j = 0; j < V[v].degree; j++ ){
				int u = V[v].neighbors[j];
				if( V[u].level > V[v].level+1 ) {
					#pragma omp critical
					{
						max_level = (max_level < V[v].level+1)? V[v].level+1 : max_level;
						V[u].level = V[v].level+1;
						local_wl[t++] = u;
					}//end_ciritcal
				}//end_if
			}//end_for
		}//end_for

		tail = 0;
		for( int i = 0; i < t; i++ )
			wl[tail++] = local_wl[i];
	}//end_while

	return max_level;

}//end bfs()



//! The `main` function of this file. 
/*
    Implements the Reverse Cuthill-McKee algorithm.
*/
void parallel_rcm( const int n, Vertex vertices[], int R[] ) {

	/* Set the global vertex array. */
	V = vertices;

	int source = firstNode(n),
			max_level = 0,
			level = 0,
			l = 0,
			counts[n],
			sums[n];

		/* Run BFS for every connected component. */
		level = bfs(n,source,level);
		for( source = 0; source < n; source++ ) {
			if( V[source].level == INT_MAX )
				level = bfs(n,source,level);
		}//end_for


		/* Count the number of nodes at each level. */
		#pragma omp parallel for
		for( int l = 0; l < n; l++ )
			counts[l] = 0;
		
		for( int u = 0; u < n; u++ ) {
			l = V[u].level;
			max_level = (l > max_level)? l : max_level;
			counts[l]++;
		}//end_for

		/* Calculate the prefix sum */
		#pragma omp parallel for
		for( int i = 0; i < n; i++ ) {
			sums[i] = 0;
			for( int j = 0; j < i; j++ )
				sums[i] += counts[j];
		}//end_for


		/* Place nodes in permutation array */
		qsort(V,n,sizeof(Vertex),cmp_l);
		
		#pragma omp parallel for
		for(int l = 0; l <= max_level; l++) {
			qsort(V+sums[l], sums[l+1]-sums[l], sizeof(Vertex), cmp_d);
			for(int i = sums[l]; i < sums[l+1]; i++)
				R[i] = V[i].id;
		}//end_for

}//end rcm()
