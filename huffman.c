#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct Node
{
    char c;
    int freq;
    struct Node *lchild;
    struct Node *rchild;
}MiniHeapNode;

typedef struct heap
{
    int size;
    int capacity;
    MiniHeapNode **elements;
}MiniHeap;

MiniHeapNode* BuildHuffmanTree(char data[], int freqs[], int size);
MiniHeap* CreateHeap(int capacity);
MiniHeap* CreateMiniHeap(char data[], int freqs[], int size, int capacity);
MiniHeapNode* NewHeapNode(char data, int freq);
void BuildMiniHeap(MiniHeap *heap);
void MiniHeapify(MiniHeap *heap, int i);
void SwapMiniHeapNode(MiniHeapNode **a, MiniHeapNode **b);
MiniHeapNode* ExtractMini(MiniHeap *heap);
void IncreaseKey(MiniHeap *heap, int i, int key);
void HeapInsert(MiniHeap *heap, MiniHeapNode *node);
bool IsLeaf(MiniHeapNode *node);
void PrintArr(int arr[], int n);
void PrintHuffmanCode(MiniHeapNode *root, int arr[], int i);
int parent(int i);
int left(int i);
int right(int i);

int main()
{
    char data[6] = {'f', 'e', 'c', 'b', 'd', 'a'};
    int freqs[6] = {5, 9, 12, 13, 16, 45};
    MiniHeapNode* node = BuildHuffmanTree(data, freqs, 6);
    int arr[6];
    PrintHuffmanCode(node, arr, 0);
    
    return 0;
}

MiniHeapNode* BuildHuffmanTree(char data[], int freqs[], int size)
{
    MiniHeap* huffHeap = CreateMiniHeap(data, freqs, size, size);
    for(int i = 0; i < size - 1; i++)
    {
        MiniHeapNode *node = NewHeapNode('$', 0);
        node -> lchild = ExtractMini(huffHeap);
        node -> rchild = ExtractMini(huffHeap);
        node -> freq = node -> lchild -> freq + node -> rchild -> freq;
        HeapInsert(huffHeap, node);
    }
    return ExtractMini(huffHeap);
}

MiniHeap* CreateHeap(int capacity)
{
    MiniHeap *heap = (MiniHeap*)malloc(sizeof(MiniHeap));
    heap -> capacity = capacity;
    heap -> size = 0;
    MiniHeapNode ** elements = (MiniHeapNode**)malloc(sizeof(MiniHeapNode*) * capacity);
    heap -> elements = elements;
    return heap;
}

MiniHeap* CreateMiniHeap(char data[], int freqs[], int size, int capacity)
{
    MiniHeap *heap = CreateHeap(capacity);
    heap -> size = size;
    for(int i = 0; i < size; i++)
    {
        MiniHeapNode *node = NewHeapNode(data[i], freqs[i]);
        heap -> elements[i] = node;
    }
    BuildMiniHeap(heap);
    return heap;
}

MiniHeapNode* NewHeapNode(char data, int freq)
{
    MiniHeapNode *node = (MiniHeapNode*) malloc(sizeof(MiniHeapNode));
    node -> c = data;
    node -> freq = freq;
    node -> rchild = NULL;
    node -> lchild = NULL;
    return node;
}

void BuildMiniHeap(MiniHeap *heap)
{
    int size = heap -> size;
    for(int i = (size - 1) / 2; i >=0; i--)
    {
        MiniHeapify(heap, i);
    }
}

void MiniHeapify(MiniHeap *heap, int i)
{
    int l = left(i);
    int r = right(i);
    int least = i;
    if(l < heap -> size && heap->elements[i] -> freq > heap->elements[l] -> freq)
    {
        least = l;
    }
    if(r < heap -> size && heap->elements[least] -> freq > heap->elements[r] -> freq)
    {
        least = r;
    }
    if(least != i)
    {
        SwapMiniHeapNode(&heap -> elements[i], &heap -> elements[least]);
        MiniHeapify(heap, least);
    }
}

void SwapMiniHeapNode(MiniHeapNode **a, MiniHeapNode **b)
{
    MiniHeapNode *t = *a;
    *a = *b;
    *b = t;
}

MiniHeapNode* ExtractMini(MiniHeap *heap)
{
    int size = heap -> size;
    if(size < 1)
    {
        printf("heap underflow.");
        exit(0);
    }
    MiniHeapNode* min = heap -> elements[0];
    heap -> elements[0] = heap -> elements[size - 1];
    heap -> size --;
    MiniHeapify(heap, 0);
    return min;
}

void IncreaseKey(MiniHeap *heap, int i, int key)
{
    if(i >= heap -> size || i < 0)
    {
        return;
    }
    if(heap -> elements[i] -> freq > key)
    {
        printf("new key is smaller than current key.");
        return;
    }
    
    heap -> elements[i] -> freq = key;
    while(i > 0 && heap -> elements[parent(i)] -> freq > heap -> elements[i] -> freq)
    {
        SwapMiniHeapNode(&heap -> elements[i], &heap -> elements[parent(i)]);
        i = parent(i);
    }
}

void HeapInsert(MiniHeap *heap, MiniHeapNode *node)
{
    heap -> size ++;
    int freq = node -> freq;
    node -> freq --;
    heap -> elements[heap -> size - 1] = node;
    IncreaseKey(heap, heap -> size - 1, freq);
}

void PrintHuffmanCode(MiniHeapNode *root, int arr[], int i)
{
    if(root && root -> lchild)
    {
        arr[i] = 0;
        PrintHuffmanCode(root -> lchild, arr, i + 1);
    }
    if(root && root -> rchild)
    {
        arr[i] = 1;
        PrintHuffmanCode(root -> rchild, arr, i + 1);
    }
    if(IsLeaf(root))
    {
        printf("%c ", root -> c);
        PrintArr(arr, i);
        printf("\n");
    }
}

void PrintArr(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
    }
}

bool IsLeaf(MiniHeapNode *node)
{
    return !(node -> lchild) && !(node -> rchild);
}

int parent(int i)
{
    return (i - 1) / 2;
}

int left(int i)
{
    return i * 2 + 1;
}

int right(int i)
{
    return i * 2 + 2;
}
