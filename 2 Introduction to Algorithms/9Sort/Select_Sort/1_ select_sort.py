def select_sort(L):
	for i in range(1, len(L)-1):
		index = i
		for j in range(i, len(L)):
			if L[j] > L[index]:
				index = j
		temp = L[i]
		L[i] = L[index]
		L[index] = temp

TEST = [0, 1, 4, 2, 7, 55, 32, 99]
print('Before Insert Sort:')
print(TEST)

select_sort(TEST)

print('After Insert Sort:')
print(TEST)		
