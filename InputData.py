#!/usr/bin/python
import re

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
