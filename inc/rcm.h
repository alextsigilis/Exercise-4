//! rcm.h
/*!
	\author Αλέξανδρος Τσιγγίλης
	
	\date		31 January 2020

	\short Headre file for implementation of the Reverse Cuthill-McKee Algorithm

	\long	-

*/
#ifndef __RCM_H__
#define __RCM_H__


// ======== DEFINITION OF MACROS
#define 	idx(i,j)			i*n+j
#define		Amat(i,j)			A[idx(i,j)]

// ======= End of Definitions


//! Performs the Reverse Cuthill–McKee Algorithm
/*!
	\param n			The number of verices in the graph G=G(A)																[scalar]
	\param A			The adjacency matrix of G (A is symetric and sparse).										[n-by-n]
	\param R			The array which contains the final order of the veritces								[n-by-1]
	\return 			-	
*/
void rcm (const size_t n, const double *A, unsigned int *R );

// ======== QUEUE IMPLEMENTATION
// Type definition of Queue
typedef struct Queue {
	unsigned int *buffer;						// Array that stores the elements of the queue.
	size_t head;										// The location of the first element of the queue.
	size_t tail;										// The location of the last element of the queue.
	size_t n;
} Queue;

//! Initializes the Queue.
/*!
	\param size			The maximum size of the queue				[scalar]
	\return 				Pointer to the Queue								[pointer]
*/
Queue* init(size_t size); 

//! Adds an element to the queue.
/*!
	\param Q				The queue into which the element will be inserted.			[pointer]
	\param key			The element to be inserted.															[scalar]
	\return 				-
*/
void push( Queue *Q, unsigned int key );

//! Extracts the first element of the queue.
/*!
	\param Q 		The queue from which to extract the element		[pointer]
	\return			The The element that was extracted						[scalar]
*/
int pop( Queue *Q );


#endif /* __RCM_H__ */
