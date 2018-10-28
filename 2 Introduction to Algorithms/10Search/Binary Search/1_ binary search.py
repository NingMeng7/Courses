def Binary_search(A, v):
	low = 0
	hig = len(A) - 1
	while low <= hig:
		middle = (low+hig) // 2
		if A[middle] == v:
			return middle
		elif A[middle] > v:
			hig = middle - 1
		else:
			low = middle + 1
	print('Can not find v in A!')
	return -1

TEST = [0, 1, 2, 4, 7, 32, 55, 99]
for i in TEST:
	print(Binary_search(TEST, i))
