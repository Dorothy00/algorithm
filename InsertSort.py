#!/usr/bin/python
import os
from InputData import input_sort_data

def insert_sort(data):
	if type(data) != list:
		print 'Paramter need to be a list';
		os._exit(0);
	
	if len(data) == 0:
		print 'The list should not be empty.';
		os._exit(0);
			
	print 'unsorted data is: ',data;
	for j in range(1,len(data)):
		key = data[j];
		i = j - 1;
		while i >= 0 and data[i] > key:
			data[i + 1] = data[i];
			i = i - 1; 
		data[i + 1] = key;

	print 'sorted data is : ',data;
		


if __name__ == '__main__':
	data = input_sort_data();
	insert_sort(data);


