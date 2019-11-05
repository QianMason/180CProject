#creating linked list class for

class Node:
	def __init__(self, next=None, prev=None, cylinder=None):
		self.next = next
		self.prev = prev
		self.cylinder = cylinder

class LinkedList:
	def __init__(self, head=None):
		self.head = head

	#insertion method to insert into proper position (sorted numbers)
	def insert(self, head, val):
		new_node = Node()
		new_node.cylinder = val
		temp = head
		#if new node should be at head, insert and return
		if temp.cylinder > val:
			new_node.next = temp
			temp.prev = new_node
			head = new_node
			return new_node
		#traverse list and compare until correct position
		while temp.next is not None and temp.next.cylinder < val:
            temp = temp.next
        #move "pointers" around
		new_node.next = temp.next
        temp.next = new_node
        new_node.prev = temp
		#special case to relink potential next nodes prev pointer back to inserted node
		if new_node.next is not None:
			new_node.next.prev = new_node