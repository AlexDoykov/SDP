#include <map>
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



/*
	string trace(char x, Node* root){
		if(root == nullptr){
			return "";
		}

		if(root->data.first == x){
			return 
		}

		return 
	}*/

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


/*	string trace(char x){
		return trace(x, root);
	}*/

	/*vector<char> binarySequence(){

	}*/
};