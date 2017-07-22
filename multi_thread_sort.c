#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>
#include "mergeSort.h"
#include "minHeap.h"

#define NUMS_SIZE 10 //1M
#define THREAD_NUM 4

typedef struct interval_tag
{
    int begin;
    int end;
}interval_t;

pthread_barrier_t b;
int nums[NUMS_SIZE];
int temp[NUMS_SIZE];
interval_t seg[THREAD_NUM];

void mergeN()
{
    heap_node_t *minHeap[THREAD_NUM];
    int heap_size = THREAD_NUM;

    for (int i = 0; i < heap_size; i++)
    {
        minHeap[i] = (heap_node_t *)malloc(sizeof(heap_node_t));
        minHeap[i]->num = nums[seg[i].begin];
        minHeap[i]->segNo = i;
        minHeap[i]->index = seg[i].begin;
    }

    make_heap(minHeap, minHeap + heap_size);//[ )
    int j = 0;
    while(heap_size)
    {
        pop_heap(minHeap, minHeap + heap_size);
        temp[j++] = minHeap[heap_size - 1]->num;
        
        if (++minHeap[heap_size - 1]->index <= seg[minHeap[heap_size - 1]->segNo].end)
        {
            minHeap[heap_size - 1]->num = nums[minHeap[heap_size - 1]->index];
            push_heap(minHeap, minHeap + heap_size);
        }
        else
            heap_size--;
    }
}

void *sort_thread_func(void *arg)
{
    interval_t *interval = (interval_t *)arg;
    mergeSort(nums, interval->begin, interval->end, temp);

    pthread_barrier_wait(&b);
    pthread_exit(NULL);
}

void err_exit(const char *errmsg)
{
    perror(errmsg);
    exit(-1);
}

int main(int argc, char **argv)
{
    FILE *fp;
    if ((fp = fopen("data.txt", "r")) ==  NULL)
        err_exit("fopen error\n");
        
    for (int i = 0; i < NUMS_SIZE; i++)
        fscanf(fp, "%d", &nums[i]);
    fclose(fp);

    for (int i = 0; i < THREAD_NUM; i++)//[ ]
    {
        seg[i].begin = i * (NUMS_SIZE / THREAD_NUM);
        seg[i].end = (i + 1 < THREAD_NUM) ? (i + 1) * (NUMS_SIZE / THREAD_NUM) - 1 : NUMS_SIZE - 1;
    }

    pthread_t tid;
    struct timeval start, end;
    long long startusec, endusec;
    double elapsed;

    gettimeofday(&start, NULL);
    pthread_barrier_init(&b, NULL, THREAD_NUM + 1);
    for (int i = 0; i < THREAD_NUM; i++)
    {
        int err = pthread_create(&tid, NULL, sort_thread_func, (void *)&seg[i]);
        if (err != 0)
            err_exit("pthread_create error\n");
    }
    pthread_barrier_wait(&b);
    mergeN();
	gettimeofday(&end, NULL);
	
	startusec = start.tv_sec * 1000000 + start.tv_usec;
	endusec = end.tv_sec * 1000000 + end.tv_usec;
	elapsed = (double)(endusec - startusec) / 1000000.0;
	printf("sort took %.4f seconds\n", elapsed);
	
     for (int i = 0; i < NUMS_SIZE; i++)
         printf("%d\n", temp[i]);
}
