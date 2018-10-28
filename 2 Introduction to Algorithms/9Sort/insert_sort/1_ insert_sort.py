# data: 1->n
def insert_sort(L):
	temp = L[0]
	for i in range(2, len(L)):	# range右边是开区间，与数组下标少1正好符合
		L[0] = L[i]
		j = i - 1
		while L[j] < L[0]:
			L[j+1] = L[j]
			j = j - 1
		L[j+1] = L[0]
	L[0] = temp

TEST = [0, 1, 4, 2, 7, 55, 32, 99]
print('Before Insert Sort:')
print(TEST)

insert_sort(TEST)

print('After Insert Sort:')
print(TEST)
