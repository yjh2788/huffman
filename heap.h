#pragma once
#include <stdio.h>
#include<stdlib.h>
#include"list.h"
#define MAX 2000


//typedef struct {
//    char data;
//    int num;
//}element;

typedef struct {
    element heap[MAX];
    int heap_size;
}heap;

heap* createheap()
{
    heap* h = (heap*)malloc(sizeof(heap));
    h->heap_size = 0;
    return h;
}

void insertheap(heap* h, element *item)
{
    int i;
    h->heap_size = h->heap_size + 1;
    i = h->heap_size;
    while ((i != 1) && (item->num < h->heap[i / 2].num))
    {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = *item;
    //h->heap[i].num = item.num;
    //h->heap[i].data = item.data;
}

inline element deletHeap(heap* h)
{
    int parent, child,n;
    element item, temp;
    n = h->heap_size;
    item = h->heap[1];
    temp = h->heap[h->heap_size];
    h->heap_size = h->heap_size - 1;
    parent = 1;
    child = 2;
    while (child <= h->heap_size)
    {
        if ((child < h->heap_size) && (h->heap[child].num > h->heap[child + 1].num))
            child++;

        if (temp.num <= h->heap[child].num) break;
        else {
            h->heap[parent] = h->heap[child];
            parent = child;
            child = child * 2;
        }
    }
    h->heap[parent]= temp;
    h->heap[h->heap_size+1].data = NULL;
    h->heap[h->heap_size+1].num = 0;
    return item;
}
/*
element deletHeap2(heap* h)
{
    element item, tmp;
    int parent=1, child=2,i;
    item = h->heap[h->heap_size];
    h->heap[1] = item;
    while ()
    {

    }

}*/


void printheap(heap* h)
{
    int i;
    printf("heap: ");
    for (i = 1; i <= h->heap_size; i++)
    {
        printf("[%d]", h->heap[i].num);
    }
}

