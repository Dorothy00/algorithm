#include <stdio.h>

typedef struct
{
	int* elements;
	int d;   // d heap
	int heap_size; // length of heap
	int length;    // length of elements
} heap_t;

void max_heapify(heap_t*, int);
int child(int, int, int);
int parent(int, int);

int main()
{
	int items[] = {16,4,10,14,7,9,3,2,8,1};
	heap_t heap = {
		items,
		2,
		10,
		10
	};
	max_heapify(&heap, 1);
	for(int i = 0; i < heap.heap_size; i++)
	{
		printf("%d, %d ",i,heap.elements[i]);
	}

	return 0;
}

void max_heapify(heap_t* heap, int i)
{
	int largest = i;
	for(int k = 0; k < heap->heap_size; k ++)
	{
		int ch = child(heap->d, k, i);
		if(ch < heap->heap_size && heap->elements[largest] < heap->elements[ch])
		{
			largest = ch;
		}
	}
	
	if(largest != i)
	{
		int tmp = heap->elements[i];
		heap->elements[i] = heap->elements[largest];
		heap->elements[largest] = tmp;
		max_heapify(heap, largest);
	}
}

void build_max_heap(heap_t* heap)
{
	if(heap->length == 0)
	{
		printf("heap is empty.");
		exit(0);
	}


}

int heap_extract_max(heap_t* heap)
{
	
}

int child(int d, int c, int parent)
{
	return d * parent + c + 1;
}

int parent(int d, int i)
{
	return (i - 1) / d;
}
