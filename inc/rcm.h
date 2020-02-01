//! rcm.h
/*!
	\author Αλέξανδρος Τσιγγίλης
	
	\date		31 January 2020

	\short Headre file for implementation of the Reverse Cuthill-McKee Algorithm

	\long	-

*/
#ifndef __RCM_H__
#define __RCM_H__

#include <inttypes.h>

// ======== DEFINITION OF MACROS
#define		TRUE					1
#define		FALSE					0
#define 	idx(i,j)			j*n+i
#define		Amat(i,j)			A[idx(i,j)]
#define		Bmat(i,j)			B[idx(i,j)]
#define		empty(Q)			(Q->head == Q->tail)

// ======= End of Definitions

// Type definition of Vertex `object`
typedef struct Vertex {
	int id;																		// The initial id of the vertex.
	int degree;															  // The degree of the vertex.
	struct Vertex** neighbors;								// An array that contain all of it's neighbors.
	int visited;															// TRUE/FALSE depends on weath has been visited during the BFS.
} Vertex;


//! Performs the Reverse Cuthill–McKee Algorithm
/*!
	\param n			The number of verices in the graph G=G(A)																[scalar]
	\param A			The adjacency matrix of G (A is symetric and sparse).										[n-by-n]
	\param R			The array which contains the final order of the veritces								[n-by-1]
	\return 			-	
*/
void rcm (const int n, const double *A, int *R );

// ======== QUEUE IMPLEMENTATION
// Type definition of Queue
typedef struct Queue {
	Vertex** buffer;						// Array that stores the elements of the queue.
	int head;										// The location of the first element of the queue.
	int tail;										// The location of the last element of the queue.
	int n;
} Queue;

//! Initializes the Queue.
/*!
	\param size			The maximum size of the queue				[scalar]
	\return 				Pointer to the Queue								[pointer]
*/
Queue* init(int size); 


//! Adds an element to the queue.
/*!
	\param Q				The queue into which the element will be inserted.			[pointer]
	\param key			The element to be inserted.															[scalar]
	\return 				-
*/
void push( Queue *Q, Vertex* key );

//! Extracts the first element of the queue.
/*!
	\param Q 		The queue from which to extract the element		[pointer]
	\return			The The element that was extracted						[scalar]
*/
Vertex* pop( Queue *Q );


#endif /* __RCM_H__ */
