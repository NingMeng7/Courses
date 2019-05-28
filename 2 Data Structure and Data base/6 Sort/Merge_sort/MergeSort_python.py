def merge(A, p, q, r): # A[p...q] A[q+1...r] 已排序
	n1 = q - p + 1
	n2 = r - (q+1) + 1  
	L = A[p:q+1] + [float('inf')]	# slice的左开右闭规则
	R = A[q+1:r+1] + [float('inf')]	

	i = 0
	j = 0

	for k in range(p, r+1):
		if L[i] <= R[j]:	# 升序排序
			A[k] = L[i]
			i += 1
		else:
			A[k] = R[j]
			j += 1
def merge_sort(A, p, r):
	if p < r:
		q = (p+r)//2	# 向下取整
		merge_sort(A, p, q)
		merge_sort(A, q+1, r)
		merge(A, p, q, r)

TEST = [0, 1, 4, 2, 7, 55, 32, 99]
print('Before Insert Sort:')
print(TEST)

merge_sort(TEST, 1, len(TEST)-1)

print('After Insert Sort:')
print(TEST)		
