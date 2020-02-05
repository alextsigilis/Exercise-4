#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include "rcm.h"


int calcDegree( const int n, const double *A, const int v ) {
    int k = 0;																		// Start with degree 0
    for(int i=0; i < n; i++)											// For every i vertex in the Graph,
    	k += (Amat(v,i) == 0 || v == i)? 0 : 1;			// 	If i is connected to v and thery are not the same, then  increment k
    return k;
}

//! Create an array which contains references to every neighbor vertex of a given vertex v.
void createNeighborhood( const int n, const double* A, Vertex V[], Vertex* v) {
    
    v->neighbors = malloc( v->degree  * sizeof(Vertex*));	// Allocate memory for all the neibhors,

    int l = 0, i = v->id;																	// `l` holds the number of elements that have been added so far,
    																									  	// `i` is the index of the given vertex. 
    for( int j = 0; j < n; j++ )
    	if( Amat(i,j) != 0 && i != j )                      // if i and j are neighbors,
    		v->neighbors[l++] = &V[j];                        // add j to N(v) and increment l.
}

int main (int argc, char** argv) {

	int n = atoi(argv[1]),
			R[n];
	double *A = malloc(n*n*sizeof(double)),
				 dt;
	Vertex V[n];
	time_t t1,t2;

	FILE *in = fopen("data.in", "rb");
	fread(A, sizeof(double), n*n, in);
	fclose(in);

	/* 
		Initialization of variables, 
		and find the vertex with the minimu degree.
	*/
	for( int v = 0; v < n; v++ ) {
		V[v].id = v;                                                           // Set the original id of the vertex.
		V[v].degree = calcDegree(n,A,v);                                       // Computes it's degree.
		createNeighborhood(n, A, V, &V[v]);                                    // Create is adjacent list.
		V[v].visited = false;                                                  // Set it un-visited.

	}

	free(A);
	
	printf("Starting RCM...");

	t1 = time(NULL);
		rcm(n,V,R);
	t2 = time(NULL);
	
	dt = difftime(t2,t1);

	printf("It took %f seconds.\n", dt);

	FILE *out = fopen("data.out", "wb");
	fwrite(&dt, sizeof(double), 1, out);
	fclose(out);

	return 0;
}
