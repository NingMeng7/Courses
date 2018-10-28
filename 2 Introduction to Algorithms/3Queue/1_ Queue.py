from Stack import Stack
class Queue(object):
	def __init__(self):
		self._item = []


	def isEmpty(self):
		return self._item == []


	def enQueue(self, item):
		self._item.insert(0, item)


	def deQueue(self):
		return self._item.pop()


	def size(self):
		return len(self._item)


	def print_queue(self):
		print(self._item)

q = Queue()
for i in range(10):
	q.enQueue(i)
	q.print_queue()
for i in range(9):
	q.deQueue()
	q.print_queue()

q = Queue()
s = Stack()
str_ = '98789'
for i in range(len(str_)):
	s.push(str_[i])
	q.enQueue(str_[i])
for i in range(len(str_)):
	if s.pop() != q.deQueue():
		print('wrong!')
		break
