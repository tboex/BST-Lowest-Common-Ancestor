#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct node
{
	int key_value;
	node *left;
	node *right;
	node *parent;
};

class btree
{
public:
	btree();
	~btree();

	void insert(int key);
	node *search(int key);
	void destroy_tree();
	node *lowestAncestor(node* left, node* right);

private:
	void destroy_tree(node *leaf);
	void insert(int key, node *leaf);
	node *search(int key, node *leaf);
	node *lowestAncestor(node* left, node* right, node* curr);
	node *root;
};
btree::btree()
{
	root = NULL;
}
btree::~btree()
{
	destroy_tree();
}
void btree::destroy_tree(node *leaf)
{
	if (leaf != NULL)
	{
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}
void btree::insert(int key, node *leaf)
{
	if (key< leaf->key_value)
	{
		if (leaf->left != NULL)
			insert(key, leaf->left);
		else
		{
			leaf->left = new node;
			leaf->left->key_value = key;
			leaf->left->left = NULL;    //Sets the left child of the child node to null
			leaf->left->right = NULL;   //Sets the right child of the child node to null
			leaf->left->parent = leaf;
		}
	}
	else if (key >= leaf->key_value)
	{
		if (leaf->right != NULL)
			insert(key, leaf->right);
		else
		{
			leaf->right = new node;
			leaf->right->key_value = key;
			leaf->right->left = NULL;  //Sets the left child of the child node to null
			leaf->right->right = NULL; //Sets the right child of the child node to null
			leaf->right->parent = leaf;
		}
	}
}
node *btree::search(int key, node *leaf)
{
	if (leaf != NULL)
	{
		if (key == leaf->key_value)
			return leaf;
		if (key<leaf->key_value)
			return search(key, leaf->left);
		else
			return search(key, leaf->right);
	}
	else return NULL;
}
void btree::insert(int key)
{
	if (root != NULL)
		insert(key, root);
	else
	{
		root = new node;
		root->key_value = key;
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
	}
}
node *btree::search(int key)
{
	return search(key, root);
}
node *btree::lowestAncestor(node* left, node* right)
{
	return lowestAncestor(left, right, root);
}
void btree::destroy_tree()
{
	destroy_tree(root);
}
node *btree::lowestAncestor(node* left, node* right, node* curr)
{
	if (curr != NULL)
	{
		if ((left->key_value < curr->key_value) && (right->key_value < curr->key_value))
		{
			return lowestAncestor(left, right, curr->left);
		} else if ((left->key_value > curr->key_value) && (right->key_value > curr->key_value))
		{
			return lowestAncestor(left, right, curr->right);
		}
		else
		{
			return curr;
		}
	}
	else return NULL;
}

int main(int argc, char* argv[])
{
	ifstream ifs(argv[1]);
	int x, y;
	string line;
	btree tree;
	tree.insert(30);
	tree.insert(8);
	tree.insert(52);
	tree.insert(3);
	tree.insert(20);
	tree.insert(10);
	tree.insert(29);
	while (getline(ifs, line)) {
		istringstream iss(line);
		iss >> x >> y;
		node* left = tree.search(x);
		node* right = tree.search(y);
		node* lca = tree.lowestAncestor(left, right);
		cout << lca->key_value << endl;
	}
	return 0;
}