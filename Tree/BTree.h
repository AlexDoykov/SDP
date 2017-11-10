#include <iostream>
#include <string>
#include <vector>
template<class T>
struct Node{
	T data;
	Node<T> *left;
	Node<T> *right;
	Node(const T& data):data(data), left(nullptr), right(nullptr){
	}
};



template<class T>
class BTree
{
private:
Node<T>* root;
	bool insert(const T& data, std::string path, Node<T> *&root){
		if(root == nullptr && path == ""){
			root = new Node<T>(data);
			return true;
		}
		
		if(root == nullptr && path != ""){
			return false;
		}

		if(root != nullptr && path == ""){
			return false;
		}

		if(path[0] == 'L'){
			path.erase(path.begin());
			return insert(data, path, root->left);
		}
		if(path[0] == 'R'){
			path.erase(path.begin());
			return insert(data, path, root->right);
		}	
		return false;
	}

	unsigned count(Node<T> *root) const{
		if(root == nullptr){
			return 0;
		}
		return 1 + count(root->left) + count(root->right);
	}

	unsigned countEvens(Node<T> *root) const{
		if(root == nullptr){
			return 0;
		}
		if(root->data % 2 == 0){
			return 1 + countEvens(root->left) + countEvens(root->right);
		}

		return countEvens(root->left) + countEvens(root->right);
	}

	unsigned height(Node<T>* root) const{
		if(root == nullptr){
			return 0;
		}
		unsigned heightOfLeftTree = height(root->left);
		unsigned heightOfRightTree =  height(root->right);
		return 1 + ((heightOfLeftTree > heightOfRightTree) ? heightOfLeftTree : heightOfRightTree);
	}

	unsigned countLeaves(Node<T> *root) const{
		if(root == nullptr){
			return 0;
		}

		if(root->left == nullptr && root->right == nullptr){
			return 1;
		}

		return countLeaves(root->left) + countLeaves(root->right);
	}

	T maxLeaf(Node<T> *root) const{
		if(root->left == nullptr && root->right == nullptr){
			return root->data;
		}

		if(root->left != nullptr && root->right != nullptr){
			return ((maxLeaf(root->left) > maxLeaf(root->right)) ? maxLeaf(root->left) : maxLeaf(root->right));
		}

		if(root->left != nullptr){
			return maxLeaf(root->left);
		}
		T maxRightLeaf;
		if(root->right != nullptr){
			return maxLeaf(root->right);
		}

	}

	//подавайте само верни пътища защото наистина не знам какво да връщам като стойност ако го омажете

	T& getElement(const char *s, Node<T>* root){
		//std::cout<<s[0]<<" "<<root->data<<std::endl;
		if(s[0] == '\0'){
			std::cout<<s[0]<<" "<<root->data<<std::endl;
			return root->data;
		}

		if(s[0] == 'L'){
			getElement(s + 1, root->left);
		}
		getElement(s + 1, root->right);
	}

public:
	BTree():root(nullptr){

	}

	bool insert(const T& data, std::string path){
		return insert(data, path, root);
	}

	unsigned count() const{
		return count(root);
	}

	unsigned countEvens() const{
		return countEvens(root);
	}

	unsigned height () const{
		return height(root);
	}

	unsigned countLeaves() const{
		return countLeaves(root);
	}

	T maxLeaf() const{
		return maxLeaf(root);
	}

	T& getElement(const char *s){
		return getElement(s, root);
	}

	vector<T> BTree<T>::listLeaves (){

	}
	/* data */
};