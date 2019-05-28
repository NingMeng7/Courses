def insert_sort(L):
	'''
  description: 升序插入排序的python实现,假定要排序的元素为L[1...L.length]
  Arg: 待排序数组
  return: list是可变对象,无返回值
  '''
  
	for j in range(2, len(L)):	# range右边是开区间，与数组下标少1正好符合
		L[0] = L[j]
		i = j - 1
		while L[i] > L[0] and i > 0:
			L[i+1] = L[i]
			i = i - 1
		L[i+1] = L[0]



TEST = [0, 1, 4, 2, 7, 55, 32, 99]
print('Before Insert Sort:')
print(TEST[1:])

insert_sort(TEST)

print('After Insert Sort:')
print(TEST[1:])
