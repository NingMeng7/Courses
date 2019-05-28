class Stack(object):
	def __init__(self):
		self._items = []


	def isEmpty(self):
		return self._items == []


	def push(self, item):
		self._items.append(item)


	def pop(self):
		if self.isEmpty():
			print('Stack is empty!')
		else:
			return self._items.pop()


	def get_top(self):
		if self.isEmpty():
			print('Stack is empty!')
		else:
			return self._items[-1]


	def print_stack(self):
		print(self._items)


stack = Stack()
e = 10
for i in range(10):
	stack.push(i)
	stack.print_stack()
for i in range(9):
	stack.pop()
	stack.print_stack()
