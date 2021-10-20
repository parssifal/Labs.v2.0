#include "common.h"
#include "data.h"

#include <stdlib.h>

#ifdef FLAG
	#include "list.h"
#else
	#include "vector.h"
#endif

void pop_queue(CONTEINER* q, int time){
	#ifdef FLAG
		pop_list(&q->cont, time);
	#else 
		pop_vector(&q->cont, time);
	#endif
}

void push_queue(CONTEINER* q, dpas* pq, int time){
	#ifdef FLAG
		push_list(&q->cont, pq, time);
	#else 
		push_vector(&q->cont, pq, time);
	#endif
}

void delete_queue(CONTEINER* q){
	#ifdef FLAG
		delete_list(&q->cont);
	#else
		delete_vector(&q->cont);
	#endif
}

int check_queue(CONTEINER* q){
	int z;
	#ifdef FLAG
		z = check_list(&q->cont);
	#else 
		z = check_vector(&q->cont);
	#endif
	return z;
}


CONTEINER* init_queue(CONTEINER* q, int g){
	q = (CONTEINER *)calloc(1, sizeof(CONTEINER));
	#ifdef FLAG
		q->cont = init_list(&q->cont, g);
	#else 
		q->cont = init_vector(&q->cont, g);
	#endif
	return q;
}

void delete_cont(CONTEINER* q){
	free(q);
}