#!/usr/bin/python
import sys
from InputData import input_sort_data;

def binary_search(data,target):
	""" binary search
		time complexity is: (lgn)
	"""
	if type(data) != list:
		print 'Paramter need to be a list';
		sys.exit();
	
	if len(data) == 0:
		print 'The list should not be empty.';
		sys.exit();

	length = len(data);
	low = 0;
	high = length - 1;
	mid = (low + high) / 2;
	while low <= high:
		if data[mid] < target:
			low = mid + 1;
			mid = (low + high) / 2;
		elif data[mid] > target:
			high = mid - 1;
			mid = (low + high) / 2;
		else:
			return mid;

def binary_search_recursive(data,low,high,target):
	""" recursive version of binary search
		time complexity is: (lgn)
	"""
	if type(data) != list:
		print 'Paramter need to be a list';
		sys.exit();
	
	if len(data) == 0:
		print 'The list should not be empty.';
		sys.exit();
	
	mid = (low + high) / 2;
	if data[mid] < target:
		low = mid + 1;
   		return binary_search_recursive(data[low:],target);
	elif data[mid] > target:
		high = mid - 1;
		return binary_search_recursive(data[:high],target);
	else:
		return mid;
	

if __name__ == '__main__':
	data = input_sort_data();
    #	print binary_search_recursive(data,0,4,5);
	binary_search(data,5);

