//! test.c
/*!
	\author Αλέξανδρος Τσιγγίλης
	
	\date		7 February 2020

	\short	Timing the RCM implementation. 

	\long		This file contains the main function of the program that times the rcm() and parallel_rcm() functions.
					A random graph is created and the the two rcm implementations are executed.

*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <omp.h>
#include "rcm.h"

/*!
	Initializes a vertex randomly, meaning that it performs a bernouli trial with p = d,
	for each vertex that v can be connected to if the tial `successeds it connects them.
*/
void random_vertex( const int n, double d, Vertex V[], Vertex* v ) {
		int k = 0;
		v->neighbors = malloc(n*sizeof(int*));
		for(int i = 0; i < n; i++) {
			double p = (double)rand() / RAND_MAX;
			if( p <= d && i != v->id) {
				v->neighbors[k++] = i;
			}
		}
		v->degree = k;
		v->neighbors = realloc(v->neighbors, k*sizeof(int));
		v->level = INT_MAX;
		return;
}

//! Main function.
int main (int argc, char** argv) {

	int n = atoi(argv[2]), R[n];
	double	d = atof(argv[3]), time;
	Vertex V[n];

	printf("Creating random graph...");
	#pragma omp parallel for shared(V,n,d)
	for( int v = 0; v < n; v++ ) {
		V[v].id = v; 
		random_vertex(n,d,V,&V[v]);
	}
	printf(" done!\n");

	if( argv[1][1] == 'S') {
		printf("Running sequentialy... ");
		time = omp_get_wtime();
		rcm(n,V,R);
		time = omp_get_wtime() - time;
	}
	else {
		printf("Running in parallel... ");
		time = omp_get_wtime();
		parallel_rcm(n,V,R);
		time = omp_get_wtime() - time;
	}
	
	printf("It took %f seconds.\n", time);

	return 0;
}
