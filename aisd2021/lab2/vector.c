#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "data.h"
#include "vector.h"
//#include "common.h"

queue_v* init_vector(queue_v* q, int g){
	q->sts = g;
	q->st = (stand_v *)malloc(g * sizeof(stand_v));
	for (int i = 0; i < g; i ++){
		q->st[i].pass = (pas_v *)malloc(sizeof(pas_v) * 2);
		q->st[i].lengh = 0;
	}
	return q;
}

int push_vector(queue_v* q, dpas* pq, int time){
	int k = 100000, r;
        for (int l = 0; l < q->sts; l++){
			if (q->st[l].lengh != 0) {
				if ((q->st[l].time/q->st[l].lengh) < k){
					k = q->st[l].time/q->st[l].lengh;
					r = l;
				}
			} else if (q->st[l].lengh == 0){
				r = l;
				k = 0;
				break;
			}
        }
	if (q->st[r].lengh == 2){
		printf("Sorry, queue is full(\n");
		return 1;
	}
	if (q->st[r].lengh == 0) q->st[r].time = pq->ta;
	q->st[r].pass[q->st[r].lengh].id = pq->id;
	q->st[r].pass[q->st[r].lengh].ta = pq->ta;
	q->st[r].pass[q->st[r].lengh].ts = pq->ts;
	q->st[r].lengh ++;
	read_vector(q, time);
	return 0;
}

void pop_vector(queue_v* q, int time){
	for (int r = 0; r < q->sts; r ++){
		while (q->st[r].lengh > 0 && q->st[r].time + q->st[r].pass[0].ts == time){
			q->st[r].time = time;
			for (int i = 0; i < q->st[r].lengh - 1; i ++){
				q->st[r].pass[i] = q->st[r].pass[i + 1];
			}
			
			q->st[r].lengh --;
			read_vector(q, time);
		}
        }
}

void read_vector(queue_v* q, int time){
	printf("Time is %d.\n", time);
	for (int i = 0; i < q->sts; i ++){
		printf("Stand %d: ", i + 1);
		if (q->st[i].lengh > 0){
			for (int j = 0; j < q->st[i].lengh; j ++){
				printf("%s ", q->st[i].pass[j].id);
			}	
		}
		printf("\n");
	}
	printf("\n");
}

void delete_vector(queue_v* q){
	for (int i = 0; i < q->sts; i ++){
		free(q->st[i].pass);
	}
	free(q->st);
	free(q);
}

int check_vector(queue_v* q){
	for (int v = 0; v < q->sts; v ++){
			if (q->st[v].lengh > 0){
				return 1;
			}
	}
	return 0;
}