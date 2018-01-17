#include <map>
#include "boost/dynamic_bitset.hpp"
using namespace boost;
using Pair = std::pair<char,unsigned>;
using std::map;
using std::string;

struct Node{
public:
	std::pair<char, unsigned> data;
	Node *left, *right;
	Node(std::pair<char, unsigned> _data):data(_data), left(nullptr), 
														right(nullptr){

	}

	Node(std::pair<char, unsigned> _data, Node *_left, Node *_right):
							data(_data), left(_left), right(_right){

	}

	int getId (){
	  return id;
	}
private:
	static int maxid;
	int id;
};

class Tree
{
private:
	Node* root;

	Node* copy(Node *subRoot){
		if(subRoot == nullptr){
			return nullptr;
		}
		return new Node(subRoot->data, copy(subRoot->left), copy(subRoot->right));
	}

	void table(map<char, string> &result, Node* root, string code){
		if(root->data.first != char()){
			result[root->data.first] = code;
			code.clear();
			return;
		}

		table(result, root->left, code + '0');
		table(result, root->right, code + '1');
		return;
	}

	void printSpaces(unsigned spaces) {
		for(int i = 0; i < spaces; i++){
			std::cout<<"     ";
		}
	}

	unsigned count(Node *root){
		if(root == nullptr){
			return 0;
		}
		return 1 + count(root->left) + count(root->right);
	}

	void print(Node *root, unsigned spaces){
		if(root == nullptr){
			return;
		}

		print(root->right, spaces + 1);
		printSpaces(spaces);
		std::cout<<root->data.first<<" "<<root->data.second<<std::endl;
		print(root->left, spaces + 1);

	}


	/*взето е от примерния код от лекции*/
	void printNodesDotty (std::ostream& out, Node *root)
	{
	  if (root == nullptr)
	  {
	    return;
	  }

	  out << root->getId()
	      << "[label=\""
	      << root->data.second
	      << "\"];"
	      << std::endl;

	  if (root->left != nullptr)
	  {
	    out << root->getId()
	        << "->"
	        << root->left->getId()
	        << "[color = \"red\"]"
	        << ";"
	        << std::endl;
	  }

	  if (root->right != nullptr)
	  {
	    out << root->getId()
	        << "->"
	        << root->right->getId()
	        << ";"
	        << std::endl;
	  }
	  printNodesDotty (out, root->left);
	  printNodesDotty (out, root->right);
	}

	void fillGaps (const Pair &x, Node *&crr, unsigned int h)
	{
	  if (h == 0)
	  {
	    return;
	  }

	  if (crr == nullptr)
	  {
	    crr = new Node (x,nullptr,nullptr);
	  }

	  fillGaps (x,crr->left,h-1);
	  fillGaps (x,crr->right,h-1);
	}




	void getString(dynamic_bitset<> bitset, Node* subRoot, unsigned index, string& result){
		if(index == bitset.size() + 1){
			return;
		}
		if(subRoot->data.first != char()){
			result += subRoot->data.first;
			getString(bitset, root, index, result);
			return;
		}
		if(bitset[index] == true){
			getString(bitset, subRoot->right, index + 1, result);
			return;
		}

		getString(bitset, subRoot->left, index + 1, result);
		return;
	}

public:
	Tree():root(nullptr){

	}

	Tree(std::pair<char, unsigned> data){
		root = new Node(data);
	}

	Tree(std::pair<char, unsigned> data, const Tree& leftTree,
											const Tree& rightTree){
		root = new Node(data, copy(leftTree.root), copy(rightTree.root));
	}

	Pair rootData() const{
		return root->data;
	}

	unsigned count(){
		return count(root);
	}

	void print(){
		print(root, 0);
	}

	map<char, string> table(){
		map<char, string> result;
		table(result, root, "");
		return result;
	}

	void printDotty(std::ostream& out){
		printNodesDotty(out, root);
	}

	void fillGaps (const Pair& x, unsigned int h)
	{
	  fillGaps (x,root,h);
	}


	string getString(dynamic_bitset<> bitset){
		string result;
		getString(bitset, root, 0, result);
		return result;
	}
};