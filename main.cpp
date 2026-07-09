//	Term Project 
//	Red Black Tree
//	Submitted By:
//	Muhammad Baqir Raza(0230)
//	Taha Khalid(0245)

#include<iostream>
#include<iomanip>
using namespace std;

template<class T>
struct Node
{
	T data;
	char color;
	Node<T>* right;
	Node<T>* left;
	Node()
	{
		data = 0;
		color = '\0';
		right = nullptr;
		left = nullptr;
	}
};

template<class T>
class RedBlackTree
{
	Node<T>* root;
	// wrapper functions
	Node<T>* findParent(Node<T>* root, Node<T>* node)
	{
		if (node == nullptr || root == nullptr)
		{
			return nullptr;
		}
		if (root->left == node || root->right == node)
		{
			return root;
		}
		Node<T>* leftS = nullptr;
		Node<T>* rightS = nullptr;
		if (root->left != nullptr) {
			leftS = findParent(root->left, node);
		}
		if (leftS != nullptr) {
			return leftS;
		}
		if (root->right != nullptr) {
			rightS = findParent(root->right, node);
		}
		return rightS;
	}

	void leftRotation(Node<T>* node)
	{
		Node<T>* newP = node->right;
		node->right = newP->left;
		newP->left = node;

		Node<T>* grandP = findParent(root, node);
		if (grandP == nullptr)
		{
			root = newP;
		}
		else if (grandP->left == node)
		{
			grandP->left = newP;
		}
		else
		{
			grandP->right = newP;
		}
	}
	void rightRotation(Node<T>* node)
	{
		Node<T>* newP = node->left;
		node->left = newP->right;
		newP->right = node;
		Node<T>* grandP = findParent(root, node);
		if (grandP == nullptr)
		{
			root = newP;
		}
		else if (grandP->left == node)
		{
			grandP->left = newP;
		}
		else
		{
			grandP->right = newP;
		}
	}

	void fixInsert(Node<T>* node)
	{
		while (node != root)
		{
			Node<T>* parent = findParent(root, node);
			if (parent == nullptr)
			{
				break;
			}
			if (parent->color == 'B')
			{
				break;
			}
			Node<T>* grandPa = findParent(root, parent);

			if (grandPa == nullptr)
			{
				break;
			}
			Node<T>* uncle = nullptr;
			if (grandPa->right == parent)
			{
				uncle = grandPa->left;
			}
			else
			{
				uncle = grandPa->right;
			}

			// case 1 red uncle
			if (uncle != nullptr && uncle->color == 'R')
			{
				parent->color = 'B';
				uncle->color = 'B';
				grandPa->color = 'R';
				node = grandPa;
			}
			else
			{
				// Case 2,3 black uncle or NULL
				if (grandPa->left == parent)
				{
					if (parent->right == node)
					{
						leftRotation(parent);
						node = parent;
						parent = findParent(root, node);
					}
					rightRotation(grandPa);
					char t = parent->color;
					parent->color = grandPa->color;
					grandPa->color = t;
				}
				else
				{
					if (parent->left == node)
					{
						rightRotation(parent);
						node = parent;
						parent = findParent(root, node);
					}

					leftRotation(grandPa);
					char t = parent->color;
					parent->color = grandPa->color;
					grandPa->color = t;
				}
			}
		}
		root->color = 'B';
	}

	void inorder(Node<T>* node)
	{
		if (node == nullptr)
		{
			return;
		}
		inorder(node->left);
		cout << node->data << "(" << node->color << ")  ";
		inorder(node->right);
	}

	void preorder(Node<T>* node)
	{
		if (node == nullptr)
		{
			return;
		}
		cout << node->data << "(" << node->color << ")  ";
		preorder(node->left);
		preorder(node->right);
	}

	void postorder(Node<T>* node)
	{
		if (node == nullptr)
		{
			return;
		}
		postorder(node->left);
		postorder(node->right);
		cout << node->data << "(" << node->color << ")  ";
	}

	void fixDelete(Node<T>* db, Node<T>* dbParent)
	{
		while (db != root && (db == nullptr || db->color == 'B'))
		{
			if (dbParent == nullptr) {
				break;
			}
			bool dbIsLeft;
			if (dbParent->left == db) {
				dbIsLeft = true;
			}
			else {
				dbIsLeft = false;
			}
			Node<T>* sibling = nullptr;
			if (dbIsLeft)
			{
				sibling = dbParent->right;
			}
			else {
				sibling = dbParent->left;
			}

			if (sibling == nullptr)
			{
				db = dbParent;
				dbParent = findParent(root, db);
				continue;
			}
			// Case 1  sibling is Red
			if (sibling->color == 'R')
			{
				char t = sibling->color;
				sibling->color = dbParent->color;
				dbParent->color = t;

				if (dbIsLeft) {
					leftRotation(dbParent);
				}
				else {
					rightRotation(dbParent);
				}
				// update sibling after rotation
				if (dbIsLeft)
				{
					sibling = dbParent->right;
				}
				else {
					sibling = dbParent->left;
				}
			}
			// sibling is black from here
			Node<T>* farChild = nullptr;
			if (dbIsLeft)
			{
				farChild = sibling->right;
			}
			else {
				farChild = sibling->left;
			}

			Node<T>* nearChild = dbIsLeft ? sibling->left : sibling->right;
			if (dbIsLeft)
			{
				nearChild = sibling->left;
			}
			else
			{
				nearChild = sibling->right;
			}

			bool farBlack;
			if (farChild == nullptr || farChild->color == 'B')
			{
				farBlack = true;
			}
			else
			{
				farBlack = false;
			}
			bool nearBlack;
			if (nearChild == nullptr || nearChild->color == 'B')
			{
				nearBlack = true;
			}
			else
			{
				nearBlack = false;
			}
			// Case 2 both sibling children black
			if (farBlack && nearBlack)
			{
				sibling->color = 'R';
				if (dbParent->color == 'R')
				{
					dbParent->color = 'B';
					break;
				}
				db = dbParent;
				dbParent = findParent(root, db);
			}
			else
			{
				// Case 3 is far black, near Red
				if (farBlack)
				{
					char t = nearChild->color;
					nearChild->color = sibling->color;
					sibling->color = t;

					if (dbIsLeft)
						rightRotation(sibling);
					else
						leftRotation(sibling);

					if (dbIsLeft)
					{
						sibling = dbParent->right;
					}
					else
						sibling = dbParent->left;


					if (dbIsLeft)
					{
						farChild = sibling->right;
					}
					else
						farChild = sibling->left;
				}
				// Case 4 is far child Red
				char t = sibling->color;
				sibling->color = dbParent->color;
				dbParent->color = t;
				if (dbIsLeft)
				{
					leftRotation(dbParent);
				}
				else
				{ 
					rightRotation(dbParent);
				}
				if (farChild != nullptr)
					farChild->color = 'B';

				break;
			}
		}
		if (root != nullptr)
			root->color = 'B';
	}
	bool searchWrapper(Node<T>* node, T val)
	{
		if (node == nullptr)
		{
			return false;
		}
		if (node->data == val)
		{
			return true;
		}
		if (val > node->data)
		{
			return searchWrapper(node->right, val);
		}
		else
		{
			return searchWrapper(node->left, val);
		}
		return false;
	}

	void visualize(Node<T>* node, int space)
	{
		if (node == nullptr) {
			return;
		}
		const int gap = 8;
		visualize(node->right, space + gap);
		cout << endl;
		cout << setw(space) << "";
		cout << node->data << "(" << node->color << ")" << endl;
		visualize(node->left, space + gap);
	}
public:
	RedBlackTree()
	{
		root = nullptr;
	}
	void insert(T data)
	{
		Node<T>* newNode = new Node<T>;
		newNode->data = data;
		newNode->color = 'R';
		if (root == nullptr)
		{
			newNode->color = 'B';
			root = newNode;
			return;
		}
		Node<T>* temp = root;
		while (true)
		{
			if (data < temp->data)
			{
				if (temp->left == nullptr)
				{
					temp->left = newNode;
					break;
				}
				temp = temp->left;
			}
			else if (data > temp->data)
			{
				if (temp->right == nullptr)
				{
					temp->right = newNode;
					break;
				}
				temp = temp->right;
			}
			else {
				cout << "Data already exists" << endl;
				delete newNode;
				return;
			}
		}
		fixInsert(newNode);
	}

	void display(int choice)
	{
		if (choice == 1)
		{
			if (root != nullptr)
			{
				cout << "In-order Traversal" << endl;
				inorder(root);
				cout << endl;
			}
			else
			{
				cout << "No data to display!" << endl;
			}
		}
		else if (choice == 2)
		{
			if (root != nullptr)
			{
				cout << "Pre-order Traversal" << endl;
				preorder(root);
				cout << endl;
			}
			else
			{
				cout << "No data to display!" << endl;
			}
		}
		else if (choice == 3)
		{
			if (root != nullptr)
			{
				cout << "Post-order Traversal" << endl;
				postorder(root);
				cout << endl;
			}
			else
			{
				cout << "No data to display!" << endl;
			}
		}
		else
		{
			cout << "Invalid choice!" << endl;
		}
	}

	void deleteValue(T val)
	{
		if (root == nullptr)
		{
			cout << "Tree is empty!" << endl;
			return;
		}

		Node<T>* curr = root;
		Node<T>* parent = nullptr;

		// 1) locate the node to delete
		while (curr != nullptr && curr->data != val)
		{
			parent = curr;
			if (val < curr->data) {
				curr = curr->left;
			}
			else {
				curr = curr->right;
			}
		}
		if (curr == nullptr)
		{
			cout << val << " not found!" << endl;
			return;
		}
		// 2 child
		if (curr->left != nullptr && curr->right != nullptr)
		{
			Node<T>* suc = curr->right;
			parent = curr;
			while (suc->left != nullptr)
			{
				parent = suc;
				suc = suc->left;
			}
			curr->data = suc->data;
			curr = suc;
		}

		// 1 child
		Node<T>* child = (curr->left != nullptr) ? curr->left : curr->right;
		if (curr->left != nullptr)
		{
			child = curr->left;
		}
		else 
		{
			child = curr->right;
		}
		char deletedColor = curr->color;

		if (parent == nullptr) {
			root = child;
		}
		else if (parent->left == curr) {
			parent->left = child;
		}
		else {
			parent->right = child;
		}
		Node<T>* dbNode = child;
		Node<T>* dbParent = parent;
		delete curr;
		if (deletedColor == 'B') {
			fixDelete(dbNode, dbParent);
		}
		cout << val << " deleted successfully!" << endl;
	}

	void visualizeTree()
	{
		if (root == nullptr)
		{
			cout << "Tree is empty!\n";
			return;
		}

		cout << "\n===== Tree Visualization =====\n";
		visualize(root, 0);
	}

	bool search(T val)
	{
		if (searchWrapper(root, val) == true)
		{
			cout << val << " found in tree." << endl;
			return true;
		}
		else
		{
			cout << val << " not found in tree!" << endl;
			return false;
		}
	}
};
int main()
{
	system("color 0E");
	cout << "===== Red-Black Tree =====" << endl;
	RedBlackTree<int> tree;
	char choice;
	do
	{
		cout << "********* Menu *********" << endl;
		cout << "1. Enter a to insert data.\n";
		cout << "2. Enter b to delete data.\n";
		cout << "3. Enter c to search data.\n";
		cout << "4. Enter d for In-order Traversal.\n";
		cout << "5. Enter e for Pre-order Traversal.\n";
		cout << "6. Enter f for Post-order Traversal.\n";
		cout << "7. Enter g to visualize tree.\n";
		cout << "8. Enter h to clear console for clear output.\n";
		cout << "8. Enter z to exit.\n";
		cout << "Enter choice: ";
		cin >> choice;
		cout << endl;
		if (choice == 'a')
		{
			cout << "Enter -1 to stop inserting\n";
			while (true)
			{
				int data;
				cout << "Enter a value to insert: ";
				cin >> data;
				if (data == -1)
				{
					break;
				}
				tree.insert(data);
				cout << data << " Inserted successfully!" << endl << endl;
			}

		}
		else if (choice == 'b')
		{
			int data;
			cout << "Enter value to Delete in tree: ";
			cin >> data;
			if (tree.search(data))
			{
				tree.deleteValue(data);
			}
			else
				cout << "Value not Found in Tree" << endl;
		}
		else if (choice == 'c')
		{
			int data;
			cout << "Enter value to search in tree: ";
			cin >> data;
			tree.search(data);
		}
		else if (choice == 'd')
		{
			tree.display(1);
		}
		else if (choice == 'e')
		{
			tree.display(2);
		}
		else if (choice == 'f')
		{
			tree.display(3);
		}
		else if (choice == 'g')
		{
			tree.visualizeTree();
		}
		else if (choice == 'z')
		{
			cout << "Exiting...." << endl;
		}
		else if (choice == 'h') {
			system("cls");
		}
		else
		{
			cout << "Invalid Input! Please Try Again\n";
		}
		cout << endl;
	} while (choice != 'z');
	return 0;
}