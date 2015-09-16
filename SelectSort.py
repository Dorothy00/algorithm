#!/usr/bin/python
import os
from InputData import input_sort_data

def select_sort(data):
	if type(data) != list:
		print 'Paramter need to be a list';
		os._exit(0);
	
	if len(data) == 0:
		print 'The list should not be empty.';
		os._exit(0);
	
	print 'Unsorted data is: ',data;
	for i in range(0,len(data)-1):
		min_data = data[i];
		for j in range(i,len(data)):
			if min_data > data[j]:
				min_data = data[j];
				data[j] = data[i];
				data[i] = min_data;
	
	print 'Sorted data is: ',data;

if __name__ == '__main__':
	data = input_sort_data();
	select_sort(data);
