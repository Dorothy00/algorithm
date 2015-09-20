#!/usr/bin/python
import sys
from InputData import input_sort_data

def bubble_sort(data):
	""" sort list use bubble sort
		time complexity is (n2)
	"""
	if type(data) != list:
		print 'Paramter need to be a list';
		sys.exit();
	
	if len(data) == 0:
		print 'The list should not be empty.';
		sys.exit();

	for i in range(0,len(data) - 1):
		for j in range(1,len(data)-i):
			if data[j] < data[j - 1]:   
				tmp = data[j];
				data[j] = data[j - 1];
				data[j - 1] = tmp;
	return data;

if __name__ == '__main__':
	data = input_sort_data();
	print bubble_sort(data);

