#include <stdlib.h>
#include "rcm.h"

//! Initializes the Queue.
Queue* init(int size) {
	Queue *q = malloc(sizeof(Queue));
	q->buffer = malloc( size * sizeof(int) );
	q->head = 0;
	q->tail = 0;
	q->n = size;
	return q;
}

//! Adds an element to the queue.
void push( Queue *Q, int key ) {
	if( Q->tail < Q->n ) {
		Q->buffer[Q->tail++] = key;
	}
}

//! Extracts the first element of the queue.
int pop( Queue *Q ) {
	if( Q->head < Q->tail ) {
		return Q->buffer[Q->head++];
	}
	else {
		return -1;
	}
}
