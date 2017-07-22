#include "minHeap.h"

//leftChild = 2 * i + 1, rightChild = 2 * i + 2;
//parent = (i - 1) / 2;
static void min_heap_sink(heap_node_t **begin, heap_node_t **end, int i)
{
    int child;
    heap_node_t *initialNode = begin[i];
    for (; 2 * i + 1 < end - begin; i = child)
    {
        child = 2 * i + 1;
        if (child + 1 < end - begin && begin[child]->num > begin[child + 1]->num)//取子节点中最小的
            child = child + 1;
        
        if (initialNode->num > begin[child]->num)
            begin[i] = begin[child];
        else
            break;
    }
    begin[i] = initialNode;
}

static void min_heap_swim(heap_node_t **begin, heap_node_t **end, int i)
{
    heap_node_t *initialNode = begin[i];
    for (; i > 0 && initialNode->num < begin[(i - 1) / 2]->num; i = (i - 1) / 2)
        begin[i] = begin[(i - 1) / 2];
        
    begin[i] = initialNode;
}

void make_heap(heap_node_t **begin, heap_node_t **end)
{
    for (int i = (end - begin) / 2 - 1; i >= 0; i--)
    {
        min_heap_sink(begin, end, i);
    }

}

void push_heap(heap_node_t **begin, heap_node_t **end)
{
    min_heap_swim(begin, end, end - begin - 1);
}

void pop_heap(heap_node_t **begin, heap_node_t **end)
{
    heap_node_t *tempNode = *begin;
    *begin = *(end - 1);
    *(end - 1) = tempNode;
    min_heap_sink(begin, end - 1, 0);
}