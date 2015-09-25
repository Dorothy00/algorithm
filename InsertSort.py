#!/usr/bin/python
import os
from InputData import input_sort_data

def insert_sort(data):
	""" sort list use insert sort
		time complexity is (n2)
	"""
	if type(data) != list:
		print 'Paramter need to be a list'
		os._exit(0)
	
	if len(data) == 0:
		print 'The list should not be empty.'
		os._exit(0)
			
	for j in range(1,len(data)):
		key = data[j]
		i = j - 1
		while i >= 0 and data[i] > key:
			data[i + 1] = data[i]
			i = i - 1 
		data[i + 1] = key
	return data

def insert(data,n):
	if n > len(data):
		print 'Insert invalid.'
		os._exit(0)

	if len(data) == 1:
		return data

	j = n - 2
	key = data[n - 1]
	while j >= 0 and data[j] > key:
		data[j + 1] = data[j]
		j -= 1
	data[j + 1] = key
	return data

def insert_sort_recursive(data,n):
	""" recursive version of insert sort
		best time complexity is (n)
		worst time complexity is (n2)
	"""
	if type(data) != list:
		print 'Parameter should be a list.'
		os._exit(0)
	if len(data) == 0:
		print 'The list should not be empty.'
		os._exit(0)
	
	if n > 1:
		insert_sort_recursive(data,n-1)
		print 'data',data
		return insert(data,n)
	else:
		return data

def find_insert_index(data,high,target):
	low = 0
	index = (low + high) / 2
	while low < high:
		if data[index] < target:
			low = index + 1
		else:
			high = index - 1
		index = (low + high) /2
	if data[index] < target: #should not be <= important!
		index += 1
	return index

def insert_binary_sort(data):
	for i in range(1,len(data)):
		index = find_insert_index(data,i,data[i])
		key = data[i]
		j = i
		while j >= index:
			print j
			data[j] = data[j - 1]
			j -= 1
		data[index] = key
	return data


if __name__ == '__main__':
	data = input_sort_data()
	#print insert_sort(data)
	print insert_sort_recursive(data,4)
	#print insert_binary_sort(data)
	

