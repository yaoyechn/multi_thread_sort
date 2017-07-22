#ifndef MINHEAP_H_
#define MINHEAP_H_

typedef struct heap_node_tag
{
    int num;
    int segNo;
    int index;
}heap_node_t;

static void min_heap_sink(heap_node_t **begin, heap_node_t **end, int i);
static void min_heap_swim(heap_node_t **begin, heap_node_t **end, int i);

extern void make_heap(heap_node_t **begin, heap_node_t **end);
extern void push_heap(heap_node_t **begin, heap_node_t **end);
extern void pop_heap(heap_node_t **begin, heap_node_t **end);

#endif