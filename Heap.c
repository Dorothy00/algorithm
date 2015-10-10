#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int* elements;
	int heap_size; // length of heap
	int length;    // length of elements
} heap_t;

void max_heapify(heap_t*, int);
void build_max_heap(heap_t*);
int heap_extract_max(heap_t*);
void heap_sort(heap_t*);
void heap_increase_key(heap_t*, int, int);
void heap_insert(heap_t*, int);
int left(int);
int right(int);
int parent(int);

int main()
{
	int items[] = {16,4,10,14,7,9,3,2,8,1};
	heap_t heap = {
		items,
		10,
		10
	};
	max_heapify(&heap, 1);
	for(int i = 0; i < heap.heap_size; i++)
	{
		printf("%d ",heap.elements[i]);
	}
	printf("\n");
	int items2[] = {4,1,3,2,16,9,10,14,8,7};
	heap_t heap2 = {
		items2,
		10,
		10
	};
	build_max_heap(&heap2);
	for(int i = 0; i < heap2.heap_size; i++)
	{
		printf("%d ",heap2.elements[i]);
	}
	heap_extract_max(&heap);
	printf("\n");
	for(int i = 0; i < heap.heap_size; i++)
	{
		printf("%d ",heap.elements[i]);
	}
	printf("\n");
	heap_sort(&heap2);
	for(int i = 0; i < heap2.length; i++)
	{
		printf("%d ",heap2.elements[i]);
	}
	printf("\n");
	int items3[] = {4,1,3,2,16,9,10,14,8,7};
	heap_t heap3 = {
		items3,
		10,
		10
	};
	build_max_heap(&heap3);
	heap_increase_key(&heap3, 8, 15);
	for(int i = 0; i < heap3.length; i++)
	{
		printf("%d ",heap3.elements[i]);
	}

	printf("start\n");
	int items4[] = {15,13,9,5,12,8,7,4,0,6,2,1};
	heap_t heap4 = {
		items4,
		12,
		12
	};
	heap_insert(&heap4,10);
	for(int i = 0; i < heap4.length; i++)
	{
		printf("%d ",heap4.elements[i]);
	}
	return 0;
}

void max_heapify(heap_t* heap, int i)
{
	int largest = i;
	int l = left(i);
	int r = right(i);
	if(l < heap->heap_size && heap->elements[i] < heap->elements[l])
	{
		largest = l;
	}
	if(r < heap->heap_size && heap->elements[largest] < heap->elements[r])
	{
		largest = r;
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
	for(int i = heap->heap_size / 2 - 1; i >= 0; i --)
	{
		max_heapify(heap,i);
	}
}

int heap_extract_max(heap_t* heap)
{
	if(heap->heap_size == 0)
	{
		printf("heap is empty.");
		exit(0);
	}
	int max = heap->elements[0];
	heap->elements[0] = heap->elements[heap->heap_size - 1];
	heap->heap_size = heap->heap_size - 1;
	max_heapify(heap, 0);
	return max;	
}

void heap_sort(heap_t* heap)
{
	if(heap->length < 2)
	{
		return;
	}
	int heap_size = heap->heap_size;
	for(int i = heap_size - 1; i > 0; i--)
	{
		int tmp = heap->elements[i];
		heap->elements[i] = heap->elements[0];
		heap->elements[0] = tmp;
		heap->heap_size --;
		max_heapify(heap,0);
	}
}

void heap_increase_key(heap_t* heap, int i, int key)
{
	if(i >= heap->heap_size)
	{
		printf("index underflow.");
		exit(0);
	}
	if(heap->elements[i] > key)
	{
		printf("key should smaller than current key.");
		exit(0);
	}
	while(i > 0 && heap->elements[parent(i)] < key)
	{
		heap->elements[i] = heap->elements[parent(i)];
		i = parent(i);
	}
	heap->elements[i] = key;
}

void heap_insert(heap_t* heap, int key)
{
	heap->heap_size ++;
	if(heap->heap_size > heap->length)
	{
		int* items = malloc(sizeof(int) * heap->heap_size); // 内存泄露，由于items不是全局的，不好释放
		for(int i = 0; i < heap->length; i++)
		{
			items[i] = heap->elements[i];
		}
		items[heap->heap_size - 1] = key - 1;
		heap->elements = items;
		heap->length ++;
	}
	heap_increase_key(heap, heap->heap_size - 1, key);
}

int left(int parent)
{
	return (parent << 1) + 1;
}

int right(int parent)
{
	return (parent << 1) + 2;
}

int parent(int child)
{
	return (child - 1) >> 1;
}
