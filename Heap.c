#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
	printf("----------------------Heap---------------------\n");
	printf("\t0. max_heapify(heap_t*, int)\n");
	printf("\t1. build_max_heap(heap_t*)\n");
	printf("\t2. heap_extract_max(heap_t*)\n");
	printf("\t3. heap_sort(heap_t*)\n");
	printf("\t4. heap_increase_key(heap_t*, int, int)\n");
	printf("\t5. heap_insert(heap_t*, int)\n");
	printf("Please select (-1 to quit): ");
	int select;
	scanf("%d", &select);
	if(select == -1)
	{
		exit(0);
	}
	while(select != -1)
	{
		heap_t heap;
		int length;
		int heap_size;
		printf("Now create a heap\n");
		printf("Enter heap length: ");
		scanf("%d",&length);
		printf("Enter heap size: ");
		scanf("%d",&heap_size);
		printf("Enter elements: \n");
		int items[length];
		for(int i = 0; i < heap_size; i++)
		{
			scanf("%d",&items[i]); 
		}
		heap.length = length;
		heap.heap_size = heap_size;
		heap.elements = items;
		
		switch(select)
		{
			case 0:
				printf("Please enter index you want to heapify: ");
				int index;
				scanf("%d",&index);
				max_heapify(&heap, index);
				break;
			case 1:
				build_max_heap(&heap);
				break;
			case 2:
				build_max_heap(&heap);
				heap_extract_max(&heap);
				break;
			case 3:
				build_max_heap(&heap);
				heap_sort(&heap);
				break;
			case 4:
				build_max_heap(&heap);
				printf("Please enter index you want to increase: ");
				int i = getchar();
				printf("Please enter key: ");
				int key = getchar();
				heap_increase_key(&heap, i, key);
				break;
			case 5:
				build_max_heap(&heap);
				printf("Please enter elements you want to insert: ");
				int element = getchar();
				heap_insert(&heap,element);
				break;
			default:
				printf("Num error.");
		}
		for(int i = 0; i < heap.length; i++)
		{
			printf("%d ", heap.elements[i]);
		}

		printf("\n\n");
		printf("\t0. max_heapify(heap_t*, int)\n");
		printf("\t1. build_max_heap(heap_t*)\n");
		printf("\t2. heap_extract_max(heap_t*)\n");
		printf("\t3. heap_sort(heap_t*)\n");
		printf("\t4. heap_increase_key(heap_t*, int, int)\n");
		printf("\t5. heap_insert(heap_t*, int)\n");
		printf("Please select (-1 to quit): ");
		scanf("%d",&select);
	}
	printf("----------------------End---------------------\n");

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
