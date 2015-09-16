#!/usr/bin/python
import re

/*
 *  @author Dorothy
 *	insert sort
 */
def insert_sort(data):
	if type(data) != list:
		print 'Paramter need to be a list';
		os.exit();
	
	if len(data) == 0:
		print 'The list should not be empty.';
		os.exit();
			
	print 'unsorted data is: ',data;
	for j in range(1,len(data)):
		key = data[j];
		i = j - 1;
		while i >= 0 and data[i] > key:
			data[i + 1] = data[i];
			i = i - 1; 
		data[i + 1] = key;

	print 'sorted data is : ',data;
		
def input_sort_data():
	print 'Please enter your data (q to quit):';
	data = [];
	input = raw_input();
	while input:
		if re.match('[+-]?\d+(\.\d+)?$',input):
			if input.isdigit():
				data.append(int(input));
			else:
				data.append(float(input));
		elif input != 'q':
			print 'Please enter a digit data (q to quit): ';
		else:
			break;
		input = raw_input();
	
	return data;


if __name__ == '__main__':
	data = input_sort_data();
	insert_sort(data);


