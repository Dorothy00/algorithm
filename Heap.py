#!/usr/bin/python
import sys
from InputData import input_sort_data  

def max_heapify(A,heap_size,i):
	if type(A) != list:
		print 'Paramter need to be a list'
		sys.exit()
	
	if heap_size == 0:
		print 'The list should not be empty.'
		sys.exit()

	if i >= heap_size:
		print 'Index i should be in list A'
		sys.exit()
		
	l = left(i) 
	r = right(i) 

	if l < heap_size and A[i] < A[l]:
		largest = l
	else:
		largest = i
	if r < heap_size and A[largest] < A[r]:
		largest = r
	
	if largest != i:
		tmp = A[i]
		A[i] = A[largest]
		A[largest] = tmp
		max_heapify(A,heap_size,largest)

def max_heapify_iterator(A,heap_size,i):
	if type(A) != list:
		print 'Paramter need to be a list'
		sys.exit()
	
	if heap_size == 0:
		print 'The list should not be empty.'
		sys.exit()

	if i >= heap_size:
		print 'Index i should be in list A'
		sys.exit()
		
	l = left(i)
	r = right(i)

	while l < heap_size:
		if A[l] > A[i]:
			largest = l
		else:
			largest = i
		if A[r] > A[largest]:
			largest = r

		if largest == i:
			break
		else:
			tmp = A[i]
			A[i] = A[largest]
			A[largest] = tmp
			i = largest
			l = left(i)
			r = right(i)

def build_max_heap(A):
	if len(A) <= 1:
		return

	for i in range(len(A)/2 - 1,-1,-1):
		max_heapify(A,len(A),i)

def heap_sort(A):
	if len(A) <= 1:
		return

	build_max_heap(A)
	for i in range(len(A) - 1,0,-1): # i from len(A) - 1 to 1
		tmp = A[i]
		A[i] = A[0]
		A[0] = tmp
		max_heapify(A,i,0)

def heap_extract_max(A):
	if len(A) < 1:
		print 'heap underflow'
		sys.exit()
	if len(A) == 1:
		return A[0]

	h_max = A[0]
	A[0] = A[len(A) - 1]
	max_heapify(A,len(A) - 1,0)
	return h_max

def heap_increase_key(A,i,key):
	if type(A) != list:
		print 'Paramter need to be a list'
		sys.exit()
	if i < 0 or i > len(A) - 1:
		print 'Index i is invalid.'
		sys.exit()
	if key < A[i]:
		print 'new key is smaller than current key.'
		sys.exit()
	
	while i > 0 and A[parent(i)] < key:
		A[i] = A[parent(i)]
		i = parent(i)
	A[i] = key

def max_heap_insert(A,key):
	if type(A) != list:
		print 'Paramter need to be a list'
		sys.exit()

	A.append(key-1)
	heap_increase_key(A,len(A)-1,key)

def left(i):
	return (i << 1) + 1

def right(i):
	return (i << 1) + 2

def parent(i):
	return (i - 1) >> 1

if __name__ == '__main__':
	A = input_sort_data()
	#max_heapify(A,1)
	#build_max_heap(A)
	#heap_sort(A)
	#print 'max ', heap_extract_max(A)
	#heap_increase_key(A,8,15)
	max_heap_insert(A,10)
	print A
