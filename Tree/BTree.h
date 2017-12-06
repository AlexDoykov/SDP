#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <assert.h>
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
		if(root == nullptr){
			assert(false);
		}

		if(root->left == nullptr && root->right == nullptr){
			return root->data;
		}

		if(root->left == nullptr){
			return maxLeaf(root->right);

		}

		if(root->right == nullptr){
			return maxLeaf(root->left);
		}

		T maxLeftLeaf = maxLeaf(root->left);
		T maxRightLeaf = maxLeaf(root->right);

		return (maxRightLeaf > maxLeftLeaf) ? maxRightLeaf : maxLeftLeaf;

	}

	T& getElement(const char *s, Node<T>* root){

		if(root == nullptr || (s[0] != 'R' && s[0] != 'L' && s[0] != '\0')){
			assert(false);
		}

		if(s[0] == '\0'){
			return root->data;
		}

		if(s[0] == 'L'){
			return getElement(s + 1, root->left);
		}
		return getElement(s + 1, root->right);
	}

	Node<T>* pop(std::stack<Node<T>*>& st){
		Node<T>* result = st.top();
		st.pop();
		return result;
	}

	void checkForEqualLevels(Node<T> *root, unsigned level, std::vector<std::unordered_set<T>>& result) const{
		if(result.size() <= level){
			result.resize(result.size() + 1);
		}
		if(root != nullptr){
			result[level].insert(root->data);
		}
		if(root->left != nullptr){
			checkForEqualLevels(root->left, level + 1, result);			
		}
		if(root->right != nullptr){
			checkForEqualLevels(root->right, level + 1, result);			
		}
	}

	void findTrace(const T& x, std::string& trace, Node<T>* root, bool& found){
		if(root == nullptr){
			return;
		}
		if(root->data == x){
			trace = "";
			found = 1;
			return;
		}

		findTrace(x, trace, root->left, found);
		if(found == true){
			trace += 'L';
			return;
		}

		findTrace(x, trace, root->right, found);
		if(found == true){
			trace += 'R';
			return;
		}

		trace = "_";
		return;
	}

	bool isBOT(Node<T>* root, const T& lowerBound, const T& upperBound, int token){
		std::cout<<root->data<<" "<<lowerBound<<" "<<upperBound<<" "<<token<<std::endl;

		if(token == -1 && root->data > upperBound){
			return 0;
		}

		if(token == 1 && root->data < lowerBound){
			return 0;
		}

		if((root->data < lowerBound || root->data > upperBound) && token == 0 ){
						std::cout<<"\nHERE "<<token<<" "<<root->data<<" "<<lowerBound<<" "<<upperBound<<"\n";

			return 0;
		}	

		if(root->left == nullptr && root->right == nullptr){
			return 1;
		}

		if(root->left == nullptr){
			if(token == -1){
				std::cout<<"from 197 ";
				return isBOT(root->right, root->data, upperBound, 0);
			}

			if(token == 1){
				std::cout<<"from 201 ";
				return isBOT(root->right, root->data, upperBound, token);
			}

			return isBOT(root->right, root->data, upperBound, token);
		}


		if(root->right == nullptr){
			if(token == -1){
				std::cout<<"from 207 ";
				return isBOT(root->left, lowerBound, upperBound, token);
			}

			if(token == 1){
				std::cout<<"from 211 ";
				return isBOT(root->left, lowerBound, root->data, 0);
			}

			return isBOT(root->left, lowerBound, upperBound, token);
		}

		if(token == 1){
			std::cout<<"from 216 ";
			return isBOT(root->right, root->data, upperBound, token) &&
				isBOT(root->left, lowerBound, root->data, 0);
		}

		if(token == -1){
			std::cout<<"from 222 ";
			return isBOT(root->left, lowerBound, root->data, token) &&
				isBOT(root->right, root->data, upperBound, 0);
		}

		std::cout<<"from 227 ";
		return isBOT(root->left, lowerBound, root->data, token) &&
			isBOT(root->right, root->data, upperBound, token);

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

	std::vector<T> listLeaves (){
		std::stack<Node<T>*> subTrees;
		std::vector<T> leaves;
		if(root == nullptr){
			return leaves;
		}
		subTrees.push(root);
		while(!subTrees.empty()){
			//тук много ли е грешно, че така съм го написал
			Node<T>* curr = pop(subTrees);
				if(curr->left == nullptr && curr->right == nullptr){
				leaves.push_back(curr->data);
			}
			if(curr->right != nullptr){
				subTrees.push(curr->right);
			}
			if(curr->left != nullptr){
				subTrees.push(curr->left);
			}
		}
		return leaves;
	}

	std::string findTrace(const T& x){
		std::string str;
		bool found = 0;
		findTrace(x, str, root, found);
		return str;
	}

	std::vector<std::unordered_set<T>> checkForEqualLevels() const{
		std::vector<std::unordered_set<T>> result;
		checkForEqualLevels(root, 0, result);
		return result;
	}

	bool isBOT(){
		if(root == nullptr){
			return 0;
		}

		if(root->left == nullptr && root->right == nullptr){
			return 1;
		}

		if(root->left == nullptr){
			return isBOT(root->right, root->data, 0, 1);
		}

		if(root->right == nullptr){
			return isBOT(root->left, 0, root->data, -1);
		}

		return isBOT(root->right, root->data, 0, 1) && isBOT(root->left, 0, root->data, -1);
	}
	/* data */
};