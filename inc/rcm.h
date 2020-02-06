//! rcm.h
/*!
	\author Αλέξανδρος Τσιγγίλης
	
	\date		31 January 2020

	\short Headre file for implementation of the Reverse Cuthill-McKee Algorithm

	\long	-

*/
#ifndef __RCM_H__
#define __RCM_H__

#include <stdbool.h>

// ======== DEFINITION OF MACROS
#define 	idx(i,j)			j*n+i               // Collumn major order.
#define		Amat(i,j)			A[idx(i,j)]
#define		Bmat(i,j)			B[idx(i,j)]

// ======= End of Definitions

// Type definition of Vertex `object`
typedef struct Vertex {
	int id;																		// The initial id of the vertex.
	bool visited;															// TRUE/FALSE depends on weath has been visited during the BFS.
	int degree;                               // Holds the degree of the vertex.
	int* neighbors;                           // An array - a list that contains pointer to the neighbors.
} Vertex;


//! Performs the Reverse Cuthill–McKee Algorithm
/*!
	\param n			The number of verices in the graph G=G(A)																[scalar]
	\param V			Array of the vertices.                                                  [n-by-1]
	\param R			The array which contains the final order of the veritces								[n-by-1]
	\return 			-	
*/
void rcm ( const int n, Vertex V[], int R[] );

#endif /* __RCM_H__ */
