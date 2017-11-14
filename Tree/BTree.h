#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
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
		if(s[0] == '\0'){
			return root->data;
		}

		if(s[0] == 'L'){
			getElement(s + 1, root->left);
		}
		getElement(s + 1, root->right);
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
		subTrees.push(root);
		std::vector<T> leaves;
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
	//not working
	/*std::string findTrace (const T& x) const{
		std::stack<Node<T>*> subTrees;
		subTrees.push(root);
		std::string trace;
		while(!subTrees.empty()){
			Node<T>* curr = subTrees.top();
			subTrees.pop();
			if(curr->data == x){
				return trace;
			}
			if(curr->right != nullptr){
				trace += 'R';
				subTrees.push(curr->right);
			}
			if(curr->left != nullptr){
				trace += 'L';
				subTrees.push(curr->left);
			}
		}

		return "_";
	}*/

	std::vector<std::unordered_set<T>> checkForEqualLevels() const{
		std::vector<std::unordered_set<T>> result;
		checkForEqualLevels(root, 0, result);
		return result;
	}


	/* data */
};