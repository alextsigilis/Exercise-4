#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "rcm.h"

typedef struct Vertex {
	int id;
	int degree;
	struct Vertex** neighbors;
	int visited;
} Vertex;

static inline int cmp( const void* a, const void* b ) {
	
	Vertex *u = (Vertex*)a,
				 *w = (Vertex*)b;

	return ( u->degree - w->degree ); 

}

static inline int calcDegree( const int n, const double *A, const int v ) {
	int k = 0;
	for(int i=0; i < n; i++)
		k += (Amat(v,i) == 0 || v == i)? 0 : 1;
	return k;
}

static inline void createNeighborhood( const int n, const double* A, Vertex V[], Vertex* v) {
	
	v->neighbors = malloc( v->degree  * sizeof(Vertex*));
	int l = 0, i = v->id;
	for( int j = 0; j < n; j++ )
		if( Amat(i,j) != 0 && i != j )
			v->neighbors[l++] = &V[j];
}

static inline int startVertex( const int n, Vertex V[] ) {
	
	// Find the first un-visited vertex.
	int initial = -1;
	for( int i = 0; i < n; i++ )
		if( !V[i].visited ) {
			initial = i;
			break;
		}

	// Exit if all nodes have been visited before.
	if( initial == -1 ) return -1;


	// Find the vertex with the minimum degree,
	// that can be reached from the initial vertex.
	int min = initial;
	for( int i = 0; i < n; i++)
		if( V[i].degree < V[min].degree  && V[i].visited==FALSE)
			min = i;

	return min;

}

void rcm( const int n, const double *A, int *R ) {

	Vertex V[n];

	for( int v = 0; v < n; v++ ) {
		V[v].id = v;
		V[v].degree = calcDegree(n,A,v);
		createNeighborhood(n, A, V, &V[v]);
		V[v].visited = FALSE;
		
	}

	for(int v = 0; v < n; v++) {
		
		printf("\n d(%d) = %d | ", v+1, V[v].degree);

		printf("N(%d) = { ", v+1);
		for(int i = 0; i < V[v].degree; i++) {
				printf("%d ", V[v].neighbors[i]->id+1);
		}
		printf("}\n\n");

	}


	/*
	Queue* Q = init(2*n);

	int r = startVertex(n,V),
			l = 0;

	while( r != -1 ) {
		
		push(Q,r);

		while( ! empty(Q) ) {
			
			int v = pop(Q);
		
			printf("%ith possition of R filled with %d.\n", l, v);

			R[l++] = v;
			V[v].visited = TRUE;


			// Put the neighbors to the qeueue.
			for( int i = 0; i < V[v].degree; i++ ) {
				
				// u is the ith neighbor of v
				int u = V[v].neighbors[i];

				// If u is un-visited, then
				// add u to the queue.
				if( ! V[u].visited ) push(Q,u);

			}

		}
		
		printf("looking for unvisited vertex to start...");
		r = startVertex(n,V);
		printf(" done.\n");
	}
*/	
}
