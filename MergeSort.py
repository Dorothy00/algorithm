#!/usr/bin/python
import sys
from InputData import input_sort_data;

def merge_sort(data):
	""" sort a list of data use merge sort
		time complexity is (nlgn)
	"""
	if type(data)!=list:
		print 'Parameter of data should be a list.';
		sys.exit();
	length = len(data);
	if length > 1:
		q = length/2;
		left= merge_sort(data[:q]);
		right = merge_sort(data[q:]);
		return merge(left,right);
	else:
		return data;

def merge(left,right):
	if type(left)!=list or type(right)!=list:
		print 'Parameter should be list.';
		sys.exit();

	data = [];
	n_left = len(left);
	n_right = len(right);
	
	i = 0;
	j = 0;
	while i < n_left and j < n_right:
		if left[i] <= right[j]:
			data.append(left[i]);
			i = i + 1;
		else:
			data.append(right[j]);
			j = j + 1;
	
	while j < n_right:
		data.append(right[j]);
		j = j + 1;
	while i < n_left:
		data.append(left[i]);
		i = i + 1;
	return data;
	
if __name__ == '__main__':
	data = input_sort_data();
	print merge_sort(data);

