#include <stdio.h>

#include "data.h"
#include "common.h"

int main(int argc, char const* argv[]){
	int g;
	data* l = new_data(l);
	dpas* pq = l->first;
	printf("Enter number of stands: ");
	scanf("%d", &g);
	if (g == 0) return 1;
	CONTEINER* q = init_queue(q, g); 
	int time = 1, z = 0;
    	while(pq || z){
		if (time > 1){
			pop_queue(q, time);
		}
		while (pq && pq->ta == time){
			push_queue(q, pq, time);
			pq = pq->next;
		}
		z = check_queue(q);
		time ++;
	}
	delete_data(l);
	delete_queue(q);
	printf("Good bye\n");
	return 0;
}
