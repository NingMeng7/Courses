class BinarySearchTree(object):
	def __init__(self, item):
		self.key = item
		self.leftchild = None
		self.rightchild = None


	def get_root(self):
		return self.key 


	def set_root(self, item):
		self.key = item


	def get_left(self):
		return self.leftchild


	def get_right(self):
		return self.rightchild

	
	def preorder(self):
		print(self.key)
		if self.leftchild is not None:
			self.leftchild.preorder()
		if self.rightchild is not None:
			self.rightchild.preorder()


	def inorder(self):
		if self.leftchild is not None:
			self.leftchild.inorder()
		print(self.key)
		if self.rightchild is not None:
			self.rightchild.inorder()

	
	def add_node(self, node):
		if self.key > node.key:
			if self.leftchild is not None:
				self.leftchild.add_node(node)
			else:
				self.leftchild = node
		if self.key < node.key:
			if self.rightchild is not None:
				self.rightchild.add_node(node)
			else:
				self.rightchild = node


	def search(self, kval):
		if self.key == kval:
			return self
		elif kval < self.key:
			if not self.leftchild:
				print('Can not find it!')
				return None
			else:
				self.leftchild.search(kval)

		else:
			if not self.rightchild:
				print('Can not find it!')
				return None
			else:
				self.rightchild.search(kval)


bt = BinarySearchTree(5)
node1 = BinarySearchTree(10)
node2 = BinarySearchTree(7)
node3 = BinarySearchTree(99)
node4 = BinarySearchTree(44)
bt.add_node(node1)
bt.add_node(node2)
bt.add_node(node3)
bt.add_node(node4)
bt.inorder()
bt.preorder()
