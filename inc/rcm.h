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
	int degree;															  // The degree of the vertex.
	struct Vertex** neighbors;								// An array that contain all of it's neighbors.
	int visited;															// TRUE/FALSE depends on weath has been visited during the BFS.
} Vertex;


//! Performs the Reverse Cuthill–McKee Algorithm
/*!
	\param n			The number of verices in the graph G=G(A)																[scalar]
	\param V			Array of the vertices.                                                  [n-by-1]
	\param R			The array which contains the final order of the veritces								[n-by-1]
	\return 			-	
*/
void rcm (const int n, Vertex V[], int R[] );

// ======== QUEUE IMPLEMENTATION
// Type definition of Queue
typedef struct Queue {
	Vertex** buffer;						// Array that stores the elements of the queue.
	int head;										// The location of the first element of the queue.
	int tail;										// The location of the last element of the queue.
	int n;											// The maximum capacity of the queue.
} Queue;

//! Initializes the Queue.
/*!
	\param size			The maximum size of the queue				[scalar]
	\return 				Pointer to the Queue								[pointer]
*/
static inline Queue* init(int size) {
	Queue *q = malloc(sizeof(Queue));
	q->buffer = malloc( size * sizeof(Vertex*) );
	q->head = 0;
	q->tail = 0;
	q->n = size;
	return q;
}


//! Adds an element to the queue.
/*!
	\param Q				The queue into which the element will be inserted.			[pointer]
	\param key			The element to be inserted.															[scalar]
	\return 				-
*/
static inline void enqueue( Queue *Q, Vertex* key ) {
	if( Q->tail < Q->n ) {
		Q->buffer[Q->tail++] = key;
	}
}

//! Extracts the first element of the queue.
/*!
	\param Q 		The queue from which to extract the element		[pointer]
	\return			The The element that was extracted						[scalar]
*/
static inline Vertex* dequeue( Queue *Q ) {
	if( Q->head < Q->tail ) {
		return Q->buffer[Q->head++];
	}	
	else {
		return  NULL;
	}
}

//! Checks if the Queue is empty.
/*
	\param Q		The Queue to be checked								[pointer]
	\return			TRUE if is empty, FALSE otherwise			[boolean]
*/
static inline bool empty( Queue *Q ) {
	return (Q->head < Q->tail)? false : true;
}

#endif /* __RCM_H__ */
