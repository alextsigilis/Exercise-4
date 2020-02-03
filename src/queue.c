//! rcm.c
/*!
	\author Αλέξανδρος Τσιγγίλης.
	
	\date		2 February 2020.

	\short 	Implementation for the Queue defined in inc/rcm.h

	\long	-

*/
#include <stdlib.h>
#include "rcm.h"

//! Initializes the Queue.
Queue* init(int size) {
	Queue *q = malloc(sizeof(Queue));
	q->buffer = malloc( size * sizeof(Vertex*) );
	q->head = 0;
	q->tail = 0;
	q->n = size;
	return q;
}

//! Adds an element to the queue.
void push( Queue *Q, Vertex* key ) {
	if( Q->tail < Q->n ) {
		Q->buffer[Q->tail++] = key;
	}
}

//! Extracts the first element of the queue.
Vertex* pop( Queue *Q ) {
	if( Q->head < Q->tail ) {
		return Q->buffer[Q->head++];
	}	
	else {
		return  NULL;
	}
}

//! Checks if the Queue is empty.
int empty( Queue *Q ) {
	return (Q->head < Q->tail)? FALSE : TRUE;
}

