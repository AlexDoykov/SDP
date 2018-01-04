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

	Node(const T& data, Node<T>* _left, Node<T>* _right):data(data), 
														left(_left), 
														right(_right){
	}
};



template<class T>
class BTree
{
private:
	Node<T>* root;
	
	Node<T>* pop(std::stack<Node<T>*>& st) const{
		Node<T>* result = st.top();
		st.pop();
		return result;
	}

	void printSpaces(unsigned spaces) {
		for(int i = 0; i < spaces; i++){
			std::cout<<"     ";
		}
	}


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

	void checkForEqualLevels(Node<T> *root, unsigned level, 
		std::vector<std::unordered_set<T>>& result) const{
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

	std::string findTrace(const T& x, Node<T>* root) const{

		if(root == nullptr){
			return "-";
		}

		if(root->data == x){
			return "";
		}
		
		std::string leftResult = findTrace(x, root->left);
		if(leftResult != "-"){
			return "L" + leftResult;
		}

		std::string rightResult = findTrace(x, root->right);
		if(rightResult != "-"){
			return "R" + rightResult;
		}

		return "-";
		
	}

	bool isBOT(Node<T>* root, const T& lowerBound, 
		const T& upperBound, int token) const{

		if(token == -1 && root->data > upperBound ||
			token == 1 && root->data < lowerBound ||
			((root->data < lowerBound || root->data > upperBound) && token == 0)){

			return 0;
		}

		if(root->left == nullptr && root->right == nullptr){
			return 1;
		}

		if(root->left == nullptr){
			if(token == -1){
				return isBOT(root->right, root->data, upperBound, 0);
			}

			return isBOT(root->right, root->data, upperBound, token);
		}


		if(root->right == nullptr){
			if(token == 1){
				return isBOT(root->left, lowerBound, root->data, 0);
			}

			return isBOT(root->left, lowerBound, upperBound, token);
		}

		int rightToken = token, leftToken = token;
		if(token == 1){
			leftToken = 0;
		}

		if(token == -1){
			rightToken = 0;	
		}

		return isBOT(root->left, lowerBound, root->data, leftToken) &&
			isBOT(root->right, root->data, upperBound, rightToken);
	}

	void prettyPrint(Node<T>* root, unsigned spaces) const{		
		if(root == nullptr){
			return;
		}

		prettyPrint(root->right, spaces + 1);
		printSpaces(spaces);
		std::cout<<root->data<<std::endl;
		prettyPrint(root->left, spaces + 1);
	}

	T findByIndex(unsigned& index, Node<T>* root){
		if(root == nullptr){
			return T();
		}

		if(index == 0){
			return root->data;
		}
		T result = T();
		index -= 1;
		result = findByIndex(index, root->left);

		if(result == T()){
			result = findByIndex(index, root->right);
		}
		return result;
		
	}

	void serealize(std::ostream& out, Node<T>* root) const{
		if(root == nullptr){
			out<<"()";
			return;
		}

		out<<"("<<root->data<<" ";

		serealize(out, root->left);
		out<<" ";
		serealize(out, root->right);
		out<<" )";
	}

	/*fillStack(std::stack& st, std::string stringToParse, unsigned first, unsigned last){
		int openBracket = -1;

		for(int i = 0; i < stringToParse.size(); i++){
			if(stringToParse[i] == '('){
				openBracket = i;
			}
			if(stringToParse[i] == ')'){
				fillStack(st, stringToParse, openBracket + 1, i - 1);	
			}
		}

		if(openBracket == -1)
	}*/

public:
	BTree():root(nullptr){

	}


	class Iterator{
	private:
	public:
		void operator ++();
		const T& operator *();

	};

/*	BTree(const T& rootData, const BTree<T>& leftSubTree, const BTree<T>& RightSubTree):root(nullptr){
		root = new Node<T>(rootData, leftSubTree.root, RightSubTree);
	}*/

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

	std::vector<T> listLeaves() const{
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

	std::string findTrace(const T& x) const{
		return findTrace(x, root);
	}

	std::vector<std::unordered_set<T>> checkForEqualLevels() const{
		std::vector<std::unordered_set<T>> result;
		checkForEqualLevels(root, 0, result);
		return result;
	}

	bool isBOT() const{
		if(root == nullptr){
			return 0;
		}

		if(root->left == nullptr && root->right == nullptr){
			return 1;
		}

		if(root->left == nullptr){
			return isBOT(root->right, root->data, T(), 1);
		}

		if(root->right == nullptr){
			return isBOT(root->left, T(), root->data, -1);
		}

		return isBOT(root->right, root->data, T(), 1) && isBOT(root->left, T(), root->data, -1);
	}


	void prettyPrint() const{
		return prettyPrint(root, 0);
	}


	T operator[] (unsigned index){
		if(index > count()){
			assert(false);
		}
		return findByIndex(index, root);
	}

	/*void parseExpression(const std::string& s) const{
		std::stack<char> st;
		fillStack(st, s);
	}*/

	void serealize(std::ostream& out) const{
		serealize(out, root);
	}

	Node<T>* findMostLeft(Node<T>* root) const{
		if(root == nullptr){
			return nullptr;
		}
		if(root->left == nullptr){
			return new Node<T>(root->data);
		}

		return findMostLeft(root->left);
	}

	Node<T>* copyTree(Node<T>* root) const{
		if(root == nullptr){
			return nullptr;
		}

		return new Node<T>(root->data, 
					copyTree(root->left), 
					copyTree(root->right));
	}

	void deleteNode(Node<T>* root, const T& x){
		if(root == nullptr){
			return;
		}

		if(root->data == x && root->left == nullptr && root->right == nullptr){
			delete root;
			root == nullptr;
		}

		if(root->data == x && root->left == nullptr){
			Node<T>* tempChild = root->right;
			delete root;
			root = tempChild;
		}

		if(root->data == x && root->right == nullptr){
			Node<T>* tempChild = root->left;
			delete root;
			root = tempChild;
		}

		if(root->data == x){
			Node<T>* tempRightChild = root->right;
			Node<T>* tempLeftChild = root->left;
			delete root;
			root = tempChild;
		}
	}

	BTree<T> deletedBOT (const T& x, Node<T>* root) const{
		Node<T>* newRoot = copyTree(root);
		deleteNode(newRoot, x);
		return BTree(root, deletedBOT(x, root->left), deletedBOT(x, root->right));
	}
};