#!/usr/bin/python
import sys
from InputData import input_sort_data
from math import ceil

def find_maxmum_subarray(data,low,high):
	""" find maxmun subarray in a given array
		time complexity is O(nlgn)
	"""
	if low == high:
		return (low,high,data[low])
	else:
		(left_low,left_high,left_sum) = find_maxmum_subarray(data,low,(low + high) / 2)
		(right_low,right_high,right_sum) = find_maxmum_subarray(data,int(ceil((low + high) / 2.0)),high)
		(cross_low,cross_high,cross_sum) = find_max_cross_subarray(data,low,(low + high) / 2,high)

		if left_sum >= right_sum and left_sum >= cross_sum:
			return (left_low,left_high,left_sum)
		elif right_sum >= left_sum and right_sum >= cross_sum:
			return (right_low,right_high,right_sum)
		else:
			return (cross_low,cross_high,cross_sum)

def find_maxmum_subarray_linear(data,low,high):
	max_sum = -sys.maxint - 1
	total = 0
	m_low = 0
	m_high = 0
	for i in range(low, high+1):
		total += data[i]
		if total > max_sum:
			max_sum = total
			m_high = i
		if total < 0:
			total = 0

	return (m_low,m_high,max_sum)

def find_maxmum_subarray_violence(data,low,high):
	(max_low,max_high,max_sum) = (low,low,data[low])
	for i in range(low + 1,high):   # from index 1 to len - 2 
		(cross_low,cross_high,cross_sum) = find_max_cross_subarray(data,low,i,high)
		if max_sum < cross_sum:
			(max_low,max_high,max_sum) = (cross_low,cross_high,cross_sum)
	
	return (max_low,max_high,max_sum)


def find_max_cross_subarray(data,low,mid,high):
	left_sum = -sys.maxint - 1
	total = 0
	for i in range(mid,low-1,-1):
		total += data[i]
		if total > left_sum:
			left_sum = total
			left_max_index = i
	
	right_sum = -sys.maxint - 1
	total = 0
	for j in range(mid+1,high+1):
		total += data[j]
		if total > right_sum:
			right_sum = total
			right_max_index = j
	
	return (left_max_index,right_max_index,left_sum + right_sum)


if __name__ == '__main__':
	data = input_sort_data()
	print find_maxmum_subarray(data,0,5)
	print find_maxmum_subarray_violence(data,0,5)
