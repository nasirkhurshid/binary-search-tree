#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <typename T>								//structure for binary tree
struct node {
	T data;
	node<T>* left, * right;
};

template <typename T>
queue<T> copy(node<T>* src) {						//function for copying tree data
	queue<node<T>*> qtemp;							//temporary queue for storing pointers to nodes
	queue<T> q;										//queue for storing data in nodes
	qtemp.push(src);								//pushing root pointer to qtemp
	while (!qtemp.empty()) {						//while qtemp is not empty
		node<T>* ptr;
		ptr = qtemp.front();						//removing pointer one by one from queue
		q.push(ptr->data);							//pushing node's data to q
		qtemp.pop();
		if (ptr->left != NULL) {					//checking if left 
			qtemp.push(ptr->left);					//and right child of node
		}											//exist or not
		if (ptr->right != NULL) {					//if exist then
			qtemp.push(ptr->right);					//pushing them in qtemp
		}
	}
	return q;										//returning queue containing data of nodes
}


template <typename T>
void reset_iter(node<T>* ptr, queue<T>& q) {			//function for resetting BST
	queue<node<T>*> qtemp;								//temporary queue for storing pointers
	qtemp.push(ptr);									//pushing root node to qtemp
	while (!qtemp.empty()) {							//while qtemp is not empty
		node<T>* p;										//accessing qtemp's pointers
		p = qtemp.front();								//one by one
		qtemp.pop();									//and popping them from queue
		q.push(p->data);								//pushing pointers' data to q, which is queue of BST
		if (p->left != NULL) {							//checking for left and right children
			qtemp.push(p->left);						//of pointer's node
		}												//if they exist
		if (p->right != NULL) {							//then pushing their
			qtemp.push(p->right);						//pointers in qtemp
		}
	}

	/*the code commented below is for resetting the BST in such a way that leaf nodes
	are displayed first and root node is displayed last, (in reverse LEVEL ORDER)*/

	/*queue<node<T>*> qtemp;
	stack<T> s;
	qtemp.push(ptr);
	while (!qtemp.empty()) {
		node<T>* p;
		p = qtemp.front();
		qtemp.pop();
		s.push(p->data);
		if (p->left != NULL) {
			qtemp.push(p->left);
		}
		if (p->right != NULL) {
			qtemp.push(p->right);
		}
	}
	while (!s.empty()) {
		q.push(s.top());
		s.pop();
	}*/
}

template <typename T>
int count_nodes(node<T>* ptr) {							//function for counting nodes of BST
	queue<node<T>*> qtemp;								//same logic
	queue<T> q;											//is used here
	qtemp.push(ptr);									//which is used in
	while (!qtemp.empty()) {							//reset_iter()
		node<T>* p;										//the one difference is that
		p = qtemp.front();								//in reset_iter(), BST's queue is used 
		qtemp.pop();									//for pushing data but here
		q.push(p->data);								//local queue is used
		if (p->left != NULL) {							//because we have no concern
			qtemp.push(p->left);						//with the data, but with
		}												//their number/strength
		if (p->right != NULL) {							//therefore
			qtemp.push(p->right);						//we
		}												//just
	}													//return
	return q.size();									//the size if queue, which is infact no. of nodes
}

template <typename T>
void makeempty_iter(node<T>* ptr) {						//function for making queue empty
	queue<node<T>*> qtemp;								//temporary queue, as used in functions above			
	stack<node<T>*> stemp;								//stack storing same things as in queue
	qtemp.push(ptr);									//pushing root's pointer
	while (!qtemp.empty()) {							//while qtemp is not empty
		node<T>* p;
		p = qtemp.front();								//getting its data one by one
		stemp.push(p);									//and pushing it in queue
		qtemp.pop();
		if (p->left != NULL) {							//checking for 
			qtemp.push(p->left);						//left
		}												//and
		if (p->right != NULL) {							//right
			qtemp.push(p->right);						//children
		}
	}
	while (!stemp.empty()) {							//deleting each node pointed by pointers in stack
		node<T>* del;									//while the stack is not empty
		del = stemp.top();								//here stack
		stemp.pop();									//is used because
		delete del;										//we wanted to delete leaf nodes first 
	}													//and root node last
}

///////////////////	CLASS OF BINARY SEARCH TREE	/////////////////////

template <typename T>
class BST {
	node<T>* root;							//pointer for root node
	queue<T> qlevel;						//queue for iterators
public:
	BST() {
		root = NULL;						//making root=NULL in constructor
	}
	BST(BST<T>& t) {
		queue<T> q;							//using queue in copy constructor
		q = copy(t.root);					//for copying data, copy function is used
		while (!q.empty()) {				//for getting data of tree to be copied
			T val = q.front();				//storing data in the
			q.pop();						//tree by getting it one by one
			insert(val);					//from queue
		}
	}
	void operator = (BST<T>& t) {
		makeempty();						//making tree empty, before copying any other tree's data to it
		queue<T> q;							//same operations
		q = copy(t.root);					//being performed
		while (!q.empty()) {				//as in
			T val = q.front();				//copy constructor
			q.pop();
			insert(val);
		}
	}
	~BST() {
		makeempty_iter(root);				//destructing tree by makeempty_iter()
	}
	void insert(const T& val) {				//fuction for inserting values
		node<T>* temp;						//temporary pointer for
		temp = new node<T>;					//creating new memory
		temp->data = val;					//putting value in data part
		temp->left = temp->right = NULL;	//and making left and right part NULL
		if (root == NULL) {					//if tree is empty
			root = temp;					//then pointing root to new node
		}
		else {								//else
			node<T>* ptr;					//visiting the tree using temporary pointer ptr
			ptr = root;
			while (1) {
				if (val < ptr->data) {			//if value to be inserted is less than the root's value of tree/subtree
					if (ptr->left == NULL) {	//if left child is NULL/available
						ptr->left = temp;		//then making new node the left child
						return;
					}
					ptr = ptr->left;			//else moving pointer to left
				}
				else if (val > ptr->data) {		//if value to be inserted is greater than the root's value of tree/subtree
					if (ptr->right == NULL) {	//if right child is NULL/available
						ptr->right = temp;		//then making new node the right child
						return;
					}
					ptr = ptr->right;			//else moving pointer to right
				}
				else {							//restricting user from inserting duplicate values
					throw "Duplicate keys are not allowed!\n";
				}
			}
		}
	}
	bool find(const T& val) {					//function for finding data in the tree
		if (empty()) {
			throw "Can't Read Data, Tree is Empty!\n";
		}
		node<T>* temp;							//visiting the tree using
		temp = root;							//a temporary pointer
		while (1) {								//if found , returning true
			if (temp == NULL) {					//if not found, returning false
				return false;
			}
			else if (val < temp->data) {		//if value is less than node's value
				temp = temp->left;				//moving to left	
			}
			else if (val > temp->data) {		//if value is greater than node's value
				temp = temp->right;				//moving to right
			}
			else {								//if found , returning true
				return true;
			}
		}
	}
	bool update(const T& oldval, const T& newval) {			//function for updating data
		if (empty()) {
			throw "Can't Update Data from Empty Tree!\n";
		}
		if (erase(oldval)) {								//if old data is found and erased
			insert(newval);									//inserting new data
			return true;									//returning true
		}
		return false;										//else returning false
	}
	bool erase(const T& val) {								//function for deleting data
		if (empty()) {
			throw "Can't Delete Data from Empty Tree!\n";
		}
		if (find(val)) {									//if value to be deleted found
			node<T>* ptr, * prev;							//ptr for keeping track of node to be deleted, prev for keeping track of ptr's previous node
			ptr = root;
			prev = NULL;
			while (1) {										//using while loop to find the data and delete respected node
				if (val < ptr->data) {
					prev = ptr;								//prev pointing to ptr's previous node
					ptr = ptr->left;						//ptr moving forward
				}
				else if (val > ptr->data) {
					prev = ptr;
					ptr = ptr->right;
				}
				else {										//if node found
					node<T>* del;							//temporary pointer for deleting node
					if (ptr->left == NULL && ptr->right == NULL) {	//checking if node is leaf node
						if (prev->left == ptr) {					//checking if leaf node is previous pointer's left or right child
							prev->left = NULL;						//making previous node NULL
							del = ptr;								//and
							delete del;								//deleting leaf node
						}
						else {
							prev->right = NULL;
							del = ptr;
							delete del;
						}
					}
					else if (ptr->left != NULL && ptr->right == NULL) {	//checking if node has only left child
						if (prev->left == ptr) {						//same operations 
							del = ptr;									//as performed in above condition
							prev->left = ptr->left;
							delete del;
						}
						else {
							del = ptr;
							prev->right = ptr->left;
							delete del;
						}
					}
					else if (ptr->right != NULL && ptr->left == NULL) {	//checking if node has only right child
						if (prev->left == ptr) {						//same operations
							del = ptr;									//as performed in above conditions
							prev->left = ptr->right;
							delete del;
						}
						else {
							del = ptr;
							prev->right = ptr->right;
							delete del;
						}
					}
					else {												//if node has both children
						node<T>* suc;									//pointer for successor's node
						suc = ptr->right;								//finding successor
						prev = NULL;									//of the required data
						while (suc->left != NULL) {						//using loop 
							prev = suc;									//and also finding successor node's previous node
							suc = suc->left;
						}
						ptr->data = suc->data;							//overwriting successor node's data to current node
						if (prev != NULL) {								//if current node is not previous node
							prev->left = suc->right;					//connecting previous node to successor node's right child
						}
						else {											//if current node is the previous node
							ptr->right = suc->right;					//connecting current node to successor node's right child
						}
						delete suc;										//deleting successor node
					}
					return true;
				}
			}
		}
		return false;
	}
	bool full() {											//function for checking whether tree is full or not
		node<T>* temp;
		temp = new node <T>;
		if (temp == NULL) {
			return true;
		}
		else {
			delete temp;
			return false;
		}
	}
	bool empty() {										//function for checking whether tree is empty or not
		return root == NULL;
	}
	void makeempty() {									//function for making tree empty
		if (empty()) {
			throw "Tree is already Empty!\n";
		}
		makeempty_iter(root);							//making tree empty using iterative makeempty_iter()
		root = NULL;
	}
	void reset() {										//function for resetting tree
		if (empty()) {
			throw "Tree is Empty!\n";
		}
		reset_iter(root, qlevel);						//resetting tree using iterative reset_iter()
	}
	bool is_last() {									//function for checking whether last element is reached or not
		return qlevel.empty();							//if qlevel is empty, returning true
	}
	T get_next() {										//function for getting next element of tree
		if (is_last()) {
			throw "Last element reached!\n";
		}
		T val = qlevel.front();							//getting next element using queue
		qlevel.pop();
		return val;
	}
	int length() {										//function for getting length of tree (no. of nodes)
		if (empty()) {
			throw "Tree is empty!\n";
		}
		return count_nodes(root);
	}
	void display() {									//function for displaying tree's data in LEVEL ORDER
		reset();										//displaying data
		while (!is_last()) {							//using iterators
			cout << get_next() << "	";
		}
		cout << endl;
	}
};

////////////////	CLIENT CODE		/////////////////////
int main()
{
	BST<int> tree;													//declaring a BST and inserting different values in it
	tree.insert(50); tree.insert(25); tree.insert(75); tree.insert(100); tree.insert(80);
	tree.insert(90); tree.insert(30); tree.insert(28); tree.insert(10); tree.insert(5); tree.insert(3);

	cout << "No. of Nodes: " << tree.length() << endl;				//getting no. of nodes
	tree.display();													//displaying tree's data in LEVEL ORDER
	cout << endl;

	if (tree.erase(5)) {											//erasing 5 from tree
		tree.display();
		cout << "Erased!\n\n";
		if (tree.find(3)) {											//finding 3 in tree
			tree.display();
			cout << "Found!\n\n";
			if (tree.update(3, 8)) {								//updating 3 by 8
				tree.display();
				cout << "Updated!\n\n";
			}
		}
	}

	BST<int> tree2, tree3(tree);							//using copy constructor to copy tree's data to tree3
	tree2.insert(50); tree2.insert(10); tree2.insert(70); tree2.insert(8);
	cout << "Original Tree 2: \n";
	tree2.display();
	tree2 = tree;											//using = operator to copy tree's data to tree2
	cout << "\nTree 2 after copying data: \n";
	tree2.display();
	cout << "\nTree 3: \n";
	tree3.display();

	return 0;
}